#include "eigenvalue.h"

eigenvalue::eigenvalue(Mat img)
{
    Ident_Img = new Mat(img);
    //图片
    cvtColor(img,*Ident_Img,COLOR_BGR2Lab);
    Mat channels[3];
    split(*Ident_Img,channels);

    L = new Mat(channels[0]);
    a = new Mat(channels[1]);
    b = new Mat(channels[2]);

    //各分量均值
    avg_L = calculate_avg_L(*L);      //明度
    avg_a = calculate_avg_a(*a);      //红绿轴
    avg_b = calculate_avg_b(*b);      //黄蓝轴

    avg_Ag = calculate_avg_Ag(*a,*b);    //色调角均值
    avg_C = calculate_avg_C(*a,*b);      //彩度均值

    //均差
    avg_dev_L = calculate_avg_dev_L(*L);  //明度
    avg_dev_a = calculate_avg_dev_a(*a);  //红绿轴
    avg_dev_b = calculate_avg_dev_b(*b);  //黄蓝轴
    avg_dev_Ag = calculate_avg_dev_Ag(*a,*b);//色调角
    avg_dev_C = calculate_avg_dev_C(*a,*b);  //彩度
    avg_dev_E = calculate_avg_dev_E(*L,*a,*b);  //Lab空间距离
    avg_dev_H = calculate_avg_dev_H(avg_dev_L,avg_dev_E,avg_dev_C);  //去明度距离

    //标准差
    std_dev_L = calculate_std_dev_L(*L);  //明度
    std_dev_a = calculate_std_dev_a(*a);  //红绿轴
    std_dev_b = calculate_std_dev_b(*b);  //黄蓝轴
    std_dev_Ag = calculate_std_dev_Ag(*a,*b);//色调角
    std_dev_C = calculate_std_dev_C(*a,*b);  //彩度
    std_dev_E = calculate_std_dev_E(*L,*a,*b);  //Lab空间距离
    std_dev_H = calculate_std_dev_H(*a,*b);  //去明度距离

    Eigenvalue[0] = avg_L;
    Eigenvalue[1] = avg_a;
    Eigenvalue[2] = avg_b;

    Eigenvalue[3] = avg_Ag;
    Eigenvalue[4] = avg_C;

    Eigenvalue[5] = avg_dev_L;
    Eigenvalue[6] = avg_dev_a;
    Eigenvalue[7] = avg_dev_b;
    Eigenvalue[8] = avg_dev_Ag;
    Eigenvalue[9] = avg_dev_C;
    Eigenvalue[10] = avg_dev_E;
    Eigenvalue[11] = avg_dev_H;

    Eigenvalue[12] = std_dev_L;
    Eigenvalue[13] = std_dev_a;
    Eigenvalue[14] = std_dev_b;
    Eigenvalue[15] = std_dev_Ag;
    Eigenvalue[16] = std_dev_C;
    Eigenvalue[17] = std_dev_E;
    Eigenvalue[18] = std_dev_H;
}

eigenvalue::~eigenvalue()
{
    delete Ident_Img;
    delete L;
    delete a;
    delete b;
}

void eigenvalue::display_eigenvalue(char *message)
{
    std::cout<<message<<std::endl;

    std::cout<<"avg_L="<<avg_L<<std::endl;
    std::cout<<"avg_a="<<avg_a<<std::endl;
    std::cout<<"avg_b="<<avg_b<<std::endl;
    std::cout<<"avg_Ag="<<avg_Ag<<std::endl;
    std::cout<<"avg_C="<<avg_C<<std::endl;

    std::cout<<"avg_dev_L="<<avg_dev_L<<std::endl;
    std::cout<<"avg_dev_a="<<avg_dev_a<<std::endl;
    std::cout<<"avg_dev_b="<<avg_dev_b<<std::endl;
    std::cout<<"avg_dev_Ag="<<avg_dev_Ag<<std::endl;
    std::cout<<"avg_dev_C="<<avg_dev_C<<std::endl;
    std::cout<<"avg_dev_E="<<avg_dev_E<<std::endl;
    std::cout<<"avg_dev_H="<<avg_dev_H<<std::endl;

    std::cout<<"std_dev_L="<<std_dev_L<<std::endl;
    std::cout<<"std_dev_a="<<std_dev_a<<std::endl;
    std::cout<<"std_dev_b="<<std_dev_b<<std::endl;
    std::cout<<"std_dev_Ag="<<std_dev_Ag<<std::endl;
    std::cout<<"std_dev_C="<<std_dev_C<<std::endl;
    std::cout<<"std_dev_E="<<std_dev_E<<std::endl;
    std::cout<<"std_dev_H="<<std_dev_H<<std::endl;
}

double eigenvalue::calculate_avg_L(Mat img)
{
    img.convertTo(img,CV_32F);
    auto avg_L = mean(img);
    return avg_L[0];
}

double eigenvalue::calculate_avg_a(Mat img)
{
    img.convertTo(img,CV_32F);
    auto avg_a = mean(img);
    return avg_a[0];
}

double eigenvalue::calculate_avg_b(Mat img)
{
    img.convertTo(img,CV_32F);
    auto avg_b = mean(img);
    return avg_b[0];
}

