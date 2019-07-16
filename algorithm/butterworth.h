#ifndef BUTTERWORTH_H
#define BUTTERWORTH_H

#include <opencv2/opencv.hpp>

using namespace cv;

void shiftDFT(Mat &fImage);

Mat create_spectrum_magnitude_display(Mat &complexImg, bool rearrange);

//����Ҷ�任
Mat Fourier_Tran(Mat input);

//����Ҷ��任
Mat IFourier_Tran(Mat complexImg);

//n��ʾ������˹�˲����Ľ���,D0��ʾ�˲��뾶
Mat Butterworth_Low_Paass_Filter(Mat src,int n,double D0,bool show_img);
#endif // BUTTERWORTH_H
