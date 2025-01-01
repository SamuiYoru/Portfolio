/***********************************************
* Filename    : 4_2_3.cpp                      *
* Update date : 12/11/2022                     *
* Author      : 顏郁芩                         *
* Note        : improve house_blur_noise       *
***********************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;

void MY_HW4::HW4_2_3() {
    //--------------------------參數---------------------------//
    int H = 790;
    int W = 720;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2;
    FILE* output_file;
    char in_imgpath[] = ".\\HW4_images_file\\house_blur_noise_790x720.raw";
    char out_imgpath[] = "house_blur_noise_790x720_after.raw";
    char out_imgpath2[] = "house_blur_noise_790x720_after2.raw";

    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    unsigned char imgIN[720][790];
    unsigned char imgIN_big[720+4][790+4];
    unsigned char imgOUT[720][790];
    unsigned char imgOUT2[720][790];
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image house_blur_noise_790x720.raw!\n");
    }
    fread(img, sizeof(unsigned char), 720 * 790, input_file);


    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 720; x++) {
        for (int y = 0; y < 790; y++) {
            imgIN[x][y] = img[c];
            c++;
        }
    }


    //--------------------------mirroring 放大---------------------------//
    for (int x = 0; x < 720 + 4; x++) {
        for (int y = 0; y < 790+ 4; y++) {
            if (x == 0) {
                if (y == 0) {
                    imgIN_big[x][y] = imgIN[1][1];
                }
                else if (y == 1) {
                    imgIN_big[x][y] = imgIN[1][0];
                }
                else if (y == 792) {
                    imgIN_big[x][y] = imgIN[1][789];
                }
                else if (y == 793) {
                    imgIN_big[x][y] = imgIN[1][788];
                }
                else {
                    imgIN_big[x][y] = imgIN[1][y - 2];

                }
            }
            else if (x == 1) {
                if (y == 0) {
                    imgIN_big[x][y] = imgIN[0][1];
                }
                else if (y == 1) {
                    imgIN_big[x][y] = imgIN[0][0];
                }
                else if (y == 792) {
                    imgIN_big[x][y] = imgIN[0][788];
                }
                else if (y == 793) {
                    imgIN_big[x][y] = imgIN[0][789];
                }
                else {
                    imgIN_big[x][y] = imgIN[0][y - 2];
                }
            }
            else if (x == 722) {
                if (y == 0) {
                    imgIN_big[x][y] = imgIN[719][1];
                }
                else if (y == 1) {
                    imgIN_big[x][y] = imgIN[719][0];
                }
                else if (y == 792) {
                    imgIN_big[x][y] = imgIN[719][789];
                }
                else if (y == 793) {
                    imgIN_big[x][y] = imgIN[719][788];
                }
                else {
                    imgIN_big[x][y] = imgIN[719][y - 2];
                }
            }
            else if (x == 723) {
                if (y == 0) {
                    imgIN_big[x][y] = imgIN[718][1];
                }
                else if (y == 1) {
                    imgIN_big[x][y] = imgIN[718][0];
                }
                else if (y == 792) {
                    imgIN_big[x][y] = imgIN[718][789];
                }
                else if (y == 793) {
                    imgIN_big[x][y] = imgIN[718][788];
                }
                else {
                    imgIN_big[x][y] = imgIN[478][y - 2];
                }
            }
            else if (y == 0) {
                imgIN_big[x][y] = imgIN[x - 2][1];
            }
            else if (y == 1) {
                imgIN_big[x][y] = imgIN[x - 2][0];
            }
            else if (y == 792) {
                imgIN_big[x][y] = imgIN[x - 2][789];
            }
            else if (y == 793) {
                imgIN_big[x][y] = imgIN[x - 2][788];
            }

            else {
                imgIN_big[x][y] = imgIN[x - 2][y - 2];
            }

        }

    }

    //-----------------------用5x5 median filter--------------------//
    for (int x = 0; x < 720; x++) {
        for (int y = 0; y < 790; y++) {
            //imgOUT[x][y] = MY_HW4::convolution5X5_mean2(x + 2, y + 2, imgIN_big);
            imgOUT[x][y] = MY_HW4::median_filter3x3(x + 2, y + 2, imgIN_big);
            
        }

    }

    //--------------------------輸出檔案---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(imgOUT, 1, 720*790, output_file);
    fclose(output_file);


    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);

}