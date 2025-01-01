/*****************************************************************************
* Filename    : 5_2_1.cpp                                                    *
* Update date : 23/11/2022                                                   *
* Author      : 顏郁芩                                                       *
* Note        : Use BUTTERWORTH LPF and HPF filter on raccoon_256            *
*****************************************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
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

void IDFT_merge(Mat real, Mat image, string name) {
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
}
void shift(Mat in, int x, int y) {
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

void BW_Filter_maker_LPF(int D0, int n, Mat output) {//,int distance
    unsigned char ans;
    double a;
    //cout << +data << endl;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            float dist;
            float disx = abs(x - 256);
            float disy = abs(y - 256);
            dist = sqrt(disx * disx + disy * disy);
            output.at<float>(x,y)= 1.0 / (1 + pow((dist / D0), (2 * n)));
        }
    }
}

void BW_Filter_maker_HPF(int D0, int n, Mat output) {//,int distance
    unsigned char ans;
    double a;
    //cout << +data << endl;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            float dist;
            float disx = abs(x - 256);
            float disy = abs(y - 256);
            dist = sqrt(disx * disx + disy * disy);
            output.at<float>(x, y) = 1.0 / (1 + pow((D0 / dist), (2 * n)));
        }
    }
}

void MY_HW5::HW5_2_1_LPF() {
    MY_HW5 HW5;
    //--------------------------參數---------------------------//
    int H = 512;
    int W = 512;

    FILE* input_file, * input_file2, * input_file3;
    char in_imgpath[] = ".\\HW5_images_file\\raccoon_512.raw";
    FILE* output_file;
    char out_imgpath[] = "";
    int size = H * W;
    unsigned char* img = new unsigned char[size];


    unsigned char img_input[512][512];


       //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image raccoon_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    //-------處理-------//

    Mat imgCV(512, 512, CV_8UC1, img);

    imshow("raccoon 512", imgCV);

    Mat planes[] = { Mat_<float>(imgCV), Mat::zeros(imgCV.size(), CV_32F) };
    Mat complexImg;
    merge(planes, 2, complexImg);//DFT需要二通道的輸入，一個是實部(讀入資料)，一個是虛部(0)
    dft(complexImg, complexImg);
                                                                                            
    split(complexImg, planes);  //輸入拆成兩個plane
    Mat IMG_ori_re = planes[0].clone();
    Mat IMG_ori_im = planes[1].clone();

    Mat ans1 = complexImg.clone();
    Mat ans2 = complexImg.clone();
    Mat ans3 = complexImg.clone();
    Mat ans4 = complexImg.clone();
    Mat ans5 = complexImg.clone();
    Mat ans6 = complexImg.clone();
    Mat ans7 = complexImg.clone();
    Mat ans8 = complexImg.clone();
    Mat ans9 = complexImg.clone();

    Mat img_re = planes[0].clone();
    Mat img_im = planes[1].clone();

    Mat ori_mag;
    magnitude(planes[0], planes[1], ori_mag);//算magnitude
    Mat mag = ori_mag.clone();
    //Mat mag2 = ori_mag;
    //mag += Scalar::all(1);
    log(mag, mag);                                                                                                     
    int cx = mag.cols / 2;
    int cy = mag.rows / 2;

    shift(mag, 512, 512);

    normalize(mag, mag, 0, 1, NORM_MINMAX);  

    Mat mag_ori = mag.clone();//輸出MAGNITUDE
    Mat mag1 = mag.clone();
    Mat mag2 = mag.clone();
    Mat mag3 = mag.clone();
    Mat mag4 = mag.clone();
    Mat mag5 = mag.clone();
    Mat mag6 = mag.clone();
    Mat mag7 = mag.clone();
    Mat mag8 = mag.clone();
    Mat mag9 = mag.clone();

    Mat filter1(512,512, CV_32F);
    BW_Filter_maker_LPF(5, 1, filter1);
    Mat filter2(512, 512, CV_32F);
    BW_Filter_maker_LPF(5, 2, filter2);
    Mat filter3(512, 512, CV_32F);
    BW_Filter_maker_LPF(5, 3, filter3);
    Mat filter4(512, 512, CV_32F);
    BW_Filter_maker_LPF(20, 1, filter4);
    Mat filter5(512, 512, CV_32F);
    BW_Filter_maker_LPF(20, 2, filter5);
    Mat filter6(512, 512, CV_32F);
    BW_Filter_maker_LPF(20, 3, filter6);
    Mat filter7(512, 512, CV_32F);
    BW_Filter_maker_LPF(50, 1, filter7);
    Mat filter8(512, 512, CV_32F);
    BW_Filter_maker_LPF(50, 2, filter8);
    Mat filter9(512, 512, CV_32F);
    BW_Filter_maker_LPF(50, 3, filter9);

    imshow("butterworth 5 1 FILTER", filter1);
    filter1 = filter1 * 255;
    imwrite("butterworth 5 1 FILTER_LPF.jpg", filter1);

    imshow("butterworth 5 2 FILTER", filter2);
    filter2 = filter2 * 255;
    imwrite("butterworth 5 2 FILTER_LPF.jpg", filter2);

    imshow("butterworth 5 3 FILTER", filter3);
    filter3 = filter3 * 255;
    imwrite("butterworth 5 3 FILTER_LPF.jpg", filter3);

    imshow("butterworth 20 1 FILTER", filter4);
    filter4 = filter4 * 255;
    imwrite("butterworth 20 1 FILTER_LPF.jpg", filter4);

    imshow("butterworth 20 2 FILTER", filter5);
    filter5 = filter5 * 255;
    imwrite("butterworth 20 2 FILTER_LPF.jpg", filter5);

    imshow("butterworth 20 3 FILTER", filter6);
    filter6 = filter6* 255;
    imwrite("butterworth 20 3 FILTER_LPF.jpg", filter6);

    imshow("butterworth 50 1 FILTER", filter7);
    filter7 = filter7 * 255;
    imwrite("butterworth 50 1 FILTER_LPF_LPF.jpg", filter7);

    imshow("butterworth 50 2 FILTER", filter8);
    filter8 = filter8 * 255;
    imwrite("butterworth 50 2 FILTER_LPF.jpg", filter8);

    imshow("butterworth 50 3 FILTER", filter9);
    filter9 = filter9 * 255;
    imwrite("butterworth 50 3 FILTER_LPF.jpg", filter9);



    Mat filter1_clone = filter1.clone();
    Mat filter2_clone = filter2.clone();
    Mat filter3_clone = filter3.clone();
    Mat filter4_clone = filter4.clone();
    Mat filter5_clone = filter5.clone();
    Mat filter6_clone = filter6.clone();
    Mat filter7_clone = filter7.clone();
    Mat filter8_clone = filter8.clone();
    Mat filter9_clone = filter9.clone();

    shift(filter1_clone, 512, 512);
    shift(filter2_clone, 512, 512);
    shift(filter3_clone, 512, 512);
    shift(filter4_clone, 512, 512);
    shift(filter5_clone, 512, 512);
    shift(filter6_clone, 512, 512);
    shift(filter7_clone, 512, 512);
    shift(filter8_clone, 512, 512);
    shift(filter9_clone, 512, 512);

    Mat planesfil1[] = { Mat_<float>(filter1_clone),Mat_<float>(filter1_clone) };
    Mat planesfil;
    merge(planesfil1, 2, planesfil);

    Mat planesfil2[] = { Mat_<float>(filter2_clone),Mat_<float>(filter2_clone) };
    Mat planesfi2;
    merge(planesfil2, 2, planesfi2);

    Mat planesfil3[] = { Mat_<float>(filter3_clone),Mat_<float>(filter3_clone) };
    Mat planesfi3;
    merge(planesfil3, 2, planesfi3);

    Mat planesfil4[] = { Mat_<float>(filter4_clone),Mat_<float>(filter4_clone) };
    Mat planesfi4;
    merge(planesfil4, 2, planesfi4);

    Mat planesfil5[] = { Mat_<float>(filter5_clone),Mat_<float>(filter5_clone) };
    Mat planesfi5;
    merge(planesfil5, 2, planesfi5);

    Mat planesfil6[] = { Mat_<float>(filter6_clone),Mat_<float>(filter6_clone) };
    Mat planesfi6;
    merge(planesfil6, 2, planesfi6);

    Mat planesfil7[] = { Mat_<float>(filter7_clone),Mat_<float>(filter7_clone) };
    Mat planesfi7;
    merge(planesfil7, 2, planesfi7);

    Mat planesfil8[] = { Mat_<float>(filter8_clone),Mat_<float>(filter8_clone) };
    Mat planesfi8;
    merge(planesfil8, 2, planesfi8);

    Mat planesfil9[] = { Mat_<float>(filter9_clone),Mat_<float>(filter9_clone) };
    Mat planesfi9;
    merge(planesfil9, 2, planesfi9);

    
    for (int x = 0; x < mag.cols; x++) {
        for (int y = 0; y < mag.rows ; y++) {
            int H = 256;//mag.cols /2
            int W = 256;//mag.rows / 2
            int dist = sqrt(pow(abs(H - x), 2) + pow(abs(H - y), 2));

            mag1.at<float>(x, y) = filter1.at<float>(x, y) * mag1.at<float>(x, y);//做完filter的頻譜圖
            ans1.at<float>(x, y) = planesfil.at<float>(x, y) * ans1.at<float>(x, y);

            mag2.at<float>(x, y) = filter2.at<float>(x, y) * mag2.at<float>(x, y);//做完filter的頻譜圖
            ans2.at<float>(x, y) = planesfi2.at<float>(x, y) * ans2.at<float>(x, y);

            mag3.at<float>(x, y) = filter3.at<float>(x, y) * mag3.at<float>(x, y);//做完filter的頻譜圖
            ans3.at<float>(x, y) = planesfi3.at<float>(x, y) * ans3.at<float>(x, y);

            mag4.at<float>(x, y) = filter4.at<float>(x, y) * mag4.at<float>(x, y);//做完filter的頻譜圖
            ans4.at<float>(x, y) = planesfi4.at<float>(x, y) * ans4.at<float>(x, y);

            mag5.at<float>(x, y) = filter5.at<float>(x, y) * mag5.at<float>(x, y);//做完filter的頻譜圖
            ans5.at<float>(x, y) = planesfi5.at<float>(x, y) * ans5.at<float>(x, y);

            mag6.at<float>(x, y) = filter6.at<float>(x, y) * mag6.at<float>(x, y);//做完filter的頻譜圖
            ans6.at<float>(x, y) = planesfi6.at<float>(x, y) * ans6.at<float>(x, y);

            mag7.at<float>(x, y) = filter7.at<float>(x, y) * mag7.at<float>(x, y);//做完filter的頻譜圖
            ans7.at<float>(x, y) = planesfi7.at<float>(x, y) * ans7.at<float>(x, y);

            mag8.at<float>(x, y) = filter8.at<float>(x, y) * mag8.at<float>(x, y);//做完filter的頻譜圖
            ans8.at<float>(x, y) = planesfi8.at<float>(x, y) * ans8.at<float>(x, y);

            mag9.at<float>(x, y) = filter9.at<float>(x, y) * mag9.at<float>(x, y);//做完filter的頻譜圖
            ans9.at<float>(x, y) = planesfi9.at<float>(x, y) * ans9.at<float>(x, y);

        }
    }

    normalize(mag1, mag1, 0, 1, NORM_MINMAX);
    normalize(mag2, mag2, 0, 1, NORM_MINMAX);
    normalize(mag3, mag3, 0, 1, NORM_MINMAX);
    normalize(mag4, mag4, 0, 1, NORM_MINMAX);
    normalize(mag5, mag5, 0, 1, NORM_MINMAX);
    normalize(mag6, mag6, 0, 1, NORM_MINMAX);
    normalize(mag7, mag7, 0, 1, NORM_MINMAX);
    normalize(mag8, mag8, 0, 1, NORM_MINMAX);
    normalize(mag9, mag9, 0, 1, NORM_MINMAX);

    Mat ifft1;
    idft(ans1, ifft1, DFT_REAL_OUTPUT);
    normalize(ifft1, ifft1, 0, 1, NORM_MINMAX);

    Mat ifft2;
    idft(ans2, ifft2, DFT_REAL_OUTPUT);
    normalize(ifft2, ifft2, 0, 1, NORM_MINMAX);

    Mat ifft3;
    idft(ans3, ifft3, DFT_REAL_OUTPUT);
    normalize(ifft3, ifft3, 0, 1, NORM_MINMAX);

    Mat ifft4;
    idft(ans4, ifft4, DFT_REAL_OUTPUT);
    normalize(ifft4, ifft4, 0, 1, NORM_MINMAX);

    Mat ifft5;
    idft(ans5, ifft5, DFT_REAL_OUTPUT);
    normalize(ifft5, ifft5, 0, 1, NORM_MINMAX);

    Mat ifft6;
    idft(ans6, ifft6, DFT_REAL_OUTPUT);
    normalize(ifft6, ifft6, 0, 1, NORM_MINMAX);

    Mat ifft7;
    idft(ans7, ifft7, DFT_REAL_OUTPUT);
    normalize(ifft7, ifft7, 0, 1, NORM_MINMAX);

    Mat ifft8;
    idft(ans8, ifft8, DFT_REAL_OUTPUT);
    normalize(ifft8, ifft8, 0, 1, NORM_MINMAX);

    Mat ifft9;
    idft(ans9, ifft9, DFT_REAL_OUTPUT);
    normalize(ifft9, ifft9, 0, 1, NORM_MINMAX);

    imshow("idft 5 1", ifft1);
    ifft1 = ifft1 * 255;
    imwrite("idft 5 1_LPF.jpg", ifft1);

    imshow("idft 5 2", ifft2);
    ifft2 = ifft2 * 255;
    imwrite("idft 5 2_LPF.jpg", ifft2);

    imshow("idft 5 3", ifft3);
    ifft3 = ifft3 * 255;
    imwrite("idft 5 3_LPF.jpg", ifft3);

    imshow("idft 20 1", ifft4);
    ifft4 = ifft4 * 255;
    imwrite("idft 20 1_LPF.jpg", ifft4);

    imshow("idft 20 2", ifft5);
    ifft5 = ifft5 * 255;
    imwrite("idft 20 2_LPF.jpg", ifft5);

    imshow("idft 20 3", ifft6);
    ifft6 = ifft6 * 255;
    imwrite("idft 20 3_LPF.jpg", ifft6);

    imshow("idft 50 1", ifft7);
    ifft7 = ifft7 * 255;
    imwrite("idft 50 1_LPF.jpg", ifft7);

    imshow("idft 50 2", ifft8);
    ifft8 = ifft8 * 255;
    imwrite("idft 50 2_LPF.jpg", ifft8);

    imshow("idft 50 3", ifft9);
    ifft9 = ifft9 * 255;
    imwrite("idft 50 3_LPF.jpg", ifft9);

    waitKey();
    destroyAllWindows();
  


    imshow("raccoon 512 spectrum", mag_ori);
    mag_ori = mag_ori * 255;
    imwrite("raccoon 512 spectrum.jpg", mag_ori);

    imshow("raccoon 512 + butterworth_LPF 5 1 頻譜", mag1);
    mag1 = mag1 * 255;
    imwrite("raccoon 512  + butterworth_LPF 5 1 頻譜.jpg", mag1);

    imshow("raccoon 512  + butterworth_LPF 5 2 頻譜", mag2);
    mag2 = mag2 * 255;
    imwrite("raccoon 512  + butterworth_LPF 5 2 頻譜.jpg", mag2);

    imshow("raccoon 512  + butterworth_LPF 5 3 頻譜", mag3);
    mag3 = mag3 * 255;
    imwrite("raccoon 512  + butterworth_LPF 5 3 頻譜.jpg", mag3);

    imshow("raccoon 512  + butterworth_LPF 20 1 頻譜", mag4);
    mag4 = mag4 * 255;
    imwrite("raccoon 512  + butterworth_LPF 20 1 頻譜.jpg", mag4);

    imshow("raccoon 512  + butterworth_LPF 20 2 頻譜", mag5);
    mag5 = mag5 * 255;
    imwrite("raccoon 512  + butterworth_LPF 20 2 頻譜.jpg", mag5);

    imshow("raccoon 512  + butterworth_LPF 20 3 頻譜", mag6);
    mag6 = mag6 * 255;
    imwrite("raccoon 512  + butterworth_LPF 20 3 頻譜.jpg", mag6);

    imshow("raccoon 512  + butterworth_LPF 50 1 頻譜", mag7);
    mag7 = mag7 * 255;
    imwrite("raccoon 512  + butterworth_LPF 50 1 頻譜.jpg", mag7);

    imshow("raccoon 512  + butterworth_LPF 50 2 頻譜", mag8);
    mag8 = mag8 * 255;
    imwrite("raccoon 512  + butterworth_LPF 50 2 頻譜.jpg", mag8);

    imshow("raccoon 512  + butterworth_LPF 50 3 頻譜", mag9);
    mag9 = mag9 * 255;
    imwrite("raccoon 512 + butterworth_LPF 50 3 頻譜.jpg", mag9);
    waitKey();
    destroyAllWindows();

    
    //--原圖做IDFT-----------//
    IDFT_merge(IMG_ori_re, IMG_ori_im, "原始圖片 IDFT");

}




void MY_HW5::HW5_2_1_HPF() {
    MY_HW5 HW5;
    //--------------------------參數---------------------------//
    int H = 512;
    int W = 512;

    FILE* input_file, * input_file2, * input_file3;
    char in_imgpath[] = ".\\HW5_images_file\\raccoon_512.raw";
    FILE* output_file;
    char out_imgpath[] = "";
    int size = H * W;
    unsigned char* img = new unsigned char[size];


    unsigned char img_input[512][512];

    double DFTvalue[256][256];

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image raccoon_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    //-------處理-------//

    Mat imgCV(512, 512, CV_8UC1, img);

    imshow("raccoon 512", imgCV);

    Mat planes[] = { Mat_<float>(imgCV), Mat::zeros(imgCV.size(), CV_32F) };
    Mat complexImg;
    merge(planes, 2, complexImg);//DFT需要二通道的輸入，一個是實部(讀入資料)，一個是虛部(0)
    dft(complexImg, complexImg);

    split(complexImg, planes);  //輸入拆成兩個plane
    Mat IMG_ori_re = planes[0].clone();
    Mat IMG_ori_im = planes[1].clone();

    Mat ans1 = complexImg.clone();
    Mat ans2 = complexImg.clone();
    Mat ans3 = complexImg.clone();
    Mat ans4 = complexImg.clone();
    Mat ans5 = complexImg.clone();
    Mat ans6 = complexImg.clone();
    Mat ans7 = complexImg.clone();
    Mat ans8 = complexImg.clone();
    Mat ans9 = complexImg.clone();

    Mat img_re = planes[0].clone();
    Mat img_im = planes[1].clone();

    Mat ori_mag;
    magnitude(planes[0], planes[1], ori_mag);//算magnitude
    Mat mag = ori_mag.clone();
    //Mat mag2 = ori_mag;
    //mag += Scalar::all(1);
    log(mag, mag);
    int cx = mag.cols / 2;
    int cy = mag.rows / 2;

    shift(mag, 512, 512);

    normalize(mag, mag, 0, 1, NORM_MINMAX);

    Mat mag_ori = mag.clone();//輸出MAGNITUDE
    Mat mag1 = mag.clone();
    Mat mag2 = mag.clone();
    Mat mag3 = mag.clone();
    Mat mag4 = mag.clone();
    Mat mag5 = mag.clone();
    Mat mag6 = mag.clone();
    Mat mag7 = mag.clone();
    Mat mag8 = mag.clone();
    Mat mag9 = mag.clone();

    Mat filter1(512, 512, CV_32F);
    BW_Filter_maker_HPF(5, 1, filter1);
    Mat filter2(512, 512, CV_32F);
    BW_Filter_maker_HPF(5, 2, filter2);
    Mat filter3(512, 512, CV_32F);
    BW_Filter_maker_HPF(5, 3, filter3);
    Mat filter4(512, 512, CV_32F);
    BW_Filter_maker_HPF(20, 1, filter4);
    Mat filter5(512, 512, CV_32F);
    BW_Filter_maker_HPF(20, 2, filter5);
    Mat filter6(512, 512, CV_32F);
    BW_Filter_maker_HPF(20, 3, filter6);
    Mat filter7(512, 512, CV_32F);
    BW_Filter_maker_HPF(50, 1, filter7);
    Mat filter8(512, 512, CV_32F);
    BW_Filter_maker_HPF(50, 2, filter8);
    Mat filter9(512, 512, CV_32F);
    BW_Filter_maker_HPF(50, 3, filter9);

    imshow("butterworth 5 1 FILTER", filter1);
    filter1 = filter1 * 255;
    imwrite("butterworth 5 1 FILTER_HPF.jpg", filter1);

    imshow("butterworth 5 2 FILTER", filter2);
    filter2 = filter2 * 255;
    imwrite("butterworth 5 2 FILTER_HPF.jpg", filter2);

    imshow("butterworth 5 3 FILTER", filter3);
    filter3 = filter3 * 255;
    imwrite("butterworth 5 3 FILTER_HPF.jpg", filter3);

    imshow("butterworth 20 1 FILTER", filter4);
    filter4 = filter4 * 255;
    imwrite("butterworth 20 1 FILTER_HPF.jpg", filter4);

    imshow("butterworth 20 2 FILTER", filter5);
    filter5 = filter5 * 255;
    imwrite("butterworth 20 2 FILTER_HPF.jpg", filter5);

    imshow("butterworth 20 3 FILTER", filter6);
    filter6 = filter6 * 255;
    imwrite("butterworth 20 3 FILTER_HPF.jpg", filter6);

    imshow("butterworth 50 1 FILTER", filter7);
    filter7 = filter7 * 255;
    imwrite("butterworth 50 1 FILTER_HPF.jpg", filter7);

    imshow("butterworth 50 2 FILTER", filter8);
    filter8 = filter8 * 255;
    imwrite("butterworth 50 2 FILTER_HPF.jpg", filter8);

    imshow("butterworth 50 3 FILTER", filter9);
    filter9 = filter9 * 255;
    imwrite("butterworth 50 3 FILTER_HPF.jpg", filter9);



    Mat filter1_clone = filter1.clone();
    Mat filter2_clone = filter2.clone();
    Mat filter3_clone = filter3.clone();
    Mat filter4_clone = filter4.clone();
    Mat filter5_clone = filter5.clone();
    Mat filter6_clone = filter6.clone();
    Mat filter7_clone = filter7.clone();
    Mat filter8_clone = filter8.clone();
    Mat filter9_clone = filter9.clone();

    shift(filter1_clone, 512, 512);
    shift(filter2_clone, 512, 512);
    shift(filter3_clone, 512, 512);
    shift(filter4_clone, 512, 512);
    shift(filter5_clone, 512, 512);
    shift(filter6_clone, 512, 512);
    shift(filter7_clone, 512, 512);
    shift(filter8_clone, 512, 512);
    shift(filter9_clone, 512, 512);

    Mat planesfil1[] = { Mat_<float>(filter1_clone),Mat_<float>(filter1_clone) };
    Mat planesfil;
    merge(planesfil1, 2, planesfil);

    Mat planesfil2[] = { Mat_<float>(filter2_clone),Mat_<float>(filter2_clone) };
    Mat planesfi2;
    merge(planesfil2, 2, planesfi2);

    Mat planesfil3[] = { Mat_<float>(filter3_clone),Mat_<float>(filter3_clone) };
    Mat planesfi3;
    merge(planesfil3, 2, planesfi3);

    Mat planesfil4[] = { Mat_<float>(filter4_clone),Mat_<float>(filter4_clone) };
    Mat planesfi4;
    merge(planesfil4, 2, planesfi4);

    Mat planesfil5[] = { Mat_<float>(filter5_clone),Mat_<float>(filter5_clone) };
    Mat planesfi5;
    merge(planesfil5, 2, planesfi5);

    Mat planesfil6[] = { Mat_<float>(filter6_clone),Mat_<float>(filter6_clone) };
    Mat planesfi6;
    merge(planesfil6, 2, planesfi6);

    Mat planesfil7[] = { Mat_<float>(filter7_clone),Mat_<float>(filter7_clone) };
    Mat planesfi7;
    merge(planesfil7, 2, planesfi7);

    Mat planesfil8[] = { Mat_<float>(filter8_clone),Mat_<float>(filter8_clone) };
    Mat planesfi8;
    merge(planesfil8, 2, planesfi8);

    Mat planesfil9[] = { Mat_<float>(filter9_clone),Mat_<float>(filter9_clone) };
    Mat planesfi9;
    merge(planesfil9, 2, planesfi9);


    for (int x = 0; x < mag.cols; x++) {
        for (int y = 0; y < mag.rows; y++) {
            int H = 256;//mag.cols /2
            int W = 256;//mag.rows / 2
            int dist = sqrt(pow(abs(H - x), 2) + pow(abs(H - y), 2));

            mag1.at<float>(x, y) = filter1.at<float>(x, y) * mag1.at<float>(x, y);//做完filter的頻譜圖
            ans1.at<float>(x, y) = planesfil.at<float>(x, y) * ans1.at<float>(x, y);

            mag2.at<float>(x, y) = filter2.at<float>(x, y) * mag2.at<float>(x, y);//做完filter的頻譜圖
            ans2.at<float>(x, y) = planesfi2.at<float>(x, y) * ans2.at<float>(x, y);

            mag3.at<float>(x, y) = filter3.at<float>(x, y) * mag3.at<float>(x, y);//做完filter的頻譜圖
            ans3.at<float>(x, y) = planesfi3.at<float>(x, y) * ans3.at<float>(x, y);

            mag4.at<float>(x, y) = filter4.at<float>(x, y) * mag4.at<float>(x, y);//做完filter的頻譜圖
            ans4.at<float>(x, y) = planesfi4.at<float>(x, y) * ans4.at<float>(x, y);

            mag5.at<float>(x, y) = filter5.at<float>(x, y) * mag5.at<float>(x, y);//做完filter的頻譜圖
            ans5.at<float>(x, y) = planesfi5.at<float>(x, y) * ans5.at<float>(x, y);

            mag6.at<float>(x, y) = filter6.at<float>(x, y) * mag6.at<float>(x, y);//做完filter的頻譜圖
            ans6.at<float>(x, y) = planesfi6.at<float>(x, y) * ans6.at<float>(x, y);

            mag7.at<float>(x, y) = filter7.at<float>(x, y) * mag7.at<float>(x, y);//做完filter的頻譜圖
            ans7.at<float>(x, y) = planesfi7.at<float>(x, y) * ans7.at<float>(x, y);

            mag8.at<float>(x, y) = filter8.at<float>(x, y) * mag8.at<float>(x, y);//做完filter的頻譜圖
            ans8.at<float>(x, y) = planesfi8.at<float>(x, y) * ans8.at<float>(x, y);

            mag9.at<float>(x, y) = filter9.at<float>(x, y) * mag9.at<float>(x, y);//做完filter的頻譜圖
            ans9.at<float>(x, y) = planesfi9.at<float>(x, y) * ans9.at<float>(x, y);

        }
    }

    normalize(mag1, mag1, 0, 1, NORM_MINMAX);
    normalize(mag2, mag2, 0, 1, NORM_MINMAX);
    normalize(mag3, mag3, 0, 1, NORM_MINMAX);
    normalize(mag4, mag4, 0, 1, NORM_MINMAX);
    normalize(mag5, mag5, 0, 1, NORM_MINMAX);
    normalize(mag6, mag6, 0, 1, NORM_MINMAX);
    normalize(mag7, mag7, 0, 1, NORM_MINMAX);
    normalize(mag8, mag8, 0, 1, NORM_MINMAX);
    normalize(mag9, mag9, 0, 1, NORM_MINMAX);

    Mat ifft1;
    idft(ans1, ifft1, DFT_REAL_OUTPUT);
    normalize(ifft1, ifft1, 0, 1, NORM_MINMAX);

    Mat ifft2;
    idft(ans2, ifft2, DFT_REAL_OUTPUT);
    normalize(ifft2, ifft2, 0, 1, NORM_MINMAX);

    Mat ifft3;
    idft(ans3, ifft3, DFT_REAL_OUTPUT);
    normalize(ifft3, ifft3, 0, 1, NORM_MINMAX);

    Mat ifft4;
    idft(ans4, ifft4, DFT_REAL_OUTPUT);
    normalize(ifft4, ifft4, 0, 1, NORM_MINMAX);

    Mat ifft5;
    idft(ans5, ifft5, DFT_REAL_OUTPUT);
    normalize(ifft5, ifft5, 0, 1, NORM_MINMAX);

    Mat ifft6;
    idft(ans6, ifft6, DFT_REAL_OUTPUT);
    normalize(ifft6, ifft6, 0, 1, NORM_MINMAX);

    Mat ifft7;
    idft(ans7, ifft7, DFT_REAL_OUTPUT);
    normalize(ifft7, ifft7, 0, 1, NORM_MINMAX);

    Mat ifft8;
    idft(ans8, ifft8, DFT_REAL_OUTPUT);
    normalize(ifft8, ifft8, 0, 1, NORM_MINMAX);

    Mat ifft9;
    idft(ans9, ifft9, DFT_REAL_OUTPUT);
    normalize(ifft9, ifft9, 0, 1, NORM_MINMAX);

    imshow("idft 5 1", ifft1);
    ifft1 = ifft1 * 255;
    imwrite("idft 5 1_HPF.jpg", ifft1);

    imshow("idft 5 2", ifft2);
    ifft2 = ifft2 * 255;
    imwrite("idft 5 2_HPF.jpg", ifft2);

    imshow("idft 5 3", ifft3);
    ifft3 = ifft3 * 255;
    imwrite("idft 5 3_HPF.jpg", ifft3);

    imshow("idft 20 1", ifft4);
    ifft4 = ifft4 * 255;
    imwrite("idft 20 1_HPF.jpg", ifft4);

    imshow("idft 20 2", ifft5);
    ifft5 = ifft5 * 255;
    imwrite("idft 20 2_HPF.jpg", ifft5);

    imshow("idft 20 3", ifft6);
    ifft6 = ifft6 * 255;
    imwrite("idft 20 3_HPF.jpg", ifft6);

    imshow("idft 50 1", ifft7);
    ifft7 = ifft7 * 255;
    imwrite("idft 50 1_HPF.jpg", ifft7);

    imshow("idft 50 2", ifft8);
    ifft8 = ifft8 * 255;
    imwrite("idft 50 2_HPF.jpg", ifft8);

    imshow("idft 50 3", ifft9);
    ifft9 = ifft9 * 255;
    imwrite("idft 50 3_HPF.jpg", ifft9);

    waitKey();
    destroyAllWindows();


    imshow("raccoon 512 spectrum", mag_ori);
    mag_ori = mag_ori * 255;
    //imwrite("raccoon 512 spectrum.jpg", mag_ori);

    imshow("raccoon 512+ butterworth_HPF 5 1 頻譜", mag1);
    mag1 = mag1 * 255;
    imwrite("raccoon 512 + butterworth_HPF 5 1 頻譜.jpg", mag1);

    imshow("raccoon 512 + butterworth_HPF 5 2 頻譜", mag2);
    mag2 = mag2 * 255;
    imwrite("raccoon 512 + butterworth_HPF 5 2 頻譜.jpg", mag2);

    imshow("raccoon 512 + butterworth_HPF 5 3 頻譜", mag3);
    mag3 = mag3 * 255;
    imwrite("raccoon 512 + butterworth_HPF 5 3 頻譜.jpg", mag3);

    imshow("raccoon 512 + butterworth_HPF 20 1 頻譜", mag4);
    mag4 = mag4 * 255;
    imwrite("raccoon 512 + butterworth_HPF 20 1 頻譜.jpg", mag4);

    imshow("raccoon 512 + butterworth_HPF 20 2 頻譜", mag5);
    mag5 = mag5 * 255;
    imwrite("raccoon 512 + butterworth_HPF 20 2 頻譜.jpg", mag5);

    imshow("raccoon 512 + butterworth_HPF 20 3 頻譜", mag6);
    mag6 = mag6 * 255;
    imwrite("raccoon 512 + butterworth_HPF 20 3 頻譜.jpg", mag6);

    imshow("raccoon 512 + butterworth_HPF 50 1 頻譜", mag7);
    mag7 = mag7 * 255;
    imwrite("raccoon 512 + butterworth_HPF 50 1 頻譜.jpg", mag7);

    imshow("raccoon 512 + butterworth_HPF 50 2 頻譜", mag8);
    mag8 = mag8 * 255;
    imwrite("raccoon 512 + butterworth_HPF 50 2 頻譜.jpg", mag8);

    imshow("raccoon 512 + butterworth_HPF 50 3 頻譜", mag9);
    mag9 = mag9 * 255;
    imwrite("raccoon 512+ butterworth_HPF 50 3 頻譜.jpg", mag9);
    waitKey();
    destroyAllWindows();


    //--原圖做IDFT-----------//
    IDFT_merge(IMG_ori_re, IMG_ori_im, "原始圖片 IDFT");

}



