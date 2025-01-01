/******************************************************
* Filename    : 3-2-2.cpp                             *
* Update date : 28/10/2022                            *
* Author      : 顏郁芩                                *
* Note        : Piecewise-Linear transformation       *
******************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;

void MY_HW3::HW3_2_2() {
    //--------------------------參數---------------------------//
    int H = 800;
    int W = 600;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2, * input_file3;
    FILE* output_file, * output_file2, * output_file3, * output_file1_2, * output_file2_2, * output_file3_2;
    char in_imgpath[] = ".\\HW3_images_file\\meerkat_dark_800x600.raw";
    char in_imgpath2[] = ".\\HW3_images_file\\meerkat_bright_800x600.raw";
    char in_imgpath3[] = ".\\HW3_images_file\\meerkat_high_contrast_800x600.raw";
    char out_imgpath[] = ".\\meerkat_dark_800x600_Piecewise-Linear.raw";
    char out_imgpath2[] = ".\\meerkat_bright_800x600_Piecewise-Linear.raw";
    char out_imgpath3[] = ".\\meerkat_high_contrast_800x600_Piecewise-Linear.raw";
    char out_imgpath1_2[] = ".\\meerkat_dark_800x600_Piecewise-Linear_2.raw";
    char out_imgpath2_2[] = ".\\meerkat_bright_800x600_Piecewise-Linear_2.raw";
    char out_imgpath3_2[] = ".\\meerkat_high_contrast_800x600_Piecewise-Linear_2.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img1_2 = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    unsigned char* img2_2 = new unsigned char[size];
    unsigned char* img3 = new unsigned char[size];
    unsigned char* img3_2 = new unsigned char[size];
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image meerkat_dark_800x600.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);
    fopen_s(&input_file, in_imgpath, "rb");
    fread(img1_2, sizeof(unsigned char), size, input_file);

    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image meerkat_bright_800x600.raw!\n");
    }
    fread(img2, sizeof(unsigned char), size, input_file2);
    fopen_s(&input_file2, in_imgpath2, "rb");
    fread(img2_2, sizeof(unsigned char), size, input_file2);

    fopen_s(&input_file3, in_imgpath3, "rb");
    if (!input_file3) {
        printf("Unable to open the image meerkat_high_contrast_800x600.raw!\n");
    }
    fread(img3, sizeof(unsigned char), size, input_file3);
    fopen_s(&input_file3, in_imgpath3, "rb");
    fread(img3_2, sizeof(unsigned char), size, input_file3);


    //-------------處理-------------------//

    for (int x = 0; x < 800 * 600; x++) {//dark
        double a = img[x];
        double b = 0;
        b = a / 255;
        if (b >= 0.6) {
            a = (b /0.4)* 0.2*255;
        }
        else {
            a = (b / 0.6) * 0.8*255;
        }

        if (a >= 255) {
            a = 255;
        }
        else if (a <= 0) {
            a = 0;
        }
        else {
            a = a;
        }

        img[x] = a;
    }

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img, 1, size, output_file);
    fclose(output_file);
    delete[] img;

    for (int x = 0; x < 800 * 600; x++) {//dark
        double a = img1_2[x];
        double b = 0;
        b = a / 255;
        if (b >= 0.6) {
            a = (b / 0.4) * 0.2 * 255;
        }
        else if (b <= 0.1) {
            a = (b / 0.1) * 0.3 * 255;
        }
        else {
            a = (b / 0.5) * 0.5 * 255 + 255 * 0.2;
        }

        if (a >= 255) {
            a = 255;
        }
        else if (a <= 0) {
            a = 0;
        }
        else {
            a = a;
        }

        img1_2[x] = a;
    }

    fopen_s(&output_file1_2, out_imgpath1_2, "wb");
    fwrite(img1_2, 1, size, output_file1_2);
    fclose(output_file1_2);
    delete[] img1_2;


    for (int x = 0; x < 800 * 600; x++) {//bright
        double a = img2[x];
        double b = 0;
        b = a / 255;
        if (b >= 0.95) {
            a = (b / 0.05) * 0.3 * 255;
        }
        else {
            a = (b / 0.95) * 0.7 * 255;
        }

        if (a >= 255) {
            a = 255;
        }
        else if (a <= 0) {
            a = 0;
        }
        else {
            a = a;
        }
        img2[x] = a;
    }

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img2, 1, size, output_file2);
    fclose(output_file2);
    delete[] img2;

    for (int x = 0; x < 800 * 600; x++) {//bright
        double a = img2_2[x];
        double b = 0;
        b = a / 255;
        if (b >= 0.95) {
            a = (b / 0.05) * 0.3 * 255;
        }
        else if (b <= 0.8) {
            a = (b / 0.8) * 0.4 * 255;
        }
        else {
            a = (b / 0.15) * 0.3 * 255 - 255 * 1.2;
        }

        if (a >= 255) {
            a = 255;
        }
        else if (a <= 0) {
            a = 0;
        }
        else {
            a = a;
        }
        img2_2[x] = a;
    }

    fopen_s(&output_file2_2, out_imgpath2_2, "wb");
    fwrite(img2_2, 1, size, output_file2_2);
    fclose(output_file2_2);
    delete[] img2_2;


    for (int x = 0; x < 800 * 600; x++) {//high_contrast
        double a = img3[x];
        double b = 0;
        b = a / 255;
        if (b <= 0.1) {
            a = (b / 0.1) * 0.2 * 255;
        }
        else if (b >= 0.9) {
            a = (b / 0.1) * 0.2 * 255;
        }
        else {
            a = (b / 0.8) * 0.6 * 255+0.125*255;
        }

        if (a >= 255) {
            a = 255;
        }
        else if (a <= 0) {
            a = 0;
        }
        else {
            a = a;
        }
        img3[x] = a;
    }

    fopen_s(&output_file3, out_imgpath3, "wb");
    fwrite(img3, 1, size, output_file3);
    fclose(output_file3);
    delete[] img3;

    for (int x = 0; x < 800 * 600; x++) {//high_contrast
        double a = img3_2[x];
        double b = 0;
        b = a / 255;
        if (b <= 0.1) {
            a = (b / 0.1) * 0.3 * 255;
        }
        else if(b>=0.9) {
            a = (b / 0.1) * 0.3 * 255;
        }
        else {
            a = (b / 0.8) * 0.4 * 255 + 0.25 * 255;
        }

        if (a >= 255) {
            a = 255;
        }
        else if (a <= 0) {
            a = 0;
        }
        else {
            a = a;
        }
        img3_2[x] = a;
    }

    fopen_s(&output_file3_2, out_imgpath3_2, "wb");
    fwrite(img3_2, 1, size, output_file3_2);
    fclose(output_file3_2);
    delete[] img3_2;

    //--------------------------釋出記憶體---------------------------//

    fclose(input_file);
    fclose(input_file2);
    fclose(input_file3);


}