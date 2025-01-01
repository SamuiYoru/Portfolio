/****************************************************
* Filename    : source.cpp                          *
* Update date : 28/10/2022                          *
* Author      : ÃC­§ÍÁ                              *
* Note        : HW3 main program                    *
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
	MY_HW3 HW3;
    int sel;
    int flag = 0;

    cout << "0:exit" << endl;
    cout << "1:3_1" << endl;
    cout << "2:3_2_(1)" << endl;
    cout << "3:3_2_(2)" << endl;
    cout << "4:3_3_(1)" << endl;
    cout << "5:3_3_(2)" << endl;
    cout << "6:3_3_(3)" << endl;
        while (flag == 0) {
            cout << "Enter the question number :" << endl;
            cin >> sel;
            if (sel == 0)
                flag = 1;
            else if (sel == 1) {
                cout << "3_1  watermark the picture with bit plane slizing:" << endl;
                HW3.HW3_1();
            }
            else if (sel == 2) {
                cout << "3_2_(1) Power-Law transformation:" << endl;
                HW3.HW3_2_1();
            }
            else if (sel == 3) {
                cout << "3_2_(2) Piecewise-Linear transformation :" << endl;
                HW3.HW3_2_2();
            }
            else if (sel == 4) {
                cout << "3_3_(1) Plot histograms of the picture:" << endl;
                HW3.HW3_3_1();
            }
            else if (sel == 5) {
                cout << "3_3_(2) Apply histogram equalization:" << endl;
                HW3.HW3_3_2();
            }
            else if (sel == 6) {
                cout << "3_3_(3) Histogram matching:" << endl;
                HW3.HW3_3_3();
            }
            else {
                cout << "The question isn't exit, please reselect." << endl << endl;
            }
            cout << endl;
        }



        return 0;


}