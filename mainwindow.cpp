#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initial();
}

MainWindow::~MainWindow()
{
    if(ui->Start->isEnabled())
        closeCamara();
    delete ui;
}

void MainWindow::initial()
{
    ui->Start->setEnabled(false);

    cam = nullptr;
    timer = new QTimer(this);
    //imag = new QImage();         // 初始化

    /*信号和槽*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
}

bool MainWindow::openCamara(int idex)
{
    cam = new VideoCapture;//打开摄像头，从摄像头中获取视频
    bool flage = cam->open(idex);
    if(flage)
    timer->start(35);              // 开始计时，超时则发出timeout()信号
    return flage;
}

bool MainWindow::closeCamara()
{
    timer->stop();         // 停止读取数据。
    cam->release();
    return cam->isOpened();
}

void MainWindow::takingPictures()
{

}

void MainWindow::on_Camera_Switch_clicked()
{
    static bool flage = true;
    if(flage)
    {
        if(openCamara(ui->Camera_index->currentIndex()))
        {
            ui->Start->setEnabled(true);
            ui->Camera_Switch->setText(QString::fromLocal8Bit("关闭相机"));
            ui->Camera_index->setEnabled(false);
            flage = false;
        }
        else{
            QMessageBox message(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("未找到设备"),QMessageBox::Yes,nullptr);
            message.exec();
        }
    }else {
        closeCamara();
        ui->Camera_Switch->setText(QString::fromLocal8Bit("打开相机"));
        ui->Start->setEnabled(false);
        ui->Camera_index->setEnabled(true);
        flage = true;
    }
}

void MainWindow::readFarme()
{
    cam->read(frame);
    ui->Camera_View->displayImage(frame);
} 
