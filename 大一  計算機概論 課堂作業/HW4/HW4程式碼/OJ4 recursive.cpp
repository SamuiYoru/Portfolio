#include<iostream>
using namespace std;

int stair(int);

int main()
{
	int n;

	while(cin>>n)
	{
		int i=0;
		while(i<=n)
		{
			int a,b,c,d,e;
			c=stair(n);
			a=stair(i);
			b=stair(n-i);
			d=a*b;
			e=c/d;
			cout<<e<<" ";
			i++;
		}	
		cout<<endl;
	}
}


int stair(int y)//¶¥­¼ 
{
	
	if(y==0)
		return 1;
	else
	{
		return y*stair(y-1);
	}
	
		
}
