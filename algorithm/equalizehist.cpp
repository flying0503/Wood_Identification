#include "algorithm/equalizehist.h"

void Equalizehist(Mat src,Mat &output)
{
    Mat dst, dst1;
    //转换成灰度图像，使原图成为单通道图像
    if(src.type()==0)
        dst = src;
    else
    cvtColor(src, dst, COLOR_BGR2GRAY);

    //直方图均衡化
    equalizeHist(dst, dst1);
    output = dst1;
}

void Adj_Img(Mat input, Mat &output,adj_img AI)
{
    if(input.type() == 0)
    {
        output = AI.contrast*input;
        output = output + AI.brightness;
    }else {
        cvtColor(input,output,COLOR_BGR2GRAY);
        output = AI.contrast*output;
        output = output + AI.brightness;
    }
}
