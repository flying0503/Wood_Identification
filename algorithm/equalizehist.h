#ifndef EQUALIZEHIST_H
#define EQUALIZEHIST_H
#include <opencv2/opencv.hpp>

typedef struct Adjust_image
{
    unsigned char brightness;
    double contrast;
}adj_img;

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

void Adj_Img(Mat input, Mat &output,adj_img AI)
{
    output = AI.contrast*input;
    output = output + AI.brightness;
}

#endif // EQUALIZEHIST_H
