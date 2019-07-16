#ifndef ADJUST_DIALOG_H
#define ADJUST_DIALOG_H

#include <QDialog>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "qcvdisplay.h"
#include "algorithm/equalizehist.h"

using namespace cv;

namespace Ui {
class adjust_Dialog;
}

class adjust_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit adjust_Dialog(QWidget *parent = nullptr);
    ~adjust_Dialog();

    void initial();

    bool openCamara(int idex);      // 打开摄像头
    bool closeCamara();             // 关闭摄像头

    adj_img get_adj_value();

private slots:
    void on_brightness_valueChanged(int value);

    void on_contrast_valueChanged(int value);

    void on_Camera_Switch_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void readFarme();               // 读取当前帧信息

    void on_auto_adj_toggled(bool checked);

private:
    Ui::adjust_Dialog *ui;

    bool flag;

    adj_img AdjImg;

    QTimer *timer;
    Mat frame;
    VideoCapture *cam;          // 视频获取结构， 用来作为视频获取函数的一个参数

};

#endif // ADJUST_DIALOG_H
