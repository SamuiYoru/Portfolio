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



#include <stdio.h>
#include <stdlib.h>

#define CONTEXTNUM 367

#ifndef JPEG_LS_HEADER
#define JPEG_LS_HEADER
#define MIN_C -128
#define MAX_C 127 
#define Threshold -1
#endif



int Flag = 0;
int i,j,MODE;
int Width, Height;

unsigned char RUNval=0;
unsigned int RUNcnt=0;

void Error(const char *ch){
     printf("%s\n",ch);
     system("PAUSE");
     exit(1);
     }

void ReadSize(int *Addr){
     Width  = *(Addr);
     Height = *(++Addr);
     }
     
void ReadFile(FILE **rfp, FILE **wfp, char *ReadName, char *WriteName){

     /***********************************
     *         Ū���B���Ҵ��ռv��       *   
     ***********************************/     
     
     unsigned char *Header;
     Header = (unsigned char *) malloc(sizeof(unsigned char)*1078);
     
     if((*rfp = fopen(ReadName,"rb"))==NULL) Error("Image Open Faild!");            
     if((*wfp = fopen(WriteName,"wb"))==NULL)  Error("JPEG_LS Open Faild!");
     fread(Header,1,1078,*rfp);
     if(Header[0] != 'B' || Header[1] != 'M')  Error("It's not a BMP");
     ReadSize((int*)&Header[18]);
     fwrite(Header,1,1078,*wfp);
     free(Header);
     }
     
void InitialContext(int *A, int *B, int *C, int *N){
     
     /***********************************
     *          Context��l��           *   
     ***********************************/
          
     int i;
     for(i=0;i<CONTEXTNUM;i++){
       A[i] = 4;
       B[i] = 0;
       C[i] = 0;
       N[i] = 1;
       }  
     }     
     
void CreatOneArray(unsigned char **Buf){
     *Buf = (unsigned char *) calloc((Width),sizeof(char)); 
     if(*Buf==NULL) Error("Memory Full");
     }     
     
unsigned char ** CreateTwoDimArray(int x,int y){
         
     /***********************************
     *          �إߤG���}�C                *   
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

void CreateArray(unsigned char ***Im, unsigned char ***Om){
     
     /***********************************
     *          �I�s�إ߰}�C���        *   
     ***********************************/
     
     *Im = CreateTwoDimArray(Height,Width);
     *Om = CreateTwoDimArray(Height,Width);
     }
     
void ReadImage(FILE *fp, unsigned char **im){

     /***********************************
     *          Ū���v��������          *   
     ***********************************/
     
     int i;
     fseek(fp,1078L,SEEK_SET);
     for(i=Height-1;i>=0;i--)
        fread(&im[i][0],1,Width,fp);
     }     

void GetSample(int i, int j, unsigned char **Im, unsigned char *Ra, unsigned char *Rb, unsigned char *Rc, unsigned char *Rd, unsigned char *Ix){
     
     /***********************************
     *       ���o���T�P�乳���I         *   
     ***********************************/
     
     if(i==0 && j==0) {     // Pixel(0,0)      First Pixel
        *Ra = 0; *Rb = 0; *Rc = 0; *Rd = 0;
        *Ix = Im[i][j];
        }
     else if(i==0){         // Pixel(0,x)      First Row   
        *Ra = Im[i][j-1]; *Rb = 0; *Rc = 0; *Rd = 0;
        *Ix = Im[i][j];
        }
     else if(i==1 && j==0) {// Pixel(1,0)    
        *Ra = Im[i-1][j]; *Rb = Im[i-1][j]; *Rc = 0; *Rd = Im[i-1][j+1];
        *Ix = Im[i][j];     
        }
     else if(j==0){         // Pixel(x,0)      First Column       
        *Ra = Im[i-1][j]; *Rb = Im[i-1][j]; *Rc = Im[i-2][j]; *Rd = Im[i-1][j+1];
        *Ix = Im[i][j]; 
        }                 
     else if(j==Width-1){   // Pixel(x,Width)  Last  Column
        *Ra = Im[i][j-1]; *Rb = Im[i-1][j]; *Rc = Im[i-1][j-1]; *Rd = Im[i-1][j];
        *Ix = Im[i][j];     
        }
     else {                 // Pixel(x,x)         
        *Ra = Im[i][j-1]; *Rb = Im[i-1][j]; *Rc = Im[i-1][j-1]; *Rd = Im[i-1][j+1];
        *Ix = Im[i][j];     
        }
     }   
           
