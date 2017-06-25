#ifndef BROWSERFORM_H
#define BROWSERFORM_H
#include <QDir>
#include <QTimer>
#include <QSettings>
#include <QToolBar>
#include <QUrl>
#include <QLineEdit>
#include <QFile>
#include <QNetworkProxyFactory>
#include <QWebView>
#include <QWebFrame>
#include <QMouseEvent>
#include <chat/control/define_1.h>
#include <QStandardPaths>
#include <QNetworkDiskCache>
#include <QDesktopServices>
#include <QMimeData>
#include <QClipboard>
#include "shadowbridge.h"
#include <chat/view/dlg/suspenddlg.h>
#include <chat/control/cookiejar.h>
#include <QAbstractTextDocumentLayout>
#include <chat/control/networkaccessmanager.h>
#include <QToolButton>
#include <chat/view/module/webview.h>


namespace Ui {
class BrowserForm;
}

class BrowserForm : public QWidget
{
    Q_OBJECT

public:
    explicit BrowserForm(ShadowBridge *bridge,QWidget *parent = 0);
    explicit BrowserForm(QWidget *parent = 0);
    ~BrowserForm();
    void loadSettings();
    bool sendCoins(QMap<QString ,QVariant>* coins);

protected slots:
    void mySelectionChanged(QClipboard::Mode mode);
    void linkClicked_1(QUrl url);

    void adjustLocation();
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool b);

    void changeLocation();

private slots:
    void postLaunch();

    void onBtnClicked_1();

    void onBtnClicked_2();

    void onBtnClicked_3();

    void onBtnClicked_4();
    void onBtnClicked_5();
    void onBtnClicked_6();

    void onBtnClicked_7();
    void onBtnClicked_8();
    void onBtnClicked_9();
    void onBtnClicked_10();

    void onBtnClicked_11();
protected:
    NetworkAccessManager *mManager;
private:
    ShadowBridge *bridge;
    Ui::BrowserForm *ui;
    QString jQuery;
    WebView *view;

    QString payTo;
    QToolBar *toolBar;
    int progress;

    QLineEdit *locationEdit;

    QToolButton *btn_1;
    QToolButton *btn_2;
    QToolButton *btn_3;
    QToolButton *btn_4;
    QToolButton *btn_5;
    QToolButton *btn_6;
    QToolButton *btn_11;

    QClipboard *clipboard;
private:
    void Init();
};

#endif // BROWSERFORM_H
