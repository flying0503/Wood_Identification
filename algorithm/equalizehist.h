#ifndef EQUALIZEHIST_H
#define EQUALIZEHIST_H
#include <opencv2/opencv.hpp>

using namespace cv;

typedef struct Adjust_image
{
    bool auto_adj;
    double contrast;
    unsigned char brightness;

}adj_img;


void Equalizehist(Mat src,Mat &output);

void Adj_Img(Mat input, Mat &output,adj_img AI);


#endif // EQUALIZEHIST_H
