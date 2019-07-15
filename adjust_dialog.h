#ifndef ADJUST_DIALOG_H
#define ADJUST_DIALOG_H

#include <QDialog>
#include <QTimer>
#include "qcvdisplay.h"
#include "algorithm/equalizehist.h"

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

private slots:
    void on_brightness_valueChanged(int value);

    void on_contrast_valueChanged(int value);

private:
    Ui::adjust_Dialog *ui;

    adj_img AdjImg;

    QTimer *timer;
    Mat frame;
    VideoCapture *cam;          // 视频获取结构， 用来作为视频获取函数的一个参数

};

#endif // ADJUST_DIALOG_H