void ComputeGradient(unsigned char Ra,unsigned char Rb,unsigned char Rc,unsigned char Rd,int *D1,int *D2,int *D3){
    
     /***********************************
     *          ��׭p��                *   
     ***********************************/
       
     *D1 = Rd - Rb;
     *D2 = Rb - Rc;
     *D3 = Rc - Ra;     
     }
     
void MEDPredictor(unsigned char Ra,unsigned char Rb,unsigned char Rc,unsigned char *PxMED){
     
     /***********************************
     *          MED �w��                *   
     ***********************************/
     
     unsigned char max,min;

     max = (Ra>Rb)? Ra:Rb;
     min = (Ra<Rb)? Ra:Rb;
                   
     if(Rc>=max)      *PxMED = min;
     else if(Rc<=min) *PxMED = max;
     else             *PxMED = max + min - Rc;
     }
     


char Quantizer(int x){    

     /***********************************
     *          ��׶q��                *   
     ***********************************/     
     
     if(x>=0){
       if(x==0)                  return 0;  
       else if(x>=1 && x<=2)     return 1;
       else if(x>=3 && x<=6)     return 2;
       else if(x>=7 && x<=20)    return 3;
       else if(x>=21)            return 4;
       }
     
     else{
       if(abs(x)>=1 && abs(x)<=2)          return -1;
       else if(abs(x)>=3 && abs(x)<=6)     return -2;
       else if(abs(x)>=7 && abs(x)<=20)    return -3;
       else if(abs(x)>=21)                 return -4;
       }
            
     }    
    
void ContextDecision(int D1, int D2, int D3, char *SIGN, int *Q){

     /***********************************
     *          Context �M��            *   
     ***********************************/
     
     char Q1,Q2,Q3;
     Q1 = Quantizer(D1);
     Q2 = Quantizer(D2);
     Q3 = Quantizer(D3);
     
     if(Q1<0){  
        Q1 = -Q1;
        Q2 = -Q2;
        Q3 = -Q3;
        *SIGN = -1;
     } else if(Q1==0 && Q2<0) {
        Q2 = -Q2;
        Q3 = -Q3;
        *SIGN = -1;
     } else if(Q1==0 && Q2==0 && Q3<0) {   
        Q3 = -Q3;
        *SIGN = -1;
     } else *SIGN = 1;
        *Q = Q1*81+Q2*9+Q3;
     
     if(i>Threshold) if(Flag) printf("Q1 Q2 Q3 Q : %d %d %d %d\n",Q1,Q2,Q3,*Q);
     }
     

void ErrorCorrection(short *Px, unsigned char PxMED, char SIGN, char C) {
     
     /***********************************
     *          �w�����v                *   
     ***********************************/
          
    *Px = PxMED + SIGN * C;
    //if(*Px >= 255) *Px = 255;   //255 = MAXVAL
    //else if(*Px<0) *Px = 0;
    }

void ModRange(int Errval,char *Errvalmod){
     
     /***********************************
     *          Error Remapping         *   
     ***********************************/
     
     if(Errval < -128)
        *Errvalmod = Errval + 256;
     else if(Errval >= 128)
        *Errvalmod = Errval - 256;
     else 
        *Errvalmod = Errval;   
     }

void ComputeError(int *Errval, unsigned char Ix, short Px,char SIGN){
     
     /***********************************
     *     �~�t�p��A�çP�_�O�_��½��            
     ***********************************/
     
     *Errval = Ix - Px;
     *Errval = (SIGN==1)? *Errval : -(*Errval);
     }
     
