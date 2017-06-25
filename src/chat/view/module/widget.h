#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextCharFormat>
#include <chat/model/userdata.h>
#include <chat/control/define_1.h>
#include <QStandardItemModel>
#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include <chat/view/dlg/server.h>
#include <chat/view/dlg/client.h>
#include <QFileDialog>
#include <QTimer>
#include <QColorDialog>

class QUdpSocket;
class Server;
namespace Ui {
class Widget;
}
class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QString userName, QString frendLst,QWidget *parent=0);
    ~Widget();

    void sndMsg(QString type,UserData::Client clien=UserData::Client());
    void setUsrLst(QString userStr);
    void myClose();
protected:
    void UserEnter(UserData::Client userinfo);
    void UsrLeft(QString usrname,QString time);

    QString getMsg();

    void hasPendingFile(QString askUser, QString askAddr,qint16 askPort, QString filename);
    bool saveFile(const QString& filename);

    void closeEvent(QCloseEvent *);

private:
    Ui::Widget *ui;
    QTimer *timer;
    int timeNum;
    QMap<QString,QString> userMap;
    QStandardItemModel* model;

    void Init();
    void setTblData();
    void setTableHeaderData();
    void setTableHeader(QString col_title,QString col_name,int i);

    QUdpSocket *udpSocket;
    QString sIp;
    int sPort;
    QString uIp;
    qint16 uPort;
    QString uName;
    QString fileName;
    Server *srv;
    QColor color;
private slots:
    void processPendingDatagrams();
    void on_sendBtn_clicked();

    void getFileName(QString);
//    void on_sendTBtn_clicked();
    void on_fontCbx_currentFontChanged(const QFont &f);
    void on_sizeCbx_currentIndexChanged(const QString &arg1);
    void on_boldTBtn_clicked(bool checked);
    void on_italicTBtn_clicked(bool checked);
    void on_underlineTBtn_clicked(bool checked);
    void on_colorTBtn_clicked();

    void curFmtChanged(const QTextCharFormat &fmt);
    void on_saveTBtn_clicked();
    void on_clearTBtn_clicked();
    void on_pushButton_clicked();

    void UpdateInfo();//遍历用户列表
};

#endif // WIDGET_H
