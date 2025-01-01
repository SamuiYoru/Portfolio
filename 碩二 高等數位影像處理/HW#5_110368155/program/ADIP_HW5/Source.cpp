/****************************************************
* Filename    : source.cpp                          *
* Update date : /11/2022                          *
* Author      : 顏郁芩                              *
* Note        : HW5 main program                    *
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
    MY_HW5 HW5;
    int sel;
    int flag = 0;
    
    cout << "0:exit" << endl;
    cout << "1:5_1_1" << endl;
    cout << "2:5_1_3" << endl;
    cout << "3:5_1_5" << endl;
    cout << "4:5_2_1" << endl;
    cout << "5:5_2_2" << endl;
    cout << "6:5_3" << endl;
    cout << "7:5_4" << endl;
    while (flag == 0) {
        cout << "Enter the question number :" << endl;
        cin >> sel;
        if (sel == 0)
            flag = 1;
        else if (sel == 1) {
            cout << "5_1_1:Write your own DFT  " << endl;
            HW5.HW5_1_1();
        }
        else if (sel == 2) {
            cout << "5_1_3:Design your own IDFT and compute MSE" << endl;
            cout << "未完成" << endl;
        }
        else if (sel == 3) {
            cout << "5_1_5:Write your own DCT     " << endl;
            cout << "未完成" << endl;
        }
        else if (sel == 4) {
            cout << "5_2_1:Use BUTTERWORTH LPF and HPF filter on raccoon_256 " << endl;
            HW5.HW5_2_1_LPF();
            HW5.HW5_2_1_HPF();
        }
        else if (sel == 5) {
            cout << "5_2_2:Use High-frequency Emphasis Filtering to inprove owl_blur_512.raw " << endl;
            HW5.HW5_2_2();
        }
        else if (sel == 6) {
            cout << "5_3:water marked the image in spatial and frequency domain " << endl;
            HW5.HW5_3();
        }
        else if (sel == 7) {
            cout << "5_4:apply homomorphic filtering filter to house_512.raw " << endl;
            HW5.HW5_4();
        }
        else {
            cout << "The question isn't exit, please reselect." << endl << endl;
        }
        cout << endl;
    }
    


    
   return 0;


}
