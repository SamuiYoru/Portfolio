#include<iostream>
#include<cmath> 
using namespace std;

int main()
{
	int a,b,c,d;
	cin>>d;
	c=d%10;
	b=(d/10)%10;
	a=d/100;
	if(d<1000&&d>99)
	{
		if(pow(a,3)+pow(b,3)+pow(c,3)==100*a+10*b+c)
		cout<<"yes";
		else
		cout<<"no";
	}
	
	return 0;
}
