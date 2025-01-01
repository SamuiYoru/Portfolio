/***********************************************
* Filename    : functions.cpp                  *
* Update date : /11/2022                       *
* Author      : 顏郁芩                         *
* Note        : function of homework5          *
***********************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include <complex>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS
#define intsize sizeof(int)
#define complexsize sizeof(complex)
#define PI 3.1415926

//using namespace std;
using namespace W;

typedef struct {
	float real;
	float im;
}complex;

complex** A, ** A_In, **F;

complex Add(complex, complex);
complex Sub(complex, complex);
complex Mul(complex, complex);

int* a, * b;
int nLen, init_nLen, mLen, init_mLen, N, M;
FILE* dataFile;

int calculate_M(int);
void reverse(int, int);
void readData();
void fft(int, int);
void printResult();


/*void DFT_128(unsigned char  input[128], complex output[128]) {
	double power = (2 * PI) / 128;
	double powerv = -(2 * PI) / 128;
	complex SUMadd{ 0,0 };
	complex point[128];
	for (int n = 0; n < 128; n++) {
		for (int x = 0; x < 128; x++) {
			point[x].real = cos(x * n * power) * input[x];
			point[x].im = -sin(x * n * power) * input[x];

			SUMadd.real = SUMadd.real + point[x].real;
			SUMadd.im = SUMadd.im + point[x].im;
		}
		output[n].real = SUMadd.real;
		output[n].im = SUMadd.im;
	}
}
void DFT_calculate128(complex input[128], unsigned char  ans[128]) {
	for (int i = 0; i < 128; i++)
	{
		ans[i] = sqrt(input[i].real * input[i].real + input[i].im * input[i].im);
	}
}*/

void DFTcore128(complex  input[128], complex output[128]) {
	double power = (-2 * PI) / 128;
	complex SUMadd{ 0,0 };
	complex point[128];

	for (int x = 0; x < 128; x++) {//歸零
		point[x] = { 0,0 };
	}
	for (int n = 0; n < 128; n++) {
		for (int x = 0; x < 128; x++) {
			double p = x * n * power;
			//point[x].real = cos(p) * input[x].real;
			//point[x].im = sin(p) * input[x].im;
			point[x].real = cos(p) * input[x].real - sin(p) * input[x].im;
			point[x].im = sin(p) * input[x].real + cos(p) * input[x].im;

			SUMadd.real = SUMadd.real + point[x].real;
			SUMadd.im = SUMadd.im + point[x].im;
		}
		output[n].real = SUMadd.real / 128;
		output[n].im = SUMadd.im / 128;
	}
}


void IDFTcore128(unsigned char  input[128], complex output[128]) {
	complex cplTemp{ 0, 0 };
	complex result{ 0,0 };
	double factor = (2 * PI / 128);
	for (int n = 0; n < 128; n++) {
		for (int x = 0; x < 128; x++) {
			double power = n * x * factor;
			cplTemp.real = cos(power);
			cplTemp.im = -sin(power);

			result.real = result.real + input[x] * cplTemp.real;
			result.im = result.im + input[x] * cplTemp.im;
		}
		output[n].real = result.real;
		output[n].im = result.im;
		result = { 0,0 };
	}


}


void MY_HW5::DFT128(unsigned char img_input[128][128], unsigned char DFTvalue[128][128]) {
	//float  ans[128];
	complex img_data[128][128];
	complex data[128];
	complex com_data[128];

	for (int x = 0; x < 128; x++) {//垂直
		for (int y = 0; y < 128; y++) {
			data[y].real = img_input[x][y];
			data[y].im = 0;
		}
		DFTcore128(data, com_data);
		for (int y = 0; y < 128; y++) {
			img_data[x][y].real = com_data[y].real;
			img_data[x][y].im = com_data[y].im;
			float A;
			double B, C;
			B = img_data[x][y].real;
			C = img_data[x][y].im;
			A = sqrt(B * B + C * C);
		}
	}

	for (int x = 0; x < 128; x++) {//水平
		for (int y = 0; y < 128; y++) {
			data[y].real = img_data[y][x].real;
			data[y].im = img_data[y][x].im;
		}
		DFTcore128(data, com_data);
		for (int y = 0; y < 128; y++) {
			img_data[y][x].real = com_data[y].real;
			img_data[y][x].im = com_data[y].im;
			float A;
			double B, C;
			B = img_data[y][x].real;
			C = img_data[y][x].im;
			A = sqrt(B * B + C * C);
			img_data[y][x].real = log(A);
		}

	}

	//double big = 0;

	//-------------移到中心-----------------//
	float img_data2[128][128];
	for (int x = 0; x < 128 / 2; x++) {//第一
		for (int y = 0; y < 128 / 2; y++) {
			img_data2[x + 64][y + 64] = img_data[x][y].real;
		}
	}

	for (int x = 128 / 2; x < 128; x++) {//第二
		for (int y = 0; y < 128 / 2; y++) {
			img_data2[x - 64][y + 64] = img_data[x][y].real;
		}
	}

	for (int x = 0; x < 128 / 2; x++) {//第三
		for (int y = 128 / 2; y < 128; y++) {
			img_data2[x + 64][y - 64] = img_data[x][y].real;
		}
	}

	for (int x = 128 / 2; x < 128; x++) {//第四
		for (int y = 128 / 2; y < 128; y++) {
			img_data2[x - 64][y -64] = img_data[x][y].real;
		}
	}

	for (int x = 0; x < 128; x++) {
		for (int y = 0; y < 128; y++) {
			DFTvalue[x][y] = img_data2[x][y];
		}
	}
}



