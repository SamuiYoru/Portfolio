/*********************************************************************************************
* Filename    : 4_1_1.cpp                                                                    *
* Update date : 12/11/2022                                                                   *
* Author      : 顏郁芩                                                                       *
* Note        : roof_640x427 and roof_640x427_noise edge detection with laplacian filter     *
*********************************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;

void MY_HW4::HW4_1_1_1() {
    MY_HW4 HW4;
    //--------------------------參數---------------------------//
    int H = 640;
    int W = 427;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file, * output_file2, * output_file1_2, * output_file2_2, * output_file1_3, * output_file2_3, * output_file1_4, * output_file2_4;
    char in_imgpath[] = ".\\HW4_images_file\\roof_640x427.raw";
    char out_imgpath[] = ".\\roof_640x427_after_filter1_smaller output.raw";
    char out_imgpath2[] = ".\\roof_640x427_after_filter2_smaller output.raw";
    char out_imgpath1_2[] = ".\\roof_640x427_after_filter1_ad_hoc.raw";
    char out_imgpath2_2[] = ".\\roof_640x427_after_filter2_ad_hoc.raw";
    char out_imgpath1_3[] = ".\\roof_640x427_after_filter1_zero-padding.raw";
    char out_imgpath2_3[] = ".\\roof_640x427_after_filter2_zero-padding.raw";
    char out_imgpath1_4[] = ".\\roof_640x427_after_filter1_mirroring.raw";
    char out_imgpath2_4[] = ".\\roof_640x427_after_filter2_mirroring.raw";
    
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char img_input1[640][427];
    //unsigned char img_input2[640][427];
    unsigned char img_output1[640][427];
    //unsigned char img_output2[640][427];
    unsigned char img_input_big[640+2][427+2];
    int filter1[9] = { 0,-1,0,-1,4,-1,0,-1,0 };
    int filter2[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
    //int filter1[9] = { 1,1,1,1,1,1,1,1,1 };



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
    //--------------------------smaller output---------------------------//


    for (int x = 0; x < 640+2; x++) {
        for (int y = 0; y < 427+2; y++) {
            if (x >= 1 && x <= 640) {
                if (y >= 1 && y <= 427) {
                    img_input_big[x][y] = img_input1[x - 1][y - 1];
                }
            }
        }
    }



    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            if (x >= 1 && x <= 638) {
                if (y >= 1 && y <= 425) {
                    img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter1);
                }
            }
        }
    }

    fopen_s(&output_file, out_imgpath, "wb");//out_imgpath
    fwrite(img_output1, 1, 642*429, output_file);
    fclose(output_file);

    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            if (x >= 1 && x <= 638) {
                if (y >= 1 && y <= 425) {
                    img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter2);
                }
            }
        }
    }

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img_output1, 1, size, output_file2);
    fclose(output_file2);

    //--------------------------ad_hoc filters---------------------------//
   
    int data[9] = { 0,0,0,0,0,0,0,0,0 };
    for (int x = 0; x < 9; x++) {
        data[x] = 0;
    }
    int filter[9] = { 0,0,0,0,0,0,0,0,0 };

    for (int x = 0; x < 640 + 2; x++) {
        for (int y = 0; y < 427 + 2; y++) {
            if (x >= 1 && x <= 640) {
                if (y >= 1 && y <= 427) {
                    img_input_big[x][y] = img_input1[x - 1][y - 1];
                }
            }
            else {
                img_input_big[x][y] = 0;
            }
        }
    }


    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {

            data[0] = img_input_big[x+1][y+1];
            data[1] = img_input_big[x+1][y+2];
            data[2] = img_input_big[x+1][y + 3];

            data[3] = img_input_big[x+2][y +1];
            data[4] = img_input_big[x+2][y+2];//正中間
            data[5] = img_input_big[x+2][y + 3];

            data[6] = img_input_big[x+3][y+1];
            data[7] = img_input_big[x + 3][y+2];
            data[8] = img_input_big[x + 3][y +3];


            if (x ==0 && y==0) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = 0;
                filter[4] = 2;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }
            else if (x == 640 && y == 427) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 2;//正中間
                filter[5] = 0;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }
            else if (x == 0 && y == 427) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 2;//正中間
                filter[5] = 0;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }
            else if (x == 640 && y == 0) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = 0;
                filter[4] = 2;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }
            else if (x == 0) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }

            else if (x == 640) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }


            else if (y==0) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = 0;
                filter[4] =3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }

            else if (y == 427) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = 0;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }

            else {//   int filter1[9] = { 0,-1,0,-1,4,-1,0,-1,0 };
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 4;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }

            img_output1[x][y] = HW4.convolution3X3(filter, data);
            //img_output2[x][y] = HW4.convolution3X3(filter2, data);

        }
    }

    fopen_s(&output_file1_2, out_imgpath1_2, "wb");
    fwrite(img_output1, 1, size, output_file1_2);
    fclose(output_file1_2);


    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {

            data[0] = img_input_big[x + 1][y + 1];
            data[1] = img_input_big[x + 1][y + 2];
            data[2] = img_input_big[x + 1][y + 3];

            data[3] = img_input_big[x + 2][y + 1];
            data[4] = img_input_big[x + 2][y + 2];//正中間
            data[5] = img_input_big[x + 2][y + 3];

            data[6] = img_input_big[x + 3][y + 1];
            data[7] = img_input_big[x + 3][y + 2];
            data[8] = img_input_big[x + 3][y + 3];

            if (x == 0 && y == 0) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = 0;
                filter[4] = 3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = -1;
            }
            else if (x == 640 && y == 427) {
                filter[0] = -1;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = 0;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }
            else if (x == 0 && y == 427) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = 0;
                filter[6] = -1;
                filter[7] = -1;
                filter[8] = 0;
            }
            else if (x == 640 && y == 0) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = -1;
                filter[3] = 0;
                filter[4] = 3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }
            else if (x == 0) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 5;//正中間
                filter[5] = -1;
                filter[6] = -1;
                filter[7] = -1;
                filter[8] = -1;
            }

            else if (x == 640) {
                filter[0] = -1;
                filter[1] = -1;
                filter[2] = -1;
                filter[3] = -1;
                filter[4] = 5;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }


            else if (y == 0) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = -1;
                filter[3] = 0;
                filter[4] = 5;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = -1;
            }

            else if (y == 427) {
                filter[0] = -1;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 5;//正中間
                filter[5] = 0;
                filter[6] = -1;
                filter[7] = -1;
                filter[8] = 0;
            }

            else {//   int filter1[9] = { 0,-1,0,-1,4,-1,0,-1,0 };
                filter[0] = -1;
                filter[1] = -1;
                filter[2] = -1;
                filter[3] = -1;
                filter[4] = 8;//正中間
                filter[5] = -1;
                filter[6] = -1;
                filter[7] = -1;
                filter[8] = -1;
            }

            img_output1[x][y] = HW4.convolution3X3(filter, data);

        }
    }

    fopen_s(&output_file2_2, out_imgpath2_2, "wb");
    fwrite(img_output1, 1, size, output_file2_2);
    fclose(output_file2_2);

    //--------------------------zero-padding---------------------------//
    for (int x = 0; x < 9; x++) {
        data[x] = 0;
    }


    for (int x = 0; x < 640+2; x++) {
        for (int y = 0; y <427+2; y++) {
            if (x == 0) {
                img_input_big[x][y] = 0;
            }
            else if (x == 641) {
                img_input_big[x][y] = 0;
            }
            else if (y == 0) {
                img_input_big[x][y] = 0;
            }
            else if (y == 428) {
                img_input_big[x][y] = 0;
            }
            else {
                img_input_big[x][y] = img_input1[x-1][y-1];
            }
        }
    }   


    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x+1, y+1, img_input_big, filter1);
        }
    }

    fopen_s(&output_file1_3, out_imgpath1_3, "wb");
    fwrite(img_output1, 1, size, output_file1_3);
    fclose(output_file1_3);

    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter2);
        }
    }
    fopen_s(&output_file2_3, out_imgpath2_3, "wb");
    fwrite(img_output1, 1, size, output_file2_3);
    fclose(output_file2_3);

    //--------------------------replication/mirroring---------------------------//
    
    for (int x = 0; x < 640+2; x++) {
        for (int y = 0; y < 427+2; y++) {
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
                else if (y ==428) {
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
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter1);
        }
    }

    fopen_s(&output_file1_4, out_imgpath1_4, "wb");//out_imgpath1_4
    fwrite(img_output1, 1, size, output_file1_4);
    fclose(output_file1_4);

    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter2);
        }
    }

   fopen_s(&output_file2_4, out_imgpath2_4, "wb");
   fwrite(img_output1, 1, size, output_file2_4);
   fclose(output_file2_4);

    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);

}


void MY_HW4::HW4_1_1_2() {
    MY_HW4 HW4;
    //--------------------------參數---------------------------//
    int H = 640;
    int W = 427;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file, * output_file2, * output_file1_2, * output_file2_2, * output_file1_3, * output_file2_3, * output_file1_4, * output_file2_4;
    char in_imgpath[] = ".\\HW4_images_file\\roof_640x427_noise.raw";
    char out_imgpath[] = ".\\roof_640x427_noise_after_filter1_smaller output.raw";
    char out_imgpath2[] = ".\\roof_640x427_noise_after_filter2_smaller output.raw";
    char out_imgpath1_2[] = ".\\roof_640x427_noise_after_filter1_ad_hoc.raw";
    char out_imgpath2_2[] = ".\\roof_640x427_noise_after_filter2_ad_hoc.raw";
    char out_imgpath1_3[] = ".\\roof_640x427_noise_after_filter1_zero-padding.raw";
    char out_imgpath2_3[] = ".\\roof_640x427_noise_after_filter2_zero-padding.raw";
    char out_imgpath1_4[] = ".\\roof_640x427_noise_after_filter1_mirroring.raw";
    char out_imgpath2_4[] = ".\\roof_640x427_noise_after_filter2_mirroring.raw";

    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char img_input1[640][427];
    //unsigned char img_input2[640][427];
    unsigned char img_output1[640][427];
    //unsigned char img_output2[640][427];
    int filter1[9] = { 0,-1,0,-1,4,-1,0,-1,0 };
    int filter2[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
    unsigned char img_input_big[640 + 2][427 + 2];


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
            c++;
        }

    }

    //fopen_s(&output_file, "TEST.raw", "wb");//out_imgpath
    //fwrite(img_input1, 1, size, output_file);
    //fclose(output_file);
    //--------------------------smaller output---------------------------//
    


    for (int x = 0; x < 640 + 2; x++) {
        for (int y = 0; y < 427 + 2; y++) {
            if (x >= 1 && x <= 640) {
                if (y >= 1 && y <= 427) {
                    img_input_big[x][y] = img_input1[x - 1][y - 1];
                }
            }
        }
    }



    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            if (x >= 1 && x <= 638) {
                if (y >= 1 && y <= 425) {
                    img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter1);
                }
            }
        }
    }

    fopen_s(&output_file, out_imgpath, "wb");//out_imgpath
    fwrite(img_output1, 1, size, output_file);
    fclose(output_file);

    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            if (x >= 1 && x <= 638) {
                if (y >= 1 && y <= 425) {
                    img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter2);
                }
            }
        }
    }

    fopen_s(&output_file2, out_imgpath2, "wb");
    fwrite(img_output1, 1, size, output_file2);
    fclose(output_file2);


    //--------------------------ad_hoc filters---------------------------//

    int data[9] = { 0,0,0,0,0,0,0,0,0 };
    for (int x = 0; x < 9; x++) {
        data[x] = 0;
    }
    int filter[9] = { 0,0,0,0,0,0,0,0,0 };

    
    for (int x = 0; x < 640 + 2; x++) {
        for (int y = 0; y < 427 + 2; y++) {
            if (x >= 1 && x <= 640) {
                if (y >= 1 && y <= 427) {
                    img_input_big[x][y] = img_input1[x - 1][y - 1];
                }
            }
            else {
                img_input_big[x][y] = 0;
            }
        }
    }


    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {

            data[0] = img_input_big[x + 1][y + 1];
            data[1] = img_input_big[x + 1][y + 2];
            data[2] = img_input_big[x + 1][y + 3];

            data[3] = img_input_big[x + 2][y + 1];
            data[4] = img_input_big[x + 2][y + 2];//正中間
            data[5] = img_input_big[x + 2][y + 3];

            data[6] = img_input_big[x + 3][y + 1];
            data[7] = img_input_big[x + 3][y + 2];
            data[8] = img_input_big[x + 3][y + 3];


            if (x == 0 && y == 0) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = 0;
                filter[4] = 2;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }
            else if (x == 640 && y == 427) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 2;//正中間
                filter[5] = 0;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }
            else if (x == 0 && y == 427) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 2;//正中間
                filter[5] = 0;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }
            else if (x == 640 && y == 0) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = 0;
                filter[4] = 2;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }
            else if (x == 0) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }

            else if (x == 640) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }


            else if (y == 0) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = 0;
                filter[4] = 3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }

            else if (y == 427) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = 0;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }

            else {//   int filter1[9] = { 0,-1,0,-1,4,-1,0,-1,0 };
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 4;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = 0;
            }

            img_output1[x][y] = HW4.convolution3X3(filter, data);
            //img_output2[x][y] = HW4.convolution3X3(filter2, data);

        }
    }

    fopen_s(&output_file1_2, out_imgpath1_2, "wb");
    fwrite(img_output1, 1, size, output_file1_2);
    fclose(output_file1_2);


    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {

            data[0] = img_input_big[x + 1][y + 1];
            data[1] = img_input_big[x + 1][y + 2];
            data[2] = img_input_big[x + 1][y + 3];

            data[3] = img_input_big[x + 2][y + 1];
            data[4] = img_input_big[x + 2][y + 2];//正中間
            data[5] = img_input_big[x + 2][y + 3];

            data[6] = img_input_big[x + 3][y + 1];
            data[7] = img_input_big[x + 3][y + 2];
            data[8] = img_input_big[x + 3][y + 3];



            if (x == 0 && y == 0) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = 0;
                filter[4] = 3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = -1;
            }
            else if (x == 640 && y == 427) {
                filter[0] = -1;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = 0;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }
            else if (x == 0 && y == 427) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 3;//正中間
                filter[5] = 0;
                filter[6] = -1;
                filter[7] = -1;
                filter[8] = 0;
            }
            else if (x == 640 && y == 0) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = -1;
                filter[3] = 0;
                filter[4] = 3;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }
            else if (x == 0) {
                filter[0] = 0;
                filter[1] = 0;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 5;//正中間
                filter[5] = -1;
                filter[6] = -1;
                filter[7] = -1;
                filter[8] = -1;
            }

            else if (x == 640) {
                filter[0] = -1;
                filter[1] = -1;
                filter[2] = -1;
                filter[3] = -1;
                filter[4] = 5;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = 0;
                filter[8] = 0;
            }


            else if (y == 0) {
                filter[0] = 0;
                filter[1] = -1;
                filter[2] = -1;
                filter[3] = 0;
                filter[4] = 5;//正中間
                filter[5] = -1;
                filter[6] = 0;
                filter[7] = -1;
                filter[8] = -1;
            }

            else if (y == 427) {
                filter[0] = -1;
                filter[1] = -1;
                filter[2] = 0;
                filter[3] = -1;
                filter[4] = 5;//正中間
                filter[5] = 0;
                filter[6] = -1;
                filter[7] = -1;
                filter[8] = 0;
            }

            else {//   int filter1[9] = { 0,-1,0,-1,4,-1,0,-1,0 };
                filter[0] = -1;
                filter[1] = -1;
                filter[2] = -1;
                filter[3] = -1;
                filter[4] = 8;//正中間
                filter[5] = -1;
                filter[6] = -1;
                filter[7] = -1;
                filter[8] = -1;
            }

            img_output1[x][y] = HW4.convolution3X3(filter, data);

        }
    }

    fopen_s(&output_file2_2, out_imgpath2_2, "wb");
    fwrite(img_output1, 1, size, output_file2_2);
    fclose(output_file2_2);
    //--------------------------zero-padding---------------------------//
    for (int x = 0; x < 9; x++) {
        data[x] = 0;
    }

    
    for (int x = 0; x < 640 + 2; x++) {
        for (int y = 0; y < 427 + 2; y++) {
            if (x == 0) {
                img_input_big[x][y] = 0;
            }
            else if (x == 641) {
                img_input_big[x][y] = 0;
            }
            else if (y == 0) {
                img_input_big[x][y] = 0;
            }
            else if (y == 428) {
                img_input_big[x][y] = 0;
            }
            else {
                img_input_big[x][y] = img_input1[x - 1][y - 1];
            }
        }
    }


    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter1);
        }
    }

    fopen_s(&output_file1_3, out_imgpath1_3, "wb");
    fwrite(img_output1, 1, size, output_file1_3);
    fclose(output_file1_3);

    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter2);
        }
    }
    fopen_s(&output_file2_3, out_imgpath2_3, "wb");
    fwrite(img_output1, 1, size, output_file2_3);
    fclose(output_file2_3);
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
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter1);
        }
    }
    fopen_s(&output_file1_4, out_imgpath1_4, "wb");//out_imgpath1_4
    fwrite(img_output1, 1, size, output_file1_4);
    fclose(output_file1_4);

    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 427; y++) {
            img_output1[x][y] = MY_HW4::convolution(x + 1, y + 1, img_input_big, filter2);
        }
    }

    fopen_s(&output_file2_4, out_imgpath2_4, "wb");
    fwrite(img_output1, 1, size, output_file2_4);
    fclose(output_file2_4);


    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);


}