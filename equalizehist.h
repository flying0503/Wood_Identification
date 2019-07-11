#ifndef EQUALIZEHIST_H
#define EQUALIZEHIST_H
#include <opencv2/opencv.hpp>

using namespace cv;

Mat Equalizehist(Mat src)
{
    Mat dst, dst1;
    //转换成灰度图像，使原图成为单通道图像
    if(src.type()==0)
        dst = src;
    else
    cvtColor(src, dst, COLOR_BGR2GRAY);

    //直方图均衡化
    equalizeHist(dst, dst1);
    return dst1;
}
#endif // EQUALIZEHIST_H
