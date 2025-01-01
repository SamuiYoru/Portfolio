/*************************************************************
* Filename    : HW1_1-2-c.cpp                                *
* Update date : 09/23/2022                                   *
* Author      : 顏郁芩                                       *
* Note        : horizontal flip and rotate part of the image *
*************************************************************/

#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace N;
using namespace std;

void MY_HW::HW1_1_2_c() {
    //--------------------------參數---------------------------//

    int H = 256;
    int W = 256;
    //unsigned char img[256*256];
    int size = W * H;
    FILE* input_file;
    char imgpath[100] = ".\\HM1_images_file\\lena256.raw";
    unsigned char* img = new unsigned char[256 * 256];
    unsigned char img2d[256][256];
    unsigned char img2d_new[256][256];
    FILE* output_file;
    char out_imgpath[] = ".\\lena256_out_flip.raw";

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image!\n");
    }
    fread(img, sizeof(unsigned char), (256 * 256), input_file);

    //--------------------------轉成二維陣列---------------------------//
    int k = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            img2d[i][j] = img[k];
            k++;
        }
    }
    //--------------左右翻轉----------//
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            img2d_new[x][127-y] = img2d[x][y];
            //img2d_new[127 - y][x] = img2d[x][y];//旋轉
        }
    }
    //--------------順時針旋轉----------//
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            img2d_new[y][127 - x+128] = img2d[x][y+128];
        }
    }
    //--------------逆時針旋轉----------//
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            img2d_new[127-y+128][x] = img2d[x+128][y];

        }
    }
    //--------------和原本相同----------//
    for (int y = 128; y < 256; y++) {
        for (int x = 128; x < 256; x++) {
            img2d_new[x][y] = img2d[x][y];
        }
    }

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img2d_new, 1, size, output_file);

    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(output_file);
}