/********************************************************
* Filename    : HW1_1-2-a.cpp                           *
* Update date : 09/27/2022                              *
* Author      : 顏郁芩                                  *
* Note        : load image and select the correct pixel *
*********************************************************/
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace N;

void MY_HW::HW1_1_2_a() {

    //--------------------------參數---------------------------//

    int H = 256;
    int W = 256;
    //unsigned char img[256*256];
    FILE* input_file;
    char imgpath[100] = ".\\HM1_images_file\\lena256.raw";
    unsigned char* img = new unsigned char[256*256];

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, imgpath, "rb");
    if (!input_file){
        printf("Unable to open the image!\n");
    }
    fread(img, sizeof(unsigned char), (256*256), input_file);

    //--------------------------計算---------------------------//
        
    int row = 123;
    int column = 234;
    int pixel_num = 5044; //第5044個
    int ans_a, ans_b;
    int r, c;

    //--------------------------(1)---------------------------//

    ans_a = (row) * H + column+1;

    //--------------------------(2)---------------------------//

    ans_b = pixel_num -1;
    r = (pixel_num / 256);
    c = pixel_num % 256-1;

    //--------------------------文字輸出---------------------------------//
    int sel;
    int a = 1;
    cout << "    1:1.2.a.(1):" << endl;
    cout << "    2:1.2.a.(2):" << endl;
    cout << "    0:exit" << endl;
    while (a == 1) {
        cout << "    Enter the question number to select output result:" << endl;
        cin >> sel;
        if(sel == 0)
            a = 0;
        else if (sel == 1) {
            cout << endl;
            cout << "    1.2.a.(1):" << endl;
            cout << "        123th row and 234th column's coordinate pixel's value is = " << +img[ans_a] << endl<<endl;
        }
        else if (sel == 2) {
            cout << endl;
            cout << "    1.2.a.(2):" << endl;
            cout << "        5043th pixel's value is = "<< +img[ans_b] << endl;
            cout << "        pixel coordinate is = row:" << r<<"th, column : "<< c << "th" << endl<<endl;
        }
        else {
            cout << "    The question isn't exit"<< endl<<endl;
        }


    }

    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);
}