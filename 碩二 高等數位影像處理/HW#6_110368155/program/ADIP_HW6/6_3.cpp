/*********************************
* Filename    : 6_3.cpp          *
* Update date : 3/12/2022        *
* Author      : 顏郁芩           *
* Note        : Trimap           *
*********************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;


void erosion_Trimap(unsigned char img[600 + 4][600 + 4], unsigned char SE[25], unsigned char output[600][600]) {
    unsigned char data[25];
    for (int x = 0; x < 600; x++) {
        for (int y = 0; y < 600; y++) {
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
                if (SE[i] == 1 && data[i] > 245) {
                    flag = flag + 1;
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


void dilation_Trimap(unsigned char img[600+4][600+4], unsigned char SE[25], unsigned char output[600][600]) {
    unsigned char data[25];
    for (int x = 0; x < 600; x++) {
        for (int y = 0; y < 600; y++) {
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
                if (SE[i] == 1 && data[i]< 245) {
                    flag = flag + 1;
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

void bigger(unsigned char img2D[600][600], unsigned char imgBIG[600 + 4][600 + 4], unsigned char val) {
    for (int x = 0; x < 600 + 4; x++) {
        for (int y = 0; y < 600 + 4; y++) {
            if (x < 2 || x>602) {
                imgBIG[x][y] = val;
            }
            else if (y < 2 || y>602) {
                imgBIG[x][y] = val;
            }
            else {
                imgBIG[x][y] = img2D[x - 2][y - 2];
            }
        }
    }

}


void MY_HW6::HW6_3() {
    //--------------------------參數---------------------------//
    int H = 600;
    int W = 600;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file;
    char in_imgpath[] = ".\\HW6_image_files\\monster_600.raw";
    char out_imgpath[] = ".\\monster_600_Trimap.raw";
    char out_imgpath2[] = ".\\monster_600_overlapping.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char img_out[600][600];
    unsigned char img_out2[600][600];
    unsigned char img_out3[600][600];
    unsigned char img2D[600][600];
    unsigned char imgBIG[604][604];

    unsigned char SE[25] = {0,1,1,1,0,
                         1,1,1,1,1,
                         1,1,1,1,1,
                         1,1,1,1,1,
                         0,1,1,1,0 };
    unsigned char SE2[25] = { 0,0,1,0,0,
                     0,1,1,1,0,
                     1,1,1,1,1,
                     0,1,1,1,0,
                     0,0,1,0,0 };

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image monster_600.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    //---轉成2D-------//
    int c = 0;
    for (int x = 0; x < 600; x++) {
        for (int y = 0; y < 600; y++) {
            img2D[x][y] = img[c];
            c++;
        }
    }
    //------------------處理 -----------------------//
    bigger(img2D, imgBIG,255);

    dilation_Trimap(imgBIG, SE, img_out);
    bigger(img_out, imgBIG,0);
    erosion_Trimap(imgBIG, SE, img_out);

    fopen_s(&output_file, "monster_600_Trimap1.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);




    bigger(img2D, imgBIG, 255);
    erosion_Trimap(imgBIG, SE2, img_out2);
    bigger(img_out2, imgBIG, 0);
    dilation_Trimap(imgBIG, SE, img_out2);
    bigger(img_out2, imgBIG, 255);
    erosion_Trimap(imgBIG, SE, img_out2);
    bigger(img_out2, imgBIG, 0);
    erosion_Trimap(imgBIG, SE, img_out2);
    bigger(img_out2, imgBIG, 255);
    dilation_Trimap(imgBIG, SE, img_out2);
    bigger(img_out2, imgBIG, 255);
    erosion_Trimap(imgBIG, SE, img_out2);


    fopen_s(&output_file, "monster_600_Trimap2.raw", "wb");
    fwrite(img_out2, 1, size, output_file);
    fclose(output_file);


    for (int x = 0; x < 600; x++) {
        for (int y = 0; y < 600; y++) {
            if (img_out2[x][y] == 0) {
                img_out[x][y] = 0;
            }
        }
    }
    bigger(img_out, imgBIG, 0);
    erosion_Trimap(imgBIG, SE, img_out);


    fopen_s(&output_file, "monster_600_Trimap.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);

    //-------合併--------------//


    for (int x = 0; x < 600; x++) {
        for (int y = 0; y < 600; y++) {
            if (img_out2[x][y] == 0) {
                img_out3[x][y] = img2D[x][y];
            }
            else {
                img_out3[x][y] = img_out[x][y];
            }
        }
    }
    fopen_s(&output_file, out_imgpath2, "wb");
    fwrite(img_out3, 1, size, output_file);
    fclose(output_file);


    //------------------儲存檔案-----------------------//



    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);



}