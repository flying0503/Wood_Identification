#include "process/process.h"

double calculate_19_value_R(double Img[19],double mode_template[19])
{
    double middle[19];
    double sum = 0;
    for (int i = 0;i < 19;i++) {
        middle[i] = mode_template[i]-Img[i];
        middle[i] = middle[i]*middle[i];
        sum += middle[i];
    }
    return sqrt(sum);
}

bool judgment(double R,double R_Max)
{
    if(R_Max<0)
        throw "R_Max must be over zero";

    if(R>R_Max)
        return false;
    else
        return true;
}
