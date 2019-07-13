#ifndef EIGENVALUE_H
#define EIGENVALUE_H
#include <opencv2/opencv.hpp>

using namespace cv;

class eigenvalue
{
public:
    //ͼƬ
    Mat Ident_Img;
    Mat L,a,b;

    //��������ֵ
    int avg_L;      //����
    int avg_a;      //������
    int avg_b;      //������

    int avg_Ag;     //ɫ���Ǿ�ֵ
    int avg_C;      //�ʶȾ�ֵ

    //����
    int avg_dev_L;  //����
    int avg_dev_a;  //������
    int avg_dev_b;  //������
    int avg_dev_Ag; //ɫ����
    int avg_dev_C;  //�ʶ�
    int avg_dev_E;  //Lab�ռ����
    int avg_dev_H;  //ȥ���Ⱦ���

    //��׼��
    int std_dev_L;  //����
    int std_dev_a;  //������
    int std_dev_b;  //������
    int std_dev_Ag; //ɫ����
    int std_dev_C;  //�ʶ�
    int std_dev_E;  //Lab�ռ����
    int std_dev_H;  //ȥ���Ⱦ���

public:
    eigenvalue(Mat img);

    //��������ֵ
    int calculate_avg_L(Mat L);      //����
    int calculate_avg_a(Mat a);      //������
    int calculate_avg_b(Mat b);      //������

    int calculate_avg_Ag(Mat a,Mat b);     //ɫ���Ǿ�ֵ
    int calculate_avg_C(Mat a,Mat b);      //�ʶȾ�ֵ

    //����
    int calculate_avg_dev_L(Mat L);  //����
    int calculate_avg_dev_a(Mat a);  //������
    int calculate_avg_dev_b(Mat b);  //������
    int calculate_avg_dev_Ag(Mat a,Mat b); //ɫ����
    int calculate_avg_dev_C(Mat a, Mat b);  //�ʶ�
    int calculate_avg_dev_E(Mat L,Mat a,Mat b);  //Lab�ռ����
    int calculate_avg_dev_H(int avg_L,int avg_E,int avg_C);  //ȥ���Ⱦ���

    //��׼��
    int calculate_std_dev_L(Mat L);  //����
    int calculate_std_dev_a(Mat a);  //������
    int calculate_std_dev_b(Mat b);  //������
    int calculate_std_dev_Ag(Mat a,Mat b); //ɫ����
    int calculate_std_dev_C(Mat a,Mat b);  //�ʶ�
    int calculate_std_dev_E(Mat L,Mat a,Mat b);  //Lab�ռ����
    int calculate_std_dev_H(Mat L,Mat a,Mat b);  //ȥ���Ⱦ���
};

#endif // EIGENVALUE_H
