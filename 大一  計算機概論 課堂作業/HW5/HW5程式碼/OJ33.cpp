#include<iostream>
using namespace std;

int main()
{
	int n;
	while(cin>>n)
	{ 
		int k=3*n-2;
		int l=3*n-2;
		int line=4*(n-1)+1;
		for(int a=1;a<=n-1;a++)//(n-1)cout<<"*"*1,2,3....(n-1)
		{
			for(int a1=1;a1<=l-a;a1++)
			{
				cout<<" ";
			}
			for(int a2=1;a2<=a;a2++)
			{
				cout<<"* ";
			}
			cout<<endl;
		}
		for(int b=1;b<=n-1;b++)//(n-1)cout<<"*"*(3n-2),3n-3,3n-4.... 
		{
			for(int b1=0;b1<l-k;b1++)
			{
				cout<<" ";
			}
			for(int b2=1;b2<=k;b2++)
			{
				cout<<"* ";
			}
			k=k-1;
			cout<<endl;
		}
		for(int c=1;c<=l-2*n+1;c++)
		{
			cout<<" ";
		}
		for(int c=1;c<=2*n-1;c++)
		{
			cout<<"* ";
		}
		cout<<endl;
		k=2*n;
		for(int d=n-1;d>=1;d--)//倒著的(n-1)cout<<"*"*(3n-2),3n-3,3n-4.... 
		{
			for(int d1=0;d1<l-k;d1++)
			{
				cout<<" ";
			}
			for(int d2=1;d2<=k;d2++)
			{
				cout<<"* ";
			}
			cout<<endl;
			k=k+1;	
		}
		for(int e=n-1;e>=1;e--)//倒著的(n-1)cout<<"*"*1,2,3....(n-1)
		{
			for(int e1=1;e1<=l-e;e1++)
			{
				cout<<" ";
			}
			for(int e2=1;e2<=e;e2++)
			{
				cout<<"* ";
			}
			cout<<endl;
		}
	}
	return 0;
}