void ComputeK(unsigned char *k,int A,int N){
     
     /***********************************
     *        Golomb �Ѽ� K ���p��
     ***********************************/ 
     
     for(*k=0; (N<<(*k))<A;(*k)++);
     }    
     
void ContextUpdate(int *A,int *B,int *C,int *N ,char Errvalmod){
     
     /***********************************
     *          Context ��s            *   
     ***********************************/
     
     
     (*B) += Errvalmod;
     (*A) += abs(Errvalmod);
     if(*N == 64){
        *A >>= 1;
        *B >>= 1;
        *N >>= 1;
        }
     (*N) ++;
     
     if(*B <= (-*N)){
        (*B) += *N;
        if( *C > MIN_C )
           (*C) -= 1;
        if(*B <= (-*N))
           *B = -(*N)+1;
        }
     else if(*B > 0){
        (*B) -= *N;
        if( *C < MAX_C )
           (*C) ++;
        if(*B > 0)
           *B = 0;
        }   
     }       

void TwoToOneSideMappingSpecial(char Errvalmod,unsigned char *MErrval){

     /******************************************** 
     * �s�X�ݯS�� Two Side �� One Side Mapping *   
     *********************************************/           
     
     if(Errvalmod >=0 )
        *MErrval = 2 * Errvalmod + 1;
     else
        *MErrval = -2 * (Errvalmod + 1);
     }       
     
void TwoToOneSideMapping(char Errvalmod,unsigned char *MErrval){
     
     /**************************************** 
     * �s�X�ݤ� Two Side �� One Side Mapping *   
     *****************************************/             

     if(Errvalmod >=0 )
        *MErrval = 2*Errvalmod;
     else
        *MErrval = -2*Errvalmod -1;
     }   
     
     
void AppendToBitStream(FILE *write ,unsigned char bit,unsigned char Initial){

     /**************************************** 
     *            �g�J�� Bitstream           *   
     *****************************************/ 
     
     static unsigned char buffer=0, bits_to_go=8;     
     
     if(Initial==255){
       buffer = 0;
       bits_to_go = 8;
       return ;
       }
     
     if(bit!=255){
        buffer <<= 1;
        if (bit){
           buffer |= 0x01;
           }
        bits_to_go -= 1;
        // total_bits += 1;
        if (bits_to_go==0)  {
           putc (buffer, write);
           bits_to_go = 8;
           }
        }
     else if(bit==255){
        if(bits_to_go<8){
           for(;bits_to_go>0;bits_to_go--)
              buffer <<= 1;
           putc (buffer, write);
           }
        }    
     }

void ShowCode(FILE *wf,unsigned char Q,unsigned char R,unsigned short m,unsigned char k){


     /**************************************** 
     * �s�X�� �N�ӼƻP�l�Ƽg�J�� Bitstream   *   
     *****************************************/   
    
     unsigned char d;    
     for(;Q>0;Q--) { AppendToBitStream(wf,0,0); 
     }
     AppendToBitStream(wf,1,0);  
     for(d=m>>1;k>0;k--,d>>=1){
        if((R-d) >= 0){
           AppendToBitStream(wf,1,0); 
           R-=d;
           }
        else{ AppendToBitStream(wf,0,0); 
        }
        } 
     }
     
     
void GolombEncode(FILE *wf,unsigned char MErrval,unsigned char k){
     
     /******************************************************  
     *        �s�X�ݤ� Golomb Encoder                      *
     * ���b���p��X�ӼƻP�l�ơA�åB�P�_�ӼƬO�_�j�󵥩� 23 *
     ******************************************************/   
         

     
     unsigned short m = pow(2,k);
     unsigned char Quotient = MErrval >> k,
                   Remainder = MErrval % m;
     int i=0;
     
     if(Quotient >= 23){
        Quotient = 23;
        Remainder = MErrval;
        k=8;
        m = 256;
        }   

     ShowCode(wf,Quotient,Remainder,m,k);
     
     }

