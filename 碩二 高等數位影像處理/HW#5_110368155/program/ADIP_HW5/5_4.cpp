/******************************************************************************************
* Filename    : 5_4.cpp                                                                   *
* Update date : /11/2022                                                                  *
* Author      : 顏郁芩                                                                    *
* Note        : apply homomorphic filtering filter to house_512.raw                       *
*******************************************************************************************/


#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include<cmath>
#include<iomanip>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/core.hpp"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
using namespace W;
using namespace cv;


void shift_4(Mat in, int x, int y) {
    int cx = x / 2;
    int cy = y / 2;
    Mat tmp;
    Mat q0(in, Rect(0, 0, cx, cy));
    Mat q1(in, Rect(cx, 0, cx, cy));
    Mat q2(in, Rect(0, cy, cx, cy));
    Mat q3(in, Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

}

void Homomorphic_Filter_maker(int D0, double RL,double RH, Mat output) {//,int distance
    unsigned char ans;
    double a;
    //cout << +data << endl;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            float dist;
            float disx = abs(x - 256);
            float disy = abs(y - 256);
            dist = sqrt(disx * disx + disy * disy);
            if (dist > 100) {
                //dist = 100;
            }
            output.at<float>(x,y) = (RH-RL)*(1- exp(-2*(pow(dist,2) / pow(D0,2))))+RL;//要改
        }
    }
}

Mat Homomorphicfilter(Mat out,double RH,double RL,double C,double d0) {
    out.convertTo(out, CV_64F);
    int rows = 512;
    int cols = 512;
    Mat dst(512, 512, CV_64F);
    for (int i = 0; i < 512; i++) {
        double *srcdata =out.ptr<double>(i);
        double *logdata =  out.ptr<double>(i);
        for (int j = 0; j < 512; j++) {
            logdata[j] = log(srcdata[j]+0.001);//做log並 防止log(0)
        }
    }

    Mat mat_dct = Mat::zeros(512, 512, CV_64F);
    dct(out, mat_dct);//dct轉換

    Mat H = Mat::zeros(512,512,CV_64F);
    double d = 0;
    for (int x = 0; x < 512; x++) {
        double * dataH = H.ptr<double>(x);
        for (int y = 0; y < 512; y++) {
            d = pow(x, 2.0) + pow(y, 2.0);
            dataH[y] = (RH - RL) * (1 - exp(-C * d / d0) + RL);//公式
        }
    }
    mat_dct = mat_dct.mul(H);//DCT轉換之後乘上H

    idct(mat_dct, dst);//idct轉換

    for (int x = 0; x < 512; x++) {
        double* srcdata = dst.ptr<double>(x);
        double* dstdata = dst.ptr<double>(x);
        for (int y = 0; y < 512; y++) {
            dstdata[y] = exp(srcdata[y]);//EXP轉換回來
        }
    }
    dst.convertTo(dst, CV_8U);
    return dst;

}

