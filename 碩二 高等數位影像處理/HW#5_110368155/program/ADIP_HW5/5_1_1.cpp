/*********************************************************************************************
* Filename    : 5_1_1.cpp                                                                    *
* Update date : 26/11/2022                                                                   *
* Author      : 顏郁芩                                                                       *
* Note        : Write your own DFT                                                           *
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
/*#define intsize sizeof(int)
#define complexsize sizeof(complex)
#define PI 3.1415926*/
using namespace cv;

void MY_HW5::HW5_1_1() {
    MY_HW5 HW5;
    //--------------------------參數---------------------------//
    clock_t start, end;

    FILE* input_file, * input_file2, * input_file3;
    char in_imgpath[] = ".\\HW5_images_file\\rhombus_256.raw";
    char in_imgpath2[] = ".\\HW5_images_file\\sine_128.raw";
    char in_imgpath3[] = ".\\HW5_images_file\\lena_256.raw";

    FILE* output_file;
    char out_imgpath[] = ".\\DFTrhombus_256.raw";
    char out_imgpath2[] = ".\\DFTsine_128.raw";
    char out_imgpath3[] = ".\\DFTlena_256.raw";


    int size = 256 * 256;
    int size2 = 128 * 128;

    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size2];
    unsigned char* img3 = new unsigned char[size];

    unsigned char img1_1[256*256];
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
    MY_HW5::DFT256(img_input, DFTvalue);
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by MY DFT is : " << fixed << time_taken << setprecision(6) << " sec " << endl;

    MY_HW5::DFT128(img_input2, DFTvalue2);
    MY_HW5::DFT256(img_input3, DFTvalue3);

    int co = 0;
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img1_1[co] = DFTvalue[x][y];
            img3_1[co] = DFTvalue3[x][y];
            co++;
            //cout << +DFTvalue[x][y] << endl;
        }
    }

    co = 0;
    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 128; y++) {
            img2_1[co] = DFTvalue2[x][y];
            co++;
        }
    }


    //--------------------------用OPENCV繪圖---------------------------//

    /*int pic_w = (256), pic_h = 256;

    Mat hist1(256, 256, CV_64F, DFTvalue);
    Mat hist2(128, 128, CV_64F, DFTvalue2);
    Mat hist3(256, 256, CV_64F, DFTvalue3);


    Mat DFT1(pic_h, pic_w, CV_64F, Scalar(255, 255, 255));//CV_64F
    Mat DFT2(pic_h/2, pic_w/2, CV_64F, Scalar(255, 255, 255));
    Mat DFT3(pic_h, pic_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist1, hist1, 0, DFT1.rows, NORM_MINMAX, -1, Mat());
    normalize(hist2, hist2, 0, DFT2.rows, NORM_MINMAX, -1, Mat());
    normalize(hist3, hist3, 0, DFT3.rows, NORM_MINMAX, -1, Mat());*/



    //--------------------------用opencv 顯示並儲存---------------------------//

    /*imshow("DFT rhombus_256", hist1);
    imwrite("DFT rhombus_256.jpg", hist1);
    imshow("DFT　sine_128", hist2);
    imwrite("DFT　sine_128.jpg", hist2);
    imshow("DFT lena_256", hist3);
    imwrite("DFT lena_256.jpg", hist3);
    waitKey();
    destroyAllWindows();*/


    //------用OPENCV rhombus_256------//
    start = clock();

    Mat imgCV(256, 256, CV_8UC1, img);
    int M = getOptimalDFTSize(imgCV.rows);                              
    int N = getOptimalDFTSize(imgCV.cols);                                 
    Mat padded;
    copyMakeBorder(imgCV, padded, 0, M - imgCV.rows, 0, N - imgCV.cols, BORDER_CONSTANT, Scalar::all(0));   

    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };         
    Mat complexImg;
    merge(planes, 2, complexImg);                                                                             

    dft(complexImg, complexImg);                                                                             

                                                                                                              
    split(complexImg, planes);                                                                                     
    magnitude(planes[0], planes[1], planes[0]);                                                          
    Mat mag = planes[0];
    mag += Scalar::all(1);
    log(mag, mag);                                                                                                     

                                                                                                                        

    int cx = mag.cols / 2;
    int cy = mag.rows / 2;

 
    Mat tmp;
    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(mag, mag, 0, 1, NORM_MINMAX);                                                        
    end = clock();
    double time_taken2 = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by OPENCV DFT is : " << fixed << time_taken2 << setprecision(6) << " sec " << endl;
    imshow("rhombus_256 spectrum magnitude", mag);
    mag = mag * 255;
    imwrite("rhombus_256 spec.jpg", mag);
    waitKey();


    //------用OPENCV sine_128------//
    Mat imgCV2(128, 128, CV_8UC1, img2);
    int M2 = getOptimalDFTSize(imgCV2.rows);                              
    int N2 = getOptimalDFTSize(imgCV2.cols);                                 
    Mat padded2;
    copyMakeBorder(imgCV2, padded2, 0, M2 - imgCV2.rows, 0, N2 - imgCV2.cols, BORDER_CONSTANT, Scalar::all(0));   

    Mat planes2[] = { Mat_<float>(padded2), Mat::zeros(padded2.size(), CV_32F) };          
    Mat complexImg2;
    merge(planes2, 2, complexImg2);                                                                              

    dft(complexImg2, complexImg2);                                                                              

                                                                                                              
    split(complexImg2, planes2);                                                                                     
    magnitude(planes2[0], planes2[1], planes2[0]);                                                          
    Mat mag2 = planes2[0];
    mag2 += Scalar::all(1);
    log(mag2, mag2);                                                                                                      


    int cx2 = mag2.cols / 2;
    int cy2 = mag2.rows / 2;
    Mat tmp2;
    Mat q02(mag2, Rect(0, 0, cx2, cy2));
    Mat q12(mag2, Rect(cx2, 0, cx2, cy2));
    Mat q22(mag2, Rect(0, cy2, cx2, cy2));
    Mat q32(mag2, Rect(cx2, cy2, cx2, cy2));

    q02.copyTo(tmp2);
    q32.copyTo(q02);
    tmp2.copyTo(q32);

    q12.copyTo(tmp2);
    q22.copyTo(q12);
    tmp2.copyTo(q22);

    normalize(mag2, mag2, 0, 1, NORM_MINMAX);                                                           

    imshow("sine_128 spectrum magnitude", mag2);
    mag2 = mag2 * 255;
    imwrite("sine_128 spec.jpg", mag2);
    waitKey();

    //------用OPENCV lena_256------//
    Mat imgCV3(256, 256, CV_8UC1, img3);
    int M3 = getOptimalDFTSize(imgCV3.rows);                              
    int N3 = getOptimalDFTSize(imgCV3.cols);                                
    Mat padded3;
    copyMakeBorder(imgCV3, padded3, 0, M3 - imgCV3.rows, 0, N3 - imgCV3.cols, BORDER_CONSTANT, Scalar::all(0));   

    Mat planes3[] = { Mat_<float>(padded3), Mat::zeros(padded3.size(), CV_32F) };          
    Mat complexImg3;
    merge(planes3, 2, complexImg3);                                                          

    dft(complexImg3, complexImg3);                                                                              

                                                                                                              
    split(complexImg3, planes3);                                                                                     
    magnitude(planes3[0], planes3[1], planes3[0]);                                                         
    Mat mag3 = planes3[0];
    mag3 += Scalar::all(1);
    log(mag3, mag3);                                                                                                   

                                                        
    Mat tmp3;
    Mat q03(mag3, Rect(0, 0, cx, cy));
    Mat q13(mag3, Rect(cx, 0, cx, cy));
    Mat q23(mag3, Rect(0, cy, cx, cy));
    Mat q33(mag3, Rect(cx, cy, cx, cy));

    q03.copyTo(tmp3);
    q33.copyTo(q03);
    tmp3.copyTo(q33);

    q13.copyTo(tmp3);
    q23.copyTo(q13);
    tmp3.copyTo(q23);

    normalize(mag3, mag3, 0, 1, NORM_MINMAX);                                                           

    imshow("lena_256 spectrum magnitude", mag3);
    mag3 = mag3 * 255;
    imwrite("lena_256 spec.jpg", mag3);
    waitKey();
    destroyAllWindows();


    /*for (int x = 0; x < 256 * 256; x++) {
        img1_1[x] = mag.at<float>(x);
        img3_1[x] = mag3.at<float>(x);
    }

    for (int x = 0; x < 128 * 128; x++) {
        img2_1[x] = mag2.at<float>(x);
    }*/

    //--------------------------儲存檔案---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img1_1, 1, size, output_file);
    fclose(output_file);

    fopen_s(&output_file, out_imgpath2, "wb");
    fwrite(img2_1, 1, size2, output_file);
    fclose(output_file);

    fopen_s(&output_file, out_imgpath3, "wb");
    fwrite(img3_1, 1, size, output_file);
    fclose(output_file);


    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(input_file2);
    fclose(input_file3);

}