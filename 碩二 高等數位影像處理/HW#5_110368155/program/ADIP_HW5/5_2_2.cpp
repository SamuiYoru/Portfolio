/******************************************************************************************
* Filename    : 5_2_2.cpp                                                                 *
* Update date : 26/11/2022                                                                *
* Author      : 顏郁芩                                                                    *
* Note        : Use High-frequency Emphasis Filtering to inprove owl_blur_512.raw         *
*******************************************************************************************/

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


void IDFT_merge_2(Mat real, Mat image, string name) {
    Mat out;
    Mat planes2[] = { Mat_<float>(real),  Mat_<float>(image) };
    merge(planes2, 2, out);
    Mat ifft;
    idft(out, ifft, DFT_REAL_OUTPUT);
    normalize(ifft, ifft, 0, 1, NORM_MINMAX);
    imshow(name, ifft);
    ifft = ifft * 255;
    //imwrite(name + ".jpg", ifft);

    waitKey();
    destroyAllWindows();
}
void shift_2(Mat in, int x, int y) {
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



void BW_Filter_maker(int D0, int n, Mat output) {//,int distance
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
            output.at<float>(x, y) = 1.0 / (1 + pow((D0 / dist), (2 * n)));
            //output.at<float>(x, y) = 1-exp(-pow(dist,2)/(2*pow(D0,2)));

        }
    }
}

