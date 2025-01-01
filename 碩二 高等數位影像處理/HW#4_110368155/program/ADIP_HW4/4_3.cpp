/*************************************************************************
* Filename    : 4_3.cpp                                                  *
* Update date : 12/11/2022                                               *
* Author      : 顏郁芩                                                   *
* Note        : appply local histogram equation on tsukuba_683x512       *
*************************************************************************/
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

void MY_HW4::HW4_3() {
    //--------------------------參數---------------------------//
    int W = 683;
    int H = 512;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2;
    FILE* output_file, * output_file2, * output_file3;
    char in_imgpath[] = ".\\HW4_images_file\\tsukuba_683x512.raw";
    char out_imgpath[] = "tsukuba_683x512_3x3.raw";
    char out_imgpath2[] = "tsukuba_683x512_5x5.raw";
    char out_imgpath3[] = "tsukuba_683x512_7x7.raw";

    int size = H * W;
    unsigned char* img = new unsigned char[size];

    double HIS_1[256];
    double HIS_2[256];
    double HIS_3[256];
    double HIS_4[256];
    unsigned char imgIN[512][683];
    unsigned char imgIN_big[512 + 6][683 + 6];
    unsigned char imgOUT[512][683];

    //unsigned char img_watermark[512][512];
    //unsigned char img_back[512][512];
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image tsukuba_683x512.raw!\n");
    }
    fread(img, sizeof(unsigned char), 683 * 512, input_file);

    //------轉成二維--------------------//
    int c = 0;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 683; y++) {
            imgIN[x][y] = img[c];
            c++;
        }

    }

    //---------------計算圖像HISTOGRAM------------//

    for (int x = 0; x < 256; x++) {
        HIS_1[x] = 0;
        HIS_2[x] = 0;
        HIS_3[x] = 0;
        HIS_4[x] = 0;
    }
    for (int x = 0; x < 512*683; x++) {
            HIS_1[img[x]] = HIS_1[img[x]] + 1;

    }
    for (int x = 0; x < 256; x++) {
        HIS_1[x] = HIS_1[x] / (512 * 683);
    }




    //--------------------------用OPENCV繪圖---------------------------//
    int hist_w = (256), hist_h = 512 / 2;

    Mat hist1(1, 256, CV_64F, HIS_1);

    Mat histImage(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist1, hist1, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histImage.rows; i++)
    {
        line(histImage, Point(1 * (i), (hist_h - hist1.at<double>(i))) /*/ hist_h*3*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }

    //--------------------------用opencv 顯示並儲存HISTOGRAM---------------------------//

    imshow("Hist tsukuba_683x512", histImage);
    imwrite("Hist tsukuba_683x512_original.jpg", histImage);
    waitKey();
    destroyAllWindows();


        //--------------------------mirroring 放大---------------------------//
    for (int x = 0; x < 512 + 6; x++) {
        for (int y = 0; y < 683 + 6; y++) {
            if (x == 0) {
                if (y == 0) {
                    imgIN_big[x][y] = imgIN[2][2];
                }
                else if (y == 1) {
                    imgIN_big[x][y] = imgIN[2][1];
                }
                else if (y == 2) {
                    imgIN_big[x][y] = imgIN[2][0];
                }
                else if (y == 686) {
                    imgIN_big[x][y] = imgIN[2][682];
                }
                else if (y == 687) {
                    imgIN_big[x][y] = imgIN[2][681];
                }
                else if (y == 688) {
                    imgIN_big[x][y] = imgIN[2][680];
                }
                else {
                    imgIN_big[x][y] = imgIN[2][y - 3];

                }
            }
            else if (x == 1) {
                if (y == 0) {
                    imgIN_big[x][y] = imgIN[1][2];
                }
                else if (y == 1) {
                    imgIN_big[x][y] = imgIN[1][1];
                }
                else if (y == 2) {
                    imgIN_big[x][y] = imgIN[1][0];
                }
                else if (y == 686) {
                    imgIN_big[x][y] = imgIN[1][682];
                }
                else if (y == 687) {
                    imgIN_big[x][y] = imgIN[1][681];
                }
                else if (y == 688) {
                    imgIN_big[x][y] = imgIN[1][680];
                }
                else {
                     imgIN_big[x][y] = imgIN[1][y - 3];

                }
            }
            else if (x == 2) {
                if (y == 0) {
                    imgIN_big[x][y] = imgIN[0][2];
                }
                else if (y == 1) {
                    imgIN_big[x][y] = imgIN[0][1];
                }
                else if (y == 2) {
                    imgIN_big[x][y] = imgIN[0][0];
                }
                else if (y == 686) {
                    imgIN_big[x][y] = imgIN[0][682];
                }
                else if (y == 687) {
                    imgIN_big[x][y] = imgIN[0][681];
                }
                else if (y == 688) {
                    imgIN_big[x][y] = imgIN[0][680];
                }
                else {
                    imgIN_big[x][y] = imgIN[0][y - 3];

                }
            }
            else if (x == 515) {
                if (y == 0) {
                    imgIN_big[x][y] = imgIN[511][2];
                }
                else if (y == 1) {
                    imgIN_big[x][y] = imgIN[511][1];
                }
                else if (y == 2) {
                    imgIN_big[x][y] = imgIN[511][0];
                }
                else if (y == 686) {
                    imgIN_big[x][y] = imgIN[511][682];
                }
                else if (y == 687) {
                    imgIN_big[x][y] = imgIN[511][681];
                }
                else if (y == 688) {
                    imgIN_big[x][y] = imgIN[511][680];
                }
                else {
                    imgIN_big[x][y] = imgIN[511][y - 3];

                }
            }
            else if (x == 516) {
                if (y == 0) {
                    imgIN_big[x][y] = imgIN[510][2];
                }
                else if (y == 1) {
                    imgIN_big[x][y] = imgIN[510][1];
                }
                else if (y == 2) {
                    imgIN_big[x][y] = imgIN[510][0];
                }
                else if (y == 686) {
                    imgIN_big[x][y] = imgIN[510][682];
                }
                else if (y == 687) {
                    imgIN_big[x][y] = imgIN[510][681];
                }
                else if (y == 688) {
                    imgIN_big[x][y] = imgIN[510][680];
                }
                else {
                    imgIN_big[x][y] = imgIN[510][y - 3];

                }
            }
            else if (x == 517) {
            if (y == 0) {
                imgIN_big[x][y] = imgIN[509][2];
            }
            else if (y == 1) {
                imgIN_big[x][y] = imgIN[509][1];
            }
            else if (y == 2) {
                imgIN_big[x][y] = imgIN[509][0];
            }
            else if (y == 686) {
                imgIN_big[x][y] = imgIN[509][682];
            }
            else if (y == 687) {
                imgIN_big[x][y] = imgIN[509][681];
            }
            else if (y == 688) {
                imgIN_big[x][y] = imgIN[509][680];
            }
            else {
                imgIN_big[x][y] = imgIN[509][y - 3];
            }
            }
            else if (y == 0) {
                imgIN_big[x][y] = imgIN[x - 3][2];
            }
            else if (y == 1) {
                imgIN_big[x][y] = imgIN[x - 3][1];
            }
            else if (y == 2) {
                imgIN_big[x][y] = imgIN[x - 3][0];
            }
            else if (y == 686) {
                imgIN_big[x][y] = imgIN[x - 3][682];
            }
            else if (y == 687) {
                imgIN_big[x][y] = imgIN[x - 3][681];
            }
            else if (y == 688) {
                imgIN_big[x][y] = imgIN[x - 3][680];
            }

            else {
                imgIN_big[x][y] = imgIN[x - 3][y - 3];
            }

        }

    }

    //---------------histogram equalization處理 3x3------------//

    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 683; y++) {

            imgOUT[x][y] = MY_HW4::histogram3(x+3, y+3, imgIN_big);
        }
    }

    //---------------計算圖像HISTOGRAM  3x3 處理完------------//

    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 683; y++) {
            HIS_2[imgOUT[x][y]] = HIS_2[imgOUT[x][y]] + 1;
        }

    }

    for (int x = 0; x < 256; x++) {
        HIS_2[x] = HIS_2[x] / (512 * 683);
    }

    //--------------------------用OPENCV繪圖 3x3 處理完---------------------------//

    Mat hist2(1, 256, CV_64F, HIS_2);

    Mat histImage2(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist2, hist2, 0, histImage2.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histImage2.rows; i++)
    {
        line(histImage2, Point(1 * (i), (hist_h - hist2.at<double>(i))) /*/ hist_h*3*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }

    //--------------------------用opencv 顯示並儲存HISTOGRAM 3x3 處理完---------------------------//

    imshow("Hist tsukuba_683x512_3x3", histImage2);
    imwrite("Hist tsukuba_683x512_3x3.jpg", histImage2);
    waitKey();
    destroyAllWindows();

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(imgOUT, 1, size, output_file);
    fclose(output_file);


    //------------歸零----------------//

    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 683; y++) {
            imgOUT[x][y] =0;
        }
    }



    //---------------histogram equalization處理 5x5------------//
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 683; y++) {
            imgOUT[x][y] = MY_HW4::hq5(x + 3, y + 3, imgIN_big);
        }
    }

    //---------------做完之後計算圖像HISTOGRAM 5x5 處理完------------//

    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 683; y++) {
            HIS_3[imgOUT[x][y]] = HIS_3[imgOUT[x][y]] + 1;
        }

    }

    for (int x = 0; x < 256; x++) {
        HIS_3[x] = HIS_3[x] / (512 * 683);
    }

    //--------------------------用OPENCV繪圖  5x5 處理完---------------------------//

    Mat hist3(1, 256, CV_64F, HIS_3);

    Mat histImage3(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist3, hist3, 0, histImage3.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histImage3.rows; i++)
    {
        line(histImage3, Point(1 * (i), (hist_h - hist3.at<double>(i))) /*/ hist_h*3*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }

    //--------------------------用opencv 顯示並儲存HISTOGRAM 5x5 處理完---------------------------//

    imshow("Hist tsukuba_683x512_5x5", histImage3);
    imwrite("Hist tsukuba_683x512_5x5.jpg", histImage3);
    waitKey();
    destroyAllWindows();

    fopen_s(&output_file, out_imgpath2, "wb");
    fwrite(imgOUT, 1, size, output_file);
    fclose(output_file);


    //---------------histogram equalization處理 7x7------------//
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 683; y++) {
            imgOUT[x][y] = MY_HW4::h7(x + 3, y + 3, imgIN_big);
        }
    }

     //---------------做完之後計算圖像HISTOGRAM 7x7 處理完------------//

    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 683; y++) {
            HIS_4[imgOUT[x][y]] = HIS_4[imgOUT[x][y]] + 1;
        }

    }

    for (int x = 0; x < 256; x++) {
        HIS_4[x] = HIS_4[x] / (512 * 683);
    }

    //--------------------------用OPENCV繪圖 7x7 處理完---------------------------//

    Mat hist4(1, 256, CV_64F, HIS_4);

    Mat histImage4(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist4, hist4, 0, histImage4.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histImage4.rows; i++)
    {
        line(histImage4, Point(1 * (i), (hist_h - hist4.at<double>(i))) /*/ hist_h*3*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }





    //--------------------------用opencv 顯示並儲存HISTOGRAM 7x7 處理完---------------------------//

    imshow("Hist tsukuba_683x512_7x7", histImage4);
    imwrite("Hist tsukuba_683x512_7x7.jpg", histImage4);
    waitKey();
    destroyAllWindows();

    fopen_s(&output_file, out_imgpath3, "wb");
    fwrite(imgOUT, 1, size, output_file);
    fclose(output_file);


    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);






}