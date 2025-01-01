#include<iostream>
using namespace std;

int main(){

int count; 

while (1) { 
  if (count == 6 || count == 12) { 
   count++; 
   continue; 
  } 
  if (count > 10 && count % 3 == 1) { 
   count++; 
  } 
  if (count > 20) { 
   break; 
  } 
  count += 3; 
  cout << count << " ";  } 
}
