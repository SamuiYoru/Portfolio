/*********************************************************************************
* Filename    : HW1_1-2-e.cpp                                                    *
* Update date : 09/27/2022                                                       *
* Author      : 顏郁芩                                                           *
* Note        : reorganization the  five images                                  *
**********************************************************************************/

#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace N;
using namespace std;

void MY_HW::HW1_1_2_e() {
    //--------------------------參數---------------------------//
    int H = 64;
    int W = 64;
    //unsigned char img[256 * 256];
    FILE* input_fileA1,* input_fileA2,* input_fileA3, * input_fileA4,* input_fileA5;
    FILE* output_file;
    char in_imgpathA1[] = ".\\HM1_images_file\\A1.raw";
    char in_imgpathA2[] = ".\\HM1_images_file\\A2.raw";
    char in_imgpathA3[] = ".\\HM1_images_file\\A3.raw";
    char in_imgpathA4[] = ".\\HM1_images_file\\A4.raw";
    char in_imgpathA5[] = ".\\HM1_images_file\\A5.raw";
    char out_imgpath[] = ".\\A_reorganization.raw";
    //int size = H * W;
    unsigned char* imgA1 = new unsigned char[(2 * 64) * (2 * 64)];
    unsigned char* imgA2 = new unsigned char[(2 * 64) * (1 * 64)];
    unsigned char* imgA3 = new unsigned char[(3 * 64) * (2 * 64)];
    unsigned char* imgA4 = new unsigned char[(3 * 64) * (3 * 64)];
    unsigned char* imgA5 = new unsigned char[(1 * 64) * (1 * 64)];
    unsigned char img2d[256][256];
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_fileA1, in_imgpathA1, "rb");
    fopen_s(&input_fileA2, in_imgpathA2, "rb");
    fopen_s(&input_fileA3, in_imgpathA3, "rb");
    fopen_s(&input_fileA4, in_imgpathA4, "rb");
    fopen_s(&input_fileA5, in_imgpathA5, "rb");
    if (!input_fileA1) {
        printf("Unable to open the image A1!\n");
    }
    if (!input_fileA2) {
        printf("Unable to open the image A2!\n");
    }
    if (!input_fileA3) {
        printf("Unable to open the image A3!\n");
    }
    if (!input_fileA4) {
        printf("Unable to open the image A4!\n");
    }
    if (!input_fileA5) {
        printf("Unable to open the image A5!\n");
    }
    fread(imgA1, sizeof(unsigned char), ((2 * 64) * (2 * 64)), input_fileA1);
    fread(imgA2, sizeof(unsigned char), ((2 * 64) * (1 * 64)), input_fileA2);//1/2?
    fread(imgA3, sizeof(unsigned char), ((3 * 64) * (2 * 64)), input_fileA3);//2/3?
    fread(imgA4, sizeof(unsigned char), ((3 * 64) * (3 * 64)), input_fileA4);
    fread(imgA5, sizeof(unsigned char), ((1 * 64) * (1 * 64)), input_fileA5);
    

    //----------將圖案放到新的二維陣列上----------//
    //----------A4----------//    
    int c = 0;
    for (int x = 0; x < (64 * 3); x++) {
        for (int y = 0; y < (64 * 3); y++) {
            img2d[x][y+64] = imgA4[c];
            c++;
        }
    }
    //----------A3----------//
    c = 0;
    for (int y = 127; y >= 64; y--) {
        for (int x = 0; x <(64*3); x++) {
            if (x >= 64 && x < (64 * 2)) {
                img2d[x][y] = img2d[x][y];
            }
            else {
                img2d[x][y] = imgA3[c];
            }
            c++;
        }
    }
    for (int y = 63; y >= 0; y--) {
        for (int x = 0; x < (64 * 3); x++) {
            img2d[x][y] = imgA3[c];
            c++;
        }
    }
    //----------A5----------//
    c = 0;
    for (int x = 63; x >= 0; x--) {
        for (int y = (64 * 4 - 1); y > (64 * 3 - 1); y--) {
            img2d[x][y] = imgA5[c];
            c++;
        }
    }
    //----------A2----------//
    c = 0;
    for (int x = (64*4-1); x >= (64*3); x--) {
        for (int y = (64 * 2 - 1); y >= 0; y--) {
            img2d[x][y] = imgA2[c];
            c++;
        }
    }
    //----------A1----------//
    c = 0;
    for (int y = (64*2); y < (64 * 3 ); y++) {
        for (int x = 255; x >= (64 * 2); x--) {
            if (x >= (64 * 2) && x < (64 * 3)) {
                img2d[x][y] = img2d[x][y];
            }
            else {
                img2d[x][y] = imgA1[c];
            }
            c++;
        }
    }    
    for (int y = (64 * 3); y < 256; y++) {
        for (int x = 255; x >= (64 * 2); x--) {
            img2d[x][y] = imgA1[c];
            c++;
        }
    }

    //--------------------------輸出檔案---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img2d, 1, (256*256), output_file);
    //--------------------------釋出記憶體---------------------------//
    delete[] imgA1;
    delete[] imgA2;
    delete[] imgA3;
    delete[] imgA4;
    delete[] imgA5;
    fclose(input_fileA1);
    fclose(input_fileA2);
    fclose(input_fileA3);
    fclose(input_fileA4);
    fclose(input_fileA5);
    fclose(output_file);
    
}