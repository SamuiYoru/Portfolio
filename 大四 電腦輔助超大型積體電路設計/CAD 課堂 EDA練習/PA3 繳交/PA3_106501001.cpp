#include <iostream>
#include <fstream>
#include <string>
#include <sstream>//用istringstream
#include <stdlib.h>//把STR轉整數
#include <vector> 
using namespace std;

vector <int> v;

typedef struct {
	string word;
	vector <int> code;//解碼後 
	int how_many1;
	int primary; 
}Contain;

typedef struct {
	vector <int> code;//解碼後 
}Primary;

Contain contain[100000];
Contain contain2[100000];
Primary primary[100000];

typedef struct {
	vector <int> code;//解碼後 
	int marker;
}Prime;


vector <Prime> prime;
Prime master_prime;

typedef struct {
	vector <int> code;//解碼後 
	int end;
}Mean;

vector <Mean> mean;
Mean master_mean;
vector <string> s;//存inorder

int transfer(string X){//看有沒有驚嘆號 
	if(X.find('!')!=string::npos){//有找到驚嘆號的話
		//cout<<0<<endl; 
		return 0;	
	}
	else{
		//cout<<1<<endl;
			return 1;
	}
} 

void print_vec(vector <int>a){//輸出int向量 
	for (int n=0;n<a.size();n++){
		if(a.at(n)==2){
			cout<<"-";	
		}
		else{
			cout<<a.at(n);
		}
	}
} 

int vec_find(vector <int>a,int x){//找a中有沒有x值 
int count=0;
	for (int n=0;n<a.size();n++){
		if(a.at(n)==x){
			count++;	
		}
		else{
			count=count;
		}
	}
	
	if(count!=0){
		return 1;
	}
	else{
			return 0;
		}
} 

void spilt_and_convert(string X,int num){//拆解輸入的項 
	string S;
	master_mean.code.clear();
	S=X;
	string w;
	while(S.find('*')!=string::npos){
		w=S.substr(0,S.find_first_of("*",0));
		//cout<<"w="<<w<<endl;
		//v.push_back(transfer(w));
		contain[num].code.push_back(transfer(w));
		master_mean.code.push_back(transfer(w));
		S=S.substr(S.find_first_of("*",0)+1,S.length()-S.find_first_of("*",0));	
	}	
	if(S.find('*')==string::npos&&S.length()!=0){
		//cout<<"S="<<S<<endl;
		//v.push_back(transfer(S));
		contain[num].code.push_back(transfer(S));
		master_mean.code.push_back(transfer(S));
		S.clear();
	}
	if(S.length()==0){
		/*for (int i=0;i<v.size();i++){
			cout<<v.at(i)<<" ";
		}
				cout<<endl;*/
		master_mean.end=0;
		mean.push_back(master_mean);
		/*for (int i=0;i<contain[num].code.size();i++){
			cout<<contain[num].code.at(i)<<" ";
		}*/
		

		//cout<<endl;	
		//cout<<"how_many1="<<one_count<<endl;
	}
}

int inorder_count(string X){//拆掉inorder存進s裡面，順便算有幾個，回傳 
	int counter=0;
	string S;
	S=X;
	string w;
	while(S.find(' ')!=string::npos){
		w=S.substr(0,S.find_first_of(" ",0));
		counter++;
		//cout<<"w="<<w<<endl;
		s.push_back(w);
		S=S.substr(S.find_first_of(" ",0)+1,S.length()-S.find_first_of(" ",0));
	}
	if(S.find(' ')==string::npos&&S.length()!=0){
		//cout<<"S="<<S<<endl;
		s.push_back(S);
		S.clear();
		counter++;
	}
	/*if(S.length()==0){
		cout<<"s=";
		for (int i=0;i<s.size();i++){
			cout<<s.at(i)<<" ";
		}
				cout<<endl;
		cout<<endl;	
	}*/
	
	return counter;
}

int compare(vector <int>a,vector <int>b){//比較兩個向量是否相同，回傳相同位元數量 
	int differ_count=0;
	for (int i=0;i<a.size();i++){
			if(a.at(i)!=b.at(i)){
				differ_count++;				
			}
	}
	return 	differ_count;
}

int one_count(vector <int> a){//算int向量有幾個1 
	int one_count=0;
	for (int n=0;n<a.size();n++){
		if(a.at(n)==1){
			one_count++;	
		}
	}
	return one_count;
} 

