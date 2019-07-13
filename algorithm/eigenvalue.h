#ifndef EIGENVALUE_H
#define EIGENVALUE_H
#include <opencv2/opencv.hpp>

using namespace cv;

class eigenvalue
{
public:
    //图片
    Mat Ident_Img;
    Mat L,a,b;

    //各分量均值
    int avg_L;      //明度
    int avg_a;      //红绿轴
    int avg_b;      //黄蓝轴

    int avg_Ag;     //色调角均值
    int avg_C;      //彩度均值

    //均差
    int avg_dev_L;  //明度
    int avg_dev_a;  //红绿轴
    int avg_dev_b;  //黄蓝轴
    int avg_dev_Ag; //色调角
    int avg_dev_C;  //彩度
    int avg_dev_E;  //Lab空间距离
    int avg_dev_H;  //去明度距离

    //标准差
    int std_dev_L;  //明度
    int std_dev_a;  //红绿轴
    int std_dev_b;  //黄蓝轴
    int std_dev_Ag; //色调角
    int std_dev_C;  //彩度
    int std_dev_E;  //Lab空间距离
    int std_dev_H;  //去明度距离

public:
    eigenvalue(Mat img);

    //各分量均值
    int calculate_avg_L(Mat L);      //明度
    int calculate_avg_a(Mat a);      //红绿轴
    int calculate_avg_b(Mat b);      //黄蓝轴

    int calculate_avg_Ag(Mat a,Mat b);     //色调角均值
    int calculate_avg_C(Mat a,Mat b);      //彩度均值

    //均差
    int calculate_avg_dev_L(Mat L);  //明度
    int calculate_avg_dev_a(Mat a);  //红绿轴
    int calculate_avg_dev_b(Mat b);  //黄蓝轴
    int calculate_avg_dev_Ag(Mat a,Mat b); //色调角
    int calculate_avg_dev_C(Mat a, Mat b);  //彩度
    int calculate_avg_dev_E(Mat L,Mat a,Mat b);  //Lab空间距离
    int calculate_avg_dev_H(int avg_L,int avg_E,int avg_C);  //去明度距离

    //标准差
    int calculate_std_dev_L(Mat L);  //明度
    int calculate_std_dev_a(Mat a);  //红绿轴
    int calculate_std_dev_b(Mat b);  //黄蓝轴
    int calculate_std_dev_Ag(Mat a,Mat b); //色调角
    int calculate_std_dev_C(Mat a,Mat b);  //彩度
    int calculate_std_dev_E(Mat L,Mat a,Mat b);  //Lab空间距离
    int calculate_std_dev_H(Mat L,Mat a,Mat b);  //去明度距离
};

#endif // EIGENVALUE_H
