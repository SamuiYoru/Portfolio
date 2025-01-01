#include<iostream>
using namespace std;
int main()
{
	int x, y;
	string s;
	string smaller = "smaller";
	string bigger = "bigger";
	string equal = "equal";
	while (cin >> x >> y >> s) {
		if ((x > y) && (s ==  bigger)) {
			cout << "true\n";
		}
		else
		{
			cout << "false\n";
		}
		if ((x < y) && (s == smaller)) {
			cout << "true\n";
		}
		else {
			cout << "false\n";
		}
		if ((x == y) && (s == equal)) {
			cout << "true\n";
		}
		else
		{
			cout << "false\n";
		}
		return 0;
	}

}
