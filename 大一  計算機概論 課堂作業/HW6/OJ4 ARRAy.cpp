#include<iostream>
using namespace std;
int ever(int,int);
int stair(int);
void array(void);
int arr[100];

void array()
{
	for(int j=0;j<100;j++)
		arr[j]=j+1;
}


int main()
{
	int n;
	array();
	while(cin>>n)
	{
	
		int i=0;
		while(i<=n)
		{
			int a=1,b=1,c=1,d,e;
			if(i==0)
			{
				for(int j=0;j<n;j++)
					c=c*arr[j];
				a=1;
				for(int j=0;j<n;j++)
					b=b*arr[j];
			}
			
			else
			{
				for(int j=0;j<n;j++)
					c=c*arr[j];
				for(int j=0;j<i;j++)
					a=a*arr[j];
				for(int j=0;j<n-i;j++)
					b=b*arr[j];
			}
			d=a*b;
			e=c/d;
			cout<<e<<" ";
			i++;
		}	
		cout<<endl;
	}
}


