#include <iostream>
#include<cmath>
using namespace std;
int main()
{
	int num1, num2, num3, num4, num5, num6;
	num1 = 4; num2 = 8;
	do
	{
		num3 = num1 & num2;
		num4 = num1 && num2;
		num5 = num1 | num2;
		num6 = num1 || num2;
		cout << "num1 = " << num1 << " ; num2 = " << num2;
		cout << "\nnum3 = " << num3 << " ; num4 = " << num4;
		cout << "\nnum5 = " << num5 << " ; num6 = " << num6 <<"\n";
		if ((num3 == num4) && (num5 == num6))
		{
			cout << "special case\n";
		}
		else
		{
			cout << "enter num1 and number 2 \n";
			cin >> num1 >> num2;
		}
	}while ((num3 != num4) || (num5 != num6));
	
	return 0;
	
}
