#ifndef AQINIUAPI_H
#define AQINIUAPI_H
#include <QObject>
#include <QProcess>
class AQiniuApi : public QObject
{
    Q_OBJECT
public:
    explicit AQiniuApi(QObject *parent = 0);
    void upload(QString path);
private:
    QString m_fileKey;
    QProcess * m_nodejsProcess;
signals:
    void sig_uploadResult(bool result,QString msg);
public slots:
};

#endif // AQINIUAPI_H
