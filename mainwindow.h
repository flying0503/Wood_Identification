﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTimer>
#include <opencv.hpp>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initial();

    bool openCamara();      // 打开摄像头
    bool closeCamara();     // 关闭摄像头

    void takingPictures();  // 拍照

private slots:
    void on_Camera_Switch_clicked();
    void readFarme();       // 读取当前帧信息

private:
    Ui::MainWindow *ui;
    QTimer    *timer;
    QImage    *imag;
    CvCapture *cam;         // 视频获取结构， 用来作为视频获取函数的一个参数
    cv::Mat   *frame;       //申请IplImage类型指针，就是申请内存空间来存放每一帧图像
};

#endif // MAINWINDOW_H
 