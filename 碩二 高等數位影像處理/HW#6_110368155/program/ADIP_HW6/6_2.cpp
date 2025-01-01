/*********************************************************************
* Filename    : 6_2.cpp                                              *
* Update date : 3/12/2022                                            *
* Author      : 顏郁芩                                               *
* Note        : Greyscale image Morphology                           *
*********************************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;
unsigned char minimun(unsigned char in[], int n, unsigned char SE[25]);



void grayscale_erosion(unsigned char img[613*237], unsigned char SE[25], unsigned char output[613][237]) {
    unsigned char num[25];
    unsigned char data[25];
    for (int i = 0; i < 613 * 237; i++) {
        int posx = i / 237;
        int posy = i % 237;
        int imgx = i % 613;
        int imgy = i / 613;
        if (imgy <= 2 || imgx <= 2) {
            output[posx][posy] = img[i];
        }
        else if (imgy + 2 >= 237 || imgx + 2 >= 613) {//
            output[posx][posy] = img[i];
        }
        else {
            data[0] = img[(imgy - 2) * 613 + imgx - 2];
            data[1] = img[(imgy - 2) * 613 + imgx - 1];
            data[2] = img[(imgy - 2) * 613 + imgx];
            data[3] = img[(imgy - 2) * 613 + imgx + 1];
            data[4] = img[(imgy - 2) * 613 + imgx + 2];

            data[5] = img[(imgy - 1) * 613 + imgx - 2];
            data[6] = img[(imgy - 1) * 613 + imgx - 1];
            data[7] = img[(imgy - 1) * 613 + imgx];
            data[8] = img[(imgy - 1) * 613 + imgx + 1];
            data[9] = img[(imgy - 1) * 613 + imgx + 2];

            data[10] = img[imgy * 613 + imgx - 2];
            data[11] = img[imgy * 613 + imgx - 1];
            data[12] = img[imgy * 613 + imgx];
            data[13] = img[imgy * 613 + imgx + 1];
            data[14] = img[imgy * 613 + imgx + 2];

            data[15] = img[(imgy + 1) * 613 + imgx - 2];
            data[16] = img[(imgy + 1) * 613 + imgx - 1];
            data[17] = img[(imgy + 1) * 613 + imgx];
            data[18] = img[(imgy + 1) * 613 + imgx + 1];
            data[19] = img[(imgy + 1) * 613 + imgx + 2];

            data[20] = img[(imgy + 2) * 613 + imgx - 2];
            data[21] = img[(imgy + 2) * 613 + imgx - 1];
            data[22] = img[(imgy + 2) * 613 + imgx];
            data[23] = img[(imgy + 2) * 613 + imgx + 1];
            data[24] = img[(imgy + 2) * 613 + imgx + 2];

            //cout << posx << " " << posy << endl;
            /*if (i % 613 < 10) {//x座標小於10是黑色的
                img_out[posx][posy] = 0; //minimun(data, 25);
            }
            else {
                img_out[posx][posy] = minimun(data, 25);//img[imgy * 613 + imgx];//
            }*/
            output[posx][posy] = minimun(data, 25,SE);//img[imgy * 613 + imgx];// 
        }

    }


    }

unsigned char minimun(unsigned char in[], int n, unsigned char SE[25]) {
    unsigned char ans = in[1];
    for (int i = 0; i < n; i++) {
        if (SE[i] != 0) {
            if (in[i] < ans) {
                ans = in[i];
            }
            else {
                ans = ans;
            }
        }
    }
    return ans;
}

unsigned char maximun(unsigned char in[], int n, unsigned char SE[25]) {
    unsigned char ans = in[1];
    for (int i = 0; i < n; i++) {
        if (SE[i] != 0) {
            if (in[i] > ans) {
                ans = in[i];
            }
            else {
                ans = ans;
            }
        }
    }
    return ans;
}