void RegularEncode(FILE *wf,unsigned char MErrval,unsigned char k){
     GolombEncode(wf,MErrval,k);     
     }
     
void ModeDecesion(unsigned char Ra, unsigned char Rb, unsigned char Rc, unsigned char Rd){
     
     /**************************************** 
     *           �s�X�Ҧ��M��                *   
     *****************************************/     
     
     if((Ra==Rb) && (Rc==Rd) && (Rb==Rc)) MODE = 1;
     else MODE = 0;
     }

void RunScanning(unsigned char **Im, unsigned char Ra){     
     
     /**************************************** 
     *        �s�X�ݤ� Run Scanning          *   
     *****************************************/ 
     
     RUNval = Ra;
     RUNcnt = 0;
     while(RUNval==Im[i][j] && j<Width){
        j++;
        RUNcnt++;
        }  
      
     } 

void RunLengthCoding(FILE *wf,unsigned char Initial){

     /**************************************** 
     *      �s�X�ݤ� Run Length Coding       *   
     *****************************************/ 
     
     static const unsigned char J[32] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,5,5,6,6,7,7,8,9,10,11,12,13,14,15};     
     static unsigned char RUNindex=0;
     unsigned int num=0;
     unsigned int index;
     
     if(Initial==255){
        RUNindex = 0;
        RUNval = 0;
        RUNcnt = 0;
        return ;
        }
     num = 0x01<<J[RUNindex];      
     while(RUNcnt>=num){
        RUNcnt -= num;
        AppendToBitStream(wf,1,0);
        if(RUNindex<31) RUNindex++;       
        num = (0x01<<J[RUNindex]);   
        }
        
     if(j!=Width){
        AppendToBitStream(wf,0,0);              
        index = 0x01 << J[RUNindex];
        index >>= 1;
        while(index>0){
           if(RUNcnt >= index){
              AppendToBitStream(wf,1,0); 
              RUNcnt -= index;
              }
           else 
              AppendToBitStream(wf,0,0); 
           index >>=1;
           }
        if(RUNindex > 0)  RUNindex = RUNindex - 1;   
                         
     } else if(RUNcnt>0) {
        AppendToBitStream(wf,1,0);
        }
     RUNcnt = 0;
     }
 
void RunInterrupt(FILE *wfp, unsigned char ** Im, int *A, int *N){

     /**************************************** 
     *      �s�X�ݤ� Run Interrupt           *   
     *****************************************/
     
     unsigned char RItype = 0;
     unsigned char Ra,Rb,Rc,Rd,Ix,Px,MErrval,K;
     short Errval;
     char Errvalmod,SIGN,map;
     int TEMP,Q;
     
     GetSample(i,j,Im,&Ra,&Rb,&Rc,&Rd,&Ix);
     RItype = (Ra==Rb)? 1 : 0;
     Px = (RItype==1)? Ra : Rb;
     Errval = Ix - Px;
     if((RItype==0) && (Ra>Rb)){
        Errval = -Errval;
        SIGN = -1;
     } else SIGN = 1;
     ModRange(Errval,&Errvalmod);
     Q = RItype + 365;
     TEMP = (RItype)? A[366]+(N[366]>>1) : A[365];
     ComputeK(&K,TEMP,N[Q]);
     TwoToOneSideMapping(Errvalmod,&MErrval);
     RegularEncode(wfp,MErrval,K);     
     
     A[Q] += ((MErrval + 1 - RItype) >> 1);
     if(N[Q] == 64){
             A[Q] <<= 1;
             N[Q] <<= 1;
             }
     N[Q]++;
     
     }     

