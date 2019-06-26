#ifndef QCVDISPLAY_H
#define QCVDISPLAY_H

#include <QWidget>
#include <QException>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

// ��ͼƬ���ǻҶ�ͼ���� BGR ͼ��ʱ�׳����쳣
class UnsupportedFormatError : public QException
{
public:
    void raise() const { throw *this; }
    UnsupportedFormatError *clone() const { return new UnsupportedFormatError(*this); }
};

// ��ʾ opencv ͼƬ���Զ���ؼ�
class QCVDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit QCVDisplay(QWidget *parent = nullptr);
    cv::Mat getBuffer();

public slots:
    void displayImage(const cv::Mat& img);

protected:
    void matToQImage(const cv::Mat3b &src, QImage &dest);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    QImage data;
    cv::Mat buffer;
};

#endif // QCVDISPLAY_H
