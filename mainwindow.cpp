﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initial()
{
    ui->Start->setEnabled(false);

    cam     = nullptr;
    timer   = new QTimer(this);
    imag    = new QImage();         // 初始化

    /*信号和槽*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
}

bool MainWindow::openCamara()
{
    cam = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频

    timer->start(33);              // 开始计时，超时则发出timeout()信号
}

void MainWindow::on_Camera_Switch_clicked()
{
    static bool flage = true;
    if(flage)
    {
        ui->Camera_Switch->setText(QString::fromLocal8Bit("关闭相机"));
        ui->Start->setEnabled(true);
    }else {
        ui->Camera_Switch->setText(QString::fromLocal8Bit("打开相机"));
        ui->Start->setEnabled(false);
    }
    flage = !flage;
}
 