/*void MY_HW5::HW5_4() {
    MY_HW5 HW5;
    //--------------------------參數---------------------------//
    int size = 512 * 512;

    FILE* input_file;
    char in_imgpath[] = ".\\HW5_images_file\\house512.raw";
    FILE* output_file;
    char out_imgpath[] = ".\\ans1.raw";
    char out_imgpath2[] = ".\\ans2.raw";
    char out_imgpath3[] = ".\\ans3.raw";

    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    unsigned char input[512][512];
    unsigned char img1_1[512][512];
    unsigned char img2_1[512][512];
    unsigned char img3_1[512][512];
    float img_input[512][512];

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image house_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);


    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            input[x][y] = img[c];
            c++;
        }
    }

    //------------------處理------------------------//
    Mat imgCV1(512, 512, CV_8U, input);
    //normalize(imgCV1, imgCV1, 0, 1, NORM_MINMAX);
    imshow("house_512_ORI", imgCV1);
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            img_input[x][y] = log(1+input[x][y]);
        }
    }
    Mat imgCV(512,512 , CV_8U, img_input);
    imshow("house_512 log", imgCV);
    waitKey();
    Mat planes[] = { Mat_<float>(imgCV), Mat::zeros(imgCV.size(), CV_32F) };
    Mat complexImg;
    merge(planes, 2, complexImg);
    dft(complexImg, complexImg);
    split(complexImg, planes);
    Mat IMG_ori_re = planes[0].clone();
    Mat IMG_ori_im = planes[1].clone();
    //normalize(IMG_ori_re, IMG_ori_re, 0, 1, NORM_MINMAX);
    imshow("IMG_ori_re", IMG_ori_re);
   //normalize(IMG_ori_im, IMG_ori_im, 0, 1, NORM_MINMAX);
    imshow("IMG_ori_im", IMG_ori_im);

    Mat freq;
    magnitude(planes[0], planes[1], freq);
    log(freq, freq);
    shift_4(freq, 512, 512);
    normalize(freq, freq, 0, 1, 
        NORM_MINMAX);
    imshow("house_512 freq", freq);

    Mat FIlter(512,512,CV_32F);
    Homomorphic_Filter_maker(150, 0.25,2.2, FIlter);
    imshow("FIlter", FIlter);
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            //mag1.at<float>(x, y) = FIlter.at<float>(x, y) * mag1.at<float>(x, y);//做完filter的頻譜圖
            complexImg.at<float>(x, y) = FIlter.at<float>(x, y) * complexImg.at<float>(x, y);
        }
    }
    //imshow("after_FILTER", complexImg);
    Mat planes2[]= { Mat_<float>(complexImg), Mat::zeros(complexImg.size(), CV_32F) };;
    split(complexImg, planes2);
    Mat freq2;
    magnitude(planes2[0], planes2[1], freq2);

    log(freq2, freq2);
    shift_4(freq2, 512, 512);
    normalize(freq2, freq2, 0, 1,
        NORM_MINMAX);
    imshow("house_512 freq_after", freq2);
    //Mat planes2[] = { Mat_<float>(imgCV), Mat::zeros(imgCV.size(), CV_32F) };
   // Mat complexImg2;
    //merge(planes2, 2, complexImg2);
    Mat ifft;
    idft(complexImg, ifft, DFT_REAL_OUTPUT);
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            ifft.at<float>(x, y) = exp(ifft.at<float>(x, y))-1;
        }
    }
    normalize(ifft, ifft, 0, 1, NORM_MINMAX);
    imshow("after_FILTER IDFT", ifft);
    waitKey();
    */

    //--------------------------儲存檔案---------------------------//
    /*o = o * 255;
    for (int x = 0; x < 512 * 512; x++) {
        img1_1[x] = o.at<float>(x);
    }
    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img1_1, 1, size, output_file);
    fclose(output_file);*/
    /*fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img1_1, 1, size, output_file);
    fclose(output_file);

    fopen_s(&output_file, out_imgpath2, "wb");
    fwrite(img2_1, 1, size, output_file);
    fclose(output_file);*/

    //--------------------------釋出記憶體---------------------------//
    /*delete[] img;
    fclose(input_file);
    fclose(input_file2);*/

//}

void MY_HW5::HW5_4() {
    MY_HW5 HW5;
    //--------------------------參數---------------------------//
    int size = 512 * 512;

    FILE* input_file;
    char in_imgpath[] = ".\\HW5_images_file\\house512.raw";
    FILE* output_file;
    char out_imgpath[] = ".\\use histogram equation.raw";
    char out_imgpath2[] = ".\\ans2.raw";
    char out_imgpath3[] = ".\\ans3.raw";

    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    unsigned char input[512][512];
    unsigned char img1_1[512][512];
    unsigned char img2_1[512][512];
    unsigned char img3_1[512][512];
    float img_input[512][512];

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image house_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);


    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            input[x][y] = img[c];
            c++;
        }
    }

    //------------------處理------------------------//
    Mat imgCV1(512, 512, CV_8U, input);

    imshow("origin", imgCV1);

    Mat new1 = Homomorphicfilter(imgCV1,1.8,0.8,2,150);
    new1 = new1 * 3;
    //normalize(newY, newY, 0, 1, NORM_MINMAX);
    Mat new2 = Homomorphicfilter(imgCV1, 2.5, 0.5, 2, 150);
    new2 = new2 * 3;
    Mat new3 = Homomorphicfilter(imgCV1, 3.5, 0.5, 2, 150);
    new3 = new3 * 3;
    imshow("result1", new1);
    imshow("result2", new2);
    imshow("result3", new3);
    imwrite("result1.jpg", new1);
    imwrite("result2.jpg", new2);
    imwrite("result3.jpg", new3);
    waitKey();
    destroyAllWindows();

    //-------------HISTOHRAM EQUATION----------------//
    int Hist[256] = { 0 };
    double hist[256] = { 0.0 };
    unsigned char out_img[512][512];
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            Hist[input[x][y]] = Hist[input[x][y]]+1;
        }
    }

    for (int x = 0; x < 256; x++) {
        hist[x] = Hist[x] / (512 * 512);
    }
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            float count = 0.0;
            for (int z = 0; z < input[x][y]; z++) {
                count = count + hist[x];
            }
            out_img[x][y] = count *512*512;
        }
    }
    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(out_img, 1, 512*512, output_file);
    fclose(output_file);

    delete[] img;
    fclose(input_file);

}