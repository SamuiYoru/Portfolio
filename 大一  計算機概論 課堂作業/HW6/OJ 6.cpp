//т程そ计程そ计 
#include<iostream>
using namespace std;

int main()
{	
	int a,b,c;
	int arr[10]={2,3,5,7,11,13,15,17,19,23};
	int count;
	while(cin>>a)
	{
		cin>>b>>c;
		int a1=a,b1=b,c1=c;
		int x=1,y=1;
		int i=0;
		while(i<10)
		{
			while(a1%arr[i]==0&&b1%arr[i]==0&&c1%arr[i]==0)
			{
				a1=a1/arr[i];
				b1=b1/arr[i];
				c1=c1/arr[i];
				x=x*arr[i];
			}
			i=i+1;
			
		}
		y=x;
		int j=0;
		while(j<10)
		{
			count=0;
			if(a1%arr[j]==0)
				count=count+1;
			if(b1%arr[j]==0)
				count=count+1;
			if(c1%arr[j]==0)
				count=count+1;
			
			if(count==2)
			{
				if(a1%arr[j]==0)
					a1=a1/arr[j];
				if(b1%arr[j]==0)
					b1=b1/arr[j];
				if(c1%arr[j]==0)
					c1=c1/arr[j];
				y=y*arr[j];//y琌程そ计
			}		
			j++;
		}
	y=y*a1*b1*c1;
	cout<<x<<" "<<y<<endl;	
	}
	return 0;
}
