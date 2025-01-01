/***********************************************************************************
* Filename    : 2-3.cpp                                                            *
* Update date : 16/10/2022                                                         *
* Author      : 顏郁芩                                                             *
* Note        : zoom in the range of (177,108) to (276,249) in duck900X600         *
                with bilinear and bicubic algorithms                               *
***********************************************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include<cmath>
#include<iomanip>
#include <windows.h>
using namespace std;
using namespace W;



float bicubic(double a_value, double b_value, double c_value, double d_value, double point_location) {//Cubic Spline Interpolation
    //(a,a_value),(b,b_value),(c,c_value),(d,d_value)
    //m1*(x-a)(x-b)(x-c)(x-d)+m2(x - a)(x - b)(x - c)+m3(x - a)(x - b)+m2(x - a)+m1=0
    //用四個點找方程式並把點帶進去求解，回傳解答

    float e_value = 0;
    float y0, y1, y2;
    float a0, b0, c0, d0;
    float a1, b1, c1, d1;
    float a2, b2, c2, d2;
    y0 = b_value - a_value;
    y1 = c_value - b_value;
    y2 = d_value - c_value;
    
    c2 = -5 * y0 + 3 * y1 - 16 * y2;
    b1 = 6.5 * y0 + 2 * y1 + 8 * y2;
    a2 = -0.625 * y0 + 5 * y1 + 14 * y2;
    b2 = 1.25 * y0 - 10 * y1 - 28 * y2;
    b0 = 1.75 * y0 + y1 + 4 * y2;

    d0 = a_value;
    d1 = b_value;
    d2 = c_value;
    a0 = (b1 - b0) / 3;
    a1 = (b2 - b1) / 3;
    c0 = 0;
    c1 = y1 - b1 - (b2 - b1) / 3;

    e_value = a1* point_location* point_location* point_location + b1* point_location* point_location + c1* point_location + d1;

    if (e_value >= 255) {
        e_value = 255;
    }
    if (e_value <= 0) {
        e_value = 0;
    }
    return e_value;
}



void MY_HW2::HW2_2_3() {
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);
    FILE* input_file1;
    FILE* output_file1, * output_file2, * output_file;
    char in_imgpath1[] = ".\\HW2_images_file\\duck900x660.raw";
    char out_imgpath[] = ".\\duck_range.raw";
    char out_imgpath1[] = ".\\duck_biliner.raw";
    char out_imgpath2[] = ".\\duck_bicubic.raw";
    unsigned char* imgIN = new unsigned char[900 * 660];
    unsigned char img[249-108+1+4][276 - 177 +1+4];//146*104
    unsigned char img_biliner[(249 - 108 + 1) * 5][(276 - 177 + 1) * 5];//先用四倍試試看
    unsigned char img_bicubic[(249 - 108 + 1) * 5][(276 - 177 + 1) * 5];
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file1, in_imgpath1, "rb");
    if (!input_file1) {
        printf("Unable to open the image duck!\n");
    }
    fread(imgIN, sizeof(unsigned char), (900 * 660), input_file1);

    //--------------------------轉成二維陣列---------------------------//
    //int c = 97378;//97376? 100*141
    //for (int x = 0; x < 142; x++) {
     //   for (int y = 0; y < 100; y++) {
     //       img[x][y] = imgIN[c];
    //
     //       c++;
    //    }
    //    c = c + 800;
    //}
    // 
    //可能需要再往外兩PIXEL img[x][y]是原圖
    int c = 0;
    c = 95574;//95574; //104*146
    for (int x = 0; x < 146; x++) {
        for (int y = 0; y < 100+4; y++) {
            img[x][y] = imgIN[c];

            c=c+1;
        }
        c = c + 800-4;
    }
    //再往外兩PIXEL

    //--------------------------bilinear放大---------------------------//

    for (int x = 0; x < 710; x++) {//568
        for (int y = 0; y < 500; y++) {
            double y1 = y % 5;
            double x1 = x % 5;
            double posy = y1 * 0.2;
            double posx = x1 * 0.2;

            double v0, v1;
            int y_pos,x_pos;

            v0 = bilnear(0, img[x/5+2][y / 5+2], 1, img[x/5+2][y / 5+1+2],posy) ;
            v1 = bilnear(0, img[x /5+1+2][y /5+2], 1, img[x /5+1+2][y /5 + 1+2], posy);
            img_biliner[x][y] = bilnear(0, v0, 1, v1, posx);
        }

    }
    //--------------------------bicubic放大---------------------------//
    for (int x = 0; x < 710; x++) {
        for (int y = 0; y < 500; y++) {
            double y1 = y % 5;
            double x1 = x % 5;
            double posy = y1 * 0.2;
            double posx = x1 * 0.2;

            double v0, v1, v2, v3;
            int y_pos, x_pos;

            v0 = bicubic(img[x / 5 + 1][y / 5 + 1], img[x / 5 + 1][y / 5 + 2], img[x / 5 + 1][y / 5 + 3], img[x / 5 + 1][y / 5 + 3], posy);
            v1 = bicubic(img[x / 5 + 2][y / 5 + 1], img[x / 5 + 2][y / 5 + 2], img[x / 5 + 2][y / 5 + 3], img[x / 5 + 2][y / 5 + 3], posy);
            v2 = bicubic(img[x / 5 + 2 + 1][y / 5 + 1], img[x / 5 + 2 + 1][y / 5 + 2], img[x / 5 + 2 + 1][y / 5 + 3], img[x / 5 + 2 + 1][y / 5 + 3], posy);
            v3 = bicubic(img[x / 5 + 2 + 2][y / 5 + 1], img[x / 5 + 2 + 2][y / 5 + 2], img[x / 5 + 2 + 2][y / 5 + 3], img[x / 5 + 2 + 2][y / 5 + 3], posy);

            img_bicubic[x][y] = bicubic(v0, v1, v2, v3, posx);
        }
    }
    //double Te = bicubic(img[50 / 4 + 1][100 / 4 + 1], img[50 / 4 + 1][100 / 4 + 2], img[50 / 4 + 1][100 / 4 + 3], img[50 / 4 + 1][100 / 4 + 3], 0)
        //cout << img[50 / 4 + 1][100 / 4 + 2] - img[50 / 4 + 1][100 / 4 + 1] <<" " << img[50 / 4 + 1][100 / 4 + 3] - img[50 / 4 + 1][100 / 4 + 2] <<" " << img[50 / 4 + 1][100 / 4 + 3] - img[50 / 4 + 1][100 / 4 + 3] << endl;
        //cout << +img[50 / 4 + 1][100 / 4 + 1] << "　" << +img[50 / 4 + 1][100 / 4 + 2] << " " << +img[50 / 4 + 1][100 / 4 + 3] << " " << +img[50 / 4 + 1][100 / 4 + 3] << endl;


    //--------------------------輸出檔案---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img, 1, (249 - 108 + 1 + 4)  * (276 - 177 + 1 + 4), output_file);


    fopen_s(&output_file1, out_imgpath1, "wb");
    fwrite(img_biliner, 1, (276 - 177 + 1) * 5 * (249 - 108 + 1) * 5, output_file1);

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img_bicubic, 1, (276 - 177 + 1) * 5 * (249 - 108 + 1) * 5, output_file2);


    //--------------------------釋出記憶體---------------------------//
    delete[] imgIN;
    fclose(input_file1);
    fclose(output_file);
    fclose(output_file1);
    fclose(output_file2);


}