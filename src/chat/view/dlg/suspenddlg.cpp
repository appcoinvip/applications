#include "suspenddlg.h"
#include "ui_suspenddlg.h"

SuspendDlg::SuspendDlg(QMap<QString ,QVariant>* coins,QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::SuspendDlg)
{
    ui->setupUi(this);
    aform = new SuspendForm(coins,this);
    connect(aform,SIGNAL(susAccept()), this, SLOT(accept()));
    ui->verticalLayout_2->addWidget(aform);

    init();
    setWindowFlags(windowFlags()|Qt::WindowStaysOnTopHint);
}
SuspendDlg::SuspendDlg(ShadowBridge *bridge,QWidget *parent):
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::SuspendDlg)
{
    ui->setupUi(this);
    aform = new AwardForm(bridge,this);
    ui->verticalLayout_2->addWidget(aform);
    init();

}
void SuspendDlg::init(){
      m_Drag=false;
}

SuspendDlg::~SuspendDlg()
{
    delete ui;
    delete aform;
}
void SuspendDlg::on_minBtn_clicked()
{
    showMinimized();
}
void SuspendDlg::mouseReleaseEvent(QMouseEvent * evt){
    m_Drag = false;
    QDialog::mousePressEvent(evt);
}
void SuspendDlg::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_Drag = true;
        m_DragPosition = event->globalPos() - this->pos();
        event->accept();
    }
}
void SuspendDlg::mouseMoveEvent(QMouseEvent * event){
    if (m_Drag && (event->buttons() && Qt::LeftButton)) {
        move(event->globalPos() - m_DragPosition);
        event->accept();
    }
}

void SuspendDlg::on_quitBtn_clicked()
{
    aform->close();
    QDialog::reject();
}
