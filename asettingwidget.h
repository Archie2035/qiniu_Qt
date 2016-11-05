#ifndef ASETTINGWIDGET_H
#define ASETTINGWIDGET_H

#include <QWidget>
#include "ui_asettingwidget.h"
#include "agettheprojectdescribe.h"
class ASettingWidget : public QWidget,Ui::ASettingWidget
{
    Q_OBJECT

public:
    explicit ASettingWidget(QWidget *parent = 0);
    ~ASettingWidget();
    QString m_ak;
    QString m_sk;
    QString m_bucket;
    QString m_domain;
    bool m_mdurl;
    bool m_stayOnTop;
    bool m_autodup;

    QString getDomain();
    bool getIfStayOnTop();
    bool getIfAutoDup();
    bool getIfCopyMDUrl();
    AGetTheProjectDescribe *theProjectDescribe;
protected:
    void showEvent(QShowEvent *event);

private:
    void updateSetting();

private slots:
    void on_pushButtonSubmitSetting_clicked();
    void on_pushButtonCancelSetting_clicked();

private:

};

#endif // ASETTINGWIDGET_H
