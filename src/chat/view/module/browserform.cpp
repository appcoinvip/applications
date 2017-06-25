#include "browserform.h"
#include "ui_browserform.h"

BrowserForm::BrowserForm(ShadowBridge *bridge,QWidget *parent) :
    QWidget(parent),bridge(bridge),
    ui(new Ui::BrowserForm)
{
    Init();
    btn_1 =new QToolButton(this);
    btn_2 =new QToolButton(this);
    btn_3 =new QToolButton(this);
    btn_4 =new QToolButton(this);
    btn_5 =new QToolButton(this);
    btn_6 =new QToolButton(this);
    btn_11 =new QToolButton(this);

    btn_1->setIcon(QIcon(ICON_1));
    btn_1->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_1->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_2->setIcon(QIcon(ICON_2));
    btn_2->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_2->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_3->setIcon(QIcon(ICON_3));
    btn_3->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_3->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_4->setIcon(QIcon(ICON_4));
    btn_4->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_4->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_5->setIcon(QIcon(ICON_5));
    btn_5->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_5->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_6->setIcon(QIcon(ICON_6));
    btn_6->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_6->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));

    btn_11->setIcon(QIcon(ICON_11));
    btn_11->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_11->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));
    connect(btn_1, SIGNAL(clicked()) , this, SLOT(onBtnClicked_1()));
    connect(btn_2, SIGNAL(clicked()) , this, SLOT(onBtnClicked_2()));
    connect(btn_3, SIGNAL(clicked()) , this, SLOT(onBtnClicked_3()));
    connect(btn_4, SIGNAL(clicked()) , this, SLOT(onBtnClicked_4()));
    connect(btn_5, SIGNAL(clicked()) , this, SLOT(onBtnClicked_5()));
    connect(btn_6, SIGNAL(clicked()) , this, SLOT(onBtnClicked_6()));
    connect(btn_11, SIGNAL(clicked()) , this, SLOT(onBtnClicked_11()));

    ui->horizontalLayout->insertWidget(1,btn_1);
    ui->horizontalLayout->insertWidget(1,btn_2);
    ui->horizontalLayout->insertWidget(1,btn_3);
    ui->horizontalLayout->insertWidget(1,btn_4);
    ui->horizontalLayout->insertWidget(1,btn_5);
    ui->horizontalLayout->insertWidget(1,btn_6);

    ui->horizontalLayout->addWidget(btn_11);

    clipboard = QApplication::clipboard();
    connect(clipboard, SIGNAL(changed(QClipboard::Mode)),this,SLOT(mySelectionChanged(QClipboard::Mode)));
    onBtnClicked_1();
}

BrowserForm::BrowserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrowserForm)
{
    Init();
    btn_1 =new QToolButton(this);
    btn_2 =new QToolButton(this);
    btn_3 =new QToolButton(this);
    btn_4 =new QToolButton(this);
    btn_1->setIcon(QIcon(ICON_7));
    btn_1->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_1->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));

    btn_2->setIcon(QIcon(ICON_8));
    btn_2->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_2->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));

    btn_3->setIcon(QIcon(ICON_9));
    btn_3->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_3->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));

    btn_4->setIcon(QIcon(ICON_10));
    btn_4->setIconSize(QSize(ICON_WIDTH,ICON_HEIDGE));
    btn_4->setSizeIncrement(QSize(ICON_WIDTH,ICON_HEIDGE));
    connect(btn_1, SIGNAL(clicked()) , this, SLOT(onBtnClicked_7()));
    connect(btn_2, SIGNAL(clicked()) , this, SLOT(onBtnClicked_8()));
    connect(btn_3, SIGNAL(clicked()) , this, SLOT(onBtnClicked_9()));
    connect(btn_4, SIGNAL(clicked()) , this, SLOT(onBtnClicked_10()));

    ui->horizontalLayout->insertWidget(1,btn_1);
    ui->horizontalLayout->insertWidget(1,btn_2);
    ui->horizontalLayout->insertWidget(1,btn_3);
    ui->horizontalLayout->insertWidget(1,btn_4);
    onBtnClicked_7();
}
void BrowserForm::Init(){
    ui->setupUi(this);
    progress = 0;
    btn_5=0;
    btn_6=0;
    //    QFile file;
    //    file.setFileName(JQUERY);
    //    file.open(QIODevice::ReadOnly);
    //    jQuery = file.readAll();
    //    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    //    file.close();

    mManager = new NetworkAccessManager(this);
    mManager->setCookieJar(new CookieJar(this));
    view = new WebView(this);
    view->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    view->page()->setNetworkAccessManager(mManager);
//    view->page()->networkAccessManager()->setCookieJar(new CookieJar(this));
    toolBar = new QToolBar(this);
    toolBar->addSeparator();
    toolBar->addAction(view->pageAction(QWebPage::Back));
    toolBar->addAction(view->pageAction(QWebPage::Forward));
    //    toolBar->addAction(view->pageAction(QWebPage::Reload));
    toolBar->addAction(view->pageAction(QWebPage::Stop));
    toolBar->addSeparator();

    connect(view, SIGNAL(linkClicked(QUrl)), this, SLOT(linkClicked_1(QUrl)));
    connect(view, SIGNAL(urlChanged(QUrl)), SLOT(adjustLocation()));
    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

    locationEdit = new QLineEdit(this);
    locationEdit->setVisible(BROWASER_TEXTINPUT_VIS);
    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

    ui->horizontalLayout->insertWidget(0,toolBar);
    ui->horizontalLayout->insertWidget(1,locationEdit);
    ui->verticalLayout->insertWidget(0,view);
    QTimer::singleShot(0, this, SLOT(postLaunch()));

}

