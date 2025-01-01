/***************************************************************************************
* Filename    : 3.cpp                                                                  *
* Update date : 16/10/2022                                                             *
* Author      : 顏郁芩                                                                 *
* Note        : quantize the grey-level resolution of lena256.raw and baboon256.raw    *
                from 8 bit to 1 bit and calculate MSE, PSNR                            *
***************************************************************************************/



#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
using namespace W;

void MY_HW2::HW2_3() {
    FILE* input_file1, * input_file2;
    char in_imgpath1[] = ".\\HW2_images_file\\lena256.raw";
    char in_imgpath2[] = ".\\HW2_images_file\\baboon256.raw";
    unsigned char* imgIN_1 = new unsigned char[256 * 256];
    unsigned char* imgIN_2 = new unsigned char[256 * 256];
    FILE* output_file1, * output_file2, * output_file3, * output_file4, * output_file5, * output_file6, * output_file7;
    FILE* output_file2_1, * output_file2_2, * output_file2_3, * output_file2_4, * output_file2_5, * output_file2_6, * output_file2_7;
    char out_imgpath1[] = ".\\lena256_7.raw";
    char out_imgpath2[] = ".\\lena256_6.raw";
    char out_imgpath3[] = ".\\lena256_5.raw";
    char out_imgpath4[] = ".\\lena256_4.raw";
    char out_imgpath5[] = ".\\lena256_3.raw";
    char out_imgpath6[] = ".\\lena256_2.raw";
    char out_imgpath7[] = ".\\lena256_1.raw";
    char out_imgpath2_1[] = ".\\baboon256_7.raw";
    char out_imgpath2_2[] = ".\\baboon256_6.raw";
    char out_imgpath2_3[] = ".\\baboon256_5.raw";
    char out_imgpath2_4[] = ".\\baboon256_4.raw";
    char out_imgpath2_5[] = ".\\baboon256_3.raw";
    char out_imgpath2_6[] = ".\\baboon256_2.raw";
    char out_imgpath2_7[] = ".\\baboon256_1.raw";

    unsigned char img256_lena[256*256];
    unsigned char img256_baboon[256*256];

    float MSE = 0, PSNR = 0;

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file1, in_imgpath1, "rb");
    if (!input_file1) {
        printf("Unable to open the image lena!\n");
    }
    fread(imgIN_1, sizeof(unsigned char), (256 * 256), input_file1);

    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image baboon!\n");
    }
    fread(imgIN_2, sizeof(unsigned char), (256 * 256), input_file2);
   



    //------------------------ to 7 bits ----------------------------------//

    for (int c = 0; c < 256 * 256; c++) {
        int g = 255 / (128 - 1);
        img256_lena[c] = imgIN_1[c]/2*g;
        img256_baboon[c] = imgIN_2[c] / 2*g;
    }

    fopen_s(&output_file1, out_imgpath1, "wb");
    fwrite(img256_lena, 1, 256 * 256, output_file1);
    fopen_s(&output_file2_1, out_imgpath2_1, "wb");
    fwrite(img256_baboon, 1, 256 * 256, output_file2_1);
    fclose(output_file1);
    fclose(output_file2_1);


    //------------------------ to 6 bits ----------------------------------//

    for (int c = 0; c < 256 * 256; c++) {
        int g = 255 / (64 - 1);
        img256_lena[c] = imgIN_1[c] / 4 * g;
        img256_baboon[c] = imgIN_2[c] / 4 * g;
    }

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img256_lena, 1, 256 * 256, output_file2);
    fopen_s(&output_file2_2, out_imgpath2_2, "wb");
    fwrite(img256_baboon, 1, 256 * 256, output_file2_2);
    fclose(output_file2);
    fclose(output_file2_2);

    //------------------------ to 5 bits ----------------------------------//

    for (int c = 0; c < 256 * 256; c++) {
        int g = 255 / (32 - 1);
        img256_lena[c] = imgIN_1[c] / 8 * g;
        img256_baboon[c] = imgIN_2[c] /8 * g;
    }

    fopen_s(&output_file3, out_imgpath3, "wb");
    fwrite(img256_lena, 1, 256 * 256, output_file3);
    fopen_s(&output_file2_3, out_imgpath2_3, "wb");
    fwrite(img256_baboon, 1, 256 * 256, output_file2_3);
    fclose(output_file3);
    fclose(output_file2_3);


    //------------------------ to 4 bits ----------------------------------//

    for (int c = 0; c < 256 * 256; c++) {
        int g = 255 / (16 - 1);
        img256_lena[c] = imgIN_1[c] / 16 * g;
        img256_baboon[c] = imgIN_2[c] / 16 * g;
    }

    fopen_s(&output_file4, out_imgpath4, "wb");
    fwrite(img256_lena, 1, 256 * 256, output_file4);
    fopen_s(&output_file2_4, out_imgpath2_4, "wb");
    fwrite(img256_baboon, 1, 256 * 256, output_file2_4);
    fclose(output_file4);
    fclose(output_file2_4);


    //------------------------ to 3 bits ----------------------------------//

    for (int c = 0; c < 256 * 256; c++) {
        int g = 255 / (8 - 1);
        img256_lena[c] = imgIN_1[c] / 32 * g;
        img256_baboon[c] = imgIN_2[c] / 32 * g;
    }

    fopen_s(&output_file5, out_imgpath5, "wb");
    fwrite(img256_lena, 1, 256 * 256, output_file5);
    fopen_s(&output_file2_5, out_imgpath2_5, "wb");
    fwrite(img256_baboon, 1, 256 * 256, output_file2_5);
    fclose(output_file5);
    fclose(output_file2_5);

    //------------------------ to 2 bits ----------------------------------//

    for (int c = 0; c < 256 * 256; c++) {
        int g = 255 / (4 - 1);
        img256_lena[c] = imgIN_1[c] / 64 * g;
        img256_baboon[c] = imgIN_2[c] / 64 * g;
        //cout << +img256_baboon[c] << endl;
    }

    fopen_s(&output_file6, out_imgpath6, "wb");
    fwrite(img256_lena, 1, 256 * 256, output_file6);
    fopen_s(&output_file2_6, out_imgpath2_6, "wb");
    fwrite(img256_baboon, 1, 256 * 256, output_file2_6);
    fclose(output_file6);
    fclose(output_file2_6);

    //------------------------ to 1 bits ----------------------------------//

    for (int c = 0; c < 256 * 256; c++) {
        int g = 255 / (2 - 1);
        img256_lena[c] = imgIN_1[c] / 128 * g;
        img256_baboon[c] = imgIN_2[c] / 128 * g;
        if (c > 256 * 30 && c < 256 * 50) {
            
        }
    }

    fopen_s(&output_file7, out_imgpath7, "wb");
    fwrite(img256_lena, 1, 256 * 256, output_file7);
    fopen_s(&output_file2_7, out_imgpath2_7, "wb");
    fwrite(img256_baboon, 1, 256 * 256, output_file2_7);
    fclose(output_file7);
    fclose(output_file2_7);



    //--------------------------釋出記憶體---------------------------//
    delete[] imgIN_1, imgIN_2;
    fclose(input_file1);
    fclose(input_file2);
     
   


    //--------------------------計算MSE、PSNR---------------------------//

    MSE = MY_HW2::MSE(256, 256, in_imgpath1, out_imgpath1);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath1, out_imgpath1);
    cout << "MSE lena 7 bit nearest=" << MSE << endl;
    cout << "PSNR lena 7 bit nearest =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath1, out_imgpath2);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath1, out_imgpath2);
    cout << "MSE lena 6 bit nearest=" << MSE << endl;
    cout << "PSNR lena 6 bit nearest =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath1, out_imgpath3);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath1, out_imgpath3);
    cout << "MSE lena 5 bit nearest=" << MSE << endl;
    cout << "PSNR lena 5 bit nearest =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath1, out_imgpath4);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath1, out_imgpath4);
    cout << "MSE lena 4 bit nearest=" << MSE << endl;
    cout << "PSNR lena 4 bit nearest =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath1, out_imgpath5);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath1, out_imgpath5);
    cout << "MSE lena 3 bit nearest=" << MSE << endl;
    cout << "PSNR lena 3 bit nearest =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath1, out_imgpath6);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath1, out_imgpath6);
    cout << "MSE lena 2 bit nearest=" << MSE << endl;
    cout << "PSNR lena 2 bit nearest =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath1, out_imgpath7);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath1, out_imgpath7);
    cout << "MSE lena 1 bit nearest=" << MSE << endl;
    cout << "PSNR lena 1 bit nearest =" << PSNR << endl;




    MSE = MY_HW2::MSE(256, 256, in_imgpath2, out_imgpath2_1);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath2, out_imgpath2_1);
    cout << "MSE baboon 7 bit bilinear=" << MSE << endl;
    cout << "PSNR baboon 7 bit bilinear =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath2, out_imgpath2_2);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath2, out_imgpath2_2);
    cout << "MSE baboon 6 bit bilinear=" << MSE << endl;
    cout << "PSNR baboon 6 bit bilinear =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath2, out_imgpath2_3);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath2, out_imgpath2_3);
    cout << "MSE baboon 5 bit bilinear=" << MSE << endl;
    cout << "PSNR baboon 5 bit bilinear =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath2, out_imgpath2_4);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath2, out_imgpath2_4);
    cout << "MSE baboon 4 bit bilinear=" << MSE << endl;
    cout << "PSNR baboon 4 bit bilinear =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath2, out_imgpath2_5);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath2, out_imgpath2_5);
    cout << "MSE baboon 3 bit bilinear=" << MSE << endl;
    cout << "PSNR baboon 3 bit bilinear =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath2, out_imgpath2_6);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath2, out_imgpath2_6);
    cout << "MSE baboon 2 bit bilinear=" << MSE << endl;
    cout << "PSNR baboon 2 bit bilinear =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath2, out_imgpath2_7);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath2, out_imgpath2_7);
    cout << "MSE baboon 1 bit bilinear=" << MSE << endl;
    cout << "PSNR baboon 1 bit bilinear =" << PSNR << endl;


}