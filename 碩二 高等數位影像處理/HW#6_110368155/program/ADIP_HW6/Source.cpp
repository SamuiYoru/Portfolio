/****************************************************
* Filename    : source.cpp                          *
* Update date : /12/2022                          *
* Author      : ÃC­§ÍÁ                              *
* Note        : HW6 main program                    *
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
    MY_HW6 HW6;
    int sel;
    int flag = 0;

    cout << "0:exit" << endl;
    cout << "1:6_1" << endl;
    cout << "2:6_2" << endl;
    cout << "3:6_3" << endl;
    cout << "4:6_4" << endl;
    while (flag == 0) {
       cout << "Enter the question number :" << endl;
        cin >> sel;
        if (sel == 0)
            flag = 1;
        else if (sel == 1) {
            cout << "Binary image Morphology " << endl;
            HW6.HW6_1();
        }
        else if (sel == 2) {
            cout << "Greyscale image Morphology   " << endl;
            HW6.HW6_2();
        }
        else if (sel == 3) {
            cout << "Trimap " << endl;
            HW6.HW6_3();
        }
        else if (sel == 4) {
            cout << "Road map" << endl;
            HW6.HW6_4();
        }
        else {
            cout << "The question isn't exit, please reselect." << endl << endl;
        }
        cout << endl;
    }






    return 0;


}