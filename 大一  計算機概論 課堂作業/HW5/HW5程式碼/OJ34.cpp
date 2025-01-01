#include<iostream>
using namespace std;
int main()
{
	int n;
	while(cin>>n)
	{
		for(int i=2;i<=n;i++)
		{
			int a,b,c,d,e,f,g,h;//°Ó¼Æ 
			int a1,b1,c1,d1,e1,f1,g1,h1;//¾l¼Æ 
			a=i/2;a1=i%2;
			b=i/3;b1=i%3;
			c=i/5;c1=i%5;
			d=i/7;d1=i%7;
			e=i/11;e1=i%11;
			f=i/13;f1=i%13;
			g=i/17;g1=i%17;
			h=i/19;h1=i%19;
		if ((a==1||a1!=0)&&(b==1||b1!=0)&&(c==1||c1!=0)&&(d==1||d1!=0)&&(e==1||e1!=0)&&(f==1||f1!=0)&&(g==1||g1!=0)&&(h==1||h1!=0))
			cout<<i<<endl;
		}
	}
	return 0;
}