unsigned char input_bit (FILE *fp,unsigned char Initial)
{

     /**************************************** 
     *      �ѽX�ݤ� Bitstream ��J          *   
     *****************************************/

  static unsigned char bits_to_go=0,buffer=0,t;
  
  if(Initial==255){
     bits_to_go = 0;
     buffer = 0;
     t = 0;
     return ;
     }
  
  if (bits_to_go==0)  {
    buffer = getc(fp);
    bits_to_go = 8;
  }
  t = buffer&0x80;
  buffer <<= 1;
  bits_to_go -= 1;
  return t>>=7;
}

    
void DecodeGolomb(FILE *rfp,unsigned char k,unsigned char *EMErrval){
     
     /**************************************** 
     *      �ѽX�ݤ� Golomb Decoder          *   
     *****************************************/
     
     unsigned char num=0,Q=0,R=0,Errval;
     while(input_bit(rfp,0)==0)  Q++;
     if(Q==23) {
        k=8;
        Q=0;
        }
     for(;num<k;num++){
        R<<=1;
        R+=input_bit(rfp,0);
        }
     Errval = (Q<<k)+R;
     *EMErrval = (Q<<k)+R;
     
     }      

void DeErrorMappingSpecial(char *Errvalmod,unsigned char MErrval){
     
     /******************************************** 
     *   �ѽX�ݯS�� One Side �P Two Side �٭�  *   
     *********************************************/
          
     if(MErrval %2 == 0 )
        *Errvalmod = (-(MErrval>>1))-1;
     else
        *Errvalmod = (MErrval - 1)>>1;
     }  


void DeErrorMapping(char *Errvalmod,unsigned char MErrval){
     
     /**************************************** 
     *   �ѽX�ݤ� One Side �P Two Side �٭�  *   
     *****************************************/

     if(MErrval %2 == 0 )
        *Errvalmod = MErrval>>1;
     else
        *Errvalmod = -(MErrval+1)>>1;
     }  


void DeModRange(unsigned char *Ix,int Errval){

     /**************************************** 
     *     �ѽX�ݤ� Error Remapping �٭�     *   
     *****************************************/

     if(Errval < 0)
        *Ix = Errval + 256;
     else if(Errval >= 256)
        *Ix = Errval - 256;
     else 
        *Ix = (unsigned char)Errval;   
     }      

void RunLengthDecoding(FILE *rfp,unsigned char **Im,unsigned char Initial){

     /**************************************** 
     *       �ѽX�ݤ� RunLength �ѽX         *   
     *****************************************/
     
     static const unsigned char J[32] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,5,5,6,6,7,7,8,9,10,11,12,13,14,15};     
     static unsigned char RUNindex=0;
     unsigned char Ra,Rb,Rc,Rd,Ix;
     unsigned int num=0;
     unsigned int index;
     
     if(Initial==255){
         RUNindex = 0;
         RUNval = 0;
         RUNcnt = 0; 
         return;
         }
     GetSample(i,j,Im,&Ra,&Rb,&Rc,&Rd,&Ix);
     
     while(input_bit(rfp,0)!=0){
        for(index=0;index<0x01<<J[RUNindex];index++){
           Im[i][j] = Ra;
           j++;
           if(j==(Width)){ 
              if(index==((0x01<<J[RUNindex])-1)) RUNindex++;
              return; 
              }
           }
        if(RUNindex<31) RUNindex++;   
        }   
     
   
     index = J[RUNindex];

     num = 0;
     while(index>0){
        num <<= 1;
        num |= input_bit(rfp,0);
        index --;
        }            
        
     index=0;
     if(index<num){  
        for(;index<num;index++){
           Im[i][j] = Ra;
           if(j<(Width-1)) j++;
           }
        }
     if(RUNindex > 0)  RUNindex = RUNindex - 1;  
     }
 

