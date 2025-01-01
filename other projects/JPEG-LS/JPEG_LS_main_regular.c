/********************************************************
*    JPEG-LS C�y���{���X�����G                          *
*                                                       *
*    JPEG_LS_main.c     ���D�{��                        *
*    JPEG_LS_function.c ���Ƶ{��                        *
*                                                       *
*    �Q�� IMAGENUM �Ѽƨӱ���n���Y�B�����Y���ɮ׼ƶq   *
*    ���ռv���`�@  11 �i�AIMAGE �w�q�� 11               *
*                                                       *
*    ���ۧQ��                                           *
*    Encoder Function ���Y                              *
*    Decoder Function �����Y                            *
*********************************************************/


#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "JPEG_LS_function_regular.c" 

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
    char OrignalName[] = "image0.bmp";              //Ū���v���W�� 
    char CompressionName[] = "JPEG_LS0_regular";            //���Y�ɮצW�� 
    char ReconstructName[] = "Reconstruct0_regular.bmp";    //�����Y�ɮצW�� 
    
    
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
