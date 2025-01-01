/********************************************************************************
* Filename    : 4_2_2.cpp                                                       *
* Update date : 12/11/2022                                                      *
* Author      : 顏郁芩                                                          *
* Note        : apply gaussian filters on baboon_256 with different sigma       *
********************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
using namespace W;

void MY_HW4::HW4_2_2() {
    //--------------------------參數---------------------------//
    int H = 256;
    int W = 256;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file, * output_file2, * output_file3, * output_file4, * output_file5, * output_file6;
    char in_imgpath[] = ".\\HW4_images_file\\baboon_256.raw";
    char out_imgpath[] = "baboon_256_after_filter3x3_1.raw";
    char out_imgpath2[] = "baboon_256_after_filter3x3_2.raw";
    char out_imgpath3[] = "baboon_256_after_filter3x3_3.raw";
    char out_imgpath4[] = "baboon_256_after_filter5x5_1.raw";
    char out_imgpath5[] = "baboon_256_after_filter5x5_2.raw";
    char out_imgpath6[] = "baboon_256_after_filter5x5_3.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    //unsigned char img_watermark[512][512];
    //unsigned char img_back[512][512];
    unsigned char img_input1[256][256];
    unsigned char in_img_big3[256+2][256+2];
    unsigned char in_img_big5[256+4][256+4];
    unsigned char img_output[256][256];
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the baboon_256.raw!\n");
    }
    fread(img, sizeof(unsigned char), 256 * 256, input_file);

    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_input1[x][y] = img[c];
            c++;
        }

    }

    double a, b, G;//G = a*exp(b)
    double s;
    double n = -2;
    double s3[9] = {2, 1, 2,   1, 0, 1,   2, 1, 2};
    double s5[25] = { 8,5,4,5,8,  5,2,1,2,5,  4,1,0,1,4,  5,2,1,2,5,  8,5,4,5,8 };
    double filter3X3_1[9];
    double filter3X3_2[9];
    double filter3X3_3[9];
    double filter5X5_1[25];
    double filter5X5_2[25];
    double filter5X5_3[25];
    double c1_1 = 0;
    double c1_2 = 0;
    double c1_3 = 0;
    double c1_4 = 0;
    double c1_5 = 0;
    double c1_6 = 0;

    //----3x3 sigma =0.8----------//
    s = 0.8;
    a = 1 / (3.14 * s * s * 2);
    for (int x = 0; x < 9; x++) {
        n = s3[x]*-1;
        b = n / s * 0.5;
        G = a * exp(b);
        filter3X3_1[x] = G;
        c1_1 = c1_1 + G;
    }

    //----3x3 sigma =1.3----------//
    s = 1.3;
    a = 1 / (3.14 * s * s * 2);
    for (int x = 0; x < 9; x++) {
        n = s3[x]*-1;
        b = n / s * 0.5;
        G = a * exp(b);
        filter3X3_2[x] = G;
        c1_2 = c1_2 + G;
    }

    //----3x3 sigma =2.0------------//
    s = 2.0;
    a = 1 / (3.14 * s * s * 2);
    for (int x = 0; x < 9; x++) {
        n = s3[x]*-1;
        b = n / s * 0.5;
        G = a * exp(b);
        filter3X3_3[x] = G;
        c1_3 = c1_3 + G;
    }

    //----5x5 sigma =0.8--------//
    s = 0.8;
    a = 1 / (3.14 * s * s * 2);
    for (int x = 0; x < 25; x++) {
        n = s5[x] * -1;
        b = n / s * 0.5;
        G = a * exp(b);
        filter5X5_1[x] = G;
        c1_4 = c1_4 + G;
    }

    //----5x5 sigma =1.3------------//
    s = 1.3;
    a = 1 / (3.14 * s * s * 2);

    for (int x = 0; x < 25; x++) {
        n = s5[x] * -1;
        b = n / s * 0.5;
        G = a * exp(b);
        filter5X5_2[x] = G;
        c1_5 = c1_5 + G;
    }

    //----5x5 sigma =2.0-------------//
    s = 2.0;
    a = 1 / (3.14 * s * s * 2);
    for (int x = 0; x < 25; x++) {
        n = s5[x] * -1;
        b = n / s * 0.5;
        G = a * exp(b);
        filter5X5_3[x] = G;
        c1_6 = c1_6 + G;
    }



    //------------3x3 放大--------------//
    for (int x = 0; x < 256+2; x++) {
        for (int y = 0; y < 256+2; y++) {
            if (x == 0) {
                if (y == 0) {
                    in_img_big3[x][y] = img_input1[0][0];
                }
                else if (y == 257) {
                    in_img_big3[x][y] = img_input1[0][255];
                }
                else {
                    in_img_big3[x][y] = img_input1[0][y - 1];
                }
            }
            else if (x == 257) {
                if (y == 0) {
                    in_img_big3[x][y] = img_input1[255][0];
                }
                else if (y == 257) {
                    in_img_big3[x][y] = img_input1[255][255];
                }
                else {
                    in_img_big3[x][y] = img_input1[255][y - 1];
                }
            }
            else if (y == 0) {
                in_img_big3[x][y] = img_input1[x - 1][0];
            }
            else if (y ==257) {
                in_img_big3[x][y] = img_input1[x - 1][255];
            }

            else {
                in_img_big3[x][y] = img_input1[x - 1][y - 1];
            }

        }

    }

    //----------5x5 放大-----------//

    for (int x = 0; x < 256 + 4; x++) {
        for (int y = 0; y < 256 + 4; y++) {
            if (x == 0) {
                if (y == 0) {
                    in_img_big5[x][y] = img_input1[1][1];
                }
                else if (y == 1) {
                    in_img_big5[x][y] = img_input1[1][0];
                }
                else if (y == 258) {
                    in_img_big5[x][y] = img_input1[1][255];
                }
                else if (y == 259) {
                    in_img_big5[x][y] = img_input1[1][254];
                }
                else {
                    in_img_big5[x][y] = img_input1[1][y - 2];
                }
            }
            else if (x == 1) {
                if (y == 0) {
                    in_img_big5[x][y] = img_input1[0][1];
                }
                else if (y == 1) {
                    in_img_big5[x][y] = img_input1[0][0];
                }
                else if (y == 258) {
                    in_img_big5[x][y] = img_input1[0][255];
                }
                else if (y == 259) {
                    in_img_big5[x][y] = img_input1[0][254];
                }
                else {
                    in_img_big5[x][y] = img_input1[0][y - 2];
                }
            }
            else if (x == 258) {
                if (y == 0) {
                    in_img_big5[x][y] = img_input1[255][1];
                }
                else if (y == 1) {
                    in_img_big5[x][y] = img_input1[255][0];
                }
                else if (y == 258) {
                    in_img_big5[x][y] = img_input1[255][255];
                }
                else if (y == 259) {
                    in_img_big5[x][y] = img_input1[255][254];
                }
                else {
                    in_img_big5[x][y] = img_input1[255][y - 2];
                }
            }
            else if (x == 259) {
                if (y == 0) {
                    in_img_big5[x][y] = img_input1[254][1];
                }
                else if (y == 1) {
                    in_img_big5[x][y] = img_input1[254][0];
                }
                else if (y == 258) {
                    in_img_big5[x][y] = img_input1[254][255];
                }
                else if (y == 259) {
                    in_img_big5[x][y] = img_input1[254][254];
                }
                else {
                    in_img_big5[x][y] = img_input1[254][y - 2];
                }
            }
            else if (y == 0) {
                in_img_big5[x][y] = img_input1[x - 2][1];
            }
            else if (y == 1) {
                in_img_big5[x][y] = img_input1[x - 2][0];
            }
            else if (y == 258) {
                in_img_big5[x][y] = img_input1[x - 2][255];
            }
            else if (y == 259) {
                in_img_big5[x][y] = img_input1[x - 2][254];
            }

            else {
                in_img_big5[x][y] = img_input1[x - 2][y - 2];
            }

        }

    }

    //-----------------convolution------------------//

    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_output[x][y] = convolution256(x + 1, y + 1, in_img_big3, filter3X3_1)/c1_1;
        }
    }

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img_output, 1, size, output_file);
    fclose(output_file);

    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_output[x][y] = convolution256(x + 1, y + 1, in_img_big3, filter3X3_2)/c1_2;
        }
    }
    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img_output, 1, size, output_file2);
    fclose(output_file2);
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_output[x][y] = convolution256(x + 1, y + 1, in_img_big3, filter3X3_3)/c1_3;
        }
    }
    fopen_s(&output_file3, out_imgpath3, "wb");
    fwrite(img_output, 1, size, output_file3);
    fclose(output_file3);
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_output[x][y] = convolution5X5_256(x + 2, y + 2, in_img_big5, filter5X5_1)/c1_4;
        }
    }
    fopen_s(&output_file4, out_imgpath4, "wb");
    fwrite(img_output, 1, size, output_file4);
    fclose(output_file4);
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_output[x][y] = convolution5X5_256(x + 2, y + 2, in_img_big5, filter5X5_2)/c1_5;
        }
    }
    fopen_s(&output_file5, out_imgpath5, "wb");
    fwrite(img_output, 1, size, output_file5);
    fclose(output_file5);
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_output[x][y] = convolution5X5_256(x + 2, y + 2, in_img_big5, filter5X5_3)/c1_6;
        }
    }
    fopen_s(&output_file6, out_imgpath6, "wb");
    fwrite(img_output, 1, size, output_file6);
    fclose(output_file6);


    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);

}