void BrowserForm::postLaunch()
{
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    if (directory.isEmpty())
        directory = QDir::homePath() + QLatin1String("/.") + QCoreApplication::applicationName();
    QWebSettings::setIconDatabasePath(directory);
    QWebSettings::setOfflineStoragePath(directory);
    loadSettings();
}

void BrowserForm::loadSettings()
{
    QWebSettings *defaultSettings = view->page()->settings();
    defaultSettings->setAttribute(QWebSettings::JavascriptEnabled,true);
    defaultSettings->setAttribute(QWebSettings::PluginsEnabled, true);
    defaultSettings->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
}

BrowserForm::~BrowserForm()
{
    delete ui;

    disconnect(this,0,0,0);
    delete btn_1;
    delete btn_2;
    delete btn_3;
    delete btn_4;
    if(btn_5){
        delete btn_5;
        delete btn_6;
    }
    delete view;
    delete mManager;
    delete toolBar;
    delete locationEdit;
}

void BrowserForm::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void BrowserForm::changeLocation()
{
    QUrl url = QUrl::fromUserInput(locationEdit->text());

    //    if(url().toString().contains("weibo")){
    //       QNetworkRequest request
    //       request.setHeader(QNetworkRequest::UserAgentHeader,QVariant("spider"));
    //    }
    view->load(url);
    view->setFocus();
}

void BrowserForm::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        ui->label->setText(view->title());
    else
        ui->label->setText(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void BrowserForm::setProgress(int p)
{
    progress = p;
    adjustTitle();
}
void BrowserForm::finishLoading(bool b)
{
    progress = 100;
    adjustTitle();
    //    view->page()->mainFrame()->evaluateJavaScript(jQuery);
}

void BrowserForm::linkClicked_1(QUrl url){
    view->load(url);
    view->setFocus();
}

void BrowserForm::onBtnClicked_1()
{
    locationEdit->setText(LINK_1);
    changeLocation();
}

void BrowserForm::onBtnClicked_2()
{
    locationEdit->setText(LINK_2);
    changeLocation();
}

void BrowserForm::onBtnClicked_3()
{
    locationEdit->setText(LINK_3);
    changeLocation();
}

void BrowserForm::onBtnClicked_4()
{
    locationEdit->setText(LINK_4);
    changeLocation();
}
void BrowserForm::onBtnClicked_5()
{
    locationEdit->setText(LINK_5);
    changeLocation();
}
void BrowserForm::onBtnClicked_6()
{
    locationEdit->setText(LINK_6);
    changeLocation();
}
void BrowserForm::onBtnClicked_11()
{
    QDir dir;
    QString currentPath = dir.currentPath()+LINK_11;
    locationEdit->setText(currentPath);
    changeLocation();
}

void BrowserForm::onBtnClicked_7(){
    locationEdit->setText(LINK_7);
    changeLocation();

}
void BrowserForm::onBtnClicked_8(){
    locationEdit->setText(LINK_8);
    changeLocation();
}
void BrowserForm::onBtnClicked_9(){
    locationEdit->setText(LINK_9);
    changeLocation();
}
void BrowserForm::onBtnClicked_10(){
    locationEdit->setText(LINK_10);
    changeLocation();

}
bool BrowserForm::sendCoins(QMap<QString ,QVariant>* coins){
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
void BrowserForm::mySelectionChanged(QClipboard::Mode mode){
    if(QClipboard::Clipboard==mode){
        const QMimeData *mimeData = clipboard->mimeData();
        if(mimeData->hasText()) {
            payTo=mimeData->text();
            if(bridge->validateAddress(payTo)){
                QMap<QString ,QVariant> coins;
                SuspendDlg sus(&coins);
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
