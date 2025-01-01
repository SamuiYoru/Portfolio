#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <fstream>
#include <dirent.h>  
#include <stdlib.h>  
#include <sstream>
#include<vector>
#include <cstdio> 
#include <cstddef> 

using namespace std;


typedef struct COMMAND{
	int number;
	string com;
	struct COMMAND *next;
}command;

	command *head=new command;
	command *new_node;
	command *current = head;

void print(struct COMMAND *current){
	struct COMMAND *cur = current;
	while(cur != NULL) {
		cur = cur->next;
	}
	printf("\n");
}
void print_num(struct COMMAND *current){
	struct COMMAND *cur = current;
	while(cur != NULL) {
		printf("%d\n", cur->number);
		cur = cur->next;
	}
	printf("\n");
}

void saving(string word,int num){
				current->next=new command();
				current=current->next;
				current->com=word;
				current->number=num;
				current->next=NULL;
}

int number=0;

void spilt(string s){
		int next;
		int now = 0;
		int num=1;
		while(1){ 
		next = s.find_first_of(" ", now);
		if(next != now){
			string word=s.substr(now, next - now);
			if (word.size()!=0){
				saving(word,num);
				number++;
			}
			num++;
		}
		if(next == string::npos){
			 break;
		}
		now = next+1;			
		} 
}

string onebyone(struct COMMAND *current,int x){
	int i=0;
	struct COMMAND *cur = current;
    if (current->next == NULL) {               
        return 0;
    }
    while (current != 0) {            
		i++;
		if (current == 0) {                 
        	return 0;
    	}
		while (i==x+1){
    		i++;
   		 	return current->com;
		}
        current = current->next;
    }
    return 0;
}

void head_command(string data_name,string parameter,int num,string addr){
	string line;
	string a=addr;
	string b=data_name;
	string c=a+b;
	ifstream inFile(c,ios::in);
	int i=0;
	while(getline(inFile,line)){
		if (i<num){
			cout<<"line"<<endl;
		}
		i++;
	}
}

void tail(string data_name,string parameter,int num,string addr){
	
	string line;
	string a=addr;
	string b=data_name;
	string c=a+b;
	ifstream inFile(c,ios::in);
	int j=0;
	int i=0;
	int done=0;
	while(getline(inFile,line)){
		i++;
	}
	done=1;
	while(getline(inFile,line,'\n')&&done==1){
		if(j>=i-num&&j<=i){
			cout<<"line"<<endl;
		}
		j++;
	}
}

void ls(string com,string parameter,string addr){
	char *argv[]={(char*)"ls"/*(char*)com.c_str()*/,(char*)parameter.c_str(),(char*)addr.c_str(), NULL};
	char *envp[]={(char*)"PATH=/bin", NULL};
	pid_t pid = fork();
	if(0==pid){ 
		execve("/bin/ls", argv, envp); 
	}
	else{ 
		int status; 
		wait(&status); 
	} 
}

void make(string address,string name){
	string add=address+"/"+name;
	creat((char*)add.c_str(),0777);
}

void make_d(string address,string name){
	int status;
	string a=address;
	string b=name;
	string c=a+"/"+b;
	status = mkdir((char*)c.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void in(string address,string name){


}

void out(string address,string name){

	//fstream outfile("C:\\Users\\User\\Desktop\\testcase1.txt",ios::out);

}


int main(){
	string s;
	string whatTodo;
	string parameter;
	head->next=NULL;
	head->number=0;
	head->com="com";

	int k=0;
	int i;
	char buf[80];
	while(cin){
		getline(cin,s);
		spilt(s);
		print(head);	
		getcwd(buf, sizeof(buf));
		if(s=="end"){
			break;
		}
		else if(s=="ls"){
    		char *argv[]={(char*)"ls",buf,NULL};
    		char *envp[]={(char*)"PATH=/bin", NULL};
  			pid_t pid = fork();
			if(pid==0){ 
				execve("/bin/ls",argv,envp);
			}
			else{ 
				int status; 
				wait(&status); 
			} 
		}	
		else if(s=="address"){
			getcwd(buf, sizeof(buf));
			string A(buf);
    		cout<<"add="<<A<<endl;
		}	
		else {
			for(i=k;i<=number;i++){
				if(onebyone(head,i)=="ls"){
					ls(onebyone(head,i),onebyone(head,i+1),buf);
					i=i+1;
				}
				else if(onebyone(head,i)=="mkdir"){
    				getcwd(buf, sizeof(buf));
					make_d(buf,onebyone(head,i+1));
					i=i+1;
				}
				else if(onebyone(head,i)=="cd"){
					if(onebyone(head,i+1)==".."){				
						getcwd(buf, sizeof(buf));
    					string A(buf);
    					size_t found = A.find_last_of("/");
    					string path=A.substr(0,found);
						chdir(path.c_str());	
					}
					else{
						getcwd(buf, sizeof(buf));
	    				string A(buf);
	    				string addr=A+"/"+onebyone(head,i+1);
						chdir(addr.c_str());
						i=i+1;
					}
    			}
				else if(onebyone(head,i)=="make"){
    				getcwd(buf, sizeof(buf));
					make(buf,onebyone(head,i+1));
					i=i+1;
				}
				else if(onebyone(head,i)=="delete"){
					getcwd(buf, sizeof(buf));
    				string A(buf);
					string addr=A+"/"+onebyone(head,i+1);
					remove(addr.c_str());
					i=i+1;
				}
				else{
					i++;
				}
				k=i;
			}
		}
	
	}		
	return 0;
}





