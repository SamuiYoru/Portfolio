#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
ifstream inFile("C:\\Users\\yuchin\\Desktop\\read.txt");
string line;
fstream outfile;
outfile.open("C:\\Users\\yuchin\\Desktop\\ans.txt",ios::out);
if(outfile.fail())
	cout<<"error";

  else while(getline(inFile,line)) {
    istringstream ss(line);
    string word;
    getline(ss,word,' ');
    	if(word=="ADD"){
    	cout<<"25"<<" ";
    	outfile<<"25"<<" ";
	}	
	if(word=="MOV"){
	    cout<<"E5"<<" ";
    	outfile<<"E5"<<" ";	
	}
	if(word=="SETB"){
		cout<<"D3"<<" ";
    	outfile<<"D3"<<" ";	
	}
	
    
    while (getline(ss, word,',')){
            string str1;
            string str2;
            str2 = str2.assign(word, 0, 1);
            if(str2=="0"){
            	str1 = str1.assign(word, 1, word.size()-2); 
	    		cout<< str1 <<" ";
	    		outfile<<str1<<" ";
			}
			else{
				str1 = str1.assign(word, 0, word.size()-1); 
	    		cout<< str1 <<" ";
				outfile<<str1<<" ";	
			}
        }
    cout << endl;
    outfile<<endl;
  }    
	outfile.close();
  inFile.close();

  return 0;
}

