/*****************************************************
* Filename    : Header.h                             *
* Update date : 16/10/2022                           *
* Author      : ÃC­§ÍÁ                               *
* Note        : header for HW2                       *
*****************************************************/

//#ifndef HEADER_H // include guard
//#define HEADER_H


#pragma once

namespace W
{
    class MY_HW2
    {
    public:
        //void HW1_1_2_a();
        float MSE(int H, int W, char in_imgpath[], char in_imgpath2[]);
        float PSNR(int H, int W, char in_imgpath[], char in_imgpath2[]);
        float bilnear(double a, double a_value, double b, double b_value, double c);
        void HW2_2_1();
        void HW2_2_2();
        void HW2_2_3();
        void HW2_3();
        void HW2_4();
    };

}

//#endif /* HEADER_H */