void grayscale_dilation(unsigned char img[613 * 237], unsigned char SE[25], unsigned char output[613][237]) {
    unsigned char num[25];
    unsigned char data[25];
    for (int i = 0; i < 613 * 237; i++) {
        int posx = i / 237;
        int posy = i % 237;
        int imgx = i % 613;
        int imgy = i / 613;
        if (imgy <= 2 || imgx <= 2) {
            output[posx][posy] = img[i];
        }
        else if (imgy + 2 >= 237 || imgx + 2 >= 613) {//
            output[posx][posy] = img[i];
        }
        else {
            data[0] = img[(imgy - 2) * 613 + imgx - 2];
            data[1] = img[(imgy - 2) * 613 + imgx - 1];
            data[2] = img[(imgy - 2) * 613 + imgx];
            data[3] = img[(imgy - 2) * 613 + imgx + 1];
            data[4] = img[(imgy - 2) * 613 + imgx + 2];

            data[5] = img[(imgy - 1) * 613 + imgx - 2];
            data[6] = img[(imgy - 1) * 613 + imgx - 1];
            data[7] = img[(imgy - 1) * 613 + imgx];
            data[8] = img[(imgy - 1) * 613 + imgx + 1];
            data[9] = img[(imgy - 1) * 613 + imgx + 2];

            data[10] = img[imgy * 613 + imgx - 2];
            data[11] = img[imgy * 613 + imgx - 1];
            data[12] = img[imgy * 613 + imgx];
            data[13] = img[imgy * 613 + imgx + 1];
            data[14] = img[imgy * 613 + imgx + 2];

            data[15] = img[(imgy + 1) * 613 + imgx - 2];
            data[16] = img[(imgy + 1) * 613 + imgx - 1];
            data[17] = img[(imgy + 1) * 613 + imgx];
            data[18] = img[(imgy + 1) * 613 + imgx + 1];
            data[19] = img[(imgy + 1) * 613 + imgx + 2];

            data[20] = img[(imgy + 2) * 613 + imgx - 2];
            data[21] = img[(imgy + 2) * 613 + imgx - 1];
            data[22] = img[(imgy + 2) * 613 + imgx];
            data[23] = img[(imgy + 2) * 613 + imgx + 1];
            data[24] = img[(imgy + 2) * 613 + imgx + 2];

            output[posx][posy] = maximun(data, 25, SE);//img[imgy * 613 + imgx];// 
        }
    }
}

void MY_HW6::HW6_2() {
    //--------------------------參數---------------------------//
    int H = 237;
    int W = 613;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file;
    char in_imgpath[] = ".\\HW6_image_files\\check_613x237.raw";
    char out_imgpath[] = ".\\check_613x237_erosion.raw";
    char out_imgpath2[] = ".\\check_613x237_dilation.raw";
    char out_imgpath3[] = ".\\check_613x237_opening.raw";
    char out_imgpath4[] = ".\\check_613x237_closing.raw";

    char out_imgpath5[] = ".\\check_613x237_erosion 2.raw";
    char out_imgpath6[] = ".\\check_613x237_dilation 2.raw";

    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char img2D[613][237];
    unsigned char img_out[613][237];
    unsigned char img_out2[613][237];
    unsigned char img_out3[613][237];
    unsigned char img_out4[613][237];
    unsigned char img_out5[613][237];
    unsigned char img_out6[613][237];

    unsigned char SE[25] = { 0,0,1,0,0,
                             1,1,1,1,1,
                             1,1,1,1,1,
                             1,1,1,1,1,
                             0,0,1,0,0 };

    unsigned char SE2[25] = { 0,1,1,1,0,
                              0,1,1,1,0,
                              1,1,1,1,1,
                              0,1,1,1,0,
                              0,1,1,1,0 };

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image check_613x237.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    //--------------------------轉成2D---------------------------//
    int c = 0;
    for (int x = 0; x < 613; x++) {
        for (int y = 0; y < 237; y++) {
            img2D[x][y] = img[c];
            c++;
        }
    }

    //------------------處理 -----------------------//


    grayscale_erosion(img, SE, img_out);

    grayscale_dilation(img, SE, img_out2);

    unsigned char img2[613 * 237];
    grayscale_erosion(img, SE, img_out3);
    c = 0;
    for (int x = 0; x < 613; x++) {
        for (int y = 0; y < 237; y++) {
            img2[c] = img_out3[x][y];
            c++;
        }
    }
    grayscale_dilation(img2, SE, img_out3);

    grayscale_dilation(img, SE, img_out4);
    unsigned char img3[613 * 237];
    c = 0;
    for (int x = 0; x < 613; x++) {
        for (int y = 0; y < 237; y++) {
            img3[c] = img_out4[x][y];
            c++;
        }
    }
    grayscale_erosion(img3, SE, img_out4);

 


    grayscale_erosion(img, SE2, img_out5);

    grayscale_dilation(img, SE2, img_out6);




    //------------------儲存檔案-----------------------//
    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img_out, 1, size, output_file);//
    fclose(output_file);

    fopen_s(&output_file, out_imgpath2, "wb");
    fwrite(img_out2, 1, size, output_file);//
    fclose(output_file);

    fopen_s(&output_file, out_imgpath3, "wb");
    fwrite(img_out3, 1, size, output_file);//
    fclose(output_file);

    fopen_s(&output_file, out_imgpath4, "wb");
    fwrite(img_out4, 1, size, output_file);//
    fclose(output_file);

    fopen_s(&output_file, out_imgpath5, "wb");
    fwrite(img_out5, 1, size, output_file);//
    fclose(output_file);


    fopen_s(&output_file, out_imgpath6, "wb");
    fwrite(img_out6, 1, size, output_file);//
    fclose(output_file);



    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);



}