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
    //ת���ɻҶ�ͼ��ʹԭͼ��Ϊ��ͨ��ͼ��
    if(src.type()==0)
        dst = src;
    else
    cvtColor(src, dst, COLOR_BGR2GRAY);

    //ֱ��ͼ���⻯
    equalizeHist(dst, dst1);
    return dst1;
}

void Adj_Img(Mat input, Mat &output,adj_img AI)
{
    output = AI.contrast*input;
    output = output + AI.brightness;
}

#endif // EQUALIZEHIST_H
