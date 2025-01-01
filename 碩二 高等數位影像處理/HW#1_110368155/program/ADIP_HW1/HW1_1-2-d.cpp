/*********************************************************************************
* Filename    : HW1_1-2-d.cpp                                                    *
* Update date : 09/23/2022                                                       *
* Author      : �C����                                                           *
* Note        : cut image into horizontal(virtically) stripe and shift randomly  *
**********************************************************************************/

#include "Header.h"
#include <stdio.h>
#include <stdlib.h> /*�üƬ������*/
#include <time.h> /*�üƺؤl*/
#include <iostream>
using namespace N;
using namespace std;

void shift(int n[]) {
    srand(time(NULL));
    for (int i = 0; i < 8; i++) {
        int s = rand() % 8;
        //cout << s << endl;
        int x = n[i];
        n[i] = n[s];
        n[s] = x;
    }
}

void MY_HW::HW1_1_2_d() {
    //--------------------------�Ѽ�---------------------------//

    int H = 256;
    int W = 256;
    int size = W * H;
    FILE* input_file;
    char imgpath[100] = ".\\HM1_images_file\\lena256.raw";
    unsigned char* img = new unsigned char[256 * 256];
    unsigned char img2d[256][256];
    unsigned char img2d_new[256][256];
    unsigned char img2d_new2[256][256];
    FILE* output_file, * output_file2;
    char out_imgpath[] = ".\\lena256_out_horizontal_swap.raw";
    char out_imgpath2[] = ".\\lena256_out_vertical_swap.raw";

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
    //--------------------------�üư}�C---------------------------//

    int n[8];
    for (int i = 0; i < 8; i++)
        n[i]=i;
    shift(n);
    //for (int i = 0; i < 8; i++)
    //    cout<<n[i];
    //cout << endl;
   
    //--------------------------������---------------------------//
    int l=0;
    for (int i = 0; i < 8; i++) {
        //cout << n[i] << endl;
        for (int k = 1; k < 33; k++){
            //cout << n[i] * 32 - 1 + k << endl;
            int pos;
            if (n[i] * 32 - 1 + k < 0)
                pos = 0;
            else//= n[i] * 32 - 1 + k;
                pos = n[i] * 32 - 1 + k;
            //cout << pos << endl;
            for (int j = 0; j < 256; j++) {
                img2d_new[l][j] = img2d[pos][j];
            }
            //cout << k;
            //cout << endl;
            l++;
        } 
    }
    //--------------------------������---------------------------//
    shift(n);//���s�w�q�üƧǦC
    l = 0;
    //for (int i = 0; i < 8; i++)
    //    cout << n[i];
    for (int i = 0; i < 8; i++) {
        for (int k = 1; k < 33; k++) {
            int pos;
            if (n[i] * 32 - 1 + k < 0)
                pos = 0;
            else
                pos = n[i] * 32 - 1 + k;
            //cout << pos << endl;
            for (int j = 0; j < 256; j++) {
                img2d_new2[j][l] = img2d[j][pos];
            }
            l++;
        }
    }

    //--------------------------��X�ɮ�---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img2d_new, 1, size, output_file);
    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img2d_new2, 1, size, output_file2);


    //--------------------------���X�O����---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(output_file);
    fclose(output_file2);
}