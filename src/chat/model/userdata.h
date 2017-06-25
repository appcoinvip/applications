#ifndef USERDATA_H
#define USERDATA_H
#include <QString>
#include <QVector>
#include <QPixmap>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QNetworkInterface>
class UserData
{
public:
    UserData();
    typedef struct User_{
        QString UserID;
        QString Password;
        QString Client_Status;
        bool AutoLogin;
        bool RememberPwd;
    }User;
    typedef struct Client_{
        QString ClientID;
        QString Status;
        QString IP;
        quint16 Port;
        QString CMsg;
        int online;
    }Client;
};

#endif // USERDATA_H
