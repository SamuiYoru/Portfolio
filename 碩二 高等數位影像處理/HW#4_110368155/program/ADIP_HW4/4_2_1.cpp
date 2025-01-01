/*****************************************************************************
* Filename    : 4_2_1.cpp                                                    *
* Update date : 12/11/2022                                                   *
* Author      : 顏郁芩                                                       *
* Note        : block&white_256 and chessboard_256 with 5x5 mean filter      *
*****************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace W;
using namespace cv;

void MY_HW4::HW4_2_1() {
    //--------------------------參數---------------------------//
    int H = 256;
    int W = 256;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2;
    FILE* output_file, * output_file2;
    char in_imgpath[] = ".\\HW4_images_file\\block&white_256.raw";
    char in_imgpath2[] = ".\\HW4_images_file\\chessboard_256.raw";
    char out_imgpath[] = "block&white_256_mean.raw";
    char out_imgpath2[] = "chessboard_256_mean.raw";

    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    double HIS_1[256];
    double HIS_2[256];
    unsigned char img_input1[256][256];
    unsigned char img_input2[256][256];
    unsigned char img_input1_big[256+4][256+4];
    unsigned char img_input2_big[256 + 4][256 + 4];
    unsigned char img_output1[256][256];
    unsigned char img_output2[256][256];
    //unsigned char img_watermark[512][512];
    //unsigned char img_back[512][512];
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image block&white_256.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image chessboard_256.raw!\n");
    }
    fread(img2, sizeof(unsigned char), size, input_file2);


    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_input1[x][y] = img[c];
            img_input2[x][y] = img2[c];
            c++;
        }
    }

    //---------------計算圖像HISTOGRAM------------//

    for (int x = 0; x < 256; x++) {
        HIS_1[x] = 0;
        HIS_2[x] = 0;
    }

    for (int x = 0; x < 256 * 256; x++) {
        HIS_1[img[x]] = HIS_1[img[x]] + 1;
        HIS_2[img2[x]] = HIS_2[img2[x]] + 1;
    }
    for (int x = 0; x < 256; x++) {
        HIS_1[x] = HIS_1[x] / (256 * 256);
        HIS_2[x] = HIS_2[x] / (256 * 256);
    }

 
    //--------------------------用OPENCV繪圖---------------------------//
    int hist_w = (256), hist_h = 256;

    Mat hist1(1, 256, CV_64F, HIS_1);
    Mat histImage(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist1, hist1, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histImage.rows; i++)
    {
        line(histImage, Point(1 * (i), (hist_h - hist1.at<double>(i))) /*/ hist_h*3*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }

    Mat hist2(1, 256, CV_64F, HIS_2);
    Mat histImage2(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist2, hist2, 0, histImage2.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histImage2.rows; i++)
    {
        line(histImage2, Point(1 * (i), (hist_h - hist1.at<double>(i))) /*/ hist_h*3*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }

 
    //--------------------------用opencv 顯示並儲存HISTOGRAM---------------------------//

    imshow("Hist block&white_256", histImage);
    imshow("Hist chessboard_256", histImage2);
    imwrite("Hist block&white_256.jpg", histImage);
    imwrite("Hist chessboard_256.jpg", histImage2);
    waitKey();
    destroyAllWindows();

    //--------------------------mirroring 放大---------------------------//
    for (int x = 0; x < 256 + 4; x++) {
        for (int y = 0; y < 256 + 4; y++) {
            if (x == 0) {
                if (y == 0) {
                    img_input1_big[x][y] = img_input1[1][1];
                    img_input2_big[x][y] = img_input2[1][1];
                }
                else if (y == 1) {
                    img_input1_big[x][y] = img_input1[1][0];
                    img_input2_big[x][y] = img_input2[1][0];
                }
                else if (y == 258) {
                    img_input1_big[x][y] = img_input1[1][255];
                    img_input2_big[x][y] = img_input2[1][255];
                }
                else if (y == 259) {
                    img_input1_big[x][y] = img_input1[1][254];
                    img_input2_big[x][y] = img_input2[1][254];
                }
                else {
                    img_input1_big[x][y] = img_input1[1][y - 2];
                    img_input2_big[x][y] = img_input2[1][y - 2];
                }
            }
            else if (x == 1) {
                if (y == 0) {
                    img_input1_big[x][y] = img_input1[0][1];
                    img_input2_big[x][y] = img_input2[0][1];
                }
                else if (y == 1) {
                    img_input1_big[x][y] = img_input1[0][0];
                    img_input2_big[x][y] = img_input2[0][0];
                }
                else if (y == 258) {
                    img_input1_big[x][y] = img_input1[0][255];
                    img_input2_big[x][y] = img_input2[0][255];
                }
                else if (y == 259) {
                    img_input1_big[x][y] = img_input1[0][254];
                    img_input2_big[x][y] = img_input2[0][254];
                }
                else {
                    img_input1_big[x][y] = img_input1[0][y - 2];
                    img_input2_big[x][y] = img_input2[0][y - 2];
                }
            }
            else if (x == 258) {
                if (y == 0) {
                    img_input1_big[x][y] = img_input1[255][1];
                    img_input2_big[x][y] = img_input2[255][1];
                }
                else if (y == 1) {
                    img_input1_big[x][y] = img_input1[255][0];
                    img_input2_big[x][y] = img_input2[255][0];
                }
                else if (y == 258) {
                    img_input1_big[x][y] = img_input1[255][255];
                    img_input2_big[x][y] = img_input2[255][255];
                }
                else if (y == 259) {
                    img_input1_big[x][y] = img_input1[255][254];
                    img_input2_big[x][y] = img_input2[255][254];
                }
                else {
                    img_input1_big[x][y] = img_input1[255][y - 2];
                    img_input2_big[x][y] = img_input2[255][y - 2];
                }
            }
            else if (x == 259) {
                if (y == 0) {
                    img_input1_big[x][y] = img_input1[254][1];
                    img_input2_big[x][y] = img_input2[254][1];
                }
                else if (y == 1) {
                    img_input1_big[x][y] = img_input1[254][0];
                    img_input2_big[x][y] = img_input2[254][0];
                }
                else if (y == 258) {
                    img_input1_big[x][y] = img_input1[254][255];
                    img_input2_big[x][y] = img_input2[254][255];
                }
                else if (y == 259) {
                    img_input1_big[x][y] = img_input1[254][254];
                    img_input2_big[x][y] = img_input2[254][254];
                }
                else {
                    img_input1_big[x][y] = img_input1[254][y - 2];
                    img_input2_big[x][y] = img_input2[254][y - 2];
                }
            }
            else if (y == 0) {
                img_input1_big[x][y] = img_input1[x - 2][1];
                img_input2_big[x][y] = img_input2[x - 2][1];
            }
            else if (y == 1) {
                img_input1_big[x][y] = img_input1[x - 2][0];
                img_input2_big[x][y] = img_input2[x - 2][0];
            }
            else if (y == 258) {
                img_input1_big[x][y] = img_input1[x - 2][255];
                img_input2_big[x][y] = img_input2[x - 2][255];
            }
            else if (y == 259) {
                img_input1_big[x][y] = img_input1[x - 2][254];
                img_input2_big[x][y] = img_input2[x - 2][254];
            }

            else {
                img_input1_big[x][y] = img_input1[x - 2][y - 2];
                img_input2_big[x][y] = img_input2[x - 2][y - 2];
            }

        }

    }
    //-----------------mean filter-------------------//
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            img_output1[x][y] = MY_HW4::convolution5X5_mean(x + 2, y + 2, img_input1_big);
            img_output2[x][y] = MY_HW4::convolution5X5_mean(x + 2, y + 2, img_input2_big);
        }
    }



    //---------------計算圖像HISTOGRAM  處理後------------//

    for (int x = 0; x < 256; x++) {
        HIS_1[x] = 0;
        HIS_2[x] = 0;
    }

    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            HIS_1[img_output1[x][y]] = HIS_1[img_output1[x][y]] + 1;
            HIS_2[img_output2[x][y]] = HIS_2[img_output2[x][y]] + 1;
        }
    }
    for (int x = 0; x < 256; x++) {
        HIS_1[x] = HIS_1[x] / (256 * 256);
        HIS_2[x] = HIS_2[x] / (256 * 256);
    }


    //--------------------------用OPENCV繪圖  處理後---------------------------//

    Mat hist3(1, 256, CV_64F, HIS_1);
    Mat histImage3(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist3, hist3, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histImage3.rows; i++)
    {
        line(histImage3, Point(1 * (i), (hist_h - hist3.at<double>(i))) /*/ hist_h*3*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }

    Mat hist4(1, 256, CV_64F, HIS_2);
    Mat histImage4(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist4, hist4, 0, histImage4.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histImage2.rows; i++)
    {
        line(histImage4, Point(1 * (i), (hist_h - hist4.at<double>(i))) /*/ hist_h*3*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }


    //--------------------------用opencv 顯示並儲存HISTOGRAM  處理後---------------------------//

    imshow("Hist block&white_256_mean filter", histImage3);
    imshow("Hist chessboard_256_mean filter", histImage4);
    imwrite("Hist block&white_256_mean filter.jpg", histImage3);
    imwrite("Hist chessboard_256_mean filter.jpg", histImage4);
    waitKey();
    destroyAllWindows();




    //--------------------------輸出檔案---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img_output1, 1, 256*256, output_file);

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img_output2, 1, 256*256, output_file2);

    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    delete[] img2;
    fclose(input_file);
    fclose(input_file2);
    fclose(output_file);
    fclose(output_file2);





}