/**********************************************************
* Filename    : HW1_2.cpp                                 *
* Update date : 09/27/2022                                *
* Author      : �C����                                    *
* Note        : open the image with opencv and add text   *
***********************************************************/

#include "Header.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace N;
using namespace std;
using namespace cv;


void MY_HW::HW1_2() {
    //--------------------------�򥻰Ѽ�---------------------------//

    int H = 466;
    int W = 621;
    FILE* input_file;
    char imgpath[100] = ".\\HM1_images_file\\JackieChen.raw";
    unsigned char* img_lena = new unsigned char[621 * 466];

    //--------------------------�}�ҡBŪ���ɮ�---------------------------//

    fopen_s(&input_file, imgpath, "rb");
    fread(img_lena, sizeof(unsigned char), (621 * 466), input_file);
    Mat mat_JackieChen(H, W, CV_8UC1, img_lena);

    //--------------------------��r�B��m�Ѽ�---------------------------//
    string text1 = "110368155";
    string text2 = "I mean Why?";

    int Font = FONT_HERSHEY_SIMPLEX;
    int font_scale = 1;
    int thickness = 1;//�r��ʲ�

    Size text_size1 = getTextSize(text1, Font, font_scale, thickness, 0);
    Size text_size2 = getTextSize(text2, Font, font_scale, thickness, 0);

    int pointx1 = mat_JackieChen.cols / 2 - text_size1.width / 2;
    int pointy1 = mat_JackieChen.rows*1/8 + text_size2.height / 2;
    int pointx2 = mat_JackieChen.cols / 2 - text_size2.width / 2;
    int pointy2 = mat_JackieChen.rows*5 / 6 + text_size2.height / 2;
        //--------------------------��m�i�H��origin---------------------------//
        //Point origin;                                                        //
        //origin.x = mat_JackieChen.cols / 2 - text_size.width / 2;            //
        //origin.y = mat_JackieChen.rows / 2 + text_size.height / 2;           //
        //---------------------------------------------------------------------//

    //--------------------------�L�X�Ϥ�---------------------------//

    putText(mat_JackieChen, text1, Point(pointx1, pointy1), Font, font_scale, cv::Scalar(0, 0, 0), thickness, 8, 0);
    putText(mat_JackieChen, text2, Point(pointx2, pointy2), Font, font_scale, cv::Scalar(0, 0, 0), thickness, 8, 0);
    imshow("JackieChen in opencv", mat_JackieChen);
    cout << "Please press 0 to close the window" << endl;
    waitKey(0);
    destroyAllWindows();

    //--------------------------�x�s�Ϥ�---------------------------//

    imwrite("JackieChen_opencv.png", mat_JackieChen);

}