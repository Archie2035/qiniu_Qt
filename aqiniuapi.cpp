#include "aqiniuapi.h"
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
AQiniuApi::AQiniuApi(QObject *parent) : QObject(parent)
{
    m_nodejsProcess = new QProcess(this);
    connect(m_nodejsProcess,&QProcess::readyRead,[=]{
        QByteArray data = m_nodejsProcess->readAll();
        if(data.contains("success")){
            emit sig_uploadResult(true,m_fileKey);
        }else{
            emit sig_uploadResult(false,QString(data));
        }
    });
}
void AQiniuApi::upload(QString path)
{
    QFileInfo fileInfo(path);

    m_fileKey = QString("%1%2.%3").arg(QDateTime::currentDateTime().toTime_t())
            .arg(fileInfo.baseName())
            .arg(fileInfo.suffix());
    QString cmd = QString("node ./qiniujs/upload.js %1 %2").arg(path).arg(m_fileKey);
    m_nodejsProcess->start(cmd);
}
