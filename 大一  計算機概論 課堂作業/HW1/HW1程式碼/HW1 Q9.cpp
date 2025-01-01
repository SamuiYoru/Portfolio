#include<iostream>
using namespace std; 
int main()
{ 
	int count;
	for (count = 1; count <= 10; count ++)
	{ 
  		if (count == 6) 
  		 {
   			count++; 
   			continue;
   		}
		 	cout <<count << " "; 
 
 	}
	 
 	system("PAUSE");
 	return 0;
 } 
