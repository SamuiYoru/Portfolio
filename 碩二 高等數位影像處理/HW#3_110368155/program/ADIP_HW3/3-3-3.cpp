/******************************************************
* Filename    : 3-3-3.cpp                             *
* Update date : 28/10/2022                            *
* Author      : 顏郁芩                                *
* Note        : Histogram matching                    *
******************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
using namespace W;

void MY_HW3::HW3_3_3() {

    //--------------------------參數---------------------------//
    int H = 512;
    int W = 512;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2, * input_file3, * input_file_2;
    FILE* output_file, * output_file2;
    char in_imgpath[] = ".\\HW3_images_file\\cat_512.raw";
    char in_imgpath2[] = ".\\HW3_images_file\\catch_300x168.raw";
    char in_imgpath3[] = ".\\HW3_images_file\\traffic_970x646.raw";
    char out_imgpath[] = ".\\cat_512_with_catch_300x168.raw";
    char out_imgpath2[] = ".\\cat_512_with_traffic_970x646.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[300 * 168];
    unsigned char* img3 = new unsigned char[970 * 646];
    double HIS_1[256];
    double HIS1_1[256];
    double HIS1_2[256];
    double HIS_1_add[256];
    double HIS_2[256];
    double HIS_2_add[256];
    double HIS_3[256];
    double HIS_3_add[256];
    unsigned char img1_1[512 * 512];
    unsigned char img1_2[512 * 512];
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image cat_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image catch_300x168.raw!\n");
    }
    fread(img2, sizeof(unsigned char), 300*168, input_file2);

    fopen_s(&input_file3, in_imgpath3, "rb");
    if (!input_file3) {
        printf("Unable to open the image traffic_970x646.raw!\n");
    }
    fread(img3, sizeof(unsigned char), 970*646, input_file3);

    for (int x = 0; x < 512 * 512; x++) {
        img1_1[x] = img[x];
        img1_2[x] = img[x];
    }

    //---------------計算圖像HISTOGRAM------------//

    for (int x = 0; x < 256; x++) {
        HIS_1[x] = 0;
        HIS_2[x] = 0;
        HIS_3[x] = 0;
    }

    for (int x = 0; x < 512*512; x++) {
        HIS_1[img[x]] = HIS_1[img[x]] + 1;
    }

    for (int x = 0; x < 300 * 168; x++) {
        HIS_2[img2[x]] = HIS_2[img2[x]] + 1;
    }

    for (int x = 0; x < 970 * 646; x++) {
        HIS_3[img3[x]] = HIS_3[img3[x]] + 1;
    }


    for (int x = 0; x < 256; x++) {
        HIS_1[x] = HIS_1[x] / (512 * 512);
        HIS_2[x] = HIS_2[x] / (300 * 168);
        HIS_3[x] = HIS_3[x] / (970 * 646);
    }

    //----------------HISTOGRAM的累計圖表---------------------//
    for (int x = 0; x < 256; x++) {
        double a = 0;
        for (int y = 0; y <= x; y++) {
            a = a + HIS_1[y];
        }
        HIS_1_add[x] = a;
    }
    for (int x = 0; x < 256; x++) {
        double a = 0;
        for (int y = 0; y <= x; y++) {
            a = a + HIS_2[y];
        }
        HIS_2_add[x] = a;
    }
    for (int x = 0; x < 256; x++) {
        double a = 0;
        for (int y = 0; y <= x; y++) {
            a = a + HIS_3[y];
        }
        HIS_3_add[x] = a;
    }
    //--------------------------用OPENCV繪圖---------------------------//
    int hist_w = (256), hist_h = 512 / 2;

    Mat hist1(1, 256, CV_64F, HIS_1);
    Mat hist2(1, 256, CV_64F, HIS_2);
    Mat hist3(1, 256, CV_64F, HIS_3);


    Mat histImage(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));
    Mat histImage2(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));
    Mat histImage3(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));

    normalize(hist1, hist1, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(hist2, hist2, 0, histImage2.rows, NORM_MINMAX, -1, Mat());
    normalize(hist3, hist3, 0, histImage3.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < histImage.rows; i++)
    {
        line(histImage, Point(1 * (i), (hist_h - hist1.at<double>(i))) /*/ hist_h*3*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }

    for (int i = 0; i < histImage2.rows; i++)
    {
        line(histImage2, Point(1 * (i), (hist_h - hist2.at<double>(i)))/*hist_h - cvRound(hist1.at<int>(i - 1))*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }

    for (int i = 0; i < histImage3.rows; i++)
    {
        line(histImage3, Point(1 * (i), (hist_h - hist3.at<double>(i)))/*hist_h - cvRound(hist1.at<int>(i - 1))*/,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }


    //--------------------------用opencv 顯示並儲存HISTOGRAM---------------------------//

    imshow("Hist cat_512", histImage);
    imwrite("Hist cat_512_original.jpg", histImage);
    imshow("Hist catch_300x168", histImage2);
    imwrite("Hist catch_300x168.jpg", histImage2);
    imshow("Hist traffic_970x646", histImage3);
    imwrite("Hist traffic_970x646.jpg", histImage3);
    waitKey();
    destroyAllWindows();
    //-------------------------圖像處理 cat_512+catch_300x168------------------------//


    for (int x = 0; x < 512 * 512; x++) {
        double a = 0;
        double b = 0;
        int flag =0;
        for (int z = 0; z < 256; z++) {
            if (fabs(HIS_1_add[img[x]] - HIS_2_add[z])<0.1) {//要修改
                img1_1[x] = z;
            }
        }        
    }

    for (int x = 0; x < 256; x++) {
        HIS_1[x] = 0;
    }

    for (int x = 0; x < 512 * 512; x++) {
        HIS_1[img1_1[x]] = HIS_1[img1_1[x]] + 1;
    }
    for (int x = 0; x < 256; x++) {
        HIS_1[x] = HIS_1[x] / (512 * 512);
    }

    //-------------------------HISTOGRAM cat_512+catch_300x168------------------------//

    Mat hist1_1(1, 256, CV_64F, HIS_1);
    Mat histImage1_1(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));
    normalize(hist1_1, hist1_1, 0, histImage1_1.rows, NORM_MINMAX, -1, Mat());
    for (int i = 0; i < histImage.rows; i++)
    {
        line(histImage1_1, Point(1 * (i), (hist_h - hist1_1.at<double>(i))) ,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }


    imshow("Hist cat_512", histImage);
    imshow("Hist after_cat_512", histImage1_1);
    imwrite("Hist cat_512_with_catch.jpg", histImage1_1);
    imshow("Hist catch_300x168", histImage2);
    waitKey();
    destroyAllWindows();


    //-------------------------圖像處理 cat_512+traffic_970x646------------------------//

    for (int x = 0; x < 512 * 512; x++) {
        double a = 0;
        double b = 0;
        for (int z = 0; z < 256; z++) {
            if (fabs(HIS_1_add[img[x]] - HIS_3_add[z]) < 0.1) {//要修改
                img1_2[x] = z;
            }
        }
    }

    for (int x = 0; x < 256; x++) {
        HIS_1[x] = 0;
    }

    for (int x = 0; x < 512 * 512; x++) {
        HIS_1[img1_2[x]] = HIS_1[img1_2[x]] + 1;
    }
    for (int x = 0; x < 256; x++) {
        HIS_1[x] = HIS_1[x] / (512*512);
    }



    // ------------------------- HISTOGRAM cat_512+traffic_970x646------------------------//
    Mat hist1_2(1, 256, CV_64F, HIS_1);
    Mat histImage1_2(hist_h, hist_w, CV_64F, Scalar(255, 255, 255));
    normalize(hist1_2, hist1_2, 0, histImage1_2.rows, NORM_MINMAX, -1, Mat());
    for (int i = 0; i < histImage1_2.rows; i++)
    {
        line(histImage1_2, Point(1 * (i), (hist_h - hist1_2.at<double>(i))) ,
            Point(1 * (i), hist_h),
            Scalar(0, 0, 0), 1, 8, 0);
    }

    imshow("Hist cat_512", histImage);
    imshow("Hist after_cat_512_traffic", histImage1_2);
    imwrite("Hist cat_512_with_traffic.jpg", histImage1_2);
    imshow("Hist traffic_970x646", histImage3);
    waitKey();
    destroyAllWindows();

    //--------------------------輸出檔案---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img1_1, 1, size, output_file);

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img1_2, 1, size, output_file2);

    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    delete[] img2;
    delete[] img3;
    fclose(input_file);
    fclose(input_file2);
    fclose(input_file3);
    fclose(output_file);
    fclose(output_file2);

}