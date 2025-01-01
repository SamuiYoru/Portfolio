/********************************************************
* Filename    : HW1_1-2-b.cpp                           *
* Update date : 09/23/2022                              *
* Author      : �C����                                  *
* Note        : load image then save another new image  *
*********************************************************/


#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace N;

void MY_HW::HW1_1_2_b() {

    //--------------------------�Ѽ�---------------------------//
    int H = 256;
    int W = 256;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file;
    char in_imgpath[] = ".\\HM1_images_file\\lena256.raw";
    char out_imgpath[] = ".\\lena256_out.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];

    //--------------------------�}�ҡBŪ���ɮ�---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    //--------------------------��X�ɮ�---------------------------//

    fopen_s(&output_file,out_imgpath, "wb");
    fwrite(img, 1, size, output_file);

    //--------------------------���X�O����---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(output_file);
}