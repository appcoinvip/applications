#include "logining.h"
#include "ui_logining.h"
Logining::Logining(UserData::User Usr,QWidget *parent) :
    QDialog(parent),Usr(Usr),
    ui(new Ui::Logining)
{
    ui->setupUi(this);
    form_init();
    socket_init();
}
void Logining::socket_init()
{
    ui->login_button->setText("取消");
    tcpClient=new QTcpSocket(this);
    socket_link();
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(ReadData()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));
}
void Logining::on_login_button_clicked()
{
    if(ui->login_button->text() == "取消")
    {
        tcpClient->disconnectFromHost();
        tcpClient->waitForDisconnected(1000);
        if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))
        {
            ui->login_button->setText("登录");
        }
        tcpClient->abort();
        QDialog::reject();
    }else{
        socket_link();
    }
}

void Logining::ReadData()
{
    QByteArray buffer=tcpClient->readAll();
    QString s=QVariant(buffer).toString();

    if(buffer == "false" || s=="0" )
    {
        ui->CurrentStatus_label->setText("帐号错误!");
        QDialog::reject();
    }
    else
    {
        ui->CurrentStatus_label->setText("正在登录...");
        usrInfoStr = s.split("&")[1];
        QDialog::accept();
    }
}

void Logining::ReadError(QAbstractSocket::SocketError)
{
    ui->login_button->setText("登录");
    ui->CurrentStatus_label->setText("连接服务器失败");
}

void Logining::form_init()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    progressBar_init();
    timer = new QTimer();
    timer->setInterval(10);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(ProgressValue()));
}

void Logining::ProgressValue()
{
    ++Progress_value %=100;
    ui->progressBar->setValue(Progress_value);
}

Logining::~Logining()
{
    tcpClient->abort();
    tcpClient->disconnectFromHost();
    delete tcpClient;
    delete ui;
}

void Logining::progressBar_init()
{
    Progress_value = 0;
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(Progress_value);

}
void Logining::on_Close_pushButton_clicked()
{
    QDialog::reject();
}

void Logining::mousePressEvent(QMouseEvent *event)

{
    if(event->button()==Qt::LeftButton)
    {
        dragPosition=event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
    if(event->button()==Qt::RightButton)
    {
    }
}

void Logining::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口
        event->accept();
    }
}

void Logining::socket_link(){
    tcpClient->abort();//取消原有连接

    QString ip=SERV_IP;
    int port=SERV_PORT;
    tcpClient->connectToHost(ip,port);
    if (tcpClient->waitForConnected(1000))
    {
        ui->CurrentStatus_label->setText("正在登录...");
//        QByteArray pwd = QCryptographicHash::hash(Usr.Password.toLatin1(),QCryptographicHash::Md5);
        QString msg =("#Login#"+Usr.UserID+"#"+Usr.Client_Status);
        tcpClient->write(msg.toUtf8());
    }
}