void MY_HW5::HW5_2_2() {
    MY_HW5 HW5;
    //--------------------------參數---------------------------//
    int H = 512;
    int W = 512;

    FILE* input_file, * input_file2, * input_file3;
    char in_imgpath[] = ".\\HW5_images_file\\owl_blur_512.raw";
    FILE* output_file;
    char out_imgpath[] = "owl_blur_512_after.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];


    unsigned char img_input[512][512];

    double DFTvalue[256][256];

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image owl_blur_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    //-------處理-------//

    Mat imgCV(512, 512, CV_8UC1, img);
    Mat original = imgCV.clone();
    imshow("owl_blur_512", imgCV);

    Mat planes[] = { Mat_<float>(imgCV), Mat::zeros(imgCV.size(), CV_32F) };
    Mat complexImg;
    merge(planes, 2, complexImg);//DFT需要二通道的輸入，一個是實部(讀入資料)，一個是虛部(0)
   
    dft(complexImg, complexImg);

    split(complexImg, planes);  //輸入拆成兩個plane
    Mat IMG_ori_re = planes[0].clone();
    Mat IMG_ori_im = planes[1].clone();
    Mat ans1 = complexImg.clone();

    Mat ori_mag;
    magnitude(planes[0], planes[1], ori_mag);//算頻域magnitude
    Mat mag = ori_mag.clone();
    log(mag, mag);
    int cx = mag.cols / 2;
    int cy = mag.rows / 2;
    shift_2(mag, 512, 512);//把高頻中心換到中間
    normalize(mag, mag, 0, 1, NORM_MINMAX);
    Mat mag_ori = mag.clone();//輸出MAGNITUDE
    Mat mag1 = mag.clone();

    imshow("owl_blur_512 spectrum", mag_ori);
    mag_ori = mag_ori * 255;
    imwrite("owl_blur_512 spectrum.jpg", mag_ori);
    waitKey();


    Mat filter(512, 512, CV_32F);
    BW_Filter_maker(100, 1, filter);
    imshow("FILTER", filter);
    Mat filter_clone = filter.clone();
    filter = filter * 255;
    imwrite("FILTER.jpg", filter);
    waitKey();

    shift_2(filter_clone, 512, 512);
    Mat planesfil1[] = { Mat_<float>(filter_clone),Mat_<float>(filter_clone) };
    Mat planesfil;
    merge(planesfil1, 2, planesfil);//沒有轉換過的FILTER


    for (int x = 0; x < mag.cols; x++) {
        for (int y = 0; y < mag.rows; y++) {
            mag1.at<float>(x, y) = filter.at<float>(x, y) * mag1.at<float>(x, y);//做完filter的頻譜圖
            ans1.at<float>(x, y) = planesfil.at<float>(x, y) * ans1.at<float>(x, y);
        }
    }
    normalize(mag1, mag1, 0, 1, NORM_MINMAX);
    imshow("owl_blur_512_after 頻譜", mag1);
    mag1 = mag1 * 255;
    imwrite("owl_blur_512_after頻譜.jpg", mag1);
    waitKey();

    Mat ifft1;
    idft(ans1, ifft1, DFT_REAL_OUTPUT);
    normalize(ifft1, ifft1, 0, 1, NORM_MINMAX);
    ifft1 = ifft1*1.2 ;
    imshow("owl_blur_512_after_FILTER", ifft1);
    ifft1 = ifft1 * 255;
    imwrite("owl_blur_512_after_FILTER.jpg", ifft1);
    waitKey();

    Mat after_filter = ifft1.clone();//經過FILTER的圖

    normalize(ifft1, ifft1, 0, 255, NORM_MINMAX);
    Mat filter1 = ifft1.clone();
    Mat filter2 = ifft1.clone();
    Mat filter3 = ifft1.clone();
    for (int x = 0; x < filter1.cols; x++) {
        for (int y = 0; y < filter1.rows; y++) {
            if (filter1.at<float>(x, y) > 150) {
                filter1.at<float>(x, y) = 1;
            }
            else if (filter1.at<float>(x, y) < 150&& filter1.at<float>(x, y) > 145) {
                filter1.at<float>(x, y) = 0.5;
            }
            else {
                filter1.at<float>(x, y) = 0;
            }
        }
    }


    for (int x = 0; x < filter2.cols; x++) {
        for (int y = 0; y < filter2.rows; y++) {
            if (filter2.at<float>(x, y) > 140) {
                filter2.at<float>(x, y) = 1;
            }
            else {
                filter2.at<float>(x, y) = 0;
            }
        }
    }


    for (int x = 0; x < filter3.cols; x++) {
        for (int y = 0; y < filter3.rows; y++) {
            if (filter3.at<float>(x, y) > 135) {
                filter3.at<float>(x, y) = 1;
            }
            else {
                filter3.at<float>(x, y) = 0;
            }
        }
    }


    //normalize(ifft2, ifft2, 0, 1, NORM_MINMAX);
    Mat add(512, 512, CV_32F);
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            unsigned char color = (original.at<unsigned char>(x, y));
            color = color * 0.8;
            if (filter3.at<float>(x, y) == (float)1) {
                        color = color * 1.12;
            }
            else if (filter1.at<float>(x, y) == (float)1) {
                color = color * 1.15;
            }
            else if (filter1.at<float>(x, y) == (float)0.5) {
                color = color * 1.05;
            }

            
            else if (filter2.at<float>(x, y) == (float)1) {
                color = color*1.02;
            }

            add.at<float>(x, y) = color;
        }
    }


    imshow("FILTER 1 ", filter1);
    filter1 = filter1 * 255;
    imwrite("FILTER 1.jpg", filter1);
    imshow("FILTER 2", filter2);
    filter2 = filter2 * 255;
    imwrite("FILTER 2.jpg", filter2);
    imshow("FILTER 3", filter3);
    filter3 = filter3 * 255;
    imwrite("FILTER 3.jpg", filter3);


    normalize(add, add, 0, 1, NORM_MINMAX);
    imshow("增強後", add);
    add = add * 255;
    imwrite("owl_blur_512_after.jpg", add);
    waitKey();
    destroyAllWindows();
    IDFT_merge_2(IMG_ori_re, IMG_ori_im, "原始圖片 IDFT");

    unsigned char out_img[512*512];
    int c = 0;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            out_img[c] = filter1.at<float>(x, y);
            c++;
        }
    }



    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(out_img, 1, size, output_file);
    fclose(output_file);
    

    delete[] img;
    fclose(input_file);
   

}



