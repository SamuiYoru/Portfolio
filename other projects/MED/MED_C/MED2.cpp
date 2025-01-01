
#define _CRT_SECURE_NO_DEPRECATE
// #include "Header.h"
#include <stdio.h>
#include <iostream>

#include <algorithm>

using namespace std;


int main(){
    //--------------------------�Ѽ�---------------------------//
    int H =512;
    int W = 512;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file;
    FILE* output_file_MED;
    FILE* output_file_error;
    char in_imgpath[] = "C:\\Users\\yuchi\\Downloads\\HM1_images_file\\cat_512.raw";
    char out_imgpath[] = ".\\cat_512_out.raw";
    char out_imgpath_MED[] = ".\\cat_512_out_MED_BW.raw";
    char out_imgpath_error[] = ".\\cat_512_out_error.raw";
    int size = H * W;
    unsigned char* img = new unsigned char[size];
    unsigned char img_input[W][H];
    unsigned char img_output_MED[W][H];
    unsigned char img_output_error[W][H];

    //--------------------------open raw file---------------------------//
    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image!\n");
    }
    fread(img, sizeof(unsigned char), size, input_file);


    //--------------------------�transfer into 2D---------------------------//
        int count = 0;
        for (int x = 0; x < W; x++) {
            for (int y = 0; y < H; y++) {
                img_input[x][y] = img[count];
                count++;
            }
            
        }

    //------------------------padding-----------------------------//
    // for (int x = 0; x < W+2; x++) {
    //     for (int y = 0; y < H+2; y++) {

    //         if(x==0){
    //             img_input_big[x][y] = 0;
    //         }
    //         else if(y==0){
    //             img_input_big[x][y] = img_input_big[x-1][y+1];
    //         }
    //         else if(y==H+1){
    //             img_input_big[x][y] = img_input_big[x][y-1];
    //         }
    //         else if(x==W+1){
    //             img_input_big[x][y] = img_input_big[x-1][y];
    //         }
    //         else{
    //             img_input_big[x][y] = img_input[x - 1][y - 1];            
    //         }
    //     }
    // }

    //------------------------MED-----------------------------//
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char ans_final;

    for (int x = 0; x < W; x++) {
        for (int y = 0; y < H; y++) {
            if(x==0&&y==0){
                a = 0;
                b = 0;
                c = 0;
            }
            if(x==1&&y==0){
                a = 0;
                b = 0;
                c = 0;
            }
            else if(x==0){
                a = img_input[x][y-1];
                b = 0;
                c = 0;
            }
            else if(y==0){
                a = img_input[x-1][y];
                b = img_input[x-1][y];
                c = img_input[x-1][y-1];
            }
            else{
                a = img_input[x][y-1];
                b = img_input[x-1][y];
                c = img_input[x-1][y-1];
            }

            int ai = int(+a);
            int bi = int(+b);
            int ci = int(+c);


            if(ci>=max(ai,bi)){
                ans_final = min(ai,bi);
                // ans_final = 255;
                
            }
            else if(ci<=min(ai,bi)){
                ans_final = max(ai,bi);
                // ans_final = 255;
                
            }
            else{
                ans_final = ai+bi-ci;
                // ans_final = 0;
                
            }
            // ans_final = ans;
            img_output_MED[x][y]=+ans_final;
        }
        
        }
    //--------------------------error image---------------------------//


        for (int x = 0; x < W; x++) {
            for (int y = 0; y < H; y++) {
                // if(img_output_MED[x][y]>=img_input[x][y]){//negative error
                //     img_output_error[x][y]=128+img_input[x][y]-img_output_MED[x][y];
                // }
                // else{//positive error
                //     img_output_error[x][y]=128-img_output_MED[x][y]+img_input[x][y];
                // }
                
                if(img_output_MED[x][y]>=img_input[x][y]){
                    img_output_error[x][y]=img_output_MED[x][y]-img_input[x][y]+128;
                }
                else{
                    img_output_error[x][y]=128-img_output_MED[x][y]+img_input[x][y];
                }
            }
        }

    //--------------------------output---------------------------//

    fopen_s(&output_file,out_imgpath, "wb");
    fwrite(img_input,1,size,output_file);
    fopen_s(&output_file_MED,out_imgpath_MED, "wb");
    fwrite(img_output_MED,1,size,output_file_MED);
    fopen_s(&output_file_error,out_imgpath_error, "wb");
    fwrite(img_output_error,1,size,output_file_error);

    //--------------------------closefile---------------------------//
    delete[] img;

    fclose(input_file);
    fclose(output_file);
    fclose(output_file_MED);
    fclose(output_file_error);
}