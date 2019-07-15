#ifndef EIGENVALUE_H
#define EIGENVALUE_H
#include <opencv2/opencv.hpp>

using namespace cv;

class eigenvalue
{
private:
    //图片
    Mat *Ident_Img;
    Mat *L,*a,*b;

    //各分量均值
    double avg_L;      //明度
    double avg_a;      //红绿轴
    double avg_b;      //黄蓝轴

    double avg_Ag;     //色调角均值
    double avg_C;      //彩度均值

    //均差
    double avg_dev_L;  //明度
    double avg_dev_a;  //红绿轴
    double avg_dev_b;  //黄蓝轴
    double avg_dev_Ag; //色调角
    double avg_dev_C;  //彩度
    double avg_dev_E;  //Lab空间距离
    double avg_dev_H;  //去明度距离

    //标准差
    double std_dev_L;  //明度
    double std_dev_a;  //红绿轴
    double std_dev_b;  //黄蓝轴
    double std_dev_Ag; //色调角
    double std_dev_C;  //彩度
    double std_dev_E;  //Lab空间距离
    double std_dev_H;  //去明度距离

    double Eigenvalue[19];

public:
    eigenvalue(Mat img);
    ~eigenvalue();

    void display_eigenvalue(char *message);

    //各分量均值
    double calculate_avg_L(Mat L);      //明度
    double calculate_avg_a(Mat a);      //红绿轴
    double calculate_avg_b(Mat b);      //黄蓝轴

    double calculate_avg_Ag(Mat a,Mat b);     //色调角均值
    double calculate_avg_C(Mat a,Mat b);      //彩度均值
    Mat calculate_Ag(Mat a,Mat b);
    Mat calculate_C(Mat a,Mat b);


    //均差
    double calculate_avg_dev_L(Mat L);  //明度
    double calculate_avg_dev_a(Mat a);  //红绿轴
    double calculate_avg_dev_b(Mat b);  //黄蓝轴
    double calculate_avg_dev_Ag(Mat a,Mat b); //色调角
    double calculate_avg_dev_C(Mat a, Mat b);  //彩度
    double calculate_avg_dev_E(Mat L,Mat a,Mat b);  //Lab空间距离
    double calculate_avg_dev_H(double avg_L,double avg_E,double avg_C);  //去明度距离

    //标准差
    double calculate_std_dev_L(Mat L);  //明度
    double calculate_std_dev_a(Mat a);  //红绿轴
    double calculate_std_dev_b(Mat b);  //黄蓝轴
    double calculate_std_dev_Ag(Mat a,Mat b); //色调角
    double calculate_std_dev_C(Mat a,Mat b);  //彩度
    double calculate_std_dev_E(Mat L,Mat a,Mat b);  //Lab空间距离
    double calculate_std_dev_H(Mat a,Mat b);  //去明度距离

    double *get_eigenvalue();
};

#endif // EIGENVALUE_H
