/****************************************************************************************
* Filename    : 4_1_2.cpp                                                               *
* Update date : 12/11/2022                                                              *
* Author      : 顏郁芩                                                                  *
* Note        : roof_640x427 and roof_640x427_noise edge detection with sobel filter    *
****************************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;

void MY_HW4::HW4_1_2_1() {
    MY_HW4 HW4;
    //--------------------------參數---------------------------//
    int H = 640;
    int W = 427;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2;
    FILE* output_file, * output_file2;
    char in_imgpath[] = ".\\HW4_images_file\\roof_640x427.raw";
    char out_imgpath[] = "roof_640x427_after_sobel_filter1.raw";
    char out_imgpath2[] = "roof_640x427_after_sobel_filter2.raw";
    //char out_imgpath3[] = "roof_640x427_after_sobel_filter_combine.raw";

    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];

    unsigned char img_input1[640][427];
    //unsigned char img_input2[640][427];
    unsigned char img_output1[640][427];
    unsigned char img_output2[640][427];
    unsigned char img_input_big[640 + 2][427 + 2];
 
    int filter1[9] = { -1,0,1,-2,0,2,-1,0,1 };
    int filter2[9] = { -1,-2,-1,0,0,0,1,2,1 };

    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image roof_640x427.raw!\n");
    }
    fread(img, sizeof(unsigned char), 640 * 427, input_file);


    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_input1[x][y] = img[c];
            c++;
        }

    }

    //--------------------------replication/mirroring---------------------------//


for (int x = 0; x < 640 + 2; x++) {
    for (int y = 0; y < 427 + 2; y++) {
        if (x == 0) {
            if (y == 0) {
                img_input_big[x][y] = img_input1[0][0];
            }
            else if (y == 428) {
                img_input_big[x][y] = img_input1[0][426];
            }
            else {
                img_input_big[x][y] = img_input1[0][y - 1];
            }
        }
        else if (x == 641) {
            if (y == 0) {
                img_input_big[x][y] = img_input1[639][0];
            }
            else if (y == 428) {
                img_input_big[x][y] = img_input1[639][426];
            }
            else {
                img_input_big[x][y] = img_input1[639][y - 1];
            }
        }
        else if (y == 0) {
            img_input_big[x][y] = img_input1[x - 1][1];
        }
        else if (y == 428) {
            img_input_big[x][y] = img_input1[x - 1][426];
        }

        else {
            img_input_big[x][y] = img_input1[x - 1][y - 1];
        }

    }

}
    //--------convolution處理---------------------//
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter1);
        }
    }
    fopen_s(&output_file, out_imgpath, "wb");//out_imgpath1_4
    fwrite(img_output1, 1, size, output_file);
    fclose(output_file);

    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter2);
        }
    }

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img_output1, 1, size, output_file2);
    fclose(output_file2);

    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(output_file);
    fclose(output_file2);
}


void MY_HW4::HW4_1_2_2() {
    MY_HW4 HW4;
    //--------------------------參數---------------------------//
    int H = 640;
    int W = 427;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file, * output_file2, * output_file3;
    char in_imgpath[] = ".\\HW4_images_file\\roof_640x427_noise.raw";
    char out_imgpath[] = "roof_640x427_noise_after_sobel_filter1.raw";
    char out_imgpath2[] = "roof_640x427_noise_after_sobel_filter2.raw";
    char out_imgpath3[] = "roof_640x427_after_sobel_filter_combine.raw";

    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    //unsigned char img_watermark[512][512];
    //unsigned char img_back[512][512];

    unsigned char img_input1[640][427];
    //unsigned char img_input2[640][427];
    unsigned char img_output1[640][427];
    unsigned char img_output2[640][427];
    unsigned char img_input_big[640 + 2][427 + 2];

    int filter1[9] = { -1,0,1,-2,0,2,-1,0,1 };
    int filter2[9] = { -1,-2,-1,0,0,0,1,2,1 };
    //int data[9] = { 0,0,0,0,0,0,0,0,0 };
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image roof_640x427_noise.raw!\n");
    }
    fread(img, sizeof(unsigned char), 640 * 427, input_file);


    //--------------------------轉成二維陣列---------------------------//
    int c = 0;
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_input1[x][y] = img[c];
            //img_input2[x][y] = img2[c];
            c++;
        }

    }
    
    //--------------------------replication/mirroring---------------------------//


for (int x = 0; x < 640 + 2; x++) {
    for (int y = 0; y < 427 + 2; y++) {
        if (x == 0) {
            if (y == 0) {
                img_input_big[x][y] = img_input1[0][0];
            }
            else if (y == 428) {
                img_input_big[x][y] = img_input1[0][426];
            }
            else {
                img_input_big[x][y] = img_input1[0][y - 1];
            }
        }
        else if (x == 641) {
            if (y == 0) {
                img_input_big[x][y] = img_input1[639][0];
            }
            else if (y == 428) {
                img_input_big[x][y] = img_input1[639][426];
            }
            else {
                img_input_big[x][y] = img_input1[639][y - 1];
            }
        }
        else if (y == 0) {
            img_input_big[x][y] = img_input1[x - 1][1];
        }
        else if (y == 428) {
            img_input_big[x][y] = img_input1[x - 1][426];
        }

        else {
            img_input_big[x][y] = img_input1[x - 1][y - 1];
        }

    }

}

//------------------------------處理-----------------//
for (int x = 0; x < 640; x++) {
    for (int y = 0; y < 427; y++) {
        img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter1);
    }
}
fopen_s(&output_file, out_imgpath, "wb");//out_imgpath1_4
fwrite(img_output1, 1, size, output_file);
fclose(output_file);

for (int x = 0; x < 640; x++) {
    for (int y = 0; y < 427; y++) {
        img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter2);
    }
}

fopen_s(&output_file2, out_imgpath2, "wb");
fwrite(img_output1, 1, size, output_file2);
fclose(output_file2);

    //--------------------------輸出檔案---------------------------//




    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);
    fclose(output_file);
    fclose(output_file2);
}


void MY_HW4::HW4_1_2_COMBINE() {

    int H = 640;
    int W = 427;
    //unsigned char img[256 * 256];
    FILE* input_file, * input_file2, * input_file3, * input_file4;
    FILE* output_file, * output_file2;
    char in_imgpath[] = "roof_640x427_after_sobel_filter1.raw";
    char in_imgpath2[] = "roof_640x427_after_sobel_filter2.raw";
    char in_imgpath3[] = "roof_640x427_noise_after_sobel_filter1.raw";
    char in_imgpath4[] = "roof_640x427_noise_after_sobel_filter2.raw";
    char out_imgpath[] = "roof_640x427_after_sobel_filter_combine.raw";
    char out_imgpath2[] = "roof_640x427_noise_after_sobel_filter_combine.raw";

    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char* img2 = new unsigned char[size];
    unsigned char* img3 = new unsigned char[size];
    unsigned char* img4 = new unsigned char[size];
    unsigned char img_output1[640 * 427];
    unsigned char img_output2[640 * 427];

    //-------------------------------------合併------------------------//
    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image roof_640x427_after_sobel_filter1.raw!\n");
    }
    fread(img, sizeof(unsigned char), 640 * 427, input_file);

    fopen_s(&input_file2, in_imgpath2, "rb");
    if (!input_file2) {
        printf("Unable to open the image roof_640x427_after_sobel_filter2.raw!\n");
    }
    fread(img2, sizeof(unsigned char), 640 * 427, input_file2);

    fopen_s(&input_file3, in_imgpath3, "rb");
    if (!input_file3) {
        printf("Unable to open the image roof_640x427_noise_after_sobel_filter1.raw!\n");
    }
    fread(img3, sizeof(unsigned char), 640 * 427, input_file3);

    fopen_s(&input_file4, in_imgpath4, "rb");
    if (!input_file4) {
        printf("Unable to open the image roof_640x427_noise_after_sobel_filter2.raw!\n");
    }
    fread(img4, sizeof(unsigned char), 640 * 427, input_file4);


    for (int x = 0; x < 640 * 427; x++) {
        img_output1[x] = (img[x] + img2[x]) * 0.5;
        img_output2[x] = (img3[x] + img4[x]) * 0.5;
    }

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img_output1, 1, size, output_file);
    fclose(output_file);


    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img_output2, 1, size, output_file2);
    fclose(output_file2);
}