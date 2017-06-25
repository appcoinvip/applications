#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QString userName, QString frendLst,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    uName = userName;//用户本人
    Init();
    timeNum=0;
    setUsrLst(frendLst);//加载朋友列表
    UserData::Client cli;
    cli.ClientID=userName;
    cli.Status ="Online";
    cli.online = 1;
    sndMsg("UsrEnter",cli);
    timer = new QTimer();
    timer->setInterval(10000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateInfo()));
}

Widget::~Widget()
{
    myClose();
    delete ui;
    delete timer;
    delete model;
    this->disconnect();
    delete udpSocket;
    delete srv;
}
void Widget::Init()
{
    sIp=SERV_IP;
    sPort=SERV_PORT;
    model=new QStandardItemModel(this);
    ui->tableView->setModel(model);
    setTableHeaderData();
    //初始化UDPSocket和自己绑定自己的IP地址和端口号
    udpSocket = new QUdpSocket(this);
    //槽链接，监听数据读入
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    srv = new Server(this);
    connect(srv, SIGNAL(sndFileName(QString)), this, SLOT(getFileName(QString)));
    connect(ui->msgTxtEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)),this, SLOT(curFmtChanged(const QTextCharFormat)));
}

void Widget::sndMsg(QString type,UserData::Client cli)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << type ;
    if(type == "Msg")
    {
        if (ui->msgTxtEdit->toPlainText() == "") {
            QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
            return;
        }
        out << cli.ClientID<< getMsg();
        ui->msgBrowser->verticalScrollBar()->setValue(ui->msgBrowser->verticalScrollBar()->maximum());
        udpSocket->writeDatagram(data,data.length(),QHostAddress(sIp), sPort);
    }else if(type == "UsrUpdt"){
        out << cli.ClientID<< cli.Status << cli.online;
        udpSocket->writeDatagram(data,data.length(),QHostAddress(sIp), sPort);
    }else if(type == "UsrEnter"){
        out << cli.ClientID  << cli.Status << cli.online;
        udpSocket->writeDatagram(data,data.length(),QHostAddress(sIp), sPort);
    }else if(type == "UsrLeft"){
        out << cli.ClientID;
        udpSocket->writeDatagram(data,data.length(),QHostAddress(sIp), sPort);
    }else if(type == "MsgPage"){
        out <<uName << cli.CMsg;
        udpSocket->writeDatagram(data,data.length(),QHostAddress(sIp), sPort);
    }else if(type == "FileName"){
        int row = ui->tableView->currentIndex().row();
        QString clntaddr = model->item(row, 1)->text();
        QString clntport = model->item(row, 2)->text();
        out <<uName << uIp << uPort <<fileName;
        udpSocket->writeDatagram(data,data.length(),QHostAddress(clntaddr), clntport.toInt());
    }else if(type == "Refuse"){
        out << cli.ClientID ;
        udpSocket->writeDatagram(data,data.length(),QHostAddress(cli.IP), cli.Port);
    }else if(type == "CliUpdt"){
        out << cli.ClientID ;
        udpSocket->writeDatagram(data,data.length(),QHostAddress(sIp), sPort);
    }
}

void Widget::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress IP;
        quint16 Port;
        udpSocket->readDatagram(datagram.data(), datagram.size(),&IP,&Port);
        QDataStream in(&datagram, QIODevice::ReadOnly);
        QString msgType;
        in >> msgType;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        UserData::Client cli;
        if(msgType == "Msg"){
            QString usrName,msg;
            in >> usrName >> msg;
            ui->msgBrowser->setTextColor(Qt::blue);
            ui->msgBrowser->setCurrentFont(QFont("Times New Roman",12));
            ui->msgBrowser->append("[ " +usrName+" ] "+ time);
            ui->msgBrowser->append(msg);
        }else if(msgType == "UsrUpdt"){
            in >> cli.ClientID >> cli.Status >> cli.online;
            cli.online=1;
            sndMsg("UsrUpdt",cli);
        }else if(msgType == "UsrLeft"){
            QString userName;
            in >> userName;
            UsrLeft(userName,time);
        }else if(msgType == "UsrEnter"){
            in >> cli.ClientID >> cli.IP >> cli.Port >> cli.Status >> cli.online;
            UserEnter(cli);
        }else if(msgType == "MsgPage"){
            QString usrName,msg;
            in >> usrName >> msg;
            ui->msgBrowser->setTextColor(Qt::green);
            ui->msgBrowser->setCurrentFont(QFont("宋体",12));
            ui->msgBrowser->append(msg);
        }else if(msgType == "FileName") {
            QString usrName,askAddr, fileName;
            int askPort;
            in >> usrName >> askAddr;
            in >> askPort >> fileName;
            hasPendingFile(usrName, askAddr, askPort, fileName);
        }else if(msgType == "Refuse"){
            QString usrName;
            in >> usrName ;
            if(uName == usrName)
            {
                srv->refused();
            }
        }else if(msgType == "CliUpdt"){
            QString username,status;
            in >>username>>status ;
            if(username==uName&&status == "OnLine")
                timeNum=0;
        }
    }
}
void Widget::UserEnter(UserData::Client userinfo){
    if(userMap.contains(userinfo.ClientID)){
        if(userinfo.ClientID==uName){
            timeNum=0;
        }
        return ;
    }
    QList<QStandardItem *> items;
    QStandardItem* qs= new QStandardItem(QIcon(USR_ICON), userinfo.ClientID);
    QStandardItem* qs1= new QStandardItem(userinfo.IP);
    QStandardItem* qs2= new QStandardItem(QString::number(userinfo.Port));
    QStandardItem* qs3= new QStandardItem(userinfo.Status);
    items<<qs<<qs1<<qs2<<qs3;
    userMap.insert(userinfo.ClientID,userinfo.Status);
    if(userinfo.ClientID==uName){
        uIp=userinfo.IP;
        uPort=userinfo.Port;
        model->insertRow(0,items);
    }else{
        model->appendRow(items);
    }
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->msgBrowser->append(tr("%1 Online！").arg(userinfo.ClientID));
    ui->userLstHeader->setText(tr("Online Users %1").arg(model->rowCount()));
}

