#include<iostream>
using namespace std;

int main()
{
	int n;
	while(cin>>n)
	{
		int num1=1;
		int num2=1;
		cout<<num1<<endl;
		cout<<num2<<endl;
		for(int i=3;i<=n;i++)
		{
			int e=num1+num2;
			cout<<e<<endl;
			num1=num2;
			num2=e;
			
		}
	}
	system("pause");
	return 0;
 } 
