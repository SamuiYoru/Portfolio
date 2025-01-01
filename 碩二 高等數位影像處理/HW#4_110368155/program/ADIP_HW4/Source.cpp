/****************************************************
* Filename    : source.cpp                          *
* Update date : 12/11/2022                          *
* Author      : ÃC­§ÍÁ                              *
* Note        : HW4 main program                    *
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
    MY_HW4 HW4;
    int sel;
    int flag = 0;

    cout << "0:exit" << endl;
    cout << "1:4_1_1" << endl;
    cout << "2:4_1_2" << endl;
    cout << "3:4_2_1" << endl;
    cout << "4:4_2_2" << endl;
    cout << "5:4_2_3" << endl;
    cout << "6:4_3" << endl;
    while (flag == 0) {
        cout << "Enter the question number :" << endl;
        cin >> sel;
        if (sel == 0)
            flag = 1;
        else if (sel == 1) {
            cout << "roof_640x427 and roof_640x427_noise edge detection with laplacian filter" << endl;
            HW4.HW4_1_1_1();
            HW4.HW4_1_1_2();
        }
        else if (sel == 2) {
            cout << "roof_640x427 and roof_640x427_noise edge detection with sobel filter" << endl;
            HW4.HW4_1_2_1();
            HW4.HW4_1_2_2();
            HW4.HW4_1_2_COMBINE();
        }
        else if (sel == 3) {
            cout << "block&white_256 and chessboard_256 with 5x5 mean filter" << endl;
            HW4.HW4_2_1();
        }
        else if (sel == 4) {
            cout << "apply gaussian filters on baboon_256 with different sigma" << endl;
            HW4.HW4_2_2();
        }
        else if (sel == 5) {
            cout << "improve house_blur_noise" << endl;
            HW4.HW4_2_3();
        }
        else if (sel == 6) {
            cout << "appply local histogram equation on tsukuba_683x512" << endl;
            HW4.HW4_3();
        }
        else {
            cout << "The question isn't exit, please reselect." << endl << endl;
        }
        cout << endl;
    }

    return 0;


}