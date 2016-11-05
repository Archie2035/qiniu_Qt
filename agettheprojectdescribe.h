#ifndef AGETTHEPROJECTDESCRIBE_H
#define AGETTHEPROJECTDESCRIBE_H

#include <QObject>
#include <QHttpPart>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
class AGetTheProjectDescribe : public QObject
{
    Q_OBJECT
public:
    explicit AGetTheProjectDescribe(QObject *parent = 0);
    void getAboutContent();
signals:
    void sig_aboutContent(QByteArray data);
public slots:
};

#endif // AGETTHEPROJECTDESCRIBE_H
