#include <stdio.h>
#include <stdlib.h>


#define CONTEXTNUM 367
int Width, Height;


void Error(const char *ch){
     printf("%s\n",ch);
     system("PAUSE");
     exit(1);
     }

// void ReadSize(int *Addr){
// Width  = *(Addr);
// Height = *(++Addr);
// }




void HeaderData(unsigned char *Header){
printf("file type:%02x, %02x, %c%c \n",Header[0],Header[1],Header[0],Header[1]);
printf ("file size: 0X%08x bytes(probably wrong)\n", Header[2] |  Header[3] << 8 |  Header[4] << 12|  Header[5] << 16);
printf ("reserved1: %u bytes\n", Header[6] |  Header[7] << 8 );
printf ("reserved2: %u bytes\n", Header[8] |  Header[9] << 8 );
printf ("offset: %u bytes\n", Header[10] |  Header[11] << 8|Header[12] <<12|  Header[13] << 16 );
printf ("Info Header size: %u bytes\n", Header[14] |  Header[15] << 8|Header[16] <<12|  Header[17] << 16 );
printf ("width: %u pixel\n", Header[18] |  Header[19] << 8|Header[20] <<12|  Header[21] << 16 );
printf ("height: %u pixel\n", Header[22] |  Header[23] << 8|Header[24] <<12|  Header[25] << 16 );

    Width  = (Header[18] |  Header[19] << 8|Header[20] <<12|  Header[21] << 16);
    Height = (Header[22] |  Header[23] << 8|Header[24] <<12|  Header[25] << 16 );

    // printf("%u",Width);
    // printf("%u",Height);
};


void InitialContext(int *A, int *B, int *C, int *N){
     
     /***********************************
     *          Context初始化           *   
     ***********************************/
          
     int i;
     for(i=0;i<CONTEXTNUM;i++){
       A[i] = 4;
       B[i] = 0;
       C[i] = 0;
       N[i] = 1;
       }  
     }  

unsigned char ** CreateTwoDimArray(int x,int y){
         
     /***********************************
     *          建立二維陣列                *   
     ***********************************/
         
     int i;
     unsigned char **Array;
     Array = (unsigned char **) calloc((x),sizeof(char *)); 
     if(Array==NULL) Error("Memory Full");
     for(i=0;i<x;i++){
        Array[i] = (unsigned char *) calloc((y),1);
        if(Array[i]==NULL) Error("Memory Full");
        }
     
     return Array;   
     }

void ReadImage(FILE *fp, unsigned char **im){

     /***********************************
     *          讀取影像像素值          *   
     ***********************************/
     
     int i;
     fseek(fp,1078,SEEK_SET);
     for(i=Height-1;i>=0;i--)
        fread(&im[i][0],1,Width,fp);

     for(i=100;i>=0;i--){
      printf("%04x count=%d\n",im[i][0],i);
     }
  
     }  

     

void ReadFile(FILE **rfp, FILE **wfp, char *ReadName, char *WriteName){
    
     /***********************************
     *         讀取、驗證測試影像       *   
     ***********************************/     
     
     unsigned char *Header;
     Header = (unsigned char *) malloc(sizeof(unsigned char)*1078);
     
     if((*rfp = fopen(ReadName,"rb"))==NULL) Error("Image Open Faild!");            
     if((*wfp = fopen(WriteName,"wb"))==NULL)  Error("JPEG_LS Open Faild!");
     fread(Header,1,1078,*rfp);
     HeaderData(Header);
     if(Header[0] != 'B' || Header[1] != 'M')  Error("It's not a BMP");
     
    //  ReadSize((int*)&Header[18]);
     fwrite(Header,1,1078,*wfp);
     free(Header);
     }


int main(){
    FILE *rfp,*wfp;
    int A[367],B[367],C[367],N[367],Nn[2],Q=0; 
    unsigned char **Im,**Om,Ra,Rb,Rc,Rd,Ix,MErrval,PxMED,K;  
    char OrignalName[] = "image0.bmp";              //讀取影像名稱 
    char CompressionName[] = "JPEG_LS0";
    ReadFile(&rfp,&wfp,OrignalName,CompressionName);
    InitialContext(A,B,C,N); 
    Im = CreateTwoDimArray(Height,Width);
    ReadImage(rfp,Im);
    
};