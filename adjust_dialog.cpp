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

    /*�źźͲ�*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // ʱ�䵽����ȡ��ǰ����ͷ��Ϣ
}

bool adjust_Dialog::openCamara(int idex)
{
    cam = new VideoCapture;//������ͷ��������ͷ�л�ȡ��Ƶ
    bool flage = cam->open(idex);
    if(flage)
    timer->start(500);              // ��ʼ��ʱ����ʱ�򷢳�timeout()�ź�
    return flage;
}

bool adjust_Dialog::closeCamara()
{
    timer->stop();         // ֹͣ��ȡ���ݡ�
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
