#ifndef SPLIT_RGB_H
#define SPLIT_RGB_H

#include <opencv2/opencv.hpp>

using namespace cv;

void Split_RGB(Mat img,Mat &Red,Mat &Green,Mat &Blue,bool show_img);

void Merge_RGB(Mat Red,Mat Green,Mat Blue,Mat &Color);
#endif // SPLIT_RGB_H
