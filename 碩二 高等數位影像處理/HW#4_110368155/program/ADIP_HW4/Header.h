/*****************************************************
* Filename    : Header.h                             *
* Update date : /11/2022                           *
* Author      : ÃC­§ÍÁ                               *
* Note        : header for HW4                       *
*****************************************************/
#pragma once

namespace W
{
    class MY_HW4
    {
    public:
        //void HW1_1_2_a();

        unsigned char convolution3X3(int a[], int b[]);
        unsigned char convolution(int a, int b, unsigned char img[640 + 2][427 + 2], int filter[9]);
        unsigned char convolution256(int a, int b, unsigned char img[256 + 2][256 + 2], double filter[9]);
        unsigned char convolution5X5_256(int a, int b, unsigned char img[256 + 4][256 + 4], double filter[25]);
        unsigned char convolution5X5_mean(int a, int b, unsigned char img[256 + 4][256 + 4]);
        unsigned char convolution5X5_mean2(int a, int b, unsigned char img[720 + 4][790 + 4]);
        unsigned char median_filter5x5(int a, int b, unsigned char img[720 + 4][790 + 4]);
        unsigned char median_filter3x3(int a, int b, unsigned char img[720 + 4][790 + 4]);
        unsigned char convolution256_720(int a, int b, unsigned char img[720 + 4][790 + 4], double filter[9]);
        unsigned char histogram3(int a, int b, unsigned char img[512 + 6][683 + 6]);
        unsigned char hq5(int a, int b, unsigned char img[512 + 6][683 + 6]);
        unsigned char h7(int a, int b, unsigned char img[512 + 6][683 + 6]);


        void HW4_1_1_1();
        void HW4_1_1_2();
        void HW4_1_2_1();
        void HW4_1_2_2();
        void HW4_1_2_COMBINE();
        void HW4_2_1();
        void HW4_2_2();
        void HW4_2_3();
        void HW4_3();

    };

}
