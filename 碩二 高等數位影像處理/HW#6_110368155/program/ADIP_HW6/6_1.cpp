/************************************************
* Filename    : 6_1.cpp                         *
* Update date : 3/12/2022                       *
* Author      : 顏郁芩                          *
* Note        : Binary image Morphology         *
************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;

unsigned char min(unsigned char in[], int n, unsigned char SE[25]) {
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

unsigned char max(unsigned char in[], int n, unsigned char SE[25]) {
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



void erosion(unsigned char img[512+4][512+4], unsigned char SE[25], unsigned char output[512][512]) {
    unsigned char data[25];
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            int posx = x + 2;
            int posy = y + 2;
            data[0] = img[posx -2][posy-2];
            data[1] = img[posx -2][posy-1];
            data[2] = img[posx -2][posy];
            data[3] = img[posx -2][posy+1];
            data[4] = img[posx-2][posy+2];

            data[5] = img[posx -1][posy-2];
            data[6] = img[posx -1][posy-1];
            data[7] = img[posx -1][posy];
            data[8] = img[posx -1][posy+1];
            data[9] = img[posx -1][posy+2];

            data[10] = img[posx][posy-2];
            data[11] = img[posx][posy-1];
            data[12] = img[posx][posy];
            data[13] = img[posx][posy+1];
            data[14] = img[posx][posy+2];

            data[15] = img[posx+1][posy-2];
            data[16] = img[posx+1][posy-1];
            data[17] = img[posx+1][posy];
            data[18] = img[posx+1][posy+1];
            data[19] = img[posx+1][posy+2];

            data[20] = img[posx+2][posy-2];
            data[21] = img[posx+2][posy-1];
            data[22] = img[posx+2][posy];
            data[23] = img[posx+2][posy+1];
            data[24] = img[posx+2][posy+2];

            int flag = 0;//要改條件
            for (int i = 0; i < 25; i++) {
                if ( SE[i] == 1 && data[i]  == 255) {
                    flag = flag +1;
                }
                //output[x][y] = min(data, 25, SE);
            }


            if (flag == 0) {
                output[x][y] = 0;
            }
            else {
                output[x][y] = 255;
            }



        }
    }
 

}


void dilation(unsigned char img[512 + 4][512 + 4], unsigned char SE[25], unsigned char output[512][512]) {
    unsigned char data[25];
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            int posx = x + 2;
            int posy = y + 2;
            data[0] = img[posx - 2][posy - 2];
            data[1] = img[posx - 2][posy - 1];
            data[2] = img[posx - 2][posy];
            data[3] = img[posx - 2][posy + 1];
            data[4] = img[posx - 2][posy + 2];

            data[5] = img[posx - 1][posy - 2];
            data[6] = img[posx - 1][posy - 1];
            data[7] = img[posx - 1][posy];
            data[8] = img[posx - 1][posy + 1];
            data[9] = img[posx - 1][posy + 2];

            data[10] = img[posx][posy - 2];
            data[11] = img[posx][posy - 1];
            data[12] = img[posx][posy];
            data[13] = img[posx][posy + 1];
            data[14] = img[posx][posy + 2];

            data[15] = img[posx + 1][posy - 2];
            data[16] = img[posx + 1][posy - 1];
            data[17] = img[posx + 1][posy];
            data[18] = img[posx + 1][posy + 1];
            data[19] = img[posx + 1][posy + 2];

            data[20] = img[posx + 2][posy - 2];
            data[21] = img[posx + 2][posy - 1];
            data[22] = img[posx + 2][posy];
            data[23] = img[posx + 2][posy + 1];
            data[24] = img[posx + 2][posy + 2];

            int flag = 0;//要改條件
            for (int i = 0; i < 25; i++) {
                if (SE[i] == 1 && data[i] == 0) {
                    flag = flag + 1;
                }
                //output[x][y] = min(data, 25, SE);
            }


            if (flag == 0) {
                output[x][y] = 255;
            }
            else {
                output[x][y] = 1;
            }



        }
    }
}


void bigger(unsigned char img2D[512][512], unsigned char imgBIG[512+4][512+4]) {
    for (int x = 0; x < 512 + 4; x++) {
        for (int y = 0; y < 512 + 4; y++) {
            if (x < 2 || x>514) {
                imgBIG[x][y] = 255;
            }
            else if (y < 2 || y>514) {
                imgBIG[x][y] = 255;
            }
            else {
                imgBIG[x][y] = img2D[x - 2][y - 2];
            }
        }
    }

}


void MY_HW6::HW6_1() {
    //--------------------------參數---------------------------//
    int H = 512;
    int W = 512;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file;
    char in_imgpath[] = ".\\HW6_image_files\\words_512.raw";
    char out_imgpath[] = ".\\words_512_after.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char img2D[512][512];
    unsigned char imgBIG[512+4][512+4];
    unsigned char img_out[512][512];

    unsigned char SE[25] = { 0,0,0,0,0,
                             0,0,1,0,0,
                             0,1,1,1,0,
                             0,0,1,0,0,
                             0,0,0,0,0 };

    unsigned char SE2[25] = { 0,0,0,0,0,
                         0,0,1,0,0,
                         0,0,1,0,0,
                         0,0,1,0,0,
                         0,0,0,0,0 };

    unsigned char SE3[25] = { 0,0,0,0,0,
                              0,1,1,1,0,
                              0,1,1,1,0,
                              0,1,1,1,0,
                              0,0,0,0,0 };

    unsigned char SE4[25] = { 0,0,0,0,0,
                          0,1,1,0,0,
                          0,1,1,0,0,
                          0,0,0,0,0,
                          0,0,0,0,0 };


    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image words_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    //-------------------轉成2D--------------------//
    int c = 0;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            img2D[x][y] = img[c];
            c++;
        }
    }

    //---------放大--------------//
    bigger(img2D, imgBIG);
    
    //------------------處理 -----------------------//

    erosion(imgBIG, SE2, img_out);

    fopen_s(&output_file, "words_512_after-1.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);

    bigger(img_out, imgBIG);

    dilation(imgBIG, SE, img_out);
    fopen_s(&output_file, "words_512_after-2.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);

    bigger(img_out, imgBIG);

    erosion(imgBIG, SE3, img_out);
    fopen_s(&output_file, "words_512_after-3.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);

    bigger(img_out, imgBIG);


    dilation(imgBIG, SE3, img_out);
    fopen_s(&output_file, "words_512_after-4.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);

    bigger(img_out, imgBIG);


    erosion(imgBIG, SE4, img_out);
    fopen_s(&output_file, "words_512_after-5.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);



    //------------------儲存檔案-----------------------//
    /*fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);*/
    
    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);



}