/*******************************************
* Filename    : functions.cpp                      *
* Update date : //2022                     *
* Author      : 顏郁芩                         *
* Note        : Power-Law transformation       *
***********************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;


unsigned char MY_HW4::convolution3X3( int a[], int b[]) {
	int ans = 0;
	for(int x = 0 ; x < 9; x++) {
		ans = ans + a[x] * b[x];
	}
	return ans;
}

unsigned char MY_HW4::convolution(int a, int b, unsigned char img[640 + 2][427 + 2],int filter[9]) {
	unsigned char ans = 0;
	ans =
		img[a - 1][b - 1]* filter[0] + img[a - 1][  b  ] * filter[1] + img[a - 1][b + 1] * filter[2] +
		img[  a  ][b - 1] * filter[3] + img[  a  ][  b  ] * filter[4] + img[  a  ][b + 1] * filter[5] +
		img[a + 1][b - 1] * filter[6] + img[a + 1][  b  ] * filter[7] + img[a + 1][b + 1] * filter[8];

	return ans;
}

unsigned char MY_HW4::convolution256(int a, int b, unsigned char img[256+2][256+2], double filter[9]) {
	unsigned char ans = 0;
	ans =
		img[a - 1][b - 1] * filter[0] + img[a - 1][b] * filter[1] + img[a - 1][b + 1] * filter[2] +
		img[a][b - 1] * filter[3] + img[a][b] * filter[4] + img[a][b + 1] * filter[5] +
		img[a + 1][b - 1] * filter[6] + img[a + 1][b] * filter[7] + img[a + 1][b + 1] * filter[8];

	return ans;
}

unsigned char MY_HW4::convolution5X5_256(int a, int b, unsigned char img[256+4][256+4], double filter[25]) {
	unsigned char ans = 0;
	ans = img[a - 2][b - 2] * filter[0] + img[a - 2][b - 1] * filter[1] + img[a - 2][b] * filter[2] + img[a - 2][b + 1] * filter[3] + img[a - 2][b + 2] * filter[4] +
		img[a - 1][b - 2] * filter[5] + img[a - 1][b - 1] * filter[6] + img[a - 1][b] * filter[7] + img[a - 1][b + 1] * filter[8] + img[a - 1][b + 2] * filter[9] +
		img[a][b - 2] * filter[10] + img[a][b - 1] * filter[11] + img[a][b] * filter[12] + img[a][b + 1] * filter[13] + img[a][b + 2] * filter[14] +
		img[a + 1][b - 2] * filter[15] + img[a + 1][b - 1] * filter[16] + img[a + 1][b] * filter[17] + img[a + 1][b + 1] * filter[18] + img[a + 1][b + 2] * filter[19] +
		img[a + 2][b - 2] * filter[20] + img[a + 2][b - 1] * filter[21] + img[a + 2][b] * filter[22] + img[a + 2][b + 1] * filter[23] + img[a + 2][b + 2] * filter[24];
	return ans;
}

unsigned char MY_HW4::convolution5X5_mean(int a,int b, unsigned char img[256+4][256+4]) {
	int ans = 0;
	ans = img[a - 2][b - 2] + img[a - 2][b - 1] + img[a - 2][  b  ] + img[a - 2][b + 1] + img[a - 2][b + 2] +
		  img[a - 1][b - 2] + img[a - 1][b - 1] + img[a - 1][  b  ] + img[a - 1][b + 1] + img[a - 1][b + 2] +
		  img[  a  ][b - 2] + img[  a  ][b - 1] + img[  a  ][  b  ] + img[  a  ][b + 1] + img[  a  ][b + 2] +
		  img[a + 1][b - 2] + img[a + 1][b - 1] + img[a + 1][  b  ] + img[a + 1][b + 1] + img[a + 1][b + 2] +
		  img[a + 2][b - 2] + img[a + 2][b - 1] + img[a + 2][  b  ] + img[a + 2][b + 1] + img[a + 2][b + 2];

	ans = ans * 0.04;
	return ans;
}

unsigned char MY_HW4::convolution5X5_mean2(int a, int b, unsigned char img[720 + 4][790 + 4]) {
	int ans = 0;
	ans = img[a - 2][b - 2] + img[a - 2][b - 1] + img[a - 2][b] + img[a - 2][b + 1] + img[a - 2][b + 2] +
		img[a - 1][b - 2] + img[a - 1][b - 1] + img[a - 1][b] + img[a - 1][b + 1] + img[a - 1][b + 2] +
		img[a][b - 2] + img[a][b - 1] + img[a][b] + img[a][b + 1] + img[a][b + 2] +
		img[a + 1][b - 2] + img[a + 1][b - 1] + img[a + 1][b] + img[a + 1][b + 1] + img[a + 1][b + 2] +
		img[a + 2][b - 2] + img[a + 2][b - 1] + img[a + 2][b] + img[a + 2][b + 1] + img[a + 2][b + 2];

	ans = ans * 0.04;
	return ans;
}


unsigned char MY_HW4::median_filter5x5(int a, int b, unsigned char img[720 + 4][790 + 4]) {
	unsigned char ans = 0;//排序取中間12
	unsigned char data[25];
	data[0] = img[a - 2][b - 2];
	data[1] = img[a - 2][b - 1];
	data[2] = img[a - 2][b];
	data[3] = img[a - 2][b + 1];
	data[4] = img[a - 2][b + 2];

	data[5] = img[a - 1][b - 2];
	data[6] = img[a - 1][b - 1];
	data[7] = img[a - 1][b];
	data[8] = img[a - 1][b + 1];
	data[9] = img[a - 1][b + 2];

	data[10] = img[a][b - 2];
	data[11] = img[a][b - 1];
	data[12] = img[a][b];
	data[13] = img[a][b +1];
	data[14] = img[a][b +2];

	data[15] = img[a + 1][b - 2];
	data[16] = img[a +1][b - 1];
	data[17] = img[a +1][b];
	data[18] = img[a +1][b+1];
	data[19] = img[a +1][b+2];

	data[20] = img[a + 2][b - 2];
	data[21] = img[a + 2][b - 1];
	data[22] = img[a + 2][b];
	data[23] = img[a + 2][b +1];
	data[24] = img[a + 2][b +2];

	int i, j, tmp;
	int n = sizeof(data) / sizeof(unsigned char);
	for (i = n - 1; i > 0; i--)
	{
		for (j = 0; j <= i - 1; j++)
		{
			if (data[j] > data[j + 1])
			{
				tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}
	return data[12];
}


unsigned char MY_HW4::median_filter3x3(int a, int b, unsigned char img[720 + 4][790 + 4]) {
	unsigned char ans = 0;//排序取中間4
	unsigned char data[9];

	data[0] = img[a - 1][b - 1];
	data[1] = img[a - 1][b];
	data[2] = img[a - 1][b + 1];

	data[3] = img[a][b - 1];
	data[4] = img[a][b];
	data[5] = img[a][b + 1];

	data[6] = img[a + 1][b - 1];
	data[7] = img[a + 1][b];
	data[8] = img[a + 1][b + 1];



	int i, j, tmp;
	int n = sizeof(data) / sizeof(unsigned char);
	for (i = n - 1; i > 0; i--)
	{
		for (j = 0; j <= i - 1; j++)
		{
			if (data[j] > data[j + 1])
			{
				tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}
	return data[4];
}



unsigned char MY_HW4::convolution256_720(int a, int b, unsigned char img[720 + 4][790 + 4], double filter[9]) {
	unsigned char ans = 0;
	ans =
		img[a - 1][b - 1] * filter[0] + img[a - 1][b] * filter[1] + img[a - 1][b + 1] * filter[2] +
		img[a][b - 1] * filter[3] + img[a][b] * filter[4] + img[a][b + 1] * filter[5] +
		img[a + 1][b - 1] * filter[6] + img[a + 1][b] * filter[7] + img[a + 1][b + 1] * filter[8];

	return ans;
}


unsigned char MY_HW4::histogram3(int a, int b, unsigned char img[512 + 6][683 + 6]) {
	unsigned char ans = 0;
	unsigned char data[9] = { 0 };
	double HIS[256]={0};
	double a1 = 0;

	data[0] = img[a-1][b-1];
	data[1] = img[a-1][b];
	data[2] = img[a-1][b+1];

	data[3] = img[a][b-1];
	data[4] = img[a][b];
	data[5] = img[a][b+1];

	data[6] = img[a+1][b-1]; 
	data[7] = img[a+1][b];
	data[8] = img[a+1][b+1];

	for (int x = 0; x < 9; x++) {
		HIS[data[x]] = HIS[data[x]] + 1;
	}

	for (int x = 0; x < 9; x++) {
		HIS[data[x]] = HIS[data[x]] / 9;
	}

	for (int x = 0; x < img[a][b]; x++) {
			a1 = a1 + HIS[x];
	}
	ans = a1 *256;
	return ans;
}

unsigned char MY_HW4::hq5(int a, int b, unsigned char img[512 + 6][683 + 6]) {
	unsigned char ans = 0;
	unsigned char data[25] = { 0 };
	double HIS[256] = { 0 };
	double a1 = 0;


	data[0] = img[a - 2][b - 2];
	data[1] = img[a - 2][b - 1];
	data[2] = img[a - 2][b];
	data[3] = img[a - 2][b + 1];
	data[4] = img[a - 2][b + 2];

	data[5] = img[a-1][b - 2];
	data[6] = img[a-1][b - 1];
	data[7] = img[a-1][b];
	data[8] = img[a-1][b + 1];
	data[9] = img[a-1][b + 2];

	data[10] = img[a ][b - 2];
	data[11] = img[a ][b - 1];
	data[12] = img[a ][b];
	data[13] = img[a ][b + 1];
	data[14] = img[a ][b + 2];

	data[15] = img[a + 1][b - 2];
	data[16] = img[a + 1][b - 1];
	data[17] = img[a + 1][b];
	data[18] = img[a + 1][b + 1];
	data[19] = img[a + 1][b + 2];

	data[20] = img[a + 2][b - 2];
	data[21] = img[a + 2][b - 1];
	data[22] = img[a + 2][b];
	data[23] = img[a + 2][b + 1];
	data[24] = img[a + 2][b + 2];

	for (int x = 0; x < 25; x++) {
		HIS[data[x]] = HIS[data[x]] + 1;
	}

	for (int x = 0; x < 25; x++) {
		HIS[data[x]] = HIS[data[x]] / 25;
	}

	for (int x = 0; x < img[a][b]; x++) {
		a1 = a1 + HIS[x];
	}
	ans = a1 * 256;
	return ans;
}

unsigned char MY_HW4::h7(int a, int b, unsigned char img[512 + 6][683 + 6]) {
	unsigned char ans = 0;
	unsigned char data[49] = { 0 };
	double HIS[256] = { 0 };
	double a1 = 0;

	data[0] = img[a - 3][b - 3];
	data[1] = img[a - 3][b - 2];
	data[2] = img[a - 3][b - 1];
	data[3] = img[a - 3][b];
	data[4] = img[a - 3][b + 1];
	data[5] = img[a - 3][b + 2];
	data[6] = img[a - 3][b + 3];

	data[7] = img[a - 2][b - 3];
	data[8] = img[a - 2][b - 2];
	data[9] = img[a - 2][b - 1];
	data[10] = img[a - 2][b];
	data[11] = img[a - 2][b + 1];
	data[12] = img[a - 2][b + 2];
	data[13] = img[a - 2][b + 3];

	data[14] = img[a - 1][b - 3];
	data[15] = img[a - 1][b - 2];
	data[16] = img[a - 1][b - 1];
	data[17] = img[a - 1][b];
	data[18] = img[a - 1][b + 1];
	data[19] = img[a - 1][b + 2];
	data[20] = img[a - 1][b + 3];

	data[21] = img[a][b - 3];
	data[22] = img[a][b - 2];
	data[23] = img[a][b - 1];
	data[24] = img[a][b];
	data[25] = img[a][b + 1];
	data[26] = img[a][b + 2];
	data[27] = img[a][b + 3];

	data[28] = img[a + 1][b - 3];
	data[29] = img[a + 1][b - 2];
	data[30] = img[a + 1][b - 1];
	data[31] = img[a + 1][b];
	data[32] = img[a + 1][b + 1];
	data[33] = img[a + 1][b + 2];
	data[34] = img[a + 1][b + 3];

	data[35] = img[a + 2][b - 3];
	data[36] = img[a + 2][b - 2];
	data[37] = img[a + 2][b - 1];
	data[38] = img[a + 2][b];
	data[39] = img[a + 2][b + 1];
	data[40] = img[a + 2][b + 2];
	data[41] = img[a + 2][b + 3];

	data[42] = img[a + 3][b - 3];
	data[43] = img[a + 3][b - 2];
	data[44] = img[a + 3][b - 1];
	data[45] = img[a + 3][b];
	data[46] = img[a + 3][b + 1];
	data[47] = img[a + 3][b + 2];
	data[48] = img[a + 3][b + 3];


	for (int x = 0; x < 49; x++) {
		HIS[data[x]] = HIS[data[x]] + 1;
	}

	for (int x = 0; x < 49; x++) {
		HIS[data[x]] = HIS[data[x]] / 49;
	}

	for (int x = 0; x < img[a][b]; x++) {
		a1 = a1 + HIS[x];
	}
	ans = a1*256;
	return ans;
}