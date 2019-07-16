#include "algorithm/split_rgb.h"

void Split_RGB(Mat img,Mat &Red,Mat &Green,Mat &Blue,bool show_img)
{
    Mat channel[3];
    split(img,channel);

    Red = channel[2];
    Green = channel[1];
    Blue = channel[0];

    if(show_img)
    {
        imshow("B",channel[0]);
        imshow("G",channel[1]);
        imshow("R",channel[2]);
    }
}

void Merge_RGB(Mat Red,Mat Green,Mat Blue,Mat &Color)
{
    Mat channel[3];
    channel[2] = Red;
    channel[1] = Green;
    channel[0] = Blue;
    merge(channel,3,Color);
}
