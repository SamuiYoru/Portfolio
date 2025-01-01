/***********************************************************************************
* Filename    : 2-2.cpp                                                            *
* Update date : 16/10/2022                                                         *
* Author      : 顏郁芩                                                             *
* Note        : resize lena512.raw with nearest neighbor and bilinear algorithms   *
                to 256*256 and 128*128 and calculate MSE, PSNR                     *
***********************************************************************************/


#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include<cmath>
#include<iomanip>
#include <windows.h>
using namespace std;
using namespace W;



void MY_HW2::HW2_2_2() {
    //clock_t start, end;
    //--------------------------參數---------------------------//
    FILE* input_file, * input_file1, * input_file2;
    FILE* output_file1, * output_file2, * output_file3, * output_file4,
        * output_file5, * output_file6, * output_file7, * output_file8,
        * output_file9, * output_file10, * output_file11, * output_file12;
    char in_imgpath[] = ".\\HW2_images_file\\lena512.raw";
    char in_imgpath1[] = ".\\HW2_images_file\\lena512_blur20.raw";
    char in_imgpath2[] = ".\\HW2_images_file\\lena512_blur40.raw";
    char in_imgpath3[] = ".\\HW2_images_file\\lena256.raw";
    char in_imgpath4[] = ".\\HW2_images_file\\lena128.raw";

    char out_imgpath1[] = ".\\lena_S_out_256_nearest.raw";
    char out_imgpath2[] = ".\\lena_S_out_256_bilinear.raw";
    char out_imgpath3[] = ".\\lena_S_out_128_nearest.raw";
    char out_imgpath4[] = ".\\lena_S_out_128_bilinear.raw";

    char out_imgpath5[] = ".\\lena_S_out_256_nearest_20.raw";
    char out_imgpath6[] = ".\\lena_S_out_256_bilinear_20.raw";
    char out_imgpath7[] = ".\\lena_S_out_128_nearest_20.raw";
    char out_imgpath8[] = ".\\lena_S_out_128_bilinear_20.raw";

    char out_imgpath9[] = ".\\lena_S_out_256_nearest_40.raw";
    char out_imgpath10[] = ".\\lena_S_out_256_bilinear_40.raw";
    char out_imgpath11[] = ".\\lena_S_out_128_nearest_40.raw";
    char out_imgpath12[] = ".\\lena_S_out_128_bilinear_40.raw";

    unsigned char* imgIN = new unsigned char[512 * 512];
    unsigned char* imgIN_20 = new unsigned char[512 * 512];
    unsigned char* imgIN_40 = new unsigned char[512 * 512];

    unsigned char img[512][512];
    unsigned char img_20[512][512];
    unsigned char img_40[512][512];

    unsigned char img256_n[256][256];
    unsigned char img256_b[256][256];

    unsigned char img128_n[128][128];
    unsigned char img128_b[128][128];
    float MSE = 0, PSNR = 0;

    double time = 0;
    double counts = 0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image!\n");
    }
    fread(imgIN, sizeof(unsigned char), (512 * 512), input_file);

    fopen_s(&input_file1, in_imgpath1, "rb");
    if (!input_file1) {
        printf("Unable to open the image!\n");
    }
    fread(imgIN_20, sizeof(unsigned char), (512 * 512), input_file1);

    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image!\n");
    }
    fread(imgIN_40, sizeof(unsigned char), (512 * 512), input_file2);


    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            img[x][y] = imgIN[c];
            img_20[x][y] = imgIN_20[c];
            img_40[x][y] = imgIN_40[c];
            c++;
        }
    }

    //--------------------------nearest neighbor 256---------------------------//
    
    
    int x1, y1;
    //start = clock();
    QueryPerformanceCounter(&nBeginTime);

    for (int x = 0; x < 256; x++) {
        //lena_S_out_256_nearest.raw
        for (int y = 0; y < 256; y++) {
            double a, b, c, d;
            x1 = x * 2;
            y1 = y * 2;
            if (x1 + 1 >= 512 && y1 + 1 < 512) {
                x1 = 510;
            }
            else if (y1 + 1 >= 512 && x1 + 1 < 512) {
                y1 = 510;
            }
            else {
                x1 = x1;
                y1 = y1;
            }
            img256_n[x][y] = img[x1][y1];

        }
    }
    //end = clock();
    //double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    //cout << "Time taken by nearest neighbor 256 is : " << fixed << time_taken << setprecision(6) << " sec " << endl;
    QueryPerformanceCounter(&nEndTime);//停止計時
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    //cout<<"執行時間："<<time*1000<<"ms"<<endl;
    printf("Time taken by nearest neighbor 256 is : %f ms\n", (time * 1000));

    fopen_s(&output_file1, out_imgpath1, "wb");
    fwrite(img256_n, 1, 256 * 256, output_file1);
    fclose(output_file1);
    for (int x = 0; x < 256; x++) {
        //lena_S_out_256_nearest_20.raw
        for (int y = 0; y < 256; y++) {
            double a, b, c, d;
            x1 = x * 2;
            y1 = y * 2;
            if (x1 + 1 >= 512 && y1 + 1 < 512) {
                x1 = 510;
            }
            else if (y1 + 1 >= 512 && x1 + 1 < 512) {
                y1 = 510;
            }
            else {
                x1 = x1;
                y1 = y1;
            }
            img256_n[x][y] = img_20[x1][y1];

        }
    }

    fopen_s(&output_file5, out_imgpath5, "wb");
    fwrite(img256_n, 1, 256 * 256, output_file5);
    fclose(output_file5);
    for (int x = 0; x < 256; x++) {
        //lena_S_out_256_nearest_40.raw
        for (int y = 0; y < 256; y++) {
            double a, b, c, d;
            x1 = x * 2;
            y1 = y * 2;
            if (x1 + 1 >= 512 && y1 + 1 < 512) {
                x1 = 510;
            }
            else if (y1 + 1 >= 512 && x1 + 1 < 512) {
                y1 = 510;
            }
            else {
                x1 = x1;
                y1 = y1;
            }
            img256_n[x][y] = img_40[x1][y1];

        }
    }

    
    fopen_s(&output_file9, out_imgpath9, "wb");
    fwrite(img256_n, 1, 256 * 256, output_file9);
    fclose(output_file9);

    //--------------------------bilinear 256---------------------------//

    //start = clock();
    QueryPerformanceCounter(&nBeginTime);
    for (int x = 0; x < 256; x++) {
        //lena_S_out_256_bilinear.raw
        for (int y = 0; y < 256; y++) {
            double a, b, c, d;
            double ave;
            x1 = x * 2;
            y1 = y * 2;
            if (x1 + 1 >= 512 && y1 + 1 < 512) {
                x1 = 510;
            }
            else if (y1 + 1 >= 512 && x1 + 1 < 512) {
                y1 = 510;
            }
            else {
                x1 = x1;
                y1 = y1;
            }



            a = bilnear(y1, img[x1][y1], y1+1, img[x1][y1 + 1], y1);
            b = bilnear(y1, img[x1 + 1][y1], y1 + 1, img[x1 + 1][y1 + 1], y1);
            c = bilnear(x1, a, x1 + 1, b, x1);
            //a = img[x1][y1];
            //b = img[x1][y1 + 1];
            //c = img[x1 + 1][y1];
            //d = img[x1 + 1][y1 + 1];

            //ave = (a + b + c + d) / 4;
            img256_b[x][y] = c;

        }
    }

    //end = clock();
    //time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    //cout << "Time taken by bilinear 256 is : " << fixed << time_taken << setprecision(6) << " sec " << endl;;
    QueryPerformanceCounter(&nEndTime);//停止計時
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    //cout<<"執行時間："<<time*1000<<"ms"<<endl;
    printf("Time taken by bilinear 256 is : %f ms\n", (time * 1000));

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img256_b, 1, 256 * 256, output_file2);
    fclose(output_file2);

    for (int x = 0; x < 256; x++) {
        //lena_S_out_256_bilinear_20.raw
        for (int y = 0; y < 256; y++) {
            double a, b, c, d;
            double ave;
            x1 = x * 2;
            y1 = y * 2;
            if (x1 + 1 >= 512 && y1 + 1 < 512) {
                x1 = 510;
            }
            else if (y1 + 1 >= 512 && x1 + 1 < 512) {
                y1 = 510;
            }
            else {
                x1 = x1;
                y1 = y1;
            }

            a = bilnear(y1, img_20[x1][y1], y1 + 1, img_20[x1][y1 + 1], y1);
            b = bilnear(y1, img_20[x1 + 1][y1], y1 + 1, img_20[x1 + 1][y1 + 1], y1);
            c = bilnear(x1, a, x1 + 1, b, x1);

            //a = img_20[x1][y1];
            //b = img_20[x1][y1 + 1];
            //c = img_20[x1 + 1][y1];
            //d = img_20[x1 + 1][y1 + 1];
            //ave = (a + b + c + d) / 4;
            img256_b[x][y] = c;

        }
    }
    fopen_s(&output_file6, out_imgpath6, "wb");
    fwrite(img256_b, 1, 256 * 256, output_file6);
    fclose(output_file6);

    for (int x = 0; x < 256; x++) {
        //lena_S_out_256_bilinear_40.raw
        for (int y = 0; y < 256; y++) {
            double a, b, c, d;
            double ave;
            x1 = x * 2;
            y1 = y * 2;
            if (x1 + 1 >= 512 && y1 + 1 < 512) {
                x1 = 510;
            }
            else if (y1 + 1 >= 512 && x1 + 1 < 512) {
                y1 = 510;
            }
            else {
                x1 = x1;
                y1 = y1;
            }

            a = bilnear(y1, img_40[x1][y1], y1 + 1, img_40[x1][y1 + 1], y1);
            b = bilnear(y1, img_40[x1 + 1][y1], y1 + 1, img_40[x1 + 1][y1 + 1], y1);
            c = bilnear(x1, a, x1 + 1, b, x1);


            //a = img_40[x1][y1];
            //b = img_40[x1][y1 + 1];
            //c = img_40[x1 + 1][y1];
            //d = img_40[x1 + 1][y1 + 1];
            //ave = (a + b + c + d) / 4;
            img256_b[x][y] = c;

        }
    }

    fopen_s(&output_file10, out_imgpath10, "wb");
    fwrite(img256_b, 1, 256 * 256, output_file10);
    fclose(output_file10);

    //--------------------------nearest neighbor 128---------------------------//
    //start = clock();
    QueryPerformanceCounter(&nBeginTime);
    for (int x = 0; x < 128; x++) {
        //lena_S_out_128_nearest.raw
        for (int y = 0; y < 128; y++) {
            double a, b, c, d;

            x1 = x * 4;
            y1 = y * 4;
            if (x1 + 1 >= 512 && y1 + 1 < 512) {
                x1 = 510;
            }
            else if (y1 + 1 >= 512 && x1 + 1 < 512) {
                y1 = 510;
            }
            else {
                x1 = x1;
                y1 = y1;
            }
            img128_n[x][y] = img[x1][y1];

        }
    }


    //end = clock();
    //time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    //cout << "Time taken by nearest neighbor 128 is : " << fixed << time_taken << setprecision(6) << " sec " << endl;
    QueryPerformanceCounter(&nEndTime);//停止計時
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    //cout<<"執行時間："<<time*1000<<"ms"<<endl;
    printf("Time taken by nearest neighbor 128 is : %f ms\n", (time * 1000));
    fopen_s(&output_file3, out_imgpath3, "wb");
    fwrite(img128_n, 1, 128 * 128, output_file3);
    fclose(output_file3);

    for (int x = 0; x < 128; x++) {
        //lena_S_out_128_nearest_20.raw
        for (int y = 0; y < 128; y++) {
            double a, b, c, d;

            x1 = x * 4;
            y1 = y * 4;
            if (x1 + 1 >= 512 && y1 + 1 < 512) {
                x1 = 510;
            }
            else if (y1 + 1 >= 512 && x1 + 1 < 512) {
                y1 = 510;
            }
            else {
                x1 = x1;
                y1 = y1;
            }
            img128_n[x][y] = img_20[x1][y1];

        }
    }
    fopen_s(&output_file7, out_imgpath7, "wb");
    fwrite(img128_n, 1, 128 * 128, output_file7);
    fclose(output_file7);
    for (int x = 0; x < 128; x++) {
        //lena_S_out_128_nearest_40.raw
        for (int y = 0; y < 128; y++) {
            double a, b, c, d;

            x1 = x * 4;
            y1 = y * 4;
            if (x1 + 1 >= 512 && y1 + 1 < 512) {
                x1 = 510;
            }
            else if (y1 + 1 >= 512 && x1 + 1 < 512) {
                y1 = 510;
            }
            else {
                x1 = x1;
                y1 = y1;
            }
            img128_n[x][y] = img_40[x1][y1];

        }
    }
    fopen_s(&output_file11, out_imgpath11, "wb");
    fwrite(img128_n, 1, 128 * 128, output_file11);
    fclose(output_file11);
    //--------------------------bilinear 128---------------------------//
    //start = clock();
    QueryPerformanceCounter(&nBeginTime);
    for (int x = 0; x < 128; x++) {
        //lena_S_out_128_bilinear.raw
        for (int y = 0; y < 128; y++) {
            double a,b,c,ave;
            x1 = x * 4;
            y1 = y * 4;
            if (x1 + 1 >= 512 ) {
                x1 = 510;
            }
            if (y1 + 1 >= 512) {
                y1 = 510;
            }
            a = bilnear(y1, img[x1][y1], y1 + 1, img[x1][y1 + 1], y1);
            b = bilnear(y1, img[x1 + 1][y1], y1 + 1, img[x1 + 1][y1 + 1], y1);
            c = bilnear(x1, a, x1 + 1, b, x1);

            //ave = (img[x1][y1] + img[x1][y1+1] + img[x1][y1+2] + img[x1][y1+3] + 
            //       img[x1+1][y1] + img[x1+1][y1+1] + img[x1+1][y1+2] + img[x1+1][y1+3] +
            //       img[x1+2][y1] + img[x1+2][y1+1] + img[x1+2][y1+2] + img[x1+2][y1+3] +
            //       img[x1+3][y1] + img[x1+3][y1+1] + img[x1+3][y1+2] + img[x1+3][y1+3]) / 16;

            img128_b[x][y] = c;

        }
    }


    //end = clock();
    //time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    //cout << "Time taken by bilinear 128 is : " << fixed << time_taken << setprecision(6) << " sec " << endl;
    QueryPerformanceCounter(&nEndTime);//停止計時
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    //cout<<"執行時間："<<time*1000<<"ms"<<endl;
    printf("Time taken by bilinear 128 is : %f ms\n", (time * 1000));

    fopen_s(&output_file4, out_imgpath4, "wb");
    fwrite(img128_b, 1, 128 * 128, output_file4);
    fclose(output_file4);

    for (int x = 0; x < 128; x++) {
        //lena_S_out_128_bilinear_20.raw
        for (int y = 0; y < 128; y++) {
            double a, b, c, ave;
            x1 = x * 4;
            y1 = y * 4;
            if (x1 + 1 >= 512) {
                x1 = 510;
            }
            if (y1 + 1 >= 512) {
                y1 = 510;
            }
            a = bilnear(y1, img_20[x1][y1], y1 + 1, img_20[x1][y1 + 1], y1);
            b = bilnear(y1, img_20[x1 + 1][y1], y1 + 1, img_20[x1 + 1][y1 + 1], y1);
            c = bilnear(x1, a, x1 + 1, b, x1);

            //ave = (img[x1][y1] + img[x1][y1+1] + img[x1][y1+2] + img[x1][y1+3] + 
            //       img[x1+1][y1] + img[x1+1][y1+1] + img[x1+1][y1+2] + img[x1+1][y1+3] +
            //       img[x1+2][y1] + img[x1+2][y1+1] + img[x1+2][y1+2] + img[x1+2][y1+3] +
            //       img[x1+3][y1] + img[x1+3][y1+1] + img[x1+3][y1+2] + img[x1+3][y1+3]) / 16;

            img128_b[x][y] = c;

        }
    }
    fopen_s(&output_file8, out_imgpath8, "wb");
    fwrite(img128_b, 1, 128 * 128, output_file8);
    fclose(output_file8);

    for (int x = 0; x < 128; x++) {
        //lena_S_out_128_bilinear_40.raw
        for (int y = 0; y < 128; y++) {
            double a, b, c, ave;
            x1 = x * 4;
            y1 = y * 4;
            if (x1 + 1 >= 512) {
                x1 = 510;
            }
            if (y1 + 1 >= 512) {
                y1 = 510;
            }
            a = bilnear(y1, img_40[x1][y1], y1 + 1, img_40[x1][y1 + 1], y1);
            b = bilnear(y1, img_40[x1 + 1][y1], y1 + 1, img_40[x1 + 1][y1 + 1], y1);
            c = bilnear(x1, a, x1 + 1, b, x1);

            //ave = (img[x1][y1] + img[x1][y1+1] + img[x1][y1+2] + img[x1][y1+3] + 
            //       img[x1+1][y1] + img[x1+1][y1+1] + img[x1+1][y1+2] + img[x1+1][y1+3] +
            //       img[x1+2][y1] + img[x1+2][y1+1] + img[x1+2][y1+2] + img[x1+2][y1+3] +
            //       img[x1+3][y1] + img[x1+3][y1+1] + img[x1+3][y1+2] + img[x1+3][y1+3]) / 16;

            img128_b[x][y] = c;

        }
    }
    fopen_s(&output_file12, out_imgpath12, "wb");
    fwrite(img128_b, 1, 128 * 128, output_file12);
    fclose(output_file12);
    //--------------------------釋出記憶體---------------------------//
    delete[] imgIN, imgIN_20, imgIN_40;
    fclose(input_file);
    fclose(input_file1);
    fclose(input_file2);
    //--------------------------計算MSE、PSNR---------------------------//

    MSE = MY_HW2::MSE(256, 256, in_imgpath3, out_imgpath1);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath3, out_imgpath1);
    cout << "MSE 256 nearest with original image=" << MSE << endl;
    cout << "PSNR 256 nearest with original image=" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath3, out_imgpath5);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath3, out_imgpath5);
    cout << "MSE 256 nearest with blur 20 image=" << MSE << endl;
    cout << "PSNR 256 nearest with blur 20 image=" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath3, out_imgpath9);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath3, out_imgpath9);
    cout << "MSE 256 nearest with blur 40 image=" << MSE << endl;
    cout << "PSNR 256 nearest with blur 40 image=" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath3, out_imgpath2);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath3, out_imgpath2);
    cout << "MSE 256 bilinear with original image=" << MSE << endl;
    cout << "PSNR 256 bilinear with original image=" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath3, out_imgpath6);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath3, out_imgpath6);
    cout << "MSE 256 bilinear with blur 20 image=" << MSE << endl;
    cout << "PSNR 256 bilinear with blur 20 image=" << PSNR << endl;

    MSE = MY_HW2::MSE(256, 256, in_imgpath3, out_imgpath10);
    PSNR = MY_HW2::PSNR(256, 256, in_imgpath3, out_imgpath10);
    cout << "MSE 256 bilinear with blur 40 image=" << MSE << endl;
    cout << "PSNR 256 bilinear with blur 40 image=" << PSNR << endl;









    MSE = MY_HW2::MSE(128, 128, in_imgpath4, out_imgpath3);
    PSNR = MY_HW2::PSNR(128, 128, in_imgpath4, out_imgpath3);
    cout << "MSE 128 nearest with original image=" << MSE << endl;
    cout << "PSNR 128 nearest with original image=" << PSNR << endl;

    MSE = MY_HW2::MSE(128, 128, in_imgpath4, out_imgpath7);
    PSNR = MY_HW2::PSNR(128, 128, in_imgpath4, out_imgpath7);
    cout << "MSE 128 nearest with blur 20 image=" << MSE << endl;
    cout << "PSNR 128 nearest with blur 20 image=" << PSNR << endl;

    MSE = MY_HW2::MSE(128, 128, in_imgpath4, out_imgpath11);
    PSNR = MY_HW2::PSNR(128, 128, in_imgpath4, out_imgpath11);
    cout << "MSE 128 nearest with blur 40 image=" << MSE << endl;
    cout << "PSNR 128 nearest with blur 40 image=" << PSNR << endl;

    MSE = MY_HW2::MSE(128, 128, in_imgpath4, out_imgpath4);
    PSNR = MY_HW2::PSNR(128, 128, in_imgpath4, out_imgpath4);
    cout << "MSE 128 bilinear with original image=" << MSE << endl;
    cout << "PSNR 128 bilinear with original image=" << PSNR << endl;

    MSE = MY_HW2::MSE(128, 128, in_imgpath4, out_imgpath8);
    PSNR = MY_HW2::PSNR(128, 128, in_imgpath4, out_imgpath8);
    cout << "MSE 128 bilinear with blur 20 image=" << MSE << endl;
    cout << "PSNR 128 bilinear with blur 20 image=" << PSNR << endl;

    MSE = MY_HW2::MSE(128, 128, in_imgpath4, out_imgpath12);
    PSNR = MY_HW2::PSNR(128, 128, in_imgpath4, out_imgpath12);
    cout << "MSE 128 bilinear with blur 40 image=" << MSE << endl;
    cout << "PSNR 128 bilinear with blur 40 image=" << PSNR << endl;


}



