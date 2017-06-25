#include "userdefineddlg.h"
#include "ui_userdefineddlg.h"

//UserDefinedDlg* UserDefinedDlg::uDlg = NULL;
UserDefinedDlg::UserDefinedDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDefinedDlg)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(USERDEFINED_EXCHANGE));
    ui->label->setMaximumWidth(260);
    setWindowTitle(USERDEFINED_EXCHANGE_TITLE);
    widg = new BrowserForm(this);
    ui->verticalLayout_2->addWidget(widg);
    Init();
}
UserDefinedDlg::UserDefinedDlg(ShadowBridge *bridge, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDefinedDlg)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(USERDEFINED_REWARD));
    ui->label->setMaximumWidth(350);
    setWindowTitle(USERDEFINED_REWARD_TITLE);
    widg = new BrowserForm(bridge,this);
    ui->verticalLayout_2->addWidget(widg);
    Init();
}
UserDefinedDlg::UserDefinedDlg(QString username,QString usrInfoStr,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDefinedDlg)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(USERDEFINED_CHAT));
    ui->label->setMaximumWidth(350);
    setWindowTitle(USERDEFINED_CHAT_TITLE);
    widg = new Widget(username,usrInfoStr);
    ui->verticalLayout_2->addWidget(widg);
    Init();
}
UserDefinedDlg::~UserDefinedDlg()
{
    delete ui;
    delete widg;
}
void UserDefinedDlg::Init(){
    m_Drag=false;
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
    showMaximized();
    ui->maxBtn->setIcon(QIcon(MAXBTN));

}

void UserDefinedDlg::mouseReleaseEvent(QMouseEvent * evt){
    m_Drag = false;
    QDialog::mouseReleaseEvent(evt);
}
void UserDefinedDlg::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_Drag = true;
        m_DragPosition = event->globalPos() - this->pos();
        event->accept();
    }
}
void UserDefinedDlg::mouseMoveEvent(QMouseEvent * event){
    if (m_Drag && (event->buttons() && Qt::LeftButton)) {
        move(event->globalPos() - m_DragPosition);
        event->accept();
    }
}


void UserDefinedDlg::on_minBtn_clicked()
{
    showMinimized();
}

void UserDefinedDlg::on_maxBtn_clicked()
{
    Qt::WindowStates state = windowState() ;
    if(state == Qt::WindowMaximized){
        ui->maxBtn->setIcon(QIcon(FIXBTN));
        showNormal();
    }else if(state == Qt::WindowNoState){
        ui->maxBtn->setIcon(QIcon(MAXBTN));
        showMaximized();
    }
}

void UserDefinedDlg::on_quitBtn_clicked()
{
    widg->close();
    QDialog::reject();
}
