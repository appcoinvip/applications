#ifndef SUSPENDFORM_H
#define SUSPENDFORM_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
namespace Ui {
class SuspendForm;
}

class SuspendForm : public QWidget
{
    Q_OBJECT

public:
    explicit SuspendForm(QMap<QString ,QVariant>* coins,QWidget *parent = 0);
    ~SuspendForm();
signals:
    void susAccept();
private slots:

    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_2_clicked();

private:
    QMap<QString ,QVariant>* coins;
    Ui::SuspendForm *ui;


};

#endif // SUSPENDFORM_H
