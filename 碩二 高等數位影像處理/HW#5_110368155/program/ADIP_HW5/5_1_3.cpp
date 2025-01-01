/*********************************************************************************************
* Filename    : 5_1_3.cpp                                                                    *
* Update date : /11/2022                                                                     *
* Author      : 顏郁芩                                                                       *
* Note        : Design your own IDFT and compute MSE                                         *
*********************************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
using namespace W;


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/core.hpp"
#define _CRT_SECURE_NO_WARNINGS
#define intsize sizeof(int)
#define complexsize sizeof(complex)
#define PI 3.1415926
using namespace cv;

void MY_HW5::HW5_1_3() {
    MY_HW5 HW5;
    clock_t start, end;
    //--------------------------參數---------------------------/

    FILE* input_file, * input_file2, * input_file3;
    char in_imgpath[] = ".\\DFTrhombus_256.raw";
    char in_imgpath2[] = ".\\DFTsine_128.raw";
    char in_imgpath3[] = ".\\DFTlena_256.raw";

    FILE* output_file;
    char out_imgpath[] = ".\\IDFT_DFTrhombus_256.raw";
    char out_imgpath2[] = ".\\IDFT_DFTsine_128.raw";
    char out_imgpath3[] = ".\\IDFT_DFTlena_256.raw";


    int size = 256 * 256;
    int size2 = 128 * 125;

    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size2];
    unsigned char* img3 = new unsigned char[size];

    unsigned char img1_1[256 * 256];
    unsigned char img3_1[256 * 256];
    unsigned char img2_1[128 * 128];
    unsigned char img_input[256][256];
    unsigned char img_input2[128][128];
    unsigned char img_input3[256][256];
    unsigned char DFTvalue[256][256];
    unsigned char DFTvalue2[128][128];
    unsigned char DFTvalue3[256][256];



    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image rhombus_256.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);


    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image sine_128.raw!\n");
    }
    fread(img2, sizeof(unsigned char), size2, input_file2);


    fopen_s(&input_file3, in_imgpath3, "rb");
    if (!input_file3) {
        printf("Unable to open the image lena_256.raw!\n");
    }
    fread(img3, sizeof(unsigned char), size, input_file3);



    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_input[x][y] = img[c];
            img_input3[x][y] = img3[c];
            c++;
        }
    }

    c = 0;
    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 128; y++) {
            img_input2[x][y] = img2[c];
            c++;
        }
    }

    //------------------處理------------------------//
    start = clock();
    //MY_HW5::DFT256(img_input, DFTvalue);
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by MY DFT is : " << fixed << time_taken << setprecision(6) << " sec " << endl;

    //MY_HW5::DFT128(img_input2, DFTvalue2);
    //MY_HW5::DFT256(img_input3, DFTvalue3);
    
   
    int co = 0;
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img1_1[co] = DFTvalue[y][x];
            img3_1[co] = DFTvalue3[y][x];
            co++;
        }

    }
    co = 0;
    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 128; y++) {
            img2_1[co] = DFTvalue2[y][x];

            co++;
        }
    }


    //--------------------------用OPENCV繪圖---------------------------//
    int pic_w = (256), pic_h = 256;

    Mat hist1(256, 256, CV_8UC1, img1_1);
    Mat hist2(128, 128, CV_8UC1, img2_1);
    Mat hist3(256, 256, CV_8UC1, img3_1);


    Mat DFT1(pic_h, pic_w, CV_64F, Scalar(255, 255, 255));//CV_64F
    Mat DFT2(pic_h / 2, pic_w / 2, CV_64F, Scalar(255, 255, 255));
    Mat DFT3(pic_h, pic_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist1, hist1, 0, DFT1.rows, NORM_MINMAX, -1, Mat());
    normalize(hist2, hist2, 0, DFT2.rows, NORM_MINMAX, -1, Mat());
    normalize(hist3, hist3, 0, DFT3.rows, NORM_MINMAX, -1, Mat());



    //--------------------------用opencv 顯示並儲存---------------------------//

    imshow("IDFT rhombus_256", hist1);
    //imwrite("IDFT rhombus_256.jpg", hist1);
    imshow("IDFT　sine_128", hist2);
    //imwrite("IDFT　sine_128.jpg", hist2);
    imshow("IDFT lena_256", hist3);
    //imwrite("IDFT lena_256.jpg", hist3);
    waitKey();
    destroyAllWindows();


    //------用OPENCV rhombus_256 IDFT------//
    start = clock();

    
    
    end = clock();
    double time_taken2 = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by OPENCV DFT is : " << fixed << time_taken2 << setprecision(6) << " sec " << endl;
    //imshow("rhombus_256 spectrum magnitude", mag);
    //imwrite("rhombus_256 spec.jpg", mag);
    //waitKey();


    //------用OPENCV sine_128 IDFT------//
    

    //------用OPENCV lena_256 IDFT------//
    

    //--------------------------儲存檔案---------------------------//

    //fopen_s(&output_file, out_imgpath, "wb");
    //fwrite(img1_1, 1, size, output_file);
    //fclose(output_file);

    //fopen_s(&output_file, out_imgpath2, "wb");
    //fwrite(img2_1, 1, size, output_file);
    //fclose(output_file);

    //fopen_s(&output_file, out_imgpath3, "wb");
    //fwrite(img3_1, 1, size, output_file);
    //fclose(output_file);


    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(input_file2);
    fclose(input_file3);

}