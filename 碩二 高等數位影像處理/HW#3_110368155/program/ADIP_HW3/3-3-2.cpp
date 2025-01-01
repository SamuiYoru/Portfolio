/******************************************************
* Filename    : 3-3-2.cpp                             *
* Update date : 28/10/2022                            *
* Author      : 顏郁芩                                *
* Note        : Apply histogram equalization          *
******************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
using namespace W;


void MY_HW3::HW3_3_2() {
    //--------------------------參數---------------------------//
    int H = 800;
    int W = 600;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2, * input_file3;
    FILE* output_file, * output_file2, * output_file3;
    char in_imgpath[] = ".\\HW3_images_file\\meerkat_dark_800x600.raw";
    char in_imgpath2[] = ".\\HW3_images_file\\meerkat_bright_800x600.raw";
    char in_imgpath3[] = ".\\HW3_images_file\\meerkat_high_contrast_800x600.raw";
    char out_imgpath[] = ".\\meerkat_dark_800x600_histogram_equalization.raw";
    char out_imgpath2[] = ".\\meerkat_bright_800x600_histogram_equalization.raw";
    char out_imgpath3[] = ".\\meerkat_high_contrast_800x600_histogram_equalization.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    unsigned char* img3 = new unsigned char[size];
    double HIS_1[256];
    double HIS_2[256];
    double HIS_3[256];
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image meerkat_dark_800x600.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image meerkat_bright_800x600.raw!\n");
    }
    fread(img2, sizeof(unsigned char), size, input_file2);

    fopen_s(&input_file3, in_imgpath3, "rb");
    if (!input_file3) {
        printf("Unable to open the image meerkat_high_contrast_800x600.raw!\n");
    }
    fread(img3, sizeof(unsigned char), size, input_file3);



    //---------------計算圖像HISTOGRAM------------//
    
    for (int x = 0; x < 256; x++) {
        HIS_1[x] = 0;
        HIS_2[x] = 0;
        HIS_3[x] = 0;
    }
    
    for (int x = 0; x < 800 * 600; x++) {
        HIS_1[img[x]] = HIS_1[img[x]] + 1;

    }

    for (int x = 0; x < 800 * 600; x++) {
        HIS_2[img2[x]] = HIS_2[img2[x]] + 1;
    }

    for (int x = 0; x < 800 * 600; x++) {
        HIS_3[img3[x]] = HIS_3[img3[x]] + 1;
    }


    for (int x = 0; x < 256; x++) {
        HIS_1[x] = HIS_1[x] / size;
        HIS_2[x] = HIS_2[x] / size;
        HIS_3[x] = HIS_3[x] / size;
    }

    //---------------histogram equalization處理------------//
   
    for (int x = 0; x < 800 * 600; x++) {
        double a = 0;
        for (int y = 0; y < img[x]; y++) {
            a = a + HIS_1[y]; 
        } 
        img[x] = a * 256;
    }

    for (int x = 0; x < 800 * 600; x++) {
        double a = 0;
        for (int y = 0; y < img2[x]; y++) {
            a = a + HIS_2[y];
        }
        img2[x] = a * 256;
    }

    for (int x = 0; x < 800 * 600; x++) {
        double a = 0;
        for (int y = 0; y < img3[x]; y++){
            a = a + HIS_3[y];
        }
        img3[x] = a * 256;
    }




    //---------------處理完之後再計算一次HISTOGRAM------------//

    for (int x = 0; x < 256; x++) {
        HIS_1[x] = 0;
        HIS_2[x] = 0;
        HIS_3[x] = 0;
    }
    
    for (int x = 0; x < 800 * 600; x++) {
        HIS_1[img[x]] = HIS_1[img[x]] + 1;
    }

    for (int x = 0; x < 800 * 600; x++) {
        HIS_2[img2[x]] = HIS_2[img2[x]] + 1;
    }

    for (int x = 0; x < 800 * 600; x++) {
        HIS_3[img3[x]] = HIS_3[img3[x]] + 1;
    }


    for (int x = 0; x < 256; x++) {
        HIS_1[x] = HIS_1[x] / size;
        HIS_2[x] = HIS_2[x] / size;
        HIS_3[x] = HIS_3[x] / size;
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
    normalize(hist2, hist2, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(hist3, hist3, 0, histImage.rows, NORM_MINMAX, -1, Mat());

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

    imshow("Hist dark_meerkat_dark", histImage);
    imwrite("Hist meerkat_dark_histogram_equalization.jpg", histImage);
    imshow("Hist bright_meerkat_bright", histImage2);
    imwrite("Hist meerkat_bright_histogram_equalization.jpg", histImage2);
    imshow("Hist high_contrast_meerkat_high_contrast", histImage3);
    imwrite("Hist meerkat_high_contrast_histogram_equalization.jpg", histImage3);
    waitKey();
    destroyAllWindows();
    //--------------------------輸出檔案---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img, 1, size, output_file);

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img2, 1, size, output_file2);

    fopen_s(&output_file3, out_imgpath3, "wb");
    fwrite(img3, 1, size, output_file3);

    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    delete[] img2;
    delete[] img3;
    fclose(input_file);
    fclose(input_file2);
    fclose(input_file3);
    fclose(output_file);
    fclose(output_file2);
    fclose(output_file3);








}