void clean(int num,int x){//清除struct的值 
	if(x==1){
		for(int i=0;i<num;i++){
		contain[i].code.clear();
		contain[i].how_many1=0;
		contain[i].primary=0;
		contain[i].word.clear();
	}
	}
	else if(x==2){
		for(int i=0;i<num;i++){
		contain2[i].code.clear();
		contain2[i].how_many1=0;
		contain2[i].primary=0;
		contain2[i].word.clear();
	}

	}
}

vector<int> change(vector <int>a,vector <int>b){//把向量化簡 
	vector<int> new_vec;
	for (int i=0;i<a.size();i++){
			if(a.at(i)!=b.at(i)){
				new_vec.push_back(2);			
			}
			else{
				new_vec.push_back(a.at(i));
			}
	}
	return 	new_vec;
	
}

int count_end(int counter,int x){//判斷是否結束(算現在的儲存空間裡面還有沒有非primary項 
	int c=0;
	if(x==0){
			for(int i=0;i<counter;i++){				
		if(contain[i].primary==0){
			c++;
		}					
	}
		
	}
	else if(x==1){
		for(int i=0;i<counter;i++){				
		if(contain2[i].primary==0){
			c++;
		}			
	}
	}
	//cout<<"c="<<c<<endl;
	if(c!=0){
		return 0;	
	}
	else return 1;
} 

int same(vector <int>a,vector <int>b){//判斷兩個向量是否相同，相同回傳1，不相同回傳0 
	int not_same=0;
	for (int i=0;i<a.size();i++){
			if(a.at(i)!=b.at(i)){
				not_same++;				
			}
	}
	if(not_same==0){
		return 1;
	}
	else return 0; 	
}

int compare_and_ignore(vector <int>a,vector <int>b){//判斷兩個向量是否相同，相同回傳1，不相同回傳0，忽略掉DONT CARE 
	int not_same=0;
	for (int i=0;i<a.size();i++){
		if(a.at(i)==0 || a.at(i)==1){
			if(a.at(i)!=b.at(i)){
				not_same++;				
			}
		}
	}
	if(not_same==0){
		return 1;
	}
	else return 0; 	
}

int save_or_not(vector <int> a,int num,int x){//判斷要不要把化簡過後的存起來(之前有沒有存過) 
	int in=0;
	if(x==1){
		for(int i=0;i<num;i++){
			if(same(a,contain2[i].code)==1){
			in++;	
			}
		}
	}
	else if(x==2){	
		for(int i=0;i<num;i++){
			if(same(a,contain[i].code)==1){
			in++;	
			}
		}
	}
	
	if(in==0){//沒有一樣的，存 
		return 1;
	}
	else return 0;

	
}

string change_to_word(vector <int> a,vector <string> b){//把數字轉成對應的字串 
	string change;
	//cout<<a.size()<<endl;
	for(int i=0;i<a.size();i++){
		if(a.at(i)==1){
			change=change+b.at(i);
		}
		else if(a.at(i)==0){
			change=change+"!"+b.at(i);
		}
		else {
			change=change;
		}
		if(i==a.size()-1||a.at(i)==2||(i==a.size()-2&&a.at(i+1)==2)){
			change=change;
		}
		else change=change+"*";
	}
//	cout<<change<<endl;
	return change;
}

void mean_done(){//輸出mean的end項目 
		vector<Mean>::iterator iter_m = mean.begin();
		for(iter_m; iter_m != mean.end(); iter_m++){
			cout<<" "<<iter_m->end;
			if(iter_m != mean.end()-1){
				cout<<" ";
			}
			else{
				cout<<endl;
			}
		}	
}

void prime_done(){//輸出prime的marrker項目 
		vector<Prime>::iterator iter_p = prime.begin();
		for(iter_p; iter_p != prime.end(); iter_p++){
			cout<<iter_p->marker;
			if(iter_p == prime.end()-1){
				cout<<endl;
			}
			else cout<<endl;		
			}	
}

int done_OX(){//確認是不是全部做完(mean的end是不是全部為1) 
	int count=0;
		vector<Mean>::iterator iter_m = mean.begin();
		for(iter_m; iter_m != mean.end(); iter_m++){
			//cout<<" "<<iter_m->end;
			if(iter_m->end!=1){
				count++;
			}
			}
			if(count!=0){
				return 0;
			}
			else{
				return 1;
			}
		}	

