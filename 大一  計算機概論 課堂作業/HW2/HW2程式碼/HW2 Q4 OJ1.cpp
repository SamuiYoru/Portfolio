#include<iostream>
#include<string>
using namespace std;

int main()
{
	int num1;
	int num2;
	string a;
	while(cin>>num1)
	{
		cin>>num2;
		cin>>a;
		if(num1>num2)
		{
			if(a=="bigger")
			{	
				cout<<"true";
			
			}
			else
			{
				cout<<"false";
			
			}
		}
		else if(num1==num2)
		{
			if(a=="equal")
			{
				cout<<"true";
			
			}
			else
			{
				cout<<"false";
		
			}
		}
		else
		{
			if(a=="smaller")
			{
				cout<<"true";
			
			}	
			else
			{
				cout<<"false";
			
			}
		}
		cout<<"\n";	
	}
	return 0;
} 
