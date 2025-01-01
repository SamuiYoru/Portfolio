
#define _CRT_SECURE_NO_DEPRECATE
// #include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
#include <algorithm>


int main(){
    //--------------------------�Ѽ�---------------------------//
    int H =237;
    int W = 613;
    //unsigned char img[256 * 256];
    FILE* input_file;
    FILE* output_file;
    FILE* output_file_big;
    FILE* output_file_MED;
    FILE* output_file_error;
    char in_imgpath[] = "C:\\Users\\yuchi\\Downloads\\HM1_images_file\\check_613x237.raw";
    char out_imgpath[] = ".\\check_613x237_out.raw";
    char out_imgpath_big[] = ".\\check_613x237_out_padding.raw";
    char out_imgpath_MED[] = ".\\check_613x237_out_MED.raw";
    char out_imgpath_error[] = ".\\check_613x237_out_error.raw";
    int size = H * W;
    int size2=(W+2)*(H+2);
    unsigned char* img = new unsigned char[size];
    unsigned char img_input[W][H];
    unsigned char img_input_big[W+2][H+2];//[直][橫]
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
    for (int x = 0; x < W+2; x++) {
        for (int y = 0; y < H+2; y++) {

            if(x==0){
                img_input_big[x][y] = 0;
            }
            else if(y==0){
                img_input_big[x][y] = img_input_big[x-1][y+1];
            }
            else if(y==H+1){
                img_input_big[x][y] = img_input_big[x][y-1];
            }
            else if(x==W+1){
                img_input_big[x][y] = img_input_big[x-1][y];
            }
            else{
                img_input_big[x][y] = img_input[x - 1][y - 1];            
            }
        }
    }

    //------------------------MED-----------------------------//
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char ans_final;

    for (int x = 0; x < W+2; x++) {
        for (int y = 0; y < H+2; y++) {
            if((x>0 && x<=W)&&(y>0&&y<=H)){
                if((x>1 && x<=W-2)&&(y>1&&y<=H-2)){
                a = img_input_big[x][y-1];
                b = img_input_big[x-1][y+1];
                c = img_input_big[x-1][y-1];
                
                }
                else{
                a = img_input_big[x][y-1];
                b = img_input_big[x-1][y+1];
                c = img_input_big[x-1][y-1];

                }

                int ai = int(+a);
                int bi = int(+b);
                int ci = int(+c);


                if(ci>=max(ai,bi)){
                    ans_final = min(ai,bi);
                    
                }
                else if(ci<=min(ai,bi)){
                    ans_final = max(ai,bi);
                   
                }
                else{
                    ans_final = ai+bi-ci;
                   
                }
                // ans_final = ans;
                img_output_MED[x-1][y-1]=+ans_final;
                // img_output_MED[x-1][y-1]=+ans_final;
                // cout<<+ans_final<<endl;
                // cout<<+a<<" "<<+b<<" "<<+c<<" "<<+ans_final<<endl;
            }
            else{
                // cout<<x<<" "<<y<<" "<<"else"<<endl;
            }
            
        }
        
        }
    //--------------------------error image---------------------------//


        for (int x = 0; x < W; x++) {
            for (int y = 0; y < H; y++) {
                img_output_error[x][y]=img_output_MED[x][y]-img_input[x][y];
            }
        }

    //--------------------------output---------------------------//

    fopen_s(&output_file,out_imgpath, "wb");
    fwrite(img_input,1,size,output_file);
    fopen_s(&output_file_big,out_imgpath_big, "wb");
    fwrite(img_input_big,1,size2,output_file_big);
    fopen_s(&output_file_MED,out_imgpath_MED, "wb");
    fwrite(img_output_MED,1,size,output_file_MED);
    fopen_s(&output_file_error,out_imgpath_error, "wb");
    fwrite(img_output_error,1,size,output_file_error);

    //--------------------------closefile---------------------------//
    delete[] img;
    // delete[] img_input_big;
    fclose(input_file);
    fclose(output_file);
    fclose(output_file_big);
    fclose(output_file_MED);
    fclose(output_file_error);
}