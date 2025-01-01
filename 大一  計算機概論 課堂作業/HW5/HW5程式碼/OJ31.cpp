#include<iostream>
using namespace std;
int triangle[3];

int main()
{
	int flag=1;
	while(flag==1)
	{
		flag=0;
		for(int i=0;i<3;i++){cin>>triangle[i];}
		int a=triangle[1];
		if (triangle[2]>triangle[1])
		{
			triangle[1]=triangle[2];
			triangle[2]=a;
		}
		a=triangle[0];
		if (triangle[1]>triangle[0])
		{
			triangle[0]=triangle[1];
			triangle[1]=a;
		}
		a=triangle[1];
		if (triangle[2]>triangle[1])
		{
			triangle[1]=triangle[2];
			triangle[2]=a;
		}
		//cout<<"triangle[0]="<<triangle[0]<<"triangle[1]="<<triangle[1];
		//cout<<"triangle[2]="<<triangle[2]<<endl;
		if(triangle[0]>=triangle[1]+triangle[2])
		{
			flag=1;
			cout<<"N"<<endl;
		}
		else
		{
			
			cout<<"Y"<<endl;
			if (triangle[0]*triangle[0]==(triangle[1]*triangle[1]+triangle[2]*triangle[2]))
				cout<<"Right triangle"<<endl;
			else if(triangle[0]==triangle[1]||triangle[1]==triangle[2])
			{
				if(triangle[0]==triangle[2])
					cout<<"Regular triangle"<<endl;
				else
					cout<<"Isosceles triangle"<<endl;
			}
				
		}
	}


return 0;
	
}

