/****************************************************
* Filename    : source.cpp                          *
* Update date : 09/27/2022                          *
* Author      : ÃC­§ÍÁ                              *
* Note        : HW1 main program                    *
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"

using namespace N;
using namespace std;

int main() {
	MY_HW HW;
    int sel;
    int flag = 0;
    cout << "0:exit" << endl;
    cout << "1:1_1_2_a" << endl;
    cout << "2:1_1_2_b" << endl;
    cout << "3:1_1_2_c" << endl;
    cout << "4:1_1_2_d" << endl;
    cout << "5:1_1_2_e" << endl;
    cout << "6:1_1_3_a" << endl;
    cout << "7:1_2" << endl;
    while (flag == 0) {
        cout << "Enter the question number :" << endl;
        cin >> sel;
        if (sel == 0)
            flag = 1;
        else if (sel == 1) {
            cout << "1_1_2_a  load image and select the correct pixel:" << endl;
            HW.HW1_1_2_a();
        }
        else if (sel == 2) {
            cout << "1_1_2_b  load image then save another new image:" << endl;
            HW.HW1_1_2_b();
        }
        else if (sel == 3) {
            cout << "1_1_2_c  horizontal flip and rotate part of the image:" << endl;
            HW.HW1_1_2_c();
        }
        else if (sel == 4) {
            cout << "1_1_2_d  cut image into horizontal(virtically) stripe and shift randomly:" << endl;
            HW.HW1_1_2_d();
        }
        else if (sel == 5) {
            cout << "1_1_2_e  reorganization the  five images:" << endl;
            HW.HW1_1_2_e();
        }
        else if (sel == 6) {
            cout << "1_1_3_a adding value 45 (or random) to each pixel of the picture:" << endl;
            HW.HW1_1_3_a();
        }
        else if (sel == 7) {
            cout << "1_2  open the image with opencv and add text:" << endl;
            HW.HW1_2();
        }
        else {
            cout << "The question isn't exit, please reselect." << endl << endl;
        }
        cout << endl;
    }

    return 0;
}
