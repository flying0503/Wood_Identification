#include "adjust_dialog.h"
#include "ui_adjust_dialog.h"

adjust_Dialog::adjust_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adjust_Dialog)
{
    ui->setupUi(this);
}

adjust_Dialog::~adjust_Dialog()
{
    delete ui;
}

void adjust_Dialog::initial()
{
    cam = nullptr;
    timer = new QTimer(this);

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
    default:
        AdjImg.contrast = 1;
        break;
    }
}
