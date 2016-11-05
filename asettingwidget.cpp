#include "asettingwidget.h"
#include <QSettings>
#include <QDebug>
ASettingWidget::ASettingWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setupUi(this);
    updateSetting();
    theProjectDescribe = new AGetTheProjectDescribe();
    theProjectDescribe->getAboutContent();
    connect(theProjectDescribe,&AGetTheProjectDescribe::sig_aboutContent,[=](QByteArray data){
        if(!data.isEmpty())
            textBrowserAbout->setText(QString(data));
    });
}

ASettingWidget::~ASettingWidget()
{
    delete theProjectDescribe;
}
void ASettingWidget::showEvent(QShowEvent *event)
{
    updateSetting();
}
void ASettingWidget::updateSetting()
{
    QSettings *configIniRead = new QSettings("./config/main.ini", QSettings::IniFormat);
    m_ak = configIniRead->value("/qiniu/ak").toString();
    m_sk = configIniRead->value("/qiniu/sk").toString();
    m_bucket = configIniRead->value("/qiniu/bucket").toString();
    m_domain = configIniRead->value("/qiniu/domain").toString();
    m_mdurl = configIniRead->value("/preference/mdurl").toString().toInt();
    m_stayOnTop = configIniRead->value("/preference/stayontop").toString().toInt();
    m_autodup = configIniRead->value("/preference/autodup").toString().toInt();

    lineEditAK->setText(m_ak);
    lineEditSK->setText(m_sk);
    lineEditBucket->setText(m_bucket);
    lineEditDomain->setText(m_domain);
    checkBoxAutoDup->setChecked(m_autodup);
    radioButtonOriginUrl->setChecked(!m_mdurl);
    radioButtonMarkdownUrl->setChecked(m_mdurl);
    checkBoxStaysOnTop->setChecked(m_stayOnTop);
}

QString ASettingWidget::getDomain()
{
    return m_domain;
}
bool ASettingWidget::getIfStayOnTop()
{
    return m_stayOnTop;
}
bool ASettingWidget::getIfAutoDup()
{
    return m_autodup;
}
bool ASettingWidget::getIfCopyMDUrl()
{
    return m_mdurl;
}
void ASettingWidget::on_pushButtonSubmitSetting_clicked()
{
    QSettings *configIniWrite = new QSettings("./config/main.ini", QSettings::IniFormat);
    configIniWrite->setValue("/qiniu/ak",lineEditAK->text());
    configIniWrite->setValue("/qiniu/sk",lineEditSK->text());
    configIniWrite->setValue("/qiniu/bucket",lineEditBucket->text());
    configIniWrite->setValue("/qiniu/domain",lineEditDomain->text());
    configIniWrite->setValue("/preference/autodup",checkBoxAutoDup->isChecked()?"1":"0");
    configIniWrite->setValue("/preference/mdurl",radioButtonMarkdownUrl->isChecked()?"1":"0");
    configIniWrite->setValue("/preference/stayontop",checkBoxStaysOnTop->isChecked()?"1":"0");
    updateSetting();
    this->close();
}

void ASettingWidget::on_pushButtonCancelSetting_clicked()
{
    this->close();
}
