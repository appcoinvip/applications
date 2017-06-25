#include "webview.h"

WebView::WebView(QWidget *parent) :
    QWebView(parent)
{
    QSslConfiguration sslconf = QSslConfiguration::defaultConfiguration();
//    QList<QSslCertificate> cert_list = sslconf.caCertificates();
    QList<QSslCertificate> cert_list = readWindowsCa();
    QList<QSslCertificate> cert_new = QSslCertificate::fromData("CaCertificates");
    cert_list += cert_new;

    sslconf.setCaCertificates(cert_list);
    sslconf.setProtocol(QSsl::TlsV1_0);
    QSslConfiguration::setDefaultConfiguration(sslconf);
    connect(page()->networkAccessManager(),
            SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
            this,
            SLOT(handleSslErrors(QNetworkReply*, const QList<QSslError> & )));
}

WebView::~WebView(){

}

void WebView::handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    qDebug() << "handleSslErrors: ";
    foreach (QSslError e, errors)
    {
        qDebug() << "ssl error: " << e;
    }

    reply->ignoreSslErrors();
}
QList<QSslCertificate> WebView::readWindowsCa() const{
    QList<QSslCertificate> ca_list;
    HCERTSTORE hStore = CertOpenSystemStore(NULL, L"MY");
    X509 *cert;
    for ( PCCERT_CONTEXT pCertCtx = CertEnumCertificatesInStore(hStore, NULL); pCertCtx != NULL; pCertCtx = CertEnumCertificatesInStore(hStore, pCertCtx) ){
        // pCertCtx.cbCertEncoded
        cert = d2i_X509(NULL, (OPENSSL_d2i_TYPE) &pCertCtx->pbCertEncoded, pCertCtx->cbCertEncoded);
        BIO *bio = NULL;
        char *pem = NULL;
        if (NULL == cert) {
            continue;
        }
        bio = BIO_new(BIO_s_mem());
        if (NULL == bio) {
            continue;
        }
        if (0 == PEM_write_bio_X509(bio, cert)) {
            BIO_free(bio);
            continue;
        }
        pem = (char *) malloc(bio->num_write + 1);
        if (NULL == pem) {
            BIO_free(bio);
            continue;
        }
        memset(pem, 0, bio->num_write + 1);
        BIO_read(bio, pem, bio->num_write);
        BIO_free(bio);
        QSslCertificate *cert_new = new QSslCertificate(pem,QSsl::Pem);
        ca_list.append(*cert_new);
        free(pem);
        X509_free(cert);
    }
    CertCloseStore(hStore, CERT_CLOSE_STORE_CHECK_FLAG);
    return ca_list;
}