void print_list(vector <vector <int> > a,vector <Prime> b,vector <Mean> c,int num){//檢查用 
		for(int x=0; x<=num; x++){
			cout<<" ";
		}
		vector<Mean>::iterator iter_m = c.begin();
		for(iter_m; iter_m != c.end(); iter_m++){
			print_vec(iter_m->code);
			//cout<<" "<<iter_m->end;
			if(iter_m != c.end()-1){
				cout<<" ";
			}
			else{
				cout<<endl;
			}
		}
		
		
		vector<Prime>::iterator iter_p = b.begin();
		int x=0;
		for(iter_p; iter_p != b.end(); iter_p++){
			if(x<=a.size()){
			//cout<<" "<<iter_p->end;
			//vector <vector <int> >::iterator iter_l = a.begin();
				print_vec(iter_p->code);
				for(int y=0;y<a.at(x).size();y++){
					cout<<"  "<<a.at(x).at(y)<<"  ";	
				}
			cout<<endl;	
			x++;	
			}
				cout<<endl;
		}	
	
}

int straight(vector <vector <int> > a,int num){//算從mean看有幾個1(垂直方向 
	int count=0;
	for(int x=0;x<a.size();x++){
		if(a.at(x).at(num)==1){
			count++;
		}
		//cout<<a.at(x).at(num);
		if(x==a.size()-1){
			//cout<<endl;
		}
		//else cout<<" ";	
	}		
return count;
}

int straight_where(vector <vector <int> > a,int num){//如果只有一個1的話要看哪裡 
	int where=0;
	for(int x=0;x<a.size();x++){
		if(a.at(x).at(num)==1){
			where=x;
	}
	}		
return where;
}

vector<int> traverse_where(vector <vector <int> > a,int num){//找從prime方向看的1在哪裡(橫向的 
	vector<int> where;
	for(int x=0;x<a.at(num).size();x++){
		if(a.at(num).at(x)==1){
			where.push_back(x);	
		}	
	}
	return where;	
}

int one_count_patric(vector <int> a,vector <int> b){//算int向量有幾個1 且MARK掉已經END的MEAN項(B是放已經END的) 
	int one_count=0;
	for (int n=0;n<a.size();n++){
		if(vec_find(b,n)==0 && a.at(n)==1){
			one_count++;	
		}
	}
	return one_count;
} 


