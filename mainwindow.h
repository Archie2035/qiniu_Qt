#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aqiniuapi.h"
#include "asettingwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private:
    AQiniuApi *qiniu;
    QString m_localFilePath;
    QString m_remotePicUrl;
    ASettingWidget *settingObject;
    void showFilePreview(void);
    void setClipboardText(QString data);
    void autoDup();
private slots:
    void on_pushButtonOpenFile_clicked();
    void on_pushButtonSetting_clicked();
    void on_pushButtonOriginCopy_clicked();
    void on_pushButtonMarkdownCopy_clicked();

public slots:
    void showStatusMessage(QString message,int timeout = 0);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