void DeRunInterrupt(FILE *rfp,unsigned char **Im,int *A,int *N){

     /**************************************** 
     *      �ѽX�ݤ� RunInterrupt �ѽX       *   
     *****************************************/     

     unsigned char RItype = 0;
     unsigned char Ra,Rb,Rc,Rd,Ix,Px,MErrval,K;
     short Errval;
     char Errvalmod,SIGN,map;
     int TEMP,Q;
     GetSample(i,j,Im,&Ra,&Rb,&Rc,&Rd,&Ix);
     RItype = (Ra==Rb)? 1 : 0;
     Px = (RItype==1)? Ra : Rb;
     
     Q = RItype + 365;
     TEMP = (RItype)? A[366]+(N[366]>>1) : A[365];
     ComputeK(&K,TEMP,N[Q]);
     DecodeGolomb(rfp,K,&MErrval);
     DeErrorMapping(&Errvalmod,MErrval);
     
      if((RItype==0) && (Ra>Rb)){
        Errvalmod = -Errvalmod;
        SIGN = -1;
     } else SIGN = 1;
     
     
     Errval = Errvalmod + Px;      
     DeModRange(&Ix,Errval);      
     Im[i][j] = Ix;
      
     
     A[Q] += ((MErrval + 1 - RItype) >> 1);
     if(N[Q] == 64){
             A[Q] <<= 1;
             N[Q] <<= 1;
             }
     N[Q]++;
     
     }


void Encoder(char *ReadName, char*WriteName){
     
     /**************************************** 
     *         Encoder Function �s�X�Ƶ{������ 
     *     
     *    �s�X�y�{ �G 
     *    ���o���T�P�乳���I >> �P�_�s�X�Ҧ� (Regular or Run Mode) 
     * 
     *         Regular Mode : �p���� >> �M�wContext >> MED�w�� >> ���v�w���� >> 
     *                        �~�t�p�� >> Error Remapping >> One Side Mapping >> 
     *                        �p�� Golomb Code �Ѽ� K >> Golomb Encoder >> Context ��s 
     * 
     *         Run Mode : �p��B�s�X�ۦP�����I���ƶq >> �P�_�O�_�� RunInterrupt 
     *****************************************/      

    printf("JPEG-LS Encode Start\n");
    FILE *rfp,*wfp;
    int D1,D2,D3,Errval;
    char SIGN=0,Errvalmod;
    int A[367],B[367],C[367],N[367],Nn[2],Q=0;    
    unsigned char **Im,**Om,Ra,Rb,Rc,Rd,Ix,MErrval,PxMED,K;
    short Px;
    unsigned char MaxK = 0;
    
    ReadFile(&rfp,&wfp,ReadName,WriteName);  //Ū���B���Ҵ��ռv���O�_�� BMP �ɮ� 
    InitialContext(A,B,C,N);                 //Context ��l��  
    Im = CreateTwoDimArray(Height,Width);    //�إߤG���}�C 
    ReadImage(rfp,Im);                       //Ū�����ռv���������� 
   
    AppendToBitStream(wfp,0,255);            //AppendToBitstream ��ƪ�l�� 
    RunLengthCoding(wfp,255);                //RunLengthCoding ��ƪ�l�� 
    
    MODE = 0;

    for(i=0;i<Height;i++){
       for(j=0;j<Width;j++){
          GetSample(i,j,Im,&Ra,&Rb,&Rc,&Rd,&Ix);               
          ModeDecesion(Ra,Rb,Rc,Rd);                           
          if(MODE==0|MODE==1){      
             //  MODE == 0 : Regular Mode 
             ComputeGradient(Ra,Rb,Rc,Rd,&D1,&D2,&D3);
             ContextDecision(D1,D2,D3,&SIGN,&Q); 
             MEDPredictor(Ra,Rb,Rc,&PxMED);
             ErrorCorrection(&Px,PxMED,SIGN,C[Q]);
             ComputeError(&Errval,Ix,Px,SIGN);
             ModRange(Errval,&Errvalmod);
             ComputeK(&K,A[Q],N[Q]);
             
             if ( (K==0) && ((2*B[Q]) <= (-N[Q])) )
               TwoToOneSideMappingSpecial(Errvalmod,&MErrval);
             else 
               TwoToOneSideMapping(Errvalmod,&MErrval);
             
             RegularEncode(wfp,MErrval,K);
             ContextUpdate(&A[Q],&B[Q],&C[Q],&N[Q],Errvalmod);

          } 
         //  else if(MODE==1){
         //     //  MODE == 1 : Run Mode
         //     RunScanning(Im,Ra);
         //     RunLengthCoding(wfp,0);
         //     if(j<=(Width-1))
         //        RunInterrupt(wfp,Im,A,N);
         //     }
          }
       }
    AppendToBitStream(wfp,255,0);

    fclose(rfp);
    fclose(wfp);    
    printf("JPEG-LS Encode End\n");
    }
    
  
