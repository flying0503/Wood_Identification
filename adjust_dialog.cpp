#include <QMessageBox>
#include "adjust_dialog.h"
#include "ui_adjust_dialog.h"
#include "algorithm/split_rgb.h"

adjust_Dialog::adjust_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adjust_Dialog)
{
    ui->setupUi(this);
    initial();
}

adjust_Dialog::~adjust_Dialog()
{
    delete ui;
}

void adjust_Dialog::initial()
{
    cam = nullptr;
    timer = new QTimer(this);

    AdjImg.contrast=1;
    AdjImg.brightness = 0;
    AdjImg.auto_adj = false;

    /*信号和槽*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
}

bool adjust_Dialog::openCamara(int idex)
{
    cam = new VideoCapture;//打开摄像头，从摄像头中获取视频
    bool flage = cam->open(idex);
    if(flage)
    timer->start(500);              // 开始计时，超时则发出timeout()信号
    return flage;
}

bool adjust_Dialog::closeCamara()
{
    timer->stop();         // 停止读取数据。
    cam->release();
    return cam->isOpened();
}

adj_img adjust_Dialog::get_adj_value()
{
    return AdjImg;
}

void adjust_Dialog::on_brightness_valueChanged(int value)
{
    AdjImg.brightness = (unsigned char)value;
}

void adjust_Dialog::on_contrast_valueChanged(int value)
{
    switch (value) {
    case 0:
        AdjImg.contrast = 1;
        break;
    case 1:
        AdjImg.contrast = 1.5;
        break;
    case 2:
        AdjImg.contrast = 2;
        break;
    case 3:
        AdjImg.contrast = 2.5;
        break;
    case -1:
        AdjImg.contrast = 0.8;
        break;
    case -2:
        AdjImg.contrast = 0.5;
        break;
    case -3:
        AdjImg.contrast = 0.25;
        break;
    default:
        AdjImg.contrast = 1;
        break;
    }
}

void adjust_Dialog::on_Camera_Switch_clicked()
{
    flag = openCamara(ui->Camera_index->currentIndex());
    if(flag)
    {
        ui->Camera_Switch->setEnabled(false);
        ui->Camera_index->setEnabled(false);
    }
    else{
        QMessageBox message(QMessageBox::Warning,QString::fromLocal8Bit("警告"),
                            QString::fromLocal8Bit("未找到设备"),QMessageBox::Yes,nullptr);
        message.exec();
    }
}

void adjust_Dialog::on_buttonBox_accepted()
{
    if(flag)
        closeCamara();

    ui->Camera_Switch->setEnabled(true);
    ui->Camera_index->setEnabled(true);
}

void adjust_Dialog::on_buttonBox_rejected()
{
    if(flag)
        closeCamara();
    ui->Camera_Switch->setEnabled(true);
    ui->Camera_index->setEnabled(true);
}

void adjust_Dialog::readFarme()
{
    cam->read(frame);

    Mat channel[3],Mer;
    Split_RGB(frame,channel[2],channel[1],channel[0],false);
    if(AdjImg.auto_adj)
    {
        for (int i=0;i<3;i++) {
            Equalizehist(channel[i],channel[i]);
        }
    }else {
        for (int i=0;i<3;i++) {
            Adj_Img(channel[i],channel[i],AdjImg);
        }
    }

    Merge_RGB(channel[2],channel[1],channel[0],Mer);
    ui->Camera_View->displayImage(Mer);
}

void adjust_Dialog::on_auto_adj_toggled(bool checked)
{
    AdjImg.auto_adj = checked;
    if(checked)
    {
        ui->brightness->setEnabled(false);
        ui->contrast->setEnabled(false);
    }else {
        ui->brightness->setEnabled(true);
        ui->contrast->setEnabled(true);
    }
}
