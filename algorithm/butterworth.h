#ifndef BUTTERWORTH_H
#define BUTTERWORTH_H

#include <opencv2/opencv.hpp>

using namespace cv;

void shiftDFT(Mat &fImage )
{
    Mat tmp, q0, q1, q2, q3;

    // first crop the image, if it has an odd number of rows or columns

    fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));

    int cx = fImage.cols / 2;
    int cy = fImage.rows / 2;

    // rearrange the quadrants of Fourier image
    // so that the origin is at the image center

    q0 = fImage(Rect(0, 0, cx, cy));
    q1 = fImage(Rect(cx, 0, cx, cy));
    q2 = fImage(Rect(0, cy, cx, cy));
    q3 = fImage(Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

Mat create_spectrum_magnitude_display(Mat &complexImg, bool rearrange)
{
    Mat planes[2];

    // compute magnitude spectrum (N.B. for display)
    // compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))

    split(complexImg, planes);
    magnitude(planes[0], planes[1], planes[0]);

    Mat mag = (planes[0]).clone();
    mag += Scalar::all(1);
    log(mag, mag);

    if (rearrange)
    {
        // re-arrange the quaderants
        shiftDFT(mag);
    }

    normalize(mag, mag, 0, 1, NORM_MINMAX);

    return mag;

}

//����Ҷ�任
Mat Fourier_Tran(Mat input)
{
    //ȷ������Ϊ�Ҷ�ͼ
    if(input.type() == 0)
        ;
    else
        cvtColor(input, input, COLOR_BGR2GRAY);
    //����ͼ����ٸ���Ҷ�任
    int M = getOptimalDFTSize(input.rows);
    int N = getOptimalDFTSize(input.cols);
    Mat padded;
    copyMakeBorder(input, padded, 0, M - input.rows, 0, N - input.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexImg;
    merge(planes, 2, complexImg);

    dft(complexImg, complexImg);

    return complexImg;
}

//����Ҷ��任
Mat IFourier_Tran(Mat complexImg)
{
    //����Ҷ��任
    Mat invDFT, invDFTcvt;
    idft(complexImg, invDFT, DFT_SCALE | DFT_REAL_OUTPUT); // Ӧ�ñ任�� Applying IDFT
    invDFT.convertTo(invDFTcvt, CV_8U);
    return  invDFTcvt;
}

//n��ʾ������˹�˲����Ľ���,D0��ʾ�˲��뾶
Mat Butterworth_Low_Paass_Filter(Mat src,int n,double D0,bool show_img)
{
    Mat img;
    if(src.type()==0)
        img = src;
    else
        cvtColor(src, img, COLOR_BGR2GRAY);
    if(show_img)
    imshow("�Ҷ�ͼ", img);

    //����Ҷ�任
    Mat complexImg = Fourier_Tran(img);

    //��ʾƵ��
    Mat Spectrogram = create_spectrum_magnitude_display(complexImg,true);
    if(show_img)
    imshow("����ҶƵ��",Spectrogram);

    //������˹�˲�
    Mat mag = complexImg;
    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

    int cx = mag.cols / 2;
    int cy = mag.rows / 2;

    Mat tmp;
    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    //H = 1 / (1+(D/D0)^2n)
    for (int y = 0; y < mag.rows; y++){
        double* data = mag.ptr<double>(y);
        for (int x = 0; x < mag.cols; x++){
            //cout << data[x] << endl;
            double d = sqrt(pow((y - cy), 2) + pow((x - cx), 2));
            //cout << d << endl;
            double h = 1.0 / (1 + pow(d / D0, 2 * n));
            if (h <= 0.5){
                data[x] = 0;
            }
            else{
                //data[x] = data[x]*0.5;
                //cout << h << endl;
            }

            //cout << data[x] << endl;
        }
    }
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    Mat invDFTcvt = IFourier_Tran(complexImg);

    if(show_img)
    imshow("������˹��ͨ�˲���", invDFTcvt);

    return invDFTcvt;
}
#endif // BUTTERWORTH_H