void Widget::UsrLeft(QString usrname, QString time)
{
    int rowNum = model->findItems(usrname, Qt::MatchExactly).first()->row();
    userMap.remove(usrname);
    model->removeRow(rowNum);
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
    ui->msgBrowser->append(tr("%1 于 %2 离开！").arg(usrname).arg(time));
    ui->userLstHeader->setText(tr("Online Users %1").arg(model->rowCount()));
}

void Widget::setUsrLst(QString userStr){
    ui->msgBrowser->clear();
    model->removeRows(0,model->rowCount());
    QStringList clientLst = userStr.split("|");
    int len=clientLst.length();
    for(int i=0;i<len;i++){
        QString client_str=clientLst[i];
        QStringList userInfo_lst = client_str.split("@");
        int len_1=userInfo_lst.length();
        if(len_1<4||userInfo_lst.isEmpty())
            return;
        QString user=userInfo_lst[0];
        if(userMap.contains(user)){
            return;
        }
        QString ip=userInfo_lst[1];
        QString port=userInfo_lst[2];
        QString status=userInfo_lst[3];
        userMap[user]=status;

        QList<QStandardItem *> items;
        QStandardItem* qs = new QStandardItem(QIcon(USR_ICON),user);
        QStandardItem* qs_1 = new QStandardItem(ip);
        QStandardItem* qs_2 = new QStandardItem(port);
        QStandardItem* qs_3 = new QStandardItem(status);
        items<<qs<<qs_1<<qs_2<<qs_3;
        model->appendRow(items);
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman",10));
        ui->msgBrowser->append(tr("%1 Online！").arg(user));
        ui->userLstHeader->setText(tr("Online Users %1").arg(model->rowCount()));
    }
}

QString Widget::getMsg()
{
    QString msg = ui->msgTxtEdit->toHtml();
    ui->msgTxtEdit->clear();
    ui->msgTxtEdit->setFocus();
    return msg;
}
void Widget::on_sendBtn_clicked()
{
    UserData::Client cli;
    cli.ClientID = uName;
    sndMsg("Msg" ,cli);
}

void Widget::getFileName(QString name)
{
    fileName = name;
    sndMsg("FileName");
}
//void Widget::on_sendTBtn_clicked()
//{
//    QItemSelectionModel *_model=ui->tableView->selectionModel();
//    if(!_model->hasSelection()){
//        QMessageBox::warning(this, tr("选择用户"),tr("请先选择目标用户！"),
//                             tr("确定"));
//        return ;
//    }
//    srv->initSrv(uIp, uPort);
//    srv->show();
//}

void Widget::hasPendingFile(QString askUser, QString askAddr,qint16 askPort, QString filename)
{
    int btn = QMessageBox::information(this,tr("接受文件"),tr("来自%1(%2)的文件：%3,是否接收？").arg(askUser).arg(askAddr).arg(filename),QMessageBox::Yes,QMessageBox::No);
    if (btn == QMessageBox::Yes) {
        QString name = QFileDialog::getSaveFileName(0,tr("保存文件"),filename);
        if(!name.isEmpty())
        {
            Client *clnt = new Client(this);
            clnt->setFileName(name);
            clnt->setHostAddr(QHostAddress(askAddr),askPort);
            clnt->show();
        }
    } else {
        UserData::Client cli;
        cli.ClientID = askUser;
        cli.IP=askAddr;
        cli.Port=askPort;
        sndMsg("Refuse", cli);
    }
}

