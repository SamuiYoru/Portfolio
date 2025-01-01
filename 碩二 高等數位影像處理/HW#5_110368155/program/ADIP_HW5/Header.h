/*****************************************************
* Filename    : Header.h                             *
* Update date : /11/2022                             *
* Author      : ÃC­§ÍÁ                               *
* Note        : header for HW5                       *
*****************************************************/
#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/core.hpp"

namespace W
{
    class MY_HW5
    {
    public:
        void DFT128(unsigned char img_input[128][128], unsigned char DFTvalue[128][128]);
        void DFT256(unsigned char img_input[256][256], unsigned char DFTvalue[256][256]);


        //void DFT512();


        void HW5_1_1();
        void HW5_1_3();
        void HW5_2_1_LPF();
        void HW5_2_1_HPF();
        void HW5_2_2();
        //void HW5_2_2_other();
        void HW5_3();
        void HW5_4();

    };

}