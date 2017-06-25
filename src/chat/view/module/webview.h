#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>
#include <QNetworkReply>
#include <QtDebug>
#include <QSslError>
#include <QSsl>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <wincrypt.h>
#include <chat/control/define_1.h>

class WebView : public QWebView
{
    Q_OBJECT
public:
    WebView(QWidget *parent = 0);
    ~WebView();

private slots:
    void handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors);
private:
    QList<QSslCertificate> readWindowsCa() const;
};

#endif // WEBVIEW_H
