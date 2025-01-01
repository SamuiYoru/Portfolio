/***********************************************
* Filename    : 1.cpp                          *
* Update date : 16/10/2022                     *
* Author      : 顏郁芩                         *
* Note        : count  MSE and PSNR            *
***********************************************/


#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;

float MY_HW2::MSE(int H,int W, char in_imgpath[], char in_imgpath2[]) {

    //--------------------------參數---------------------------//
    
    FILE* input_file, * input_file2;
    int size = H * W;
    unsigned char* img1 = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
   
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image1!\n");
    }
    fread(img1, sizeof(unsigned char), size, input_file);
    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image2!\n");
    }
    fread(img2, sizeof(unsigned char), size, input_file2);

    //--------------------------計算---------------------------//

    float sum = 0;
    float MSE = 0;
    for (int i = 0; i < size; i++) {
        sum = sum+ ((img1[i] - img2[i])* (img1[i] - img2[i]));
    }
    MSE = sum / size;

    //--------------------------釋出記憶體---------------------------//
    delete[] img1;
    delete[] img2;
    fclose(input_file);
    fclose(input_file2);

    return MSE;
}


float MY_HW2::PSNR(int H, int W, char in_imgpath[], char in_imgpath2[]) {
    float PSNR;
    //--------------------------參數---------------------------//

    FILE* input_file, * input_file2;
    int size = H * W;
    unsigned char* img1 = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image1!\n");
    }
    fread(img1, sizeof(unsigned char), size, input_file);
    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image2!\n");
    }
    fread(img2, sizeof(unsigned char), size, input_file2);

    //--------------------------計算---------------------------//

    PSNR = 10 * log10(255 * 255 / MSE(H, W, in_imgpath, in_imgpath2));

    //--------------------------釋出記憶體---------------------------//
    delete[] img1;
    delete[] img2;
    fclose(input_file);
    fclose(input_file2);

    return PSNR;
}

