#ifndef BUTTERWORTH_H
#define BUTTERWORTH_H

#include <opencv2/opencv.hpp>

using namespace cv;

void shiftDFT(Mat &fImage);

Mat create_spectrum_magnitude_display(Mat &complexImg, bool rearrange);

//傅里叶变换
Mat Fourier_Tran(Mat input);

//傅里叶逆变换
Mat IFourier_Tran(Mat complexImg);

//n表示巴特沃斯滤波器的阶数,D0表示滤波半径
Mat Butterworth_Low_Paass_Filter(Mat src,int n,double D0,bool show_img);
#endif // BUTTERWORTH_H
