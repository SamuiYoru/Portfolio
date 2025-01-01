/**********************************************************************************
* Filename    : 5_3.cpp                                                           *
* Update date : /11/2022                                                        *
* Author      : 顏郁芩                                                            *
* Note        : water marked the image in spatial and frequency domain            *
**********************************************************************************/

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


void shift_3(Mat in, int x, int y) {
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

void IDFT_merge_3(Mat real, Mat image, string name, char out_imgpath[]) {
    unsigned char img[512 * 512];
    FILE* output_file;
    Mat out;
    Mat planes2[] = { Mat_<float>(real),  Mat_<float>(image) };
    merge(planes2, 2, out);
    Mat ifft;
    idft(out, ifft, DFT_REAL_OUTPUT);
    normalize(ifft, ifft, 0, 1, NORM_MINMAX);
    imshow(name, ifft);
    ifft = ifft * 255;
    imwrite(name + ".jpg", ifft);

    waitKey();
    destroyAllWindows();
    for (int x = 0; x < 512 * 512; x++) {
        img[x] = ifft.at<float>(x);
    }
    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img, 1, 512*512, output_file);
    fclose(output_file); 


}


void MY_HW5::HW5_3() {
    MY_HW5 HW5;
    //--------------------------參數---------------------------//
    int size = 512 * 512;

    FILE* input_file, * input_file2;
    char in_imgpath[] = ".\\HW5_images_file\\raccoon_512.raw";
    char in_imgpath2[] = ".\\HW5_images_file\\mark_512.raw";
    FILE* output_file;
    char out_imgpath[] = ".\\watermarked1.raw";
    char out_imgpath2[] = ".\\watermarked2.raw";
    char out_imgpath3[] = ".\\watermarked3.raw";
    char out_imgpath4[] = ".\\watermarked4.raw";
    char out_imgpath5[] = ".\\watermarked5.raw";
    char out_imgpath6[] = ".\\watermarked6.raw";

    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];


    unsigned char img_input[512][512];
    unsigned char img_input2[512][512];
    unsigned char DFTvalue[512][512];
    unsigned char DFTvalue2[512][512];

    unsigned char img1_1[512 * 512];
    unsigned char img2_1[512 * 512];




    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image raccoon_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);


    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image mark_512.raw!\n");
    }
    fread(img2, sizeof(unsigned char), size, input_file2);

    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            img_input[x][y] = img[c];
            img_input2[x][y] = img2[c];
            c++;
        }
    }

    //------用OPENCV 轉換成frequency domain------//

    Mat imgCV(512, 512, CV_8UC1, img);//原圖
    Mat imgCV2(512, 512, CV_8UC1, img2);//MARK

    Mat planes[] = { Mat_<float>(imgCV), Mat::zeros(imgCV.size(), CV_32F) };
    Mat planes2[] = { Mat_<float>(imgCV2), Mat::zeros(imgCV2.size(), CV_32F) };
    Mat complexImg;
    Mat complexMark;
    merge(planes, 2, complexImg);
    merge(planes2, 2, complexMark);

    dft(complexImg, complexImg);
    dft(complexMark, complexMark);
    //Mat img_ori = complexImg.clone();
    //Mat mark_ori = complexMark.clone();


    split(complexImg, planes);
    Mat img_re = planes[0].clone();
    Mat img_im = planes[1].clone();
    magnitude(planes[0], planes[1], planes[0]);
    split(complexMark, planes2);
    Mat mark_re = planes2[0].clone();
    Mat mark_im = planes2[1].clone();
    magnitude(planes2[0], planes2[1], planes2[0]);
    Mat real = planes[0].clone();
    Mat realMark = planes2[0].clone();
    log(real, real);
    log(realMark, realMark);

    shift_3(real, 512, 512);
    shift_3(realMark, 512, 512);


    normalize(real, real, 0, 1, NORM_MINMAX);
    normalize(realMark, realMark, 0, 1, NORM_MINMAX);
    imshow("image ", imgCV);
    imwrite("image.jpg", imgCV);
    imshow("mark", imgCV2);
    imwrite("mark.jpg", imgCV2);
    imshow("image spectrum magnitude", real);
    Mat real_1 = real.clone() * 255;
    imwrite("image spectrum magnitude.jpg", real_1);
    imshow("mark spectrum magnitude", realMark);
    Mat realMark_1 = realMark.clone() * 255;
    imwrite("mark spectrum magnitude.jpg", realMark_1);

    waitKey();

    //------------------處理 method1------------------------//
    //Image(frequency domain)+w*mark(spatial domain)//用不同w
    //mat=real +mat imgCV2 img_re + imgCV2 img_im 
    real = real * 255;
    realMark = realMark * 255;
    Mat w_method1_re(512, 512, CV_32F);
    Mat w_method1_im(512, 512, CV_32F);
    //w=10
    for (int x = 0; x < 512 * 512; x++) {
        unsigned char color = imgCV2.at<unsigned char>(x);
        w_method1_re.at<float>(x) = (img_re.at<float>(x) + imgCV2.at<unsigned char>(x) *10);
        w_method1_im.at<float>(x) = (img_im.at<float>(x));
    }
    imshow("w10method1_re ", w_method1_re);
    imwrite("w10method1_re.jpg", w_method1_re);
    imshow("w10method1_im ", w_method1_im);
    imwrite("w10method1_im.jpg", w_method1_im);
    Mat w10method1;
    magnitude(w_method1_re, w_method1_im, w10method1);
    IDFT_merge_3(w_method1_re, w_method1_im, "w10method1 IDFT", out_imgpath);//Mat::zeros(imgCV2.size(), CV_32F)

    
    //w=50
    for (int x = 0; x < 512 * 512; x++) {
        unsigned char color = imgCV2.at<unsigned char>(x);
        w_method1_re.at<float>(x) = (img_re.at<float>(x) + imgCV2.at<unsigned char>(x) * 50);
        w_method1_im.at<float>(x) = (img_im.at<float>(x));
    }
    imshow("w50method1_re ", w_method1_re);
    imwrite("w50method1_re.jpg", w_method1_re);
    imshow("w50method1_im ", w_method1_im);
    imwrite("w50method1_im.jpg", w_method1_im);
    Mat w50method1;
    magnitude(w_method1_re, w_method1_im, w50method1);
    IDFT_merge_3(w_method1_re, w_method1_im, "w50method1 IDFT", out_imgpath2);//Mat::zeros(imgCV2.size(), CV_32F)


    //w = 100

    for (int x = 0; x < 512 * 512; x++) {
        unsigned char color = imgCV2.at<unsigned char>(x);
        w_method1_re.at<float>(x) = (img_re.at<float>(x) + imgCV2.at<unsigned char>(x) * 100);
        w_method1_im.at<float>(x) = (img_im.at<float>(x));
    }
    imshow("w100method1_re ", w_method1_re);
    imwrite("w100method1_re.jpg", w_method1_re);
    imshow("w100method1_im ", w_method1_im);
    imwrite("w100method1_im .jpg", w_method1_im);
    Mat w100method1;
    magnitude(w_method1_re, w_method1_im, w100method1);
    IDFT_merge_3(w_method1_re, w_method1_im, "w100method1 IDFT", out_imgpath3);//Mat::zeros(imgCV2.size(), CV_32F)



    //------------------處理 method2------------------------//
    //Image(frequency domain)+w*mark(frequency domain)//用不同w
    Mat w_method2_re(512, 512, CV_32F);
    Mat w_method2_im(512, 512, CV_32F);
    //w=0.1
    for (int x = 0; x < 512 * 512; x++) {
        unsigned char color = imgCV2.at<unsigned char>(x);
        w_method2_re.at<float>(x) = (img_re.at<float>(x) + mark_re.at<float>(x)*0.1);
        w_method2_im.at<float>(x) = (img_im.at<float>(x)+mark_im.at<float>(x)*0.1 );
    }
    imshow("w01method2_re ", w_method2_re);
    imwrite("w01method2_re.jpg", w_method2_re);
    imshow("w01method2_im ", w_method2_im);
    imwrite("w01method2_im.jpg", w_method2_im);
    Mat w01method2;
    magnitude(w_method2_re, w_method2_im, w01method2);
    IDFT_merge_3(w_method2_re, w_method2_im, "w01method2 IDFT", out_imgpath4);//Mat::zeros(imgCV2.size(), CV_32F)

     //w=0.5
    for (int x = 0; x < 512 * 512; x++) {
        unsigned char color = imgCV2.at<unsigned char>(x);
        w_method2_re.at<float>(x) = (img_re.at<float>(x) + mark_re.at<float>(x) * 0.5);
        w_method2_im.at<float>(x) = (img_im.at<float>(x) + mark_im.at<float>(x) * 0.5);
    }
    imshow("w05method2_re ", w_method2_re);
    imwrite("w05method2_re.jpg", w_method2_re);
    imshow("w05method2_im ", w_method2_im);
    imwrite("w05method2_im.jpg", w_method2_im);
    destroyAllWindows();
    Mat w05method2;
    magnitude(w_method2_re, w_method2_im, w05method2);
    IDFT_merge_3(w_method2_re, w_method2_im, "w05method2 IDFT", out_imgpath5);//Mat::zeros(imgCV2.size(), CV_32F)

     //w=1
    for (int x = 0; x < 512 * 512; x++) {
        unsigned char color = imgCV2.at<unsigned char>(x);
        w_method2_re.at<float>(x) = (img_re.at<float>(x) + mark_re.at<float>(x) * 1);
        w_method2_im.at<float>(x) = (img_im.at<float>(x) + mark_im.at<float>(x) * 1);
    }
    imshow("w1method2_re ", w_method2_re);
    imwrite("w1method2_re.jpg", w_method2_re);
    imshow("w1method2_im ", w_method2_im);
    imwrite("w1method2_im.jpg", w_method2_im);
    Mat w1method2;
    magnitude(w_method2_re, w_method2_im, w1method2);
    IDFT_merge_3(w_method2_re, w_method2_im, "w1method2 IDFT", out_imgpath6);//Mat::zeros(imgCV2.size(), CV_32F)


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
    delete[] img;
    fclose(input_file);
    fclose(input_file2);

}



