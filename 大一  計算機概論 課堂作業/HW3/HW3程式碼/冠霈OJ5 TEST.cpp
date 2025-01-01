#include <iostream>

using namespace std;

int main()
{
	int x,a=0;
	int i = 1;
	cin >> x;

	for(i>0;i<x;i++)
	{
		cout << "沒有處理的i=" << i << endl;
		if (x%i == 0)
		{
			a = a + i;
			cout << "a="<<a << endl;
			cout << "進去if的i="<<i << endl;
			i++;
			cout << "離開if的i="<<i << endl;
		}	
		else
		{ 
			i++;
			cout << "沒有處理的i=" << i << endl;
		} 
		
	}
	if (a > x)
		cout << "abundant number" << endl;
	else if (a < x)
		cout << "deficient number" << endl;
	else if (a == x)
		cout << "perfect number" << endl;

	system("pause");
	return 0;
}