void Decoder(char *ReadName, char*WriteName){

     /**************************************** 
     *   Encoder Function �ѽX�Ƶ{������ 
     *     
     *    �ѽX�y�{ �G 
     *    ���o���T�P�乳���I >> �P�_�s�X�Ҧ� (Regular or Run Mode) 
     * 
     *         Regular Mode : �p���� >> �M�wContext >> MED�w�� >> ���v�w���� >>
     *                        �p�� Golomb Code �Ѽ� K >> Golomb Decoder >> One Side Mapping �٭� 
     *                        Error Remapping �٭� >> Context ��s >> �٭칳���� 
     * 
     *         Run Mode : �ѽX�ۦP�����I���ƶq >> �P�_�O�_�� DeRunInterrupt 
     **************************************/  
    
    printf("JPEG-LS Decode Start\n");
    
    FILE *rfp,*wfp;
    unsigned char **Im,**Om;
    char SIGN=0,Errvalmod;
    int A[367],B[367],C[367],N[367],Q; 
    int D1,D2,D3,Errval;
    unsigned char Ra,Rb,Rc,Rd,Ix,PxMED,MErrval,K;
    short Px;  
    
    input_bit(rfp,255); //Initial
    RunLengthDecoding(rfp,Im,255); //Initial
 
    ReadFile(&rfp,&wfp,ReadName,WriteName);
    InitialContext(A,B,C,N);
    
    Im = CreateTwoDimArray(Height,Width);
    for(i=0;i<Height;i++){
       for(j=0;j<Width;j++){
          GetSample(i,j,Im,&Ra,&Rb,&Rc,&Rd,&Ix);
          ModeDecesion(Ra,Rb,Rc,Rd);
          if(MODE==0|MODE==1){        
             //  MODE == 0 : Regular Mode 
             ComputeGradient(Ra,Rb,Rc,Rd,&D1,&D2,&D3);
             ContextDecision(D1,D2,D3,&SIGN,&Q); 
             MEDPredictor(Ra,Rb,Rc,&PxMED);   
             ErrorCorrection(&Px,PxMED,SIGN,C[Q]);         
             ComputeK(&K,A[Q],N[Q]);
             DecodeGolomb(rfp,K,&MErrval);
             
             if ( (K==0) && ((2*B[Q]) <= (-N[Q])) )
                DeErrorMappingSpecial(&Errvalmod,MErrval);
             else 
                DeErrorMapping(&Errvalmod,MErrval);
                             
             ContextUpdate(&A[Q],&B[Q],&C[Q],&N[Q],Errvalmod);
             if(SIGN == -1)  Errvalmod = - Errvalmod;
             Errval = Errvalmod + Px;    
             DeModRange(&Ix,Errval);           
             Im[i][j] = Ix;
          } 
         //  else if(MODE==1){
         //     //  MODE == 1 : Run Mode
         //     RunLengthDecoding(rfp,Im,0);
         //     if(j<=(Width-1))
         //        DeRunInterrupt(rfp,Im,A,N);
         //     }                
          }        
       }

       
    for(i=Height-1;i>=0;i--)
       fwrite(&Im[i][0],1,Width,wfp); 
 
    fclose(rfp);
    fclose(wfp);
    
    printf("JPEG-LS Decode End\n\n");
    } 