/*void DFT_calculate(complex input[256], unsigned char  ans[256]) {
	for (int i = 0; i < 256; i++)
	{
		ans[i] = sqrt(input[i].real * input[i].real + input[i].im * input[i].im);
	}
}*/


void DFTcore256(complex  input[256], complex output[256]) {
	double power = (-2 * PI) / 256;
	complex SUMadd{ 0,0 };
	complex point[256];

	for (int x = 0; x < 256; x++) {//歸零
		point[x] = { 0,0 };
	}
	for (int n = 0; n < 256; n++) {
		for (int x = 0; x < 256; x++) {
			double p = x * n * power;
			//point[x].real = cos(p) * input[x].real;
			//point[x].im = sin(p) * input[x].im;
			point[x].real = cos(p )* input[x].real- sin(p)* input[x].im;
			point[x].im = sin(p) * input[x].real+cos(p)*input[x].im;

			SUMadd.real = SUMadd.real + point[x].real;
			SUMadd.im = SUMadd.im + point[x].im;
		}
		output[n].real = SUMadd.real/256;
		output[n].im = SUMadd.im/256;
	}
}


void IDFTcore256(unsigned char  input[256], complex output[256]) {
	complex cplTemp{ 0, 0 };
	complex result{ 0,0 };
	double factor = (2 * PI / 256);
	for (int n = 0; n < 256; n++) {
		for (int x = 0; x < 256; x++) {
			double power = n * x * factor;
			cplTemp.real = cos(power);
			cplTemp.im = -sin(power);

			result.real = result.real + input[x] * cplTemp.real;
			result.im = result.im + input[x] * cplTemp.im;
		}
		output[n].real = result.real;
		output[n].im = result.im ;
		result = { 0,0 };
	}
	

}


void MY_HW5::DFT256(unsigned char img_input[256][256], unsigned char DFTvalue[256][256]) {
	//int ans = 0;
	//unsigned char  data_re[256];
	//unsigned char  data_im[256];
	unsigned char  ans[256];
	complex img_data[256][256];
	complex data[256];
	complex com_data[256];
	//complex com_data_im[256];

	for (int x = 0; x < 256; x++) {//垂直
		for (int y = 0; y < 256; y++) {
			data[y].real = img_input[x][y];
			data[y].im = 0;
		}
		DFTcore256(data, com_data);
		for (int y = 0; y < 256; y++) {
			img_data[x][y].real = com_data[y].real;
			img_data[x][y].im = com_data[y].im;
			//std::cout << +data_re[y] << " " << +data_im[y] << " " << std::endl;
			float A;
			double B, C;
			B = img_data[x][y].real;
			C = img_data[x][y].im;
			A = sqrt(B * B + C * C);
			//DFTvalue[x][y] = A;
		}

		//DFT_calculate(com_data, ans);
	}

	for (int x = 0; x < 256; x++) {//水平
		for (int y = 0; y < 256; y++) {
			data[y].real = img_data[y][x].real;
			data[y].im= img_data[y][x].im;
		}
		DFTcore256(data, com_data);
		for (int y = 0; y < 256; y++) {
			img_data[y][x].real = com_data[y].real;
			img_data[y][x].im = com_data[y].im;
			//std::cout << +data_re[y] << " " << +data_im[y] << " " << std::endl;
			float A;
			double B, C;
			B = img_data[y][x].real;
			C = img_data[y][x].im;
			A = sqrt(B * B + C * C);
			img_data[y][x].real=log(A);
		    //DFTvalue[y][x] = log(A);
		}

		//DFT_calculate(com_data, ans);
	}

	//double big = 0;
	
	//-------------移到中心-----------------//
	float img_data2[256][256];
	for (int x = 0; x < 256/2; x++) {//第一
		for (int y = 0; y < 256/2; y++) {
			img_data2[x+128][y+128] = img_data[x][y].real;
		}
	}

	for (int x = 256 / 2; x < 256; x++) {//第二
		for (int y = 0; y < 256 / 2; y++) {
			img_data2[x - 128][y + 128] = img_data[x][y].real;
		}
	}

	for (int x = 0; x < 256 / 2; x++) {//第三
		for (int y = 256 / 2; y < 256; y++) {
			img_data2[x + 128][y - 128] = img_data[x][y].real;
		}
	}

	for (int x = 256 / 2; x < 256; x++) {//第四
		for (int y = 256 / 2; y < 256; y++) {
			img_data2[x-128][y - 128] = img_data[x][y].real;
		}
	}

	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 256; y++) {
			DFTvalue[x][y] = img_data2[x][y];
		}
	}
}




