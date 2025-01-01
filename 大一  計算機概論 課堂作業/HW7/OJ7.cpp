#include<iostream>
using namespace std;

int main()
{
	int a,b,c,d,e,f,g;
	int count=0;
	int wrong=0;
	cin>>a;
	cin>>b;
	count++;
	//a個數，b是答案 
		


	if(b==0)//5 0 5 2 1 0
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d;
			count++;
			if(d!=2)wrong=1;	
			cin>>e;
			count++;
			if(e!=1)wrong=1;	
			cin>>f;
			count++;
			if(f!=0)wrong=1;	
		}
			if(a!=5||count>5)wrong=1;	
			if(wrong==0)cout<<"4 times"<<endl;
	}
	
	else if(b==1)//4 1 5 2 1
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d; 
			count++;
			if(d!=2)wrong=1;	
			cin>>e;
			count++;
			if(e!=1)wrong=1;	
		}
			if(a!=4||count>4)wrong=1;	
			if(wrong==0)cout<<"3 times"<<endl;
	}	
	else if(b==2)//3 2 5 2
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d;
			count++;
			if(d!=2)wrong=1;	
		}
			if(a!=3||count>3)wrong=1;	
			if(wrong==0)cout<<"2 times"<<endl;
	}
	
	else if(b==3)//5 3 5 2 4 3
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d;
			count++;
			if(d!=2)wrong=1;
			cin>>e;
			count++;
			if(e!=4)wrong=1;
			cin>>f;
			count++;
			if(f!=3)wrong=1;
		}
			if(a!=5||count>5)wrong=1;	
			if(wrong==0)cout<<"4 times"<<endl;
	}
	
	else if(b==4)//4 4 5 2 4
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d;
			count++;
			if(d!=2)wrong=1;
			cin>>e;
			count++;
			if(e!=4)wrong=1;
		}
			if(a!=4||count>4)wrong=1;	
			if(wrong==0)cout<<"3 times"<<endl;
	}
	
	else if(b==5)//2 5 5
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(a!=2||count>2)wrong=1;	
			if(wrong==0)cout<<"1 time"<<endl;
	}
	
	else if(b==6)//5 6 5 8 7 6
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d;
			count++;
			if(d!=8)wrong=1;
			cin>>e;
			count++;
			if(e!=7)wrong=1;
			cin>>f;
			count++;
			if(f!=6)wrong=1;
		}
			if(a!=5||count>5)wrong=1;	
			if(wrong==0)cout<<"4 times"<<endl;
	}
	
	else if(b==7)//4 7 5 8 7
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d;
			count++;
			if(d!=8)wrong=1;	
			cin>>e;
			count++;
			if(e!=7)wrong=1;	
		}
			if(a!=4||count>4)wrong=1;	
			if(wrong==0)cout<<"3 times"<<endl;
	}
	
	else if(b==8)//3 8 5 8
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d;
			count++;
			if(d!=8)wrong=1;	
		}
			if(a!=3||count>3)wrong=1;	
			if(wrong==0)cout<<"2 times"<<endl;
	}
	
	else if(b==9)//5 9 5 8 10 9
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d;
			count++;
			if(d!=8)wrong=1;	
			cin>>e;
			count++;
			if(e!=10)wrong=1;
			cin>>f;
			count++;
			if(f!=9)wrong=1;	
		}
			if(a!=5||count>5)wrong=1;	
			if(wrong==0)cout<<"4 times"<<endl;
	}
	
	else if(b==10)//4 10 5 8 10
	{
		cin>>c;
		count++;
		if(c!=5)wrong=1;	
		if(c==5)
		{
			cin>>d;
			count++;
			if(d!=8)wrong=1;	
			cin>>e;
			count++;
			if(e!=10)wrong=1;	
		}
			if(a!=4||count>4)wrong=1;	
			if(wrong==0)cout<<"3 times"<<endl;
	}
	if(wrong==1)cout<<"false"<<endl;	
 } 
