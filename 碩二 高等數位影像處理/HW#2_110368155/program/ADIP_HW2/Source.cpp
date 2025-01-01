/****************************************************
* Filename    : source.cpp                          *
* Update date : 16/10/2022                          *
* Author      : ÃC­§ÍÁ                              *
* Note        : HW2 main program                    *
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"

using namespace W;
using namespace std;

int main() {
	MY_HW2 HW2;
    int sel;
    int flag = 0;
    cout << "0:exit" << endl;
    cout << "1:2_1_(2)" << endl;
    cout << "2:2_2_(1)" << endl;
    cout << "3:2_2_(2)" << endl;
    cout << "4:2_2_(3)" << endl;
    cout << "5:2_3" << endl;
    cout << "6:2_4" << endl;
    while (flag == 0) {
        cout << "Enter the question number :" << endl;
        cin >> sel;
        if (sel == 0)
            flag = 1;
        else if (sel == 1) {
            cout << "2_1_(2)  count MSE and PSNR between blurred images and original:" << endl;
            float a, b;
            int H = 256;
            int W = 256;
            char in_imgpath[] = ".\\HW2_images_file\\lena256.raw";
            char in_imgpath1[] = ".\\HW2_images_file\\lena256_blur_5.raw";
            char in_imgpath2[] = ".\\HW2_images_file\\lena256_blur_20.raw";
            char in_imgpath3[] = ".\\HW2_images_file\\lena256_blur_40.raw";


            a = HW2.MSE(H, W, in_imgpath, in_imgpath1);
            b = HW2.PSNR(H, W, in_imgpath, in_imgpath1);
            cout << "MSE5=" << a << endl;
            cout << "PSNR5=" << b << endl;
            a = HW2.MSE(H, W, in_imgpath, in_imgpath2);
            b = HW2.PSNR(H, W, in_imgpath, in_imgpath2);
            cout << "MSE20=" << a << endl;
            cout << "PSNR20=" << b << endl;
            a = HW2.MSE(H, W, in_imgpath, in_imgpath3);
            b = HW2.PSNR(H, W, in_imgpath, in_imgpath3);
            cout << "MSE40=" << a << endl;
            cout << "PSNR40=" << b << endl;
        }
        else if (sel == 2) {
            cout << "2_2_(1)  Use nearest neighbor and bilinear algorithms to resize lena128.raw(Zoom):" << endl;
            HW2.HW2_2_1(); 
        }
        else if (sel == 3) {
            cout << "2_2_(2)   Use nearest neighbor and bilinear algorithms to resize lena128.raw(Shrink):" << endl;
            HW2.HW2_2_2(); 
        }
        else if (sel == 4) {
            cout << "2_2_(3)  Use bilinear and bicubic algorithms to zoom in part in duck900X660.raw :" << endl;
            HW2.HW2_2_3(); 
        }
        else if (sel == 5) {
            cout << "2_3 Grey level resolution:" << endl;
            HW2.HW2_3(); 
        }
        else if (sel == 6) {
            cout << "2_4: find the path with D4, D8 and Dm distance" << endl;
            cout << "¥¼§¹¦¨" << endl;
            //HW2.HW2_4();
        }
        else {
            cout << "The question isn't exit, please reselect." << endl << endl;
        }
        cout << endl;
    }

    return 0;

}

