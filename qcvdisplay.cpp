#include "qcvdisplay.h"

#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>

#include <opencv2/imgproc/imgproc.hpp>

QCVDisplay::QCVDisplay(QWidget *parent) :
    QWidget(parent)
{
}

cv::Mat QCVDisplay::getBuffer()
{
   return buffer;
}

// �� Mat ת��Ϊ QImage������ QImage ��ÿһ���ж�������ֽ�
// �ʲ��� RBG32 �����������ֽ�
void QCVDisplay::matToQImage(const cv::Mat3b &src, QImage& dest)
{
    for (int y = 0; y < src.rows; ++y) {
        const cv::Vec3b *srcrow = src[y];
        QRgb *destrow = (QRgb*)dest.scanLine(y);
        for (int x = 0; x < src.cols; ++x) {
            destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
        }
    }
}

// �ڿؼ�����ʾͼƬ��ʹ�� opencv �Դ��� resize ʹ�����ŵ��Ϳؼ���Сһ��
void QCVDisplay::displayImage(const cv::Mat &img)
{
    QSize sz = data.size();
    if (img.channels() == 3) {
        buffer = img.clone();
    } else if (img.channels() == 1) {
        cv::cvtColor(img, buffer,cv::COLOR_BGR2GRAY);
    } else {
        throw UnsupportedFormatError();
    }
    cv::Mat resized;
    if (!sz.isEmpty()) {
        cv::resize(buffer, resized, cv::Size(sz.width(), sz.height()));
        matToQImage(resized, data);
        update();
    }
}

// ��ͼ�¼�������
void QCVDisplay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(event->rect(), data, event->rect());
}

// �����¼�Ҳ���� opencv �Դ��� resize
void QCVDisplay::resizeEvent(QResizeEvent *event)
{
    if (data.size() != event->size()) {
        cv::Mat resized;
        data = QImage(event->size(), QImage::Format_RGB32);
        if (!buffer.empty() && !event->size().isEmpty()) {
            cv::resize(buffer, resized, cv::Size(event->size().width(),
                                                  event->size().height()));
            matToQImage(resized, data);
        }
    }
    QWidget::resizeEvent(event);
}
