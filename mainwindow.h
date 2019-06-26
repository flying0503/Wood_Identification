#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTimer>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "qcvdisplay.h"

using namespace cv;

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

    bool openCamara(int idex);      // 打开摄像头
    bool closeCamara();     // 关闭摄像头

    void takingPictures();  // 拍照

private slots:
    void on_Camera_Switch_clicked();
    void readFarme();       // 读取当前帧信息

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QImage *imag;
    Mat frame;
    VideoCapture *cam;          // 视频获取结构， 用来作为视频获取函数的一个参数
};

#endif // MAINWINDOW_H
 
