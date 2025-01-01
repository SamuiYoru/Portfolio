#include <iostream>
using namespace std;
int func(int n);
int main(void)
{
	int  n, k;
	cin >> n;
	
	if (n > 0) {
		for (k = 0; k <= n; k++)
		{
			cout << func(n) / (func(k)*func(n - k)) << " ";
		}
		cout << endl;
	}
	else
		cout << "Error" << endl;
	
	system("pause");
	return 0;
}

int func(int n)
{
	int j;
	int s = 1;
	if (n >= 1) {
		for (j =1 ; j <=n; j++)
		{
			s = s*j;
		}
	}
	else
	{
		s = 1;
	}
	return (s);
}
