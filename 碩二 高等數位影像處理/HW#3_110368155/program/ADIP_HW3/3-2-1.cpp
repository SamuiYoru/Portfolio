/***********************************************
* Filename    : 3-2-1.cpp                      *
* Update date : 28/10/2022                     *
* Author      : 顏郁芩                         *
* Note        : Power-Law transformation       *
***********************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
//#include<math.h>
using namespace std;
using namespace W;

void MY_HW3::HW3_2_1() {
    //--------------------------參數---------------------------//
    int H = 800;
    int W = 600;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2, * input_file3;
    FILE* output_file, * output_file2, * output_file3, * output_file1_2, * output_file2_2, * output_file3_2;
    char in_imgpath[] = ".\\HW3_images_file\\meerkat_dark_800x600.raw";
    char in_imgpath2[] = ".\\HW3_images_file\\meerkat_bright_800x600.raw";
    char in_imgpath3[] = ".\\HW3_images_file\\meerkat_high_contrast_800x600.raw";
    char out_imgpath[] = ".\\meerkat_dark_800x600_Power-Law_R=1.1.raw";
    char out_imgpath2[] = ".\\meerkat_bright_800x600_Power-Law_R=0.9.raw";
    char out_imgpath3[] = ".\\meerkat_high_contrast_800x600_Power-Law_R=0.95.raw";
    char out_imgpath1_2[] = ".\\meerkat_dark_800x600_Power-Law_R=1.125.raw";
    char out_imgpath2_2[] = ".\\meerkat_bright_800x600_Power-Law_R=0.85.raw";
    char out_imgpath3_2[] = ".\\meerkat_high_contrast_800x600_Power-Law_R=0.9.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    unsigned char* img3 = new unsigned char[size];
    unsigned char* img1_2 = new unsigned char[size];
    unsigned char* img2_2 = new unsigned char[size];
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



    //------------------處理 meerkat_dark-----------------------//

    for (int x = 0; x < 800 * 600; x++){
        unsigned char a = img[x];
        img[x] = 1 *pow(a,1.1);
        if (img[x] >= 255) {
            img[x] = 255;
        }
        else if (img[x] <= 0) {
            img[x] = 0;
        }
        else
            img[x] = img[x];
    }
    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img, 1, size, output_file);
    fclose(output_file);
    delete[] img;

    for (int x = 0; x < 800 * 600; x++) {
        unsigned char a = img1_2[x];
        img1_2[x] = 1 * pow(a, 1.125);
        if (img1_2[x] >= 255) {
            img1_2[x] = 255;
        }
        else if (img1_2[x] <= 0) {
            img1_2[x] = 0;
        }
        else
            img1_2[x] = img1_2[x];
    }
    fopen_s(&output_file1_2, out_imgpath1_2, "wb");
    fwrite(img1_2, 1, size, output_file1_2);
    fclose(output_file1_2);
    delete[] img1_2;


    //------------------處理 meerkat_bright-----------------------//
    for (int x = 0; x < 800 * 600; x++) {
        unsigned char b = img2[x];
        img2[x] = 1 * pow(b, 0.9);
        if (img2[x] >= 255) {
            img2[x] = 255;
        }
        else if (img2[x] <= 0) {
            img2[x] = 0;
        }
        else
            img2[x] = img2[x];
    }

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img2, 1, size, output_file2);
    delete[] img2;
    fclose(output_file2);


    for (int x = 0; x < 800 * 600; x++) {
        unsigned char b = img2_2[x];
        img2_2[x] = 1 * pow(b, 0.85);
        if (img2_2[x] >= 255) {
            img2_2[x] = 255;
        }
        else if (img2_2[x] <= 0) {
            img2_2[x] = 0;
        }
        else
            img2_2[x] = img2_2[x];
    }
    fopen_s(&output_file2_2, out_imgpath2_2, "wb");
    fwrite(img2_2, 1, size, output_file2_2);
    delete[] img2_2;
    fclose(output_file2_2);



    //------------------處理 meerkat_high_contrast-----------------------//

    for (int x = 0; x < 800 * 600; x++) {
        unsigned char c = img3[x];
        img3[x] = 1 * pow(c, 0.95);
        if (img3[x] >= 255) {
            img3[x] = 255;
        }
        else if (img3[x] <= 0) {
            img3[x] = 0;
        }
        else
            img3[x] = img3[x];
    }


    fopen_s(&output_file3, out_imgpath3, "wb");
    fwrite(img3, 1, size, output_file3);
    fclose(output_file3);
    delete[] img3;



    for (int x = 0; x < 800 * 600; x++) {
        unsigned char c = img3_2[x];
        img3_2[x] = 1 * pow(c, 0.9);
        if (img3_2[x] >= 255) {
            img3_2[x] = 255;
        }
        else if (img3_2[x] <= 0) {
            img3_2[x] = 0;
        }
        else
            img3_2[x] = img3_2[x];
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