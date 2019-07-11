#ifndef EQUALIZEHIST_H
#define EQUALIZEHIST_H
#include <opencv2/opencv.hpp>

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
#endif // EQUALIZEHIST_H
