/*********************************************************************
* Filename    : 3-1.cpp                                              *
* Update date : 28/10/2022                                           *
* Author      : 顏郁芩                                               *
* Note        : watermark the picture with bit plane slizing         *
*********************************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace W;
using namespace cv;

//-------------利用OPENCV改變影像大小+讀取png--------------//
void opencv_resize(unsigned char IMG[384][512]) {
    Mat image = imread("C:\\Users\\User\\source\\repos\\ADIP_HW3\\ADIP_HW3\\HW3_images_file\\JackieChen_opencv.png",IMREAD_GRAYSCALE);
    Mat resized_down, BINARY;
    //resize down
    resize(image, resized_down, Size(512, 384), INTER_LINEAR);
    int c = 0;

    for (int x = 0; x < 384; x++) {
        for (int y = 0; y < 512; y++) {
            if (resized_down.data[c] == NULL) {
                IMG[x][y] = 0;
            }
            else {
                IMG[x][y] = resized_down.data[c];
            }
            c++;
        }
    }     
    imwrite("C:\\Users\\User\\source\\repos\\ADIP_HW3\\ADIP_HW3\\HW3_images_file\\JackieChen_opencv_resize.png", resized_down);
}

void MY_HW3::HW3_1() {

    unsigned char img2[384][512];
    opencv_resize(img2);

    //--------------------------參數---------------------------//
    int H = 512;
    int W = 512;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2;
    FILE* output_file, * output_file2, * output_file3, * output_file4, * output_file5, * output_file6, * output_file7, * output_file8, * output_file9, * output_file10;
    char in_imgpath[] = ".\\HW3_images_file\\cat_512.raw";
    char out_imgpath[] = ".\\cat_512_watermark.raw"; 
    char out_imgpath2[] = ".\\cat_512_watermark_spilt_1(watermark_check).raw";
    char out_imgpath3[] = ".\\cat_512_watermark_original.raw";
    char out_imgpath4[] = ".\\cat_512_watermark_spilt_2.raw";
    char out_imgpath5[] = ".\\cat_512_watermark_spilt_3.raw";
    char out_imgpath6[] = ".\\cat_512_watermark_spilt_4.raw";
    char out_imgpath7[] = ".\\cat_512_watermark_spilt_5.raw";
    char out_imgpath8[] = ".\\cat_512_watermark_spilt_6.raw";
    char out_imgpath9[] = ".\\cat_512_watermark_spilt_7.raw";
    char out_imgpath10[] = ".\\cat_512_watermark_spilt_8.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char img_watermark[512][512];
    unsigned char img_back[512][512];


    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image cat_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), 512*512, input_file);

    //---------TEST------------------//
    
    /*int a = 0, b = 0;
    int empty = 0;
    for (int x = 0; x < 384; x++) {
        for (int y = 0; y < 512; y++) {
            //cout << +img2[x][y] << " "; 
            if (+img2[x][y] != NULL) {
                a = a + 1;
            }
            else {
                empty++;
            }
            
        }
        b = b + 1;
        //cout << endl;
    }
    cout << "y=" << a << "x=" << b << endl;
    cout << empty << endl;*/
    //-------------------浮水印處理------------------//

    int c = 0;
    int imgx = 0, imgy = 0;
    imgx = 0;
    for (int x = 0; x < 512; x++) {
        imgy = 0;
        for (int y = 0; y < 512; y++) {
            if (x<448&&x>=64) {
                if (img2[x-64][y] >= 200) {
                    img_watermark[x][y] = (img[c] / 2) * 2 + 1;
                }
                else {//img_2[x][y] == 0
                    img_watermark[x][y] = (img[c] / 2) * 2;
                }       
            }
            else {
                img_watermark[x][y] = (img[c] / 2) * 2 + 1;
            }
            c++;
            }
        imgx++;
    }
   //-------------------bit plane slizing------------------//
   
    //第1BIT 最後一個bit
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            if (img_watermark[x][y] % 2 == 1) {
                img_back[x][y] = 255;
            }
            else {//img_watermark[x][y] % 2==0
                img_back[x][y] = 0;
            }
        }
    }
    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img_back, 1, size, output_file2);
    fclose(output_file2);

    //第2BIT 
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            unsigned char ia= img_watermark[x][y] % 4 ;
            if (ia / 2 == 1) {
                img_back[x][y] = 255;
            }
            else {
                img_back[x][y] = 0;
            }
        }
    }
    fopen_s(&output_file4, out_imgpath4, "wb");
    fwrite(img_back, 1, size, output_file4);
    fclose(output_file4);

    //第3BIT 
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            unsigned char ia = img_watermark[x][y] % 8;
            if (ia / 4 == 1) {
                img_back[x][y] = 255;
            }
            else {
                img_back[x][y] = 0;
            }
        }
    }
    fopen_s(&output_file5, out_imgpath5, "wb");
    fwrite(img_back, 1, size, output_file5);
    fclose(output_file5);

    //第4BIT 
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            unsigned char ia = img_watermark[x][y] % 16;
            if (ia / 8 == 1) {
                img_back[x][y] = 255;
            }
            else {
                img_back[x][y] = 0;
            }
        }
    }
    fopen_s(&output_file6, out_imgpath6, "wb");
    fwrite(img_back, 1, size, output_file6);
    fclose(output_file6);

    //第5BIT 
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            unsigned char ia = img_watermark[x][y] % 32;
            if (ia / 16 == 1) {
                img_back[x][y] = 255;
            }
            else {
                img_back[x][y] = 0;
            }
        }
    }
    fopen_s(&output_file7, out_imgpath7, "wb");
    fwrite(img_back, 1, size, output_file7);
    fclose(output_file7);

    //第6BIT 
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            unsigned char ia = img_watermark[x][y] % 64;
            if (ia / 32 == 1) {
                img_back[x][y] = 255;
            }
            else {
                img_back[x][y] = 0;
            }
        }
    }
    fopen_s(&output_file8, out_imgpath8, "wb");
    fwrite(img_back, 1, size, output_file8);
    fclose(output_file8);

    //第7BIT 
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            unsigned char ia = img_watermark[x][y] % 128;
            if (ia / 64 == 1) {
                img_back[x][y] = 255;
            }
            else {
                img_back[x][y] = 0;
            }
        }
    }
    fopen_s(&output_file9, out_imgpath9, "wb");
    fwrite(img_back, 1, size, output_file9);
    fclose(output_file9);

    //第8BIT 
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            unsigned char ia = img_watermark[x][y] % 256;
            if (ia / 128 == 1) {
                img_back[x][y] = 255;
            }
            else {//img_watermark[x][y] % 2==0
                img_back[x][y] = 0;
            }
        }
    }
    fopen_s(&output_file10, out_imgpath10, "wb");
    fwrite(img_back, 1, size, output_file10);
    fclose(output_file10);


    //--------------------------輸出檔案---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img_watermark, 1, size, output_file);

    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(output_file);

}

