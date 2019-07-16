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
#include "algorithm/equalizehist.h"
#include "algorithm/eigenvalue.h"
#include "adjust_dialog.h"

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
    void destroy_recode();

    bool openCamara(int idex);      // 打开摄像头
    bool closeCamara();             // 关闭摄像头
    void takingPictures();          // 拍照
    bool iden_proc(Mat img,int &witch);

private slots:
    void on_Camera_Switch_clicked();

    void readFarme();               // 读取当前帧信息

    void on_Adjust_Settings_triggered();

    void on_Start_clicked();

    void on_add_clicked();

    void on_remove_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    VideoCapture *cam;          // 视频获取结构， 用来作为视频获取函数的一个参数
    Mat taking_frame;
    Mat frame;
    adj_img AI;
    adjust_Dialog D1;

    std::vector <eigenvalue*> mode_record_img;    //模板记录

};

#endif // MAINWINDOW_H
 
