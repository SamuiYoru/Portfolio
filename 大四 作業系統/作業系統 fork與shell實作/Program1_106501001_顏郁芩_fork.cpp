#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

int main(void)
{
int status;
   cout<<"i  type  pid"<<endl;
   for (int i=0;i<2;i++)
   {
       pid_t pid=fork();
       if (fpid==0){
       cout<<i<<"  "<<"child"<<"  "<<pid<<endl;
       }  
       else {
       cout<<i<<"  "<<"parent"<<"  "<<pid<<endl;
       wait(&status);
       }
   }
   return 0;
}