double eigenvalue::calculate_avg_Ag(Mat a, Mat b)
{
    Mat Ag = calculate_Ag(a,b);
    auto avg = mean(Ag);
    return avg[0];
}

double eigenvalue::calculate_avg_C(Mat a, Mat b)
{
    Mat C = calculate_C(a,b);
    auto avg = mean(C);
    return avg[0];
}

Mat eigenvalue::calculate_Ag(Mat a, Mat b)
{
    Mat da,db;
    a.convertTo(da,CV_32F);
    b.convertTo(db,CV_32F);
    Mat Ag;
    Ag = db/da;
    Ag.convertTo(Ag,CV_32F);
    for (int i = 0;i<Ag.rows;i++) {
        for (int j = 0;j<Ag.cols;j++) {
            Ag.at<float>(i,j) = atan(Ag.at<float>(i,j));
        }
    }
    return Ag;
}

Mat eigenvalue::calculate_C(Mat a, Mat b)
{
    Mat da,db;
    a.convertTo(da,CV_32F);
    b.convertTo(db,CV_32F);
    Mat a2 = da.mul(da);
    Mat b2 = db.mul(db);
    Mat C = a2+b2;
    C.convertTo(C,CV_32F);
    sqrt(C,C);
    return C;
}

double eigenvalue::calculate_avg_dev_L(Mat L)
{
    Mat dL;
    L.convertTo(dL,CV_32F);
    dL = abs(dL-avg_L);
    auto avg = mean(dL);
    return avg[0];
}

double eigenvalue::calculate_avg_dev_a(Mat a)
{
    Mat da;
    a.convertTo(da,CV_32F);
    da = abs(da-avg_a);
    auto avg = mean(da);
    return avg[0];
}

double eigenvalue::calculate_avg_dev_b(Mat b)
{
    Mat db;
    b.convertTo(db,CV_32F);
    db = abs(db-avg_b);
    auto avg = mean(db);
    return avg[0];
}

double eigenvalue::calculate_avg_dev_Ag(Mat a, Mat b)
{
    Mat Ag = calculate_Ag(a,b);
    Ag = abs(Ag-avg_Ag);
    auto avg = mean(Ag);
    return avg[0];
}

double eigenvalue::calculate_avg_dev_C(Mat a, Mat b)
{
    Mat C = calculate_C(a,b);
    Mat dC;
    C.convertTo(dC,CV_32F);
    dC = abs(dC-avg_C);
    auto avg = mean(dC);
    return avg[0];
}

double eigenvalue::calculate_avg_dev_E(Mat L, Mat a, Mat b)
{
    Mat E,dE;
    E = (L-avg_L)^2+(a-avg_a)^2+(b-avg_b)^2;
    E.convertTo(dE,CV_32F);
    sqrt(dE,dE);
    auto avg = mean(dE);
    return avg[0];
}

double eigenvalue::calculate_avg_dev_H(double avg_L, double avg_E, double avg_C)
{
    double H = avg_E*avg_E - avg_L*avg_L + avg_C*avg_C;
    H = sqrt(abs(H));
    return H;
}

double eigenvalue::calculate_std_dev_L(Mat L)
{
    Mat dL,avg,stddev;
    L.convertTo(dL,CV_32F);
    meanStdDev(dL,avg,stddev);
    return stddev.at<double>(0,0);
}

double eigenvalue::calculate_std_dev_a(Mat a)
{
    Mat da,avg,stddev;
    a.convertTo(da,CV_32F);
    meanStdDev(da,avg,stddev);
    return stddev.at<double>(0,0);
}

double eigenvalue::calculate_std_dev_b(Mat b)
{
    Mat db,avg,stddev;
    b.convertTo(db,CV_32F);
    meanStdDev(db,avg,stddev);
    return stddev.at<double>(0,0);
}

double eigenvalue::calculate_std_dev_Ag(Mat a, Mat b)
{
    Mat avg,stddev;
    Mat Ag = calculate_Ag(a,b);
    meanStdDev(Ag,avg,stddev);
    return stddev.at<double>(0,0);
}

double eigenvalue::calculate_std_dev_C(Mat a, Mat b)
{
    Mat avg,stddev;
    Mat C = calculate_C(a,b);
    meanStdDev(C,avg,stddev);
    return stddev.at<double>(0,0);
}

double eigenvalue::calculate_std_dev_E(Mat L, Mat a, Mat b)
{
    Mat E,dE,avg,stddev;

    E = (L-avg_L)^2+(a-avg_a)^2+(b-avg_b)^2;
    E.convertTo(dE,CV_32F);
    sqrt(dE,dE);

    meanStdDev(dE,avg,stddev);
    return stddev.at<double>(0,0);
}

double eigenvalue::calculate_std_dev_H(Mat a, Mat b)
{
    Mat da,db;
    a.convertTo(da,CV_32F);
    b.convertTo(db,CV_32F);

    Mat H = (avg_a*avg_a + avg_b*avg_b) - (2*avg_a*da + 2*avg_b*db);
    sqrt(abs(H),H);
    Mat avg,stddev;

    meanStdDev(H,avg,stddev);
    return stddev.at<double>(0,0);
}

double *eigenvalue::get_eigenvalue()
{
    return Eigenvalue;
}

Mat eigenvalue::get_img()
{
    return *Ident_Img;
}
