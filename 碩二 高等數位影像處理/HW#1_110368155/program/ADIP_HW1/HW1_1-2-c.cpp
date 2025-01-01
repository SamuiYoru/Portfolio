/*************************************************************
* Filename    : HW1_1-2-c.cpp                                *
* Update date : 09/23/2022                                   *
* Author      : �C����                                       *
* Note        : horizontal flip and rotate part of the image *
*************************************************************/

#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace N;
using namespace std;

void MY_HW::HW1_1_2_c() {
    //--------------------------�Ѽ�---------------------------//

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

    //--------------------------�}�ҡBŪ���ɮ�---------------------------//

    fopen_s(&input_file, imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image!\n");
    }
    fread(img, sizeof(unsigned char), (256 * 256), input_file);

    //--------------------------�ন�G���}�C---------------------------//
    int k = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            img2d[i][j] = img[k];
            k++;
        }
    }
    //--------------���k½��----------//
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            img2d_new[x][127-y] = img2d[x][y];
            //img2d_new[127 - y][x] = img2d[x][y];//����
        }
    }
    //--------------���ɰw����----------//
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            img2d_new[y][127 - x+128] = img2d[x][y+128];
        }
    }
    //--------------�f�ɰw����----------//
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            img2d_new[127-y+128][x] = img2d[x+128][y];

        }
    }
    //--------------�M�쥻�ۦP----------//
    for (int y = 128; y < 256; y++) {
        for (int x = 128; x < 256; x++) {
            img2d_new[x][y] = img2d[x][y];
        }
    }

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img2d_new, 1, size, output_file);

    //--------------------------���X�O����---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(output_file);
}