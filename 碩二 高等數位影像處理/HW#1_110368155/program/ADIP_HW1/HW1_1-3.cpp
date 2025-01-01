/*****************************************************************************
* Filename    : HW1_1-3.cpp                                                  *
* Update date : 09/23/2022                                                   *
* Author      : �C����                                                       *
* Note        : adding value 45 (or random) to each pixel of the picture     *
*****************************************************************************/

#include "Header.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h> /*�üƬ������*/
#include <time.h> /*�üƺؤl*/
using namespace N;
using namespace std;


void MY_HW::HW1_1_3_a() {
    //--------------------------�Ѽ�---------------------------//

    int H = 256;
    int W = 256;
    int size = W * H;
    FILE* input_file;
    char imgpath[100] = ".\\HM1_images_file\\lena256.raw";
    unsigned char* img = new unsigned char[256 * 256];
    unsigned char* out1_img = new unsigned char[256 * 256];
    unsigned char* out2_img = new unsigned char[256 * 256];
    FILE* output_file1, * output_file2;
    char out_imgpath1[] = ".\\lena256_out_light+45.raw";
    char out_imgpath2[] = ".\\lena256_out_light_random.raw";

    //--------------------------�}�ҡBŪ���ɮ�---------------------------//

    fopen_s(&input_file, imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image!\n");
    }
    fread(img, sizeof(unsigned char), (256 * 256), input_file);

    //--------------------------�[�W45---------------------------//
    for (int k = 0; k < (H*W); k++) {
            int light;
            if ((img[k] + 45) > 255)
                light = 255;
            else
                light = img[k] + 45;
            out1_img[k] = light;
    }

    //--------------------------�H���[�W-55~55---------------------------//
    int ran;
    srand(time(NULL));
    
    for (int k = 0; k < (H * W); k++) {
        ran = rand() % (110 - 0 + 1) + 0;//���� [L, R] �d�򪺶ü�(0~110)
        ran = ran - 55;
        int light;
        if ((img[k] + ran) > 255)
            light = 255;
        else if ((img[k] + ran) < 0)
            light = 0;
        else
            light = img[k] + ran;
        out2_img[k] = light;
    }

    //--------------------------��X�ɮ�---------------------------//
    
    fopen_s(&output_file1, out_imgpath1, "wb");
    fwrite(out1_img, 1, size, output_file1);
    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(out2_img, 1, size, output_file2);

    //--------------------------���X�O����---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(output_file1);
    fclose(output_file2);
}