/*void MY_HW5::HW5_2_2_other() {
    MY_HW5 HW5;
    //--------------------------參數---------------------------//
    int H = 512;
    int W = 512;

    FILE* input_file, * input_file2, * input_file3;
    char in_imgpath[] = ".\\HW5_images_file\\owl_blur_512.raw";
    FILE* output_file;
    char out_imgpath[] = "owl_blur_512_after.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];


    unsigned char img_input[512][512];

    double DFTvalue[256][256];

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image owl_blur_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    //-------處理-------//

    Mat imgCV(512, 512, CV_8UC1, img);
    Mat original = imgCV.clone();
    imshow("owl_blur_512", imgCV);

    Mat planes[] = { Mat_<float>(imgCV), Mat::zeros(imgCV.size(), CV_32F) };
    Mat complexImg;
    merge(planes, 2, complexImg);//DFT需要二通道的輸入，一個是實部(讀入資料)，一個是虛部(0)

    dft(complexImg, complexImg);

    split(complexImg, planes);  //輸入拆成兩個plane
    Mat IMG_ori_re = planes[0].clone();
    Mat IMG_ori_im = planes[1].clone();
    Mat ans = complexImg.clone();
    Mat ans1 = complexImg.clone();
    Mat ans2 = complexImg.clone();
    Mat ans3 = complexImg.clone();

    Mat ori_mag;
    magnitude(planes[0], planes[1], ori_mag);//算頻域magnitude
    Mat mag = ori_mag.clone();
    log(mag, mag);
    int cx = mag.cols / 2;
    int cy = mag.rows / 2;
    shift_2(mag, 512, 512);//把高頻中心換到中間
    normalize(mag, mag, 0, 1, NORM_MINMAX);
    Mat mag_ori = mag.clone();//輸出MAGNITUDE
    Mat mag1 = mag.clone();
    Mat mag2 = mag.clone();
    Mat mag3 = mag.clone();

    imshow("owl_blur_512 spectrum", mag_ori);
    mag_ori = mag_ori * 255;
   // imwrite("owl_blur_512 spectrum.jpg", mag_ori);
    waitKey();


    Mat filter(512, 512, CV_32F);
    BW_Filter_maker(200, 1, filter);
    imshow("FILTER", filter);
    Mat filter_clone = filter.clone();
    filter = filter * 255;
    //imwrite("FILTER.jpg", filter);
    waitKey();

    Mat filter2(512, 512, CV_32F);
    BW_Filter_maker(150, 1, filter2);
    imshow("FILTER2", filter2);
    Mat filter2_clone = filter2.clone();
    filter2 = filter2 * 255;
    //imwrite("FILTER2.jpg", filter2);
    waitKey();


    Mat filter3(512, 512, CV_32F);
    BW_Filter_maker(100, 1, filter3);
    imshow("FILTER3", filter3);
    Mat filter3_clone = filter3.clone();
    filter3 = filter3 * 255;
    //imwrite("FILTER3.jpg", filter3);
    waitKey();

    shift_2(filter_clone, 512, 512);
    Mat planesfil1[] = { Mat_<float>(filter_clone),Mat_<float>(filter_clone) };
    Mat planesfil;
    merge(planesfil1, 2, planesfil);//沒有轉換過的FILTER

    shift_2(filter2_clone, 512, 512);
    Mat planesfil12[] = { Mat_<float>(filter2_clone),Mat_<float>(filter2_clone) };
    Mat planesfil2;
    merge(planesfil12, 2, planesfil2);//沒有轉換過的FILTER

    shift_2(filter3_clone, 512, 512);
    Mat planesfil13[] = { Mat_<float>(filter3_clone),Mat_<float>(filter3_clone) };
    Mat planesfil3;
    merge(planesfil13, 2, planesfil3);//沒有轉換過的FILTER


    for (int x = 0; x < mag.cols; x++) {
        for (int y = 0; y < mag.rows; y++) {
            mag1.at<float>(x, y) = filter.at<float>(x, y) * mag1.at<float>(x, y);//做完filter的頻譜圖
            mag2.at<float>(x, y) = filter2.at<float>(x, y) * mag2.at<float>(x, y);//做完filter的頻譜圖
            mag3.at<float>(x, y) = filter3.at<float>(x, y) * mag3.at<float>(x, y);//做完filter的頻譜圖

            ans1.at<float>(x, y) = planesfil.at<float>(x, y) * ans1.at<float>(x, y);
            ans2.at<float>(x, y) = planesfil2.at<float>(x, y) * ans2.at<float>(x, y);
            ans3.at<float>(x, y) = planesfil3.at<float>(x, y) * ans3.at<float>(x, y);
        }
    }
    normalize(mag1, mag1, 0, 1, NORM_MINMAX);
    imshow("owl_blur_512_after 頻譜", mag1);
    //mag1 = mag1 * 255;
    //imwrite("owl_blur_512_after頻譜.jpg", mag1);
    normalize(mag2, mag2, 0, 1, NORM_MINMAX);
    imshow("owl_blur_512_after2 頻譜", mag2);
    //mag2 = mag2 * 255;
    //imwrite("owl_blur_512_after頻譜2.jpg", mag2);
    normalize(mag3, mag3, 0, 1, NORM_MINMAX);
    imshow("owl_blur_512_after3 頻譜", mag3);
    //mag3 = mag3 * 255;
    //imwrite("owl_blur_512_after頻譜3.jpg", mag3);
    waitKey();



    Mat ifft1;
    idft(ans1, ifft1, DFT_REAL_OUTPUT);
    normalize(ifft1, ifft1, 0, 2, NORM_MINMAX);
    //ifft1 = ifft1 * 1.2;
    imshow("owl_blur_512_after_FILTER", ifft1);
    //ifft1 = ifft1 * 255;
    //imwrite("owl_blur_512_after_FILTER.jpg", ifft1);
   // waitKey();


    Mat ifft2;
    idft(ans2, ifft2, DFT_REAL_OUTPUT);
    normalize(ifft2, ifft2, 0, 2, NORM_MINMAX);
    //ifft2 = ifft2 * 1.2;
    imshow("owl_blur_512_after_FILTER2", ifft2);
    //ifft2 = ifft2 * 255;
    //imwrite("owl_blur_512_after_FILTER2.jpg", ifft1);
    //waitKey();
    
    Mat ifft3;
    idft(ans3, ifft3, DFT_REAL_OUTPUT);
    normalize(ifft3, ifft3, 0, 2, NORM_MINMAX);
    //ifft3 = ifft3 * 1.2;
    imshow("owl_blur_512_after_FILTER3", ifft3);
    //ifft3 = ifft3 * 255;
   // imwrite("owl_blur_512_after_FILTER3.jpg", ifft3);
    //waitKey();

    //Mat after_filter = ifft1.clone();//經過FILTER的圖

    //normalize(ifft1, ifft1, 0, 255, NORM_MINMAX);
   
    Mat after_img(512, 512, CV_32F);
    for (int x = 0; x < 512 * 512; x++) {
        after_img.at<float>(x) = imgCV.at<unsigned char>(x)*0.25 + ifft1.at<float>(x)*2 + ifft2.at<float>(x)*1 + ifft3.at<float>(x)*20;
    }
    
    //normalize(after_img, after_img, 0, 255, NORM_MINMAX);
    //after_img = after_img/100+5;
    normalize(after_img, after_img, 0, 1, NORM_MINMAX);
    for (int x = 0; x < 512 * 512; x++) {
        //cout << +imgCV.at<unsigned char>(x)<<" "<< ifft1.at<float>(x) <<" " << after_img.at<float>(x) << endl;
    }
    imshow("增強後 頻譜", after_img);
    imshow("原圖", imgCV);
    //shift_2(after_img, 512, 512);
    Mat idft_ans;
    //idft(after_img, idft_ans, DFT_REAL_OUTPUT);
    //normalize(idft_ans, idft_ans, 0, 1, NORM_MINMAX);
    //imshow("增強後", idft_ans);
    waitKey();


  


}*/
