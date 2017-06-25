#include "suspendform.h"
#include "ui_suspendform.h"

SuspendForm::SuspendForm(QMap<QString ,QVariant>* coins,QWidget *parent) :
    QWidget(parent),coins(coins),
    ui(new Ui::SuspendForm)
{
    ui->setupUi(this);
}

SuspendForm::~SuspendForm()
{
    delete ui;
}

void SuspendForm::on_toolButton_clicked()
{
    int reward= ui->lineEdit->text().toInt();
    coins->insert("amount",reward);
    emit susAccept();
}
void SuspendForm::on_toolButton_2_clicked()
{
    coins->insert("amount",20);
    emit susAccept();
}
void SuspendForm::on_toolButton_3_clicked()
{
    coins->insert("amount",50);
    emit susAccept();
}

void SuspendForm::on_toolButton_4_clicked()
{
    coins->insert("amount",100);
    emit susAccept();
}

void SuspendForm::on_toolButton_5_clicked()
{
    coins->insert("amount",200);
    emit susAccept();
}
