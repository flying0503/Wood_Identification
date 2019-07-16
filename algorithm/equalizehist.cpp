#include "algorithm/equalizehist.h"

void Equalizehist(Mat src,Mat &output)
{
    Mat dst, dst1;
    //ת���ɻҶ�ͼ��ʹԭͼ��Ϊ��ͨ��ͼ��
    if(src.type()==0)
        dst = src;
    else
    cvtColor(src, dst, COLOR_BGR2GRAY);

    //ֱ��ͼ���⻯
    equalizeHist(dst, dst1);
    output = dst1;
}

void Adj_Img(Mat input, Mat &output,adj_img AI)
{
    if(input.type() == 0)
    {
        output = AI.contrast*input;
        output = output + AI.brightness;
    }else {
        cvtColor(input,output,COLOR_BGR2GRAY);
        output = AI.contrast*output;
        output = output + AI.brightness;
    }
}
