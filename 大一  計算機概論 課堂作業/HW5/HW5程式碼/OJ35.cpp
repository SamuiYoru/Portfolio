#include<iostream>
using namespace std;

int main()
{
	double n;
	string s;
	int flag=1;
	while(flag==1)
	{
		cin>>n;
		int m;
		m=n;
		if(m!=n)
		{
			flag=1;
			continue;
		}
		flag=0;
		int a,b,c,d;
		a=m/1000;
		b=(m%1000)/100;
		c=(m%100)/10;
		d=m%10;
		
		cout<<"1000:"<<a<<endl;
		cout<<"100:"<<b<<endl;
		cout<<"10:"<<c<<endl;
		cout<<"1:"<<d<<endl;
		
		int check=0;
		while(check==0)
		{
			cin>>s;
			if(s=="Y"||s=="y")
			{
				check=1;
				flag=0;
			}
			else if(s=="N"||s=="n")
			{
				flag=1;
				check=1;
			}
			else
				check=0;
		}
	}
	return 0;
}
