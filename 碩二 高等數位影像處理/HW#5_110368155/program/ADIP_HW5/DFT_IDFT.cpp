//https://stackoverflow.com/questions/51679516/discrete-fourier-transform-c


/*#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <complex>

#define PI 3.1415926

using namespace std;
using namespace W;



vector<double> input;
vector<double> result;
vector<complex<double>> output;

double IDFT(int n)
{
    double a = 0;
    double b = 0;
    int N = output.size();
    for (int k = 0; k < N; k++)
    {
        double value = abs(output[k]);
        a += cos((2 * PI * k * n) / N) * value;
        b += sin((2 * PI * k * n) / N) * value;
    }
    complex<double> temp(a, b);
    double result = abs(temp);
    result /= N;
    return result;
}
complex<double> DFT(double in, int k)
{
    double a = 0;
    double b = 0;
    int N = input.size();
    for (int n = 0; n < N; n++)
    {
        a += cos((2 * PI * k * n) / N) * input[n];
        b += -sin((2 * PI * k * n) / N) * input[n];
    }
    complex<double> temp(a, b);
    return temp;
}*/