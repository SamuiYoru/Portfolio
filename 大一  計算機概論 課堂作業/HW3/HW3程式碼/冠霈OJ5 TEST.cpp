#include <iostream>

using namespace std;

int main()
{
	int x,a=0;
	int i = 1;
	cin >> x;

	for(i>0;i<x;i++)
	{
		cout << "�S���B�z��i=" << i << endl;
		if (x%i == 0)
		{
			a = a + i;
			cout << "a="<<a << endl;
			cout << "�i�hif��i="<<i << endl;
			i++;
			cout << "���}if��i="<<i << endl;
		}	
		else
		{ 
			i++;
			cout << "�S���B�z��i=" << i << endl;
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
