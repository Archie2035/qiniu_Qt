#include "agettheprojectdescribe.h"
#include <QDebug>
AGetTheProjectDescribe::AGetTheProjectDescribe(QObject *parent) : QObject(parent)
{

}
void AGetTheProjectDescribe::getAboutContent()
{
    QUrl url("https://raw.githubusercontent.com/tianzhihen/projectDescribe/master/qiniu_Qt/aboutcontent.md");
    QNetworkRequest request(url);
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);
    request.setSslConfiguration(config);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect (manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {
        emit sig_aboutContent(reply->readAll());
    });
    manager->get(request);
}
