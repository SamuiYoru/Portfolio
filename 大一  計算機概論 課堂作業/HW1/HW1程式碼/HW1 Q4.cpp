#include<iostream>
using namespace std;
int main()
{
int total = 0; 
int grade = 0; 
int counter = 0; 
do{
	total=total+grade;
	counter=counter+1;
	cout<<"Enter grade,"; 
	cout<< "-1 to end:" ; 
	cin >> grade; 
}while (grade != -1) ;
	
cout << "total: "<<total; 
cout<<"\n counter: "<<counter<<endl; 
cout<<"grade: "<<grade<<"\n" ; 
}
