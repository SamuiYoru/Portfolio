#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int n,sum;
	int a,b,c;
	while(cin>>n)
	{
		a=n/100;
		b=n/10-10*a;
		c=n%10;
		sum=pow(a,3)+pow(b,3)+pow(c,3);
		if(sum==n)
		{
			cout<<"yes";
		}
		else
		{
			cout<<"no";
		}	
		cout<<"\n";
	}
	return 0;
}
 
