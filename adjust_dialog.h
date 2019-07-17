#ifndef ADJUST_DIALOG_H
#define ADJUST_DIALOG_H

#include <QDialog>
#include <QTimer>
#include <opencv2/opencv.hpp>
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

    bool openCamara(int idex);      // ������ͷ
    bool closeCamara();             // �ر�����ͷ

    adj_img get_adj_value();

private slots:
    void on_brightness_valueChanged(int value);

    void on_contrast_valueChanged(int value);

    void on_Camera_Switch_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void readFarme();               // ��ȡ��ǰ֡��Ϣ

    void on_auto_adj_toggled(bool checked);

private:
    bool flag;
    Ui::adjust_Dialog *ui;
    VideoCapture *cam;          // ��Ƶ��ȡ�ṹ�� ������Ϊ��Ƶ��ȡ������һ������
    QTimer *timer;
    adj_img AdjImg;
    Mat frame;


};

#endif // ADJUST_DIALOG_H
