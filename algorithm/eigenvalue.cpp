#include "eigenvalue.h"

eigenvalue::eigenvalue(Mat img)
{
    //ͼƬ
    cvtColor(img,Ident_Img,COLOR_BGR2Lab);
    Mat channels[3];
    split(Ident_Img,channels);

    L = channels[0];
    a = channels[1];
    b = channels[2];

    //��������ֵ
    avg_L = calculate_avg_L(L);      //����
    avg_a = calculate_avg_a(a);      //������
    avg_b = calculate_avg_b(b);      //������

    avg_Ag = calculate_avg_Ag(a,b);    //ɫ���Ǿ�ֵ
    avg_C = calculate_avg_C(a,b);      //�ʶȾ�ֵ

    //����
    avg_dev_L = calculate_avg_dev_L(L);  //����
    avg_dev_a = calculate_avg_dev_a(a);  //������
    avg_dev_b = calculate_avg_dev_b(b);  //������
    avg_dev_Ag = calculate_avg_dev_Ag(a,b);//ɫ����
    avg_dev_C = calculate_avg_dev_C(a,b);  //�ʶ�
    avg_dev_E = calculate_avg_dev_E(L,a,b);  //Lab�ռ����
    avg_dev_H = calculate_avg_dev_H(avg_dev_L,avg_dev_E,avg_dev_C);  //ȥ���Ⱦ���

    //��׼��
    std_dev_L = calculate_std_dev_L(L);  //����
    std_dev_a = calculate_std_dev_a(a);  //������
    std_dev_b = calculate_std_dev_b(b);  //������
    std_dev_Ag = calculate_std_dev_Ag(a,b);//ɫ����
    std_dev_C = calculate_std_dev_C(a,b);  //�ʶ�
    std_dev_E = calculate_std_dev_E(L,a,b);  //Lab�ռ����
    std_dev_H = calculate_std_dev_H(L,a,b);  //ȥ���Ⱦ���

}

int eigenvalue::calculate_avg_L(Mat img)
{
    Mat avg_L,temp;
    meanStdDev(img,avg_L,temp);
    return avg_L.at<int>(0,0);
}

int eigenvalue::calculate_avg_a(Mat img)
{
    Mat avg_a,temp;
    meanStdDev(img,avg_a,temp);
    return avg_a.at<int>(0,0);
}

int eigenvalue::calculate_avg_b(Mat img)
{   Mat avg_b,temp;
    meanStdDev(img,avg_b,temp);
    return avg_b.at<int>(0,0);
}

int eigenvalue::calculate_avg_Ag(Mat a, Mat b)
{
    Mat c=a;
    for (int i=0;i<c.rows;i++) {
        for (int j=0;j<c.cols;j++) {
            if(b.at<int>(i,j) == 0)
            {
                c.at<int>(i,j) = 0;
            }else {
                c.at<int>(i,j) = a.at<int>(i,j)/b.at<int>(i,j);
            }
        }
    }

}

int eigenvalue::calculate_avg_C(Mat a, Mat b)
{
    Mat a2 = a.mul(a);
    Mat b2 = b.mul(b);
    Mat C = a2+b2;
    sqrt(C,C);
    Mat mean,temp;
    meanStdDev(C,mean,temp);
    return mean.at<int>(0,0);
}
