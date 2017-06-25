#ifndef LOGINING_H
#define LOGINING_H

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QDialog>
#include <QTcpSocket>
#include <chat/view/module/widget.h>
#include <chat/control/define_1.h>
#include <QCryptographicHash>
#include <chat/model/userdata.h>
#include <chat/view/module/widget.h>
namespace Ui {
class Logining;
}

class Logining : public QDialog
{
    Q_OBJECT

public:
    explicit Logining(UserData::User Usr,QWidget *parent = 0);
    ~Logining();
    QTcpSocket *tcpClient;
    QString usrInfoStr;

protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    void progressBar_init();
    void form_init();
    void socket_init();
private slots:
    void on_Close_pushButton_clicked();
    void ProgressValue();
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);
    void on_login_button_clicked();

private:
    UserData::User Usr;
    Ui::Logining *ui;
    Widget * cWdget;
    QTimer *timer;
    QPoint dragPosition;
    int Progress_value;
    void socket_link();
};

#endif // LOGINING_H