int main(/*int argc, char *argv[]*/) {
ifstream inFile(/*argv[1]*/"C:\\Users\\User\\Desktop\\test1.eqn",ios::in);
string line;
fstream outfile;
outfile.open(/*argv[2]*/"C:\\Users\\User\\Desktop\\PA3answer1.eqn",ios::out);//ios::out檔案不在的話創造檔案
string outname;

	if(inFile.fail()){
		cout<<"error";//如果無法開啟輸入檔案輸出錯誤字樣
	}
 	else{//可以開檔案的狀況下
 		int line_count=1;
 		string line;
 		int counter=0;
 		int counter_p=0;
 		int count=0;
 		int read_done=0;
 		int primedone=0;
 		int done=0;
 		int in_num;

 		
		while(getline(inFile,line)) {
			
			if(line_count==1){
				string A;
				cout<<line<<endl;
				outfile<<line<<endl;
				A =line.substr(line.find("=")+2,line.find(";")-line.find("=")-2);
				//cout<<"A="<<A<<endl;
				in_num=inorder_count(A);
				//cout<<"in_num="<<in_num<<endl;
				line_count++;
			}
			else if(line_count==2){
				outname=line.substr(line.find("=")+2,line.find(";")-line.find("=")-2);
				cout<<line<<endl;
				outfile<<line<<endl;
				//cout<<"outname="<<outname<<endl;
				line_count++;
			}
			else {
				//cout<<"OUT=   "<<line<<endl;
				string A;
				string word;
				A =line.substr(line.find_first_of("("),line.find_last_of(")"));
				//cout<<"A="<<A<<endl;
				while(A.find(')')!=string::npos){
							string words;
							words =A.substr(A.find_first_of("(")+1,A.find_first_of(")")-A.find_first_of("(")-1);
							//cout<<words<<endl;
							contain[counter].word=words;
							contain[counter].primary=0;
							spilt_and_convert(words,counter);
							//cout<<"counter="<<counter<<endl;
							counter++;//從零開始算 
							if(A.find('+')!=string::npos){
								A=A.substr(A.find(")", 0)+2);
								//cout<<"A="<<A<<endl;
							}
							else{
								A.clear();
							}
							
				}
				read_done=1;
			}
				
			}
			
			int row=0;
		
		while(read_done==1&&primedone==0){	
			int diff,diff_average;
			int next_row_num;
			int now_row_num;
			if(row==0){
				now_row_num=counter;
				next_row_num=0;
			}
			else{
				now_row_num=next_row_num;
				next_row_num=0;
			}
			/*cout<<"row="<<row<<endl;
			cout<<"row%2="<<row%2<<endl;
			cout<<"now_row_num="<<now_row_num<<endl;
			cout<<"next_row_num="<<next_row_num<<endl;	*/
			

					
			if(row%2==0){
				
			for(int j=0;j<now_row_num;j++){
				contain[j].how_many1=one_count(contain[j].code);
				//print_vec(contain[j].code);
				//cout<<"  contain["<<j<<"]="<<contain[j].how_many1<<endl;
			}
	
			//	for(int i=0;i<in_num-row;i++){
					for(int j=0;j<now_row_num;j++){
						diff_average=0;
					//	if(contain[j].how_many1==i){
							for(int k=0;k<now_row_num;k++){
								diff=0;
								if(contain[k].how_many1==contain[j].how_many1+1||contain[k].how_many1==contain[j].how_many1-1){
									diff=compare(contain[j].code,contain[k].code);
								if(diff_average==1){
									diff_average=1;
								}
								else if(diff==0 && diff_average==0){
									diff_average=0;		
								}
								else if(diff==1){
									diff_average=1;
								}
							}
							vector <int> next_row;
							if(diff==0){
									//cout<<diff<<" ";
									//print_vec(contain[j].code);
									/*for (int n=0;n<contain[j].code.size();n++){
										cout<<contain[j].code.at(n);
									}*/
									//cout<<endl;
								}
								else {
									/*cout<<diff<<" ";
									print_vec(contain[j].code);
									cout<<",";
									print_vec(contain[k].code);
									cout<<",";*/
									if(diff==1){
										next_row=change(contain[j].code,contain[k].code);
										//print_vec(next_row);
										if(save_or_not(next_row,next_row_num,1)==1){
											contain2[next_row_num].code=next_row;
											next_row_num++;	
										}
										
									}
									//cout<<endl;
								}							
							
						}
						
						
						
						if (diff_average==0){
						//cout<<"       ";
						//print_vec(contain[j].code);
						//cout<<" "<<diff_average<<" "<<counter_p<<endl;
						contain[j].primary=1;			
					}
				//	}
					
				}
		//	}
				
		/*	cout<<endl<<endl; 
			cout<<"contain_now:"<<endl;
			for(int i=0;i<now_row_num;i++){
				print_vec(contain[i].code);
				/*for (int n=0;n<contain[i].code.size();n++){
					cout<<contain[i].code.at(n);
				}			
				//cout<<" "<<contain[i].primary<<endl;				
			}*/
			
		
			
		/*	cout<<endl;
			cout<<"contain_next:"<<endl;
			for(int i=0;i<next_row_num;i++){
				print_vec(contain2[i].code);
				/*for (int n=0;n<contain2[i].code.size();n++){
					cout<<contain2[i].code.at(n);
				}			
				cout<<" "<<contain2[i].primary<<endl;				
			}*/
				
			for(int i=0;i<now_row_num;i++){
				if(contain[i].primary==1){
					primary[counter_p].code=contain[i].code;
					master_prime.marker=0;
					master_prime.code=contain[i].code;
					prime.push_back(master_prime);
					counter_p++;		
				}		
			}
			

			if(count_end(now_row_num,row%2)==1){
				primedone=1;
			}
						clean(now_row_num,1);	
			}
			
			
			
			else if(row%2==1){
			//cout<<"2"<<endl;
			
			for(int j=0;j<now_row_num;j++){
				contain2[j].how_many1=one_count(contain2[j].code);
				//print_vec(contain2[j].code);
				//cout<<"  contain2["<<j<<"]="<<contain2[j].how_many1<<endl;
			}
			
			
					for(int j=0;j<now_row_num;j++){
						diff_average=0;
						//if(contain2[j].how_many1==i){
							for(int k=0;k<now_row_num;k++){
								diff=0;
								if(contain2[k].how_many1==contain2[j].how_many1+1||contain2[k].how_many1==contain2[j].how_many1-1){
									diff=compare(contain2[j].code,contain2[k].code);
									//print_vec(contain2[j].code);
									//cout<<",";
									//print_vec(contain2[k].code);
									//cout<<" "<<diff<<endl;
									vector <int> next_row;
									if(diff==0){
								//	cout<<diff<<" ";
								//	print_vec(contain2[j].code);
									/*for (int n=0;n<contain[j].code.size();n++){
										cout<<contain[j].code.at(n);
									}*/
									//cout<<endl;
								}
								else {
								/*	cout<<diff<<" ";
									print_vec(contain2[j].code);
									cout<<",";
									print_vec(contain2[k].code);*/
									
									if(diff==1){
										next_row=change(contain2[j].code,contain2[k].code);
										//print_vec(next_row);
										if(save_or_not(next_row,next_row_num,2)==1){
										contain[next_row_num].code=next_row;
										next_row_num++;
									}
									}
									//cout<<endl;
								}	
	
								if(diff_average==1){
									diff_average=1;
								}
								else if(diff==0 && diff_average==0){
									diff_average=0;		
								}
								else if(diff==1){
									diff_average=1;
								}
							}						
							
						}
						
						
						if (diff_average==0){
						//cout<<"       ";
						//print_vec(contain2[j].code);
						//cout<<" "<<diff_average<<" "<<counter_p<<endl;
						contain2[j].primary=1;			
					}
					//}
					
				}
				
			/*cout<<endl<<endl; 
			cout<<"contain_now:"<<endl;
			for(int i=0;i<now_row_num;i++){
				print_vec(contain2[i].code);
				/*for (int n=0;n<contain[i].code.size();n++){
					cout<<contain[i].code.at(n);
				}				
				cout<<" "<<contain2[i].primary<<endl;				
			}*/
			
			/*cout<<endl;
			cout<<"contain_next:"<<endl;
			for(int i=0;i<next_row_num;i++){
				print_vec(contain[i].code);
				/*for (int n=0;n<contain2[i].code.size();n++){
					cout<<contain2[i].code.at(n);
				}			
				cout<<" "<<contain[i].primary<<endl;				
			}*/
				
			for(int i=0;i<now_row_num;i++){
				if(contain2[i].primary==1){
					primary[counter_p].code=contain2[i].code;
					master_prime.marker=0;
					master_prime.code=contain2[i].code;
					prime.push_back(master_prime);
					counter_p++;		
				}		
			}
			if(count_end(now_row_num,row%2)==1){
				primedone=1;
			}	
			clean(now_row_num,2);

			}
			row++;
			count++;
			
			//cout<<"counter_p="<<counter_p<<endl;
			//cout<<"primary:"<<endl;
			for(int i=0;i<counter_p;i++){
				/*	cout<<i<<" "; 
					print_vec(primary[i].code);
					cout<<endl;	*/	
				}		


		/*	if(count==3){
				done=1;
			}*/
			
			//cout<<endl<<endl;
		}
			
			
	int count1=0;
	while(read_done==1&&primedone==1&&done==0){
		int step=0;
		vector <int> meanmean;
		vector <vector <int> > list;
					vector<Prime>::iterator iter_p = prime.begin();
								vector<Mean>::iterator iter_m = mean.begin();
		//vector <Mean> mean;
		//vector <Prime> prime;
			/*cout<<"mean:"<<endl;

			for(iter_m; iter_m != mean.end(); iter_m++){
				print_vec(iter_m->code);
				cout<<" "<<iter_m->end<<endl;
			}
			cout<<"prime:"<<endl;

			for(iter_p; iter_p != prime.end(); iter_p++){
				print_vec(iter_p->code);
				cout<<" "<<iter_p->marker<<endl;
			}*/ 
			
			
			for(iter_p=prime.begin(); iter_p != prime.end(); iter_p++){	
				vector <int> c;
				vector <int> p;
				vector <int> m;
				p=iter_p->code;
				for(iter_m=mean.begin(); iter_m != mean.end(); iter_m++){
					m=iter_m->code;
					/*print_vec(p);
					cout<<" ";
					print_vec(m);
					cout<<" ";
					cout<<compare_and_ignore(p,m)<<endl;*/
					c.push_back(compare_and_ignore(p,m));
			}
				list.push_back(c);
				c.clear();
		}
			
		print_list(list,prime,mean,in_num);
		
		if(step==0){
		for(int x;x<mean.size();x++){//把只有一個的MARK起來 
		int where=0;
		iter_p=prime.begin();
		iter_m=mean.begin();
			if(straight(list,x)==1){
				where=straight_where(list,x);
				//cout<<x<<endl;
				//cout<<where<<endl;
				if(vec_find(meanmean,x)==0){
				meanmean.push_back(x);
				}

				iter_p=iter_p+where;
				iter_p->marker=1;
				iter_m=iter_m+x;
				iter_m->end=1;
			}
		}
			
			step=1;
		}

		
		if(step==1){
			for(int x=0;x<prime.size();x++){//把mark起來的蓋到的end掉 
			vector <int> wh;
			iter_p=prime.begin();
			iter_m=mean.begin();
			wh=traverse_where(list,x);
			//print_vec(wh);
			for(int y=0;y<wh.size();y++){
				if(vec_find(meanmean,wh.at(y))==0){
					meanmean.push_back(wh.at(y));
				}
				iter_m=mean.begin()+wh.at(y);
				iter_m->end=1;
			}
		}
				step=2;	
		}
			/*cout<<"meanmean=";
			print_vec(meanmean);
			cout<<endl;*/ 

		if(done_OX()!=1 && step==2){
			iter_p=prime.begin();
			iter_m=mean.begin();
			vector <int> large;
			vector <int> wh;
			int large_one=0;
			int large_num=0;
			int comp;
			int co=0;

			for(iter_p=prime.begin(); iter_p != prime.end(); iter_p++){
				if(iter_p->marker==0){
					comp = one_count_patric(list.at(co),meanmean);	
					
					if(comp>large_num){
					large_num=comp;
					large=list.at(co);
					large_one=co;
					}
				}
			co++;
			}
			wh=traverse_where(list,co);
			for(int y=0;y<wh.size();y++){	
				if(vec_find(meanmean,wh.at(y))==0){
						meanmean.push_back(wh.at(y));
				}			
				iter_m=mean.begin()+wh.at(y);
				iter_m->end=1;
				iter_p=prime.begin()+co;
				iter_p->marker=1;
			}
			
		}
		
		
		/*int k;
		int where;*/

		/*k=straight(list,1);
		cout<<k<<endl;
		where=straight_where(list,1);
		cout<<where<<endl;
			vector <int> wh;
			iter_p=prime.begin();*/

			/*wh=traverse_where(list,3);
			print_vec(wh);
			for(int y=0;y<wh.size();y++){
				iter_m=mean.begin()+wh.at(y);
				iter_m->end=1;
			}*/
		//cout<<endl;
		

		
		
		//traverse(list,1);



		mean_done();
		prime_done();
		done=done_OX();


			count1++;
			/*if(count1==1){
				done=1;
			}*/

		}	
	
	vector<Prime>::iterator iter_p = prime.begin();
	int P_count=0;
	for(iter_p=prime.begin(); iter_p != prime.end(); iter_p++){	
		if(iter_p->marker==1){
			P_count++;
		}
	}
	
	
	/*for (int n=0;n<s.size();n++){
			cout<<s.at(n);
	}*/
	
	cout<<endl;
	string t;
	string l;
	cout<<outname<<" = ";
	outfile<<outname<<" = ";
	//vector<Prime>::iterator iter_p = prime.begin();
	int ii=0;
	for(iter_p=prime.begin(); iter_p != prime.end(); iter_p++){	
	 

		if(iter_p->marker==1){
		cout<<"(";	
		outfile<<"(";
		l=change_to_word(iter_p->code,s);
		cout<<l;
		ii++;
		outfile<<l;
		if(ii==P_count){
			cout<<")";	
			outfile<<")";
		}
		else{
			cout<<")+";	
			outfile<<")+";
		}
			
		}

			}
			
			cout<<endl;
			
	/*	cout<<outname<<" = ";
	for(int i=0;i<counter_p;i++){
		//cout<<i<<" "; 
		//print_vec(primary[i].code);
		//cout<<endl;
		cout<<"(";	
		outfile<<"(";
		t=change_to_word(primary[i].code,s);
		cout<<t;
		outfile<<t;
		if(i==counter_p-1){
			cout<<")";	
			outfile<<")";
		}
		else{
			cout<<")+";	
			outfile<<")+";
		}
	}	*/

	
	
	}//開啟檔案的ELSE結尾
	//outfile.close();//把輸出的檔案關起來
	inFile.close();//把輸入的檔案關起來

  	return 0;
}