void Widget::on_fontCbx_currentFontChanged(const QFont &f)
{
    ui->msgTxtEdit->setCurrentFont(f);
    ui->msgTxtEdit->setFocus();
}

void Widget::on_sizeCbx_currentIndexChanged(const QString &arg1)
{
    ui->msgTxtEdit->setFontPointSize(arg1.toDouble());
    ui->msgTxtEdit->setFocus();
}

void Widget::on_boldTBtn_clicked(bool checked)
{
    if(checked)
        ui->msgTxtEdit->setFontWeight(QFont::Bold);
    else
        ui->msgTxtEdit->setFontWeight(QFont::Normal);
    ui->msgTxtEdit->setFocus();
}

void Widget::on_italicTBtn_clicked(bool checked)
{
    ui->msgTxtEdit->setFontItalic(checked);
    ui->msgTxtEdit->setFocus();
}

void Widget::on_underlineTBtn_clicked(bool checked)
{
    ui->msgTxtEdit->setFontUnderline(checked);
    ui->msgTxtEdit->setFocus();
}

void Widget::on_colorTBtn_clicked()
{
    color = QColorDialog::getColor(color,this);
    if(color.isValid()){
        ui->msgTxtEdit->setTextColor(color);
        ui->msgTxtEdit->setFocus();
    }
}

void Widget::curFmtChanged(const QTextCharFormat &fmt)
{
    ui->fontCbx->setCurrentFont(fmt.font());

    if (fmt.fontPointSize() < 8) {
        ui->sizeCbx->setCurrentIndex(4);
    } else {
        ui->sizeCbx->setCurrentIndex(ui->sizeCbx->findText(QString::number(fmt.fontPointSize())));
    }
    ui->boldTBtn->setChecked(fmt.font().bold());
    ui->italicTBtn->setChecked(fmt.font().italic());
    ui->underlineTBtn->setChecked(fmt.font().underline());
    color = fmt.foreground().color();
}

void Widget::on_saveTBtn_clicked()
{
    if (ui->msgBrowser->document()->isEmpty()) {
        QMessageBox::warning(0, tr("警告"), tr("聊天记录为空，无法保存！"), QMessageBox::Ok);
    } else {
        QString fname = QFileDialog::getSaveFileName(this,tr("保存聊天记录"), tr("聊天记录"), tr("文本(*.txt);;所有文件(*.*)"));
        if(!fname.isEmpty())
            saveFile(fname);
    }
}

bool Widget::saveFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("保存文件"),tr("无法保存文件 %1:\n %2").arg(filename).arg(file.errorString()));
        return false;
    }
    QString msg=ui->msgBrowser->toPlainText();
    QTextStream out(&file);
    out << msg;

    return true;
}

void Widget::on_clearTBtn_clicked()
{
    ui->msgBrowser->clear();
}

void Widget::closeEvent(QCloseEvent *e)
{
    myClose();
    QWidget::closeEvent(e);
}
void Widget::setTableHeaderData(){
    userMap.clear();
    model->removeRows(0,model->rowCount());
    setTableHeader("Online Users","ClientID",0);
    setTableHeader("用户IP","IP",1);
    setTableHeader("用户端口","Port",2);
    setTableHeader("用户状态","Status",3);
    ui->tableView->setColumnHidden(1,true);
    ui->tableView->setColumnHidden(2,true);
    ui->tableView->setColumnHidden(3,true);
}
void Widget::setTableHeader(QString col_title,QString col_name,int i){
    QStandardItem* qs= new QStandardItem(QIcon(USRLst_ICON),col_title);
    qs->setData(QVariant(col_name));
    qs->setTextAlignment(Qt::AlignHCenter);
    model->setHorizontalHeaderItem(i,  qs);
}

void Widget::on_pushButton_clicked()
{
    UserData::Client cli;
    cli.CMsg =ui->pageNum->text();
    sndMsg("MsgPage",cli);
}
void Widget::UpdateInfo(){ //遍历用户列表
    //询问客户端是否在线
    if(timeNum>2){
        timer->stop();
        int ret = QMessageBox::information(this, tr("提示"),
                                           tr("客户端已经掉线,\n请重新登录。"),
                                           tr("确定"),tr("取消"));
        if (ret==1) {
            timer->start();
            return;
        }
        close();
    }
    timeNum++;
    UserData::Client clie;
    clie.ClientID=uName;
    sndMsg("CliUpdt",clie);
}
void Widget::myClose(){
    timer->stop();
    UserData::Client cli;
    cli.ClientID = uName;
    sndMsg("UsrLeft",cli);
    udpSocket->close();
}
