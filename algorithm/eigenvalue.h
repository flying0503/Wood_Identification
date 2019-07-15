#ifndef EIGENVALUE_H
#define EIGENVALUE_H
#include <opencv2/opencv.hpp>

using namespace cv;

class eigenvalue
{
private:
    //ͼƬ
    Mat *Ident_Img;
    Mat *L,*a,*b;

    //��������ֵ
    double avg_L;      //����
    double avg_a;      //������
    double avg_b;      //������

    double avg_Ag;     //ɫ���Ǿ�ֵ
    double avg_C;      //�ʶȾ�ֵ

    //����
    double avg_dev_L;  //����
    double avg_dev_a;  //������
    double avg_dev_b;  //������
    double avg_dev_Ag; //ɫ����
    double avg_dev_C;  //�ʶ�
    double avg_dev_E;  //Lab�ռ����
    double avg_dev_H;  //ȥ���Ⱦ���

    //��׼��
    double std_dev_L;  //����
    double std_dev_a;  //������
    double std_dev_b;  //������
    double std_dev_Ag; //ɫ����
    double std_dev_C;  //�ʶ�
    double std_dev_E;  //Lab�ռ����
    double std_dev_H;  //ȥ���Ⱦ���

    double Eigenvalue[19];

public:
    eigenvalue(Mat img);
    ~eigenvalue();

    void display_eigenvalue(char *message);

    //��������ֵ
    double calculate_avg_L(Mat L);      //����
    double calculate_avg_a(Mat a);      //������
    double calculate_avg_b(Mat b);      //������

    double calculate_avg_Ag(Mat a,Mat b);     //ɫ���Ǿ�ֵ
    double calculate_avg_C(Mat a,Mat b);      //�ʶȾ�ֵ
    Mat calculate_Ag(Mat a,Mat b);
    Mat calculate_C(Mat a,Mat b);


    //����
    double calculate_avg_dev_L(Mat L);  //����
    double calculate_avg_dev_a(Mat a);  //������
    double calculate_avg_dev_b(Mat b);  //������
    double calculate_avg_dev_Ag(Mat a,Mat b); //ɫ����
    double calculate_avg_dev_C(Mat a, Mat b);  //�ʶ�
    double calculate_avg_dev_E(Mat L,Mat a,Mat b);  //Lab�ռ����
    double calculate_avg_dev_H(double avg_L,double avg_E,double avg_C);  //ȥ���Ⱦ���

    //��׼��
    double calculate_std_dev_L(Mat L);  //����
    double calculate_std_dev_a(Mat a);  //������
    double calculate_std_dev_b(Mat b);  //������
    double calculate_std_dev_Ag(Mat a,Mat b); //ɫ����
    double calculate_std_dev_C(Mat a,Mat b);  //�ʶ�
    double calculate_std_dev_E(Mat L,Mat a,Mat b);  //Lab�ռ����
    double calculate_std_dev_H(Mat a,Mat b);  //ȥ���Ⱦ���

    double *get_eigenvalue();
};

#endif // EIGENVALUE_H
