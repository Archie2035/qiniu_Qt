#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileIconProvider>
#include <QClipboard>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(300,200);
    setAcceptDrops(true);
    settingObject = new ASettingWidget();
    if(settingObject->getIfStayOnTop())
    {
        setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    qiniu = new AQiniuApi();
    connect(qiniu,&AQiniuApi::sig_uploadResult,[=](bool result,QString msg){
        if(result){
            showFilePreview();
            showStatusMessage(QString("上传成功"),5000);
            m_remotePicUrl = settingObject->getDomain()+"/"+msg;
            ui->lineEditUrl->setText(m_remotePicUrl);
            autoDup();
        }else{
            showStatusMessage(QString("%1%2").arg("上传失败").arg(msg),5000);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    event = event;
    QCoreApplication::quit();
}
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty()){
        showStatusMessage("没有文件！",5000);
        return;
    }
    if(urls.count() > 1){
        showStatusMessage("只支持单个文件上传！",5000);
        return;
    }
    else{
        m_localFilePath = urls.first().toString().split("file:///").last();
        qiniu->upload(m_localFilePath);
        showStatusMessage("正在上传",5000);
    }
}
void MainWindow::on_pushButtonOpenFile_clicked()
{
    m_localFilePath = QFileDialog::getOpenFileName(this,"select pic",QDir::currentPath(),"All (*)");
    if(m_localFilePath.isEmpty())
        return;
    qiniu->upload(m_localFilePath);
    showStatusMessage("正在上传",5000);
}
void MainWindow::showFilePreview()
{
    qDebug()<<"showFilePreview"<<m_localFilePath;
    QFileInfo fileInfo(m_localFilePath);
    QString suffix = fileInfo.suffix().toLower();
    if( suffix== "png" || suffix == "jpg"|| suffix == "jpeg"
            || suffix == "bmp" || suffix == "gif" || suffix == "pbm"
            || suffix == "pgm" || suffix == "ppm" || suffix == "xbm"
            || suffix == "xpm")
    {
        QImage *image = new QImage(m_localFilePath);
        ui->labelFilePreview->setPixmap(QPixmap::fromImage(*image)
                                        .scaledToWidth(ui->labelFilePreview->width()));
    }
    else
    {
        QFileIconProvider iconPprovider;
        QIcon icon = iconPprovider.icon(fileInfo);
        ui->labelFilePreview->setPixmap(icon.pixmap(30,30));

    }
}
void MainWindow::setClipboardText(QString data)
{
    QClipboard *board = QApplication::clipboard();
    board->setText(data);
}
void MainWindow::autoDup()
{
    if(settingObject->getIfAutoDup())
    {
        if(settingObject->getIfCopyMDUrl())
        {
            setClipboardText("![]("+m_remotePicUrl+")");
        }
        else
        {
            setClipboardText(m_remotePicUrl);
        }
        showStatusMessage("复制链接完成",5000);
    }
}
void MainWindow::showStatusMessage(QString message,int timeout)
{
    ui->statusBar->showMessage(message,timeout);
}

void MainWindow::on_pushButtonSetting_clicked()
{
    settingObject->show();
}

void MainWindow::on_pushButtonOriginCopy_clicked()
{
    setClipboardText(m_remotePicUrl);
    showStatusMessage("复制链接完成",5000);
}

void MainWindow::on_pushButtonMarkdownCopy_clicked()
{
    setClipboardText("![]("+m_remotePicUrl+")");
    showStatusMessage("复制链接完成",5000);
}
