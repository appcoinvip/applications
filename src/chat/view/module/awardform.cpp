#include "awardform.h"
#include "ui_awardform.h"

AwardForm::AwardForm(ShadowBridge *bridge,QWidget *parent) :
    QWidget(parent),bridge(bridge),
    ui(new Ui::AwardForm)
{
    ui->setupUi(this);
    clipboard = QApplication::clipboard();
    connect(clipboard, SIGNAL(changed(QClipboard::Mode)),this,SLOT(mySelectionChanged(QClipboard::Mode)));
}

AwardForm::~AwardForm()
{
    delete ui;
}

bool AwardForm::sendCoins(QMap<QString ,QVariant>* coins){
    bridge->clearRecipients();
    if(bridge->validateAddress(coins->value("payTo").toString())){
        QVariant amount= bridge->unitParse(coins->value("amount"),0);//单位换算
        //        qDebug()<<"amount:"<<amount;
        bridge->addRecipient(coins->value("payTo").toString(), coins->value("lab").toString(),
                             coins->value("narration").toString(),amount.toDouble(),
                             coins->value("txnType").toInt(),coins->value("ringSize").toInt());
        bridge->sendCoins(false,"",true);
        return true;
    }else{
        return false;
    }
}
void AwardForm::mySelectionChanged(QClipboard::Mode mode){
    if(QClipboard::Clipboard==mode){
        const QMimeData *mimeData = clipboard->mimeData();
        if(mimeData->hasText()) {
            payTo=mimeData->text();
            if(bridge->validateAddress(payTo)){
                QMap<QString ,QVariant> coins;
                SuspendDlg sus(&coins);
                sus.showNormal();
                if( sus.exec()==QDialog::Accepted){
                    coins["payTo"]=payTo;
                    coins["lab"]="打赏";
                    coins["narration"]="默认";
                    coins["txnType"]=0;
                    coins["ringSize"]=16;
                    sendCoins(&coins);
                }
            }
        }
    }
}

void AwardForm::on_toolButton_2_clicked()
{
    QDir dir;
    QString currentPath = dir.currentPath()+LINK_11;
    QDesktopServices::openUrl(QUrl(currentPath));
}

void AwardForm::on_toolButton_clicked()
{
    QDir dir;
    QString currentPath = dir.currentPath()+LINK_12;
    QDesktopServices::openUrl(QUrl(currentPath));

}
