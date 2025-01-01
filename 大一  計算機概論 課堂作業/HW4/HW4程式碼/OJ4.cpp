#include<iostream>
using namespace std;
int ever(int,int);
int stair(int);

int main()
{
	int n;

	while(cin>>n)
	{
		int i=0;
		while(i<=n)
		{
			cout<<ever(n,i)<<" ";
			i++;
		}	
		cout<<endl;
	}
}

int ever(int n,int x)//x=i
{
	int a,b,c,d,e;
	c=stair(n);
	a=stair(x);
	b=stair(n-x);
	d=a*b;
	e=c/d;
	return e;
}


int stair(int y)//¶¥­¼ 
{
	int s=1;
	if(y==0)
		s=1;
	else
	{
		for(int h=1;h<=y;h++)
		{
		s=s*h;
		}
	}
	
	return s;	
}
