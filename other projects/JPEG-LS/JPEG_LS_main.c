/********************************************************
*    JPEG-LS C語言程式碼說明：                          *
*                                                       *
*    JPEG_LS_main.c     為主程式                        *
*    JPEG_LS_function.c 為副程式                        *
*                                                       *
*    利用 IMAGENUM 參數來控制要壓縮、解壓縮的檔案數量   *
*    測試影像總共  11 張，IMAGE 定義成 11               *
*                                                       *
*    接著利用                                           *
*    Encoder Function 壓縮                              *
*    Decoder Function 解壓縮                            *
*********************************************************/


#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "JPEG_LS_function.c" 

#define IMAGENUM 10 

#ifndef JPEG_LS_HEADER
#define JPEG_LS_HEADER
#define MIN_C -128
#define MAX_C 127 
#define Threshold -1
#endif

extern int Flag;
extern int i,j,MODE;
extern int Width, Height;
extern int *A,*B,*C,*N;

extern unsigned char RUNval;
extern unsigned int RUNcnt;


int main(){
    int i=0;
    char OrignalName[] = "image0.bmp";              //讀取影像名稱 
    char CompressionName[] = "JPEG_LS0";            //壓縮檔案名稱 
    char ReconstructName[] = "Reconstruct0.bmp";    //解壓縮檔案名稱 
    
    
    for(i=0;i<IMAGENUM;i++){
       printf("No. %d Image\n",i);
       Encoder(OrignalName,CompressionName);
       Decoder(CompressionName,ReconstructName);
       
       OrignalName[5]++;
       CompressionName[7]++;
       ReconstructName[11]++;
       }
    
           
    system("PAUSE");
    return 0;
}
