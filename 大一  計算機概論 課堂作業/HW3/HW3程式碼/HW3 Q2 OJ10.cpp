#include<iostream>
using namespace std;

int main()
{
	int n;
	int a=1;
	cin>>n;
	while(a<=n)
	{
		for(int i=1;i<=a;i++)
		{
			cout<<i;
		}
		for(int m=n-a-1;m>=0;m--)
		{
			cout<<"*";
		}
		cout<<endl;
	a++;
	}
}
