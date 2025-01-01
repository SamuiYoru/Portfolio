#include<iostream>
using namespace std;

int main()
{
	int x;
	int y;
	cin >> x;
	cin >> y;
	if (x > 5)
	if (y > 5)
			cout << "case1:x and y are >5";
	else
			cout << "case1:x is <=5";
	cout << endl;

	if (x > 5)
	{
		if (y > 5)
			cout << "case2:x and y are >5";
	}
	else
		cout << "case2:x is <=5";
	cout << endl;
	return 0;
	system("pause");

}
