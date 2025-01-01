/***********************************************************************************
* Filename    : 2-1.cpp                                                            *
* Update date : 16/10/2022                                                          *
* Author      : 顏郁芩                                                             *
* Note        : resize lena128.raw with nearest neighbor and bilinear algorithms   *
                to 256*256 and 512*512 and calculate MSE, PSNR                     *
***********************************************************************************/


#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
using namespace W;

float MY_HW2::bilnear(double a,double a_value,double b,double b_value,double c) {
    float c_value = 0;
    double x, y;
    x = c - a;
    y = b - c;
    c_value = ((a_value * y) + (b_value * x)) / (x + y);

    return c_value;
}


void MY_HW2::HW2_2_1() {
    clock_t start, end;
    //--------------------------參數---------------------------//
    FILE* input_file;
    FILE* output_file1,* output_file2,* output_file3,* output_file4;
    char in_imgpath[] = ".\\HW2_images_file\\lena128.raw";
    char in_imgpath1[] = ".\\HW2_images_file\\lena256.raw";
    char in_imgpath2[] = ".\\HW2_images_file\\lena512.raw";
    char out_imgpath1[] = ".\\lena_out_256_nearest.raw";
    char out_imgpath2[] = ".\\lena_out_256_bilinear.raw";
    char out_imgpath3[] = ".\\lena_out_512_nearest.raw";
    char out_imgpath4[] = ".\\lena_out_512_bilinear.raw";
    unsigned char* imgIN = new unsigned char[128*128];
    unsigned char img[128][128];
    unsigned char img256_n[256][256];
    unsigned char img256_b[256][256];
    unsigned char img512_n[512][512];
    unsigned char img512_b[512][512];
    float MSE=0, PSNR=0;

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image!\n");
    }
    fread(imgIN, sizeof(unsigned char), (128*128), input_file);



    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 128; y++) {
            img[x][y] = imgIN[c];
            c++;
        }
    }
    //--------------------------nearest neighbor 256---------------------------//
    int a, b;
    start = clock();
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            a = y / 2;//如果除完不是整數表示是中間行，要把旁邊像素複製過來，整數部分為原始像素Y
            b = x / 2;//如果除完不是整數表示是中間行，要把上面行複製下來，整數部分為原始像素X
            img256_n[x][y] = img[b][a];
        }
    }
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by nearest neighbor 256 is : " <<fixed << time_taken << setprecision(6) << " sec " << endl;;
    //--------------------------bilinear 256---------------------------//
    start = clock();
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {

            a = y / 2;
            b = x / 2;
            if (y % 2 == 0 && x % 2 == 0) {
                img256_b[x][y] = img[b][a];
            }
            else {
                int a1;
                if (a + 1 > 127) {
                    a1 = 127;
                }
                else {
                    a1 = a + 1;
                }
                int c;
                float p1, p2, p3;
                p1 = bilnear(a*2, img[b][a], ((a + 1) * 2), img[b][a1], y);
                p2 = bilnear(a*2, img[b][a], ((a + 1) * 2), img[b][a1], y);
                p3 = bilnear((b * 2), p1, ((b + 1) * 2), p2, x);
                c = round(p3);
                img256_b[x][y] = c;
            }
            }

    }
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by bilinear 256 is : " << fixed << time_taken << setprecision(6) << " sec " << endl;;

    //--------------------------nearest neighbor 512---------------------------//
    start = clock();
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            a = y / 4;
            b = x / 4;
            img512_n[x][y] = img[b][a];
        }
    }
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by nearest neighbor 512 is : " << fixed << time_taken << setprecision(6) << " sec " << endl;;
    //--------------------------bilinear 512---------------------------//
    start = clock();
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            a = y / 4;
            b = x / 4;
            if (y % 4 == 0 && x % 4 == 0) {
                img512_b[x][y] = img[b][a];
            }
            else {
                int a1;
                if (a + 1 > 127) {
                    a1 = 127;
                }
                else {
                    a1 = a + 1;
                }
                int c;
                float p1, p2, p3;
                p1 = bilnear((a * 4), img[b][a], ((a + 1) * 4), img[b][a1], y);
                p2 = bilnear((a * 4), img[b][a], ((a + 1) * 4), img[b][a1], y);
                p3 = bilnear((b * 4), p1, ((b + 1) * 4), p2, x);

                c = round(p3);
                img512_b[x][y] = c;
            }

            }

    }
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by bilinear 512 is : " << fixed << time_taken << setprecision(6) << " sec " << endl;
    //--------------------------輸出檔案---------------------------//

    fopen_s(&output_file1, out_imgpath1, "wb");
    fwrite(img256_n, 1, 256*256, output_file1);

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img256_b, 1, 256 * 256, output_file2);

    fopen_s(&output_file3, out_imgpath3, "wb");
    fwrite(img512_n, 1, 512 * 512, output_file3);

    fopen_s(&output_file4, out_imgpath4, "wb");
    fwrite(img512_b, 1, 512 * 512, output_file4);


    //--------------------------釋出記憶體---------------------------//
    delete[] imgIN;
    fclose(input_file);
    fclose(output_file1);
    fclose(output_file2);
    fclose(output_file3);
    fclose(output_file4);
    //--------------------------計算MSE、PSNR---------------------------//

    MSE = MY_HW2::MSE(256, 256, in_imgpath1, out_imgpath1);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath1, out_imgpath1);
    cout << "MSE 256 nearest=" << MSE << endl;
    cout << "PSNR 256 nearest =" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath1, out_imgpath2);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath1, out_imgpath2);
    cout << "MSE 256 bilinear=" << MSE << endl;
    cout << "PSNR 256 bilinear =" << PSNR << endl;

    MSE = MY_HW2::MSE(512, 512, in_imgpath2, out_imgpath3);
    PSNR = MY_HW2::PSNR(512, 512, in_imgpath2, out_imgpath3);
    cout << "MSE 512 nearest=" << MSE << endl;
    cout << "PSNR 512 nearest =" << PSNR << endl;

    MSE = MY_HW2::MSE(512, 512, in_imgpath2, out_imgpath4);
    PSNR = MY_HW2::PSNR(512, 512, in_imgpath2, out_imgpath4);
    cout << "MSE 512 bilinear=" << MSE << endl;
    cout << "PSNR 512 bilinear =" << PSNR << endl;

}