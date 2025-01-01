#include<iostream>
using namespace std;

int main()
{
	int n;
	while(cin>>n)
	{
		int flag=1;
		int count=0;
		int a=1;//§PÂ_¬O§_¿é¤J¿ù»~­È 
		int arr[5]={0,0,0,0,0};
		
		if (n<2||n>5)
		{
			cout<<"Format error, input invalid:\n";
			flag=0;
		}
		else
		{
			for(int i=0;i<n;i++)
			{
				cin>>arr[i];
			}	
	
			for(int j=0;j<n;j++)//§PÂ_¬O§_¿é¤J¿ù»~­È 
			{
				if(arr[j]<0)
				{	
					a=0;
					flag=0;
				}		
			}
			
		}
		if(a==0)//§PÂ_¬O§_¿é¤J¿ù»~­È 
				cout<<"Format error, restart out over:"<<endl;
		while(flag==1)
		{
			for(int m=n-1;m>=0;m--)
			{
				cout<<arr[m];
			}
			cout<<endl;
			flag=0;
		}
	}
}
