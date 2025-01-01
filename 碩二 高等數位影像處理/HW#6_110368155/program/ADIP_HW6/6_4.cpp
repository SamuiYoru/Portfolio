/************************************************
* Filename    : 6_4.cpp                         *
* Update date : 3/12/2022                       *
* Author      : 顏郁芩                          *
* Note        : Road map                        *
************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;


void dilation_MAP(unsigned char img[512 + 4][512 + 4], unsigned char SE[25], unsigned char output[512][512],string label) {
    unsigned char data[25];
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            int posx = x + 2;
            int posy = y + 2;
            data[0] = img[posx - 2][posy - 2];
            data[1] = img[posx - 2][posy - 1];
            data[2] = img[posx - 2][posy];
            data[3] = img[posx - 2][posy + 1];
            data[4] = img[posx - 2][posy + 2];

            data[5] = img[posx - 1][posy - 2];
            data[6] = img[posx - 1][posy - 1];
            data[7] = img[posx - 1][posy];
            data[8] = img[posx - 1][posy + 1];
            data[9] = img[posx - 1][posy + 2];

            data[10] = img[posx][posy - 2];
            data[11] = img[posx][posy - 1];
            data[12] = img[posx][posy];
            data[13] = img[posx][posy + 1];
            data[14] = img[posx][posy + 2];

            data[15] = img[posx + 1][posy - 2];
            data[16] = img[posx + 1][posy - 1];
            data[17] = img[posx + 1][posy];
            data[18] = img[posx + 1][posy + 1];
            data[19] = img[posx + 1][posy + 2];

            data[20] = img[posx + 2][posy - 2];
            data[21] = img[posx + 2][posy - 1];
            data[22] = img[posx + 2][posy];
            data[23] = img[posx + 2][posy + 1];
            data[24] = img[posx + 2][posy + 2];

            if (label == "dilation") {
                int flag = 0;//要改條件
                for (int i = 0; i < 25; i++) {
                    if (SE[i] == 1 && data[i] > 250) {
                        flag = flag + 1;
                    }
                    //output[x][y] = min(data, 25, SE);
                }
                //output[x][y] = img[posx][posy];

                if (flag == 0) {
                    output[x][y] = 0;
                }
                else {
                    output[x][y] = 255;
                }
            }
            else if (label == "erotion") {
                int flag = 0;//要改條件
                for (int i = 0; i < 25; i++) {
                    if (SE[i] == 1 && data[i] <10) {
                        flag = flag + 1;
                    }
                    //output[x][y] = min(data, 25, SE);
                }


                if (flag == 0) {
                    output[x][y] = 255;
                }
                else {
                    output[x][y] = 0;
                }




            }



        }
    }
}


void bigger_512(unsigned char img2D[512][512], unsigned char imgBIG[512 + 4][512 + 4], unsigned char val) {
    for (int x = 0; x < 512 + 4; x++) {
        for (int y = 0; y < 512 + 4; y++) {
            if (val == 255 || val == 0) {
                if (x < 2 || x>514) {
                    imgBIG[x][y] = val;
                }
                else if (y < 2 || y>514) {
                    imgBIG[x][y] = val;
                }
                else {
                    imgBIG[x][y] = img2D[x - 2][y - 2];
                }
            }
            else {
                if (x < 2 ) {
                    imgBIG[x][y] = img2D[0][y];
                }
                else if (x>514) {
                    imgBIG[x][y] = img2D[511][y];
                }
                else if (y < 2) {
                    imgBIG[x][y] = img2D[x][0];
                }
                else if (y > 514) {
                    imgBIG[x][y] = img2D[x][511];
                }
                else {
                    imgBIG[x][y] = img2D[x - 2][y - 2];
                }
            }

        }
    }

}


void find(int a, int b, int c) {
    cout << "find" << endl;
    cout << "a="<<a << endl;
    if (a == 0) {
        b = -1;
        c = -1;
    }
    else if (a == 1) {
        b = -1;
        c = 0;
    }
    else if (a == 2) {
        b = -1;
        c = 1;
    }
    else if (a == 3) {
        b = 0;
        c = -1;
    }
    else if (a == 4) {
        b = 0;
        c = 0;
    }
    else if (a == 5) {
        b = 0;
        c = +1;
    }
    else if (a == 6) {
        b = 1;
        c = -1;
    }
    else if (a == 7) {
        b = 1;
        c = 0;
    }
    else if (a == 8) {
        b = 1;
        c = 1;
    }

}

void MY_HW6::HW6_4() {
    //--------------------------參數---------------------------//
    int H = 512;
    int W = 512;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file;
    char in_imgpath[] = ".\\HW6_image_files\\map_512.raw";
    char out_imgpath[] = ".\\map_512_after.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char img_out[512][512];
    unsigned char imgBIG[512+4][512+4];
    unsigned char img2D[512][512];


    unsigned char SE[25] = { 1,0,0,0,1,
                              0,1,1,1,0,
                              0,1,1,1,0,
                              0,1,1,1,0,
                              1,0,0,0,1 };


    unsigned char SE2[25] = { 0,0,0,0,0,
                              0,1,1,1,0,
                              0,1,1,1,0,
                              0,1,1,1,0,
                              0,0,0,0,0 };
    //--------------------------開啟、讀取檔案---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image map_512.raw!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);

    //------------------處理 -----------------------//
    int c = 0;
    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            img2D[x][y] = img[c];
            c++;
        }
    }


    bigger_512(img2D, imgBIG,128);


    dilation_MAP(imgBIG, SE2, img_out, "dilation");

    fopen_s(&output_file, "map_512_after1.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);


    bigger_512(img_out, imgBIG,128);
    dilation_MAP(imgBIG, SE2, img_out, "dilation");

    fopen_s(&output_file, "map_512_after2.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);

    bigger_512(img_out, imgBIG, 128);
    dilation_MAP(imgBIG, SE2, img_out, "dilation");

    fopen_s(&output_file, "map_512_after3.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);

    bigger_512(img_out, imgBIG, 128);
    dilation_MAP(imgBIG, SE, img_out, "erotion");

    fopen_s(&output_file, "map_512_after4.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);

    bigger_512(img_out, imgBIG, 255);
    dilation_MAP(imgBIG, SE, img_out, "erotion");

    fopen_s(&output_file, "map_512_after5.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);




    //--計算距離------------------//
    unsigned char d[9];
    int posx = 203;
    int posy = 120;
    img_out[posx][posy] = 128;
    int arrange[4];
    int a = 0;
    int b =0;
    int step = 0;
    for (int i = 0; i < 120; i++) {//(123,162)
        d[0] = img_out[posx-1][posy-1];
        d[1] = img_out[posx-1][posy];
        d[2] = img_out[posx-1][posy+1];

        d[3] = img_out[posx][posy-1];
        d[4] = img_out[posx][posy];
        d[5] = img_out[posx][posy+1];

        d[6] = img_out[posx+1][posy-1];
        d[7] = img_out[posx+1][posy];
        d[8] = img_out[posx+1][posy+1];
        for (int j = 0; j < 9; j++) {
            //cout << +d[j] << endl;
        }


        if (posx == 123 ) {//&& 
            if (posy == 162) {
                posx = posx;
                posy = posy;
            }
            else if (d[5] == 255) {
                posx = posx;
                posy = posy + 1;
            }
            else if (d[2] == 255) {
                posx = posx;
                posy = posy + 1;
            }
            else if (d[8] == 255) {
                posx = posx +1;
                posy = posy+1;
            }

            else {
                posx = posx;
                posy = posy;
            }
        }
        else {
            if (d[2] == 255) {
                posx = posx-1 ;
                posy = posy +1;
            }
            else if (d[5] == 255) {
                posx = posx;
                posy = posy+1;
            }
            else if (d[1] == 255) {
                posx = posx -1;
                posy = posy ;
            }

            else {
                posx = posx;
                posy = posy;
            }
        }
        if (img_out[posx][posy] != 128) {
            step = step + 1;
            img_out[posx][posy] = 128;
        }
    }
     
    for (int i = 0; i < 350; i++) {//,(160,509)

        d[0] = img_out[posx - 1][posy - 1];
        d[1] = img_out[posx - 1][posy];
        d[2] = img_out[posx - 1][posy + 1];

        d[3] = img_out[posx][posy - 1];
        d[4] = img_out[posx][posy];
        d[5] = img_out[posx][posy + 1];

        d[6] = img_out[posx + 1][posy - 1];
        d[7] = img_out[posx + 1][posy];
        d[8] = img_out[posx + 1][posy + 1];


        if (posx == 160 ) {//&& 
            if (posy == 509) {
                posx = posx;
                posy = posy;
            }

            else if (509 - posy > 0) {
                if (d[5] == 255) {
                    posx = posx + 1;
                    posy = posy;
                }
                else {
                    posx = posx;
                    posy = posy;
                }
            }


            else if (509 - posy < 0) {
                if (d[3] == 255) {
                    posx = posx ;
                    posy = posy-1;
                }
                else {
                    posx = posx;
                    posy = posy;
                }
            }
        }
        else if(posx != 160) {

            if (d[8] == 255) {
                posx = posx + 1;
                posy = posy + 1;
            }
            else if (d[5] == 255) {
                posx = posx;
                posy = posy + 1;
            }
            else if (d[7] == 255) {
                posx = posx+1;
                posy = posy;
            }

            else {
                posx = posx;
                posy = posy;
            }
        }
        if (img_out[posx][posy] != 128) {
            step = step + 1;
            img_out[posx][posy] = 128;
        }
    }


    for (int i = 0; i < 500; i++) {//(503,403)

        d[0] = img_out[posx - 1][posy - 1];
        d[1] = img_out[posx - 1][posy];
        d[2] = img_out[posx - 1][posy + 1];

        d[3] = img_out[posx][posy - 1];
        d[4] = img_out[posx][posy];
        d[5] = img_out[posx][posy + 1];

        d[6] = img_out[posx + 1][posy - 1];
        d[7] = img_out[posx + 1][posy];
        d[8] = img_out[posx + 1][posy + 1];

        if (posy == 403) {//&& posx == 503
            if (posx == 503) {
                posx = posx;
                posy = posy;
                //cout << "GOAL" << endl;
                //cout << "count=" << step << endl;
            }
            else if (503 - posx > 0) {
                if (d[7] == 255) {
                    posx = posx+1;
                    posy = posy;
                }
                else {
                    posx = posx;
                    posy = posy;
                }
            }
            else if (503 - posx < 0) {
                if (d[1] == 255) {
                    posx = posx-1;
                    posy = posy;
                }
                else {
                    posx = posx;
                    posy = posy;
                }
            }
        }
        else {
            if (d[6] == 255) {
                posx = posx + 1;
                posy = posy-1;
            }
            else if (d[7] == 255) {
                posx = posx+1;
                posy = posy;
            }
            else if (d[3] == 255) {
                posx = posx;
                posy = posy-1;
            }
            else if (d[8] == 255) {
                posx = posx+1;
                posy = posy + 1;
            }


            else {
                posx = posx;
                posy = posy;
            }
        }
        if (img_out[posx][posy] != 128) {
            step = step + 1;
            img_out[posx][posy] = 128;
        }
    }
    
   
    //------------------儲存檔案-----------------------//
    cout << "count=" << step << endl;
    fopen_s(&output_file, "map_512_after_road.raw", "wb");
    fwrite(img_out, 1, size, output_file);
    fclose(output_file);


    //--------------------------釋出記憶體---------------------------//
    delete[] img;
    fclose(input_file);

}