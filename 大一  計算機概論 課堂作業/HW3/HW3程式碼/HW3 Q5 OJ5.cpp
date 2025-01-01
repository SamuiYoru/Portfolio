#include<iostream>
using namespace std;
int main()
{
	int n;
	int a,b;
	int count=1;
	int s=0;
	
	while(cin>>n)
	{
		int count=1;
		int s=0;
		while(count<n)
		{
			a=n/count;			
			b=n-(a*count);
			if(b==0)
			{
				s=s+count;
				count=count+1;
			}
			else
			{
				count++;
			}
			
		}
		if(s>n)
		{
			cout<<"abundant number\n";
		
		}
		else if(s==n)
		{
			cout<<"perfect number\n";
		
		}
		else
		{
			cout<<"deficient number\n";
		
		}
	}
	return 0;
}


 
