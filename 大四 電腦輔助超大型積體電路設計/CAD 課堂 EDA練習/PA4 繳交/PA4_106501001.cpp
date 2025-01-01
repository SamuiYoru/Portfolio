#include <iostream>
#include <fstream>
#include <string>
#include <sstream>//用istringstream
#include <stdlib.h>//把STR轉整數
#include <vector> 
#include <cstdlib>//亂數用 
#include<iomanip>
#include<ctime>
#include <math.h>//開根號SQRT 
#include <time.h>
#include<algorithm>

using namespace std;

vector <string> E;
vector <string> best;
vector <string> NE;//新的E 

typedef struct {
	int code;
	int area;
	double width;
	double high;
	double lowleft_x;
	double lowleft_y;
}BLOCK;

BLOCK block[1000];

typedef struct {
	vector <string> name;
	double width;
	double high; 
	double lowleft_x;
	double lowleft_y;
}LEAF;

vector <LEAF>  leaf;
LEAF master_leaf;


double bounder(double x,int area){
	double a;
	double upper_bound;
	double lower_bound;
	
	upper_bound=sqrt(area/0.8);
	lower_bound=sqrt(area/1.7);
	//cout<<"upper_bound="<<upper_bound<<endl;
	//cout<<"lower_bound="<<lower_bound<<endl;
	
	if(x<=upper_bound&&x>=lower_bound){
		a=x;
	}
	else if(x>upper_bound){
		a=upper_bound;
	}
	else{//x<lower_bound
		a=lower_bound;	
	}
	return a;
}

void bound(int area){
	double a;
	double upper_bound;
	double lower_bound;
	
	upper_bound=sqrt(area/0.5);
	lower_bound=sqrt(area/2);
	cout<<"upper_bound="<<upper_bound<<endl;
	cout<<"lower_bound="<<lower_bound<<endl;
}

void print_vec(vector <string> A){
	for(int i=0;i<A.size();i++){
		cout<<A.at(i);
		if(i!=A.size()-1){
		cout<<" ";
		}
	}
	cout<<endl;
}

int find_first_of_vec(vector <string>A,string X){
	int pos;
	for(int i=A.size()-1;i>=0;i--){
		if(A.at(i)==X){
		pos=i;		
		}	
	}
	return pos;
}

void xy_change(vector <string> E,double x,double y){
	for(int a=0;a<E.size();a++){
		if(E.at(a)!="V"&&E.at(a)!="H"){
			block[stoi(E.at(a))].lowleft_x=block[stoi(E.at(a))].lowleft_x+x;
			block[stoi(E.at(a))].lowleft_y=block[stoi(E.at(a))].lowleft_y+y;
			/*cout<<"block["<<stoi(E.at(a))<<"].code="<<block[stoi(E.at(a))].code<<endl;
			cout<<"block["<<stoi(E.at(a))<<"].high="<<block[stoi(E.at(a))].high<<endl;
			cout<<"block["<<stoi(E.at(a))<<"].width="<<block[stoi(E.at(a))].width<<endl;
			cout<<"block["<<stoi(E.at(a))<<"].lowleft_x="<<block[stoi(E.at(a))].lowleft_x<<endl;
			cout<<"block["<<stoi(E.at(a))<<"].lowleft_y="<<block[stoi(E.at(a))].lowleft_y<<endl;*/
	}
	}
}

void combine(vector <string> A){
	//cout<<"A="<<A<<":"<<endl;
	if(A.size()==3){//假設是LEAF狀態 
		string a0,a1,a2;
		a0=A[0];
		a1=A[1];
		a2=A[2];
		if(a0!="V"&&a1!="V"&&a0!="H"&&a1!="H"){
			//cout<<"leaf=";
			//print_vec(A);
			if(block[stoi(a0)].high==0||block[stoi(a1)].high==0){
				if(block[stoi(a0)].high==0){
					//計算
					double h,w;
					double area;
					area=block[stoi(a0)].area;
					w=bounder(10,area);
					h=area/w;
					block[stoi(a0)].width=double(long(w*100+0.5))/100;
					block[stoi(a0)].high=double(long(h*100+0.5))/100;
				}
				else{//block[stoi(a1)].high==0
					double h,w;
					double area;
					area=block[stoi(a1)].area;
					w=bounder(10,area);
					h=area/w;
					block[stoi(a1)].width=double(long(w*100+0.5))/100;
					block[stoi(a1)].high=double(long(h*100+0.5))/100;
				}
				combine(A);
			}	
			else{
				if(a2=="V"){
					if(block[stoi(a0)].high>block[stoi(a1)].high){
						master_leaf.high=block[stoi(a0)].high;
					}
					else{//block[stoi(a0)].high<block[stoi(a1)].high
						master_leaf.high=block[stoi(a1)].high;
					}
					block[stoi(a0)].lowleft_x=0;
					block[stoi(a0)].lowleft_y=0;
					block[stoi(a1)].lowleft_x=block[stoi(a0)].width;
					block[stoi(a1)].lowleft_y=block[stoi(a0)].lowleft_y;	
					master_leaf.width=block[stoi(a0)].width+block[stoi(a1)].width;	
				}		
				else if(a2=="H"){
					if(block[stoi(a0)].width>block[stoi(a1)].width){
						master_leaf.width=block[stoi(a0)].width;	
					}
					else{//block[stoi(a0)].width<block[stoi(a1)].width
						master_leaf.width=block[stoi(a1)].width;
					}
					block[stoi(a0)].lowleft_x=0;
					block[stoi(a0)].lowleft_y=0;
					block[stoi(a1)].lowleft_y=block[stoi(a0)].high;
					block[stoi(a1)].lowleft_x=block[stoi(a0)].lowleft_x;
					master_leaf.high=block[stoi(a0)].high+block[stoi(a1)].high;		
				}		
				else{
					master_leaf.high=0;	
					master_leaf.width=0;
				}			
			master_leaf.name=A;	
			leaf.push_back(master_leaf);
			/*cout<<"A=";
			print_vec(A);
			cout<<"block["<<stoi(a0)<<"]="<<block[stoi(a0)].lowleft_x<<" "<<block[stoi(a0)].lowleft_y<<endl;
			cout<<"         "<<block[stoi(a0)].width<<" "<<block[stoi(a0)].high<<endl;
			cout<<"block["<<stoi(a1)<<"]="<<block[stoi(a1)].lowleft_x<<" "<<block[stoi(a1)].lowleft_y<<endl;
			cout<<"         "<<block[stoi(a1)].width<<" "<<block[stoi(a1)].high<<endl;*/
			}
		}
		else if((a0=="V"||a0=="H")&&(a1!="V"&&a1!="H")&&(a2=="V"||a2=="H")){
			vector <string> v2(A.begin() , A.end()-2);
			vector <string> v3(A.begin()+1, A.end());
			combine(v2);
			combine(v3);
		}
		else {
			vector <string> v2(A.begin() , A.end()-1);
			combine(v2);
			vector <string> v3(A.begin()+2, A.end());
			combine(v3);
		}
	}
	else if(A.size()==2){
		vector <string> A1={"H","V"};
		vector <string> A2={"V","H"};
		vector <string> A3={"V","V"};
		vector <string> A4=	{"H","H"};
		if(A==A1||A==A2||A==A3||A==A4){
			vector <string> v2(A.begin(), A.end()-1);
			vector <string> v3(A.begin()+1, A.end());
			//cout<<"v2=";
			//print_vec(v2);
			//cout<<"v3=";
			//print_vec(v3);
			combine(v2);
			combine(v3);
		}
		else{
			vector <string> x;
			if(block[stoi(A.at(0))].high==0){
					double w,h;
					double area;
					area=block[stoi(A.at(0))].area;
					w=bounder(10,area);
					h=area/w;
					block[stoi(A.at(0))].width=double(long(w*100+0.5))/100;
					block[stoi(A.at(0))].high=double(long(h*100+0.5))/100;	
					combine(A);
				}
				else{
					//cout<<"A="<<A.at(1)<<endl;

					//cout<<"block1=";
					//print_vec(leaf.back().name);
					x=leaf.back().name;
					//cout<<"block2="<<A.at(0)<<endl;
					x.insert(x.end(),A.begin(),A.end());
					if(A.at(1)=="V"){
						double h;
						double w;
						double area;
						area=block[stoi(A.at(0))].area;
						h=bounder(leaf.back().high,area);
						w=area/h;
						block[stoi(A.at(0))].width=double(long(w*100+0.5))/100;
						block[stoi(A.at(0))].high=double(long(h*100+0.5))/100;
						block[stoi(A.at(0))].lowleft_x=leaf.back().lowleft_x+leaf.back().width;
						block[stoi(A.at(0))].lowleft_y=leaf.back().lowleft_y;
						if(leaf.back().high>block[stoi(A.at(0))].high){
							master_leaf.high=leaf.back().high;
						}
						else{//block[stoi(a0)].high<block[stoi(a1)].high
							master_leaf.high=block[stoi(A.at(0))].high;
						}	
						//block[stoi(A.at(0))].lowleft_x=leaf.back().width;
						master_leaf.width=leaf.back().width+block[stoi(A.at(0))].width;	
					}
					else if(A.at(1)=="H"){
						double h;
						double w;
						double area;
						area=block[stoi(A.at(0))].area;
						w=bounder(leaf.back().width,area);
						h=area/w;
						block[stoi(A.at(0))].width=double(long(w*100+0.5))/100;
						block[stoi(A.at(0))].high=double(long(h*100+0.5))/100;	
						block[stoi(A.at(0))].lowleft_x=leaf.back().lowleft_x;
						block[stoi(A.at(0))].lowleft_y=leaf.back().lowleft_y+leaf.back().high;
						if(leaf.back().width>block[stoi(A.at(0))].width){
							master_leaf.width=leaf.back().width;	
						}
						else{//block[stoi(a0)].width<block[stoi(a1)].width
							master_leaf.width=block[stoi(A.at(0))].width;
						}
						block[stoi(A.at(0))].lowleft_y=leaf.back().high;
						master_leaf.high=leaf.back().high+block[stoi(A.at(0))].high;	
					}
					else{
						master_leaf.high=0;	
						master_leaf.width=0;
					}
				}
			/*cout<<"A=";
			print_vec(A);
			cout<<"front block="<<leaf.back().lowleft_x<<" "<<leaf.back().lowleft_y<<endl;
			cout<<"            "<<leaf.back().width<<" "<<leaf.back().high<<endl;
			cout<<"block["<<stoi(A[0])<<"]="<<block[stoi(A[0])].lowleft_x<<" "<<block[stoi(A[0])].lowleft_y<<endl;
			cout<<"            "<<block[stoi(A[0])].width<<" "<<block[stoi(A[0])].high<<endl;*/
			leaf.pop_back();
			master_leaf.name=x;	
			leaf.push_back(master_leaf);

			//cout<<endl; 
		}	

	}
	else if(A.size()==1){
		//cout<<"A=";
		//print_vec(A);
		double x_x,x_y;
		vector <string> x,y;
		x=leaf.back().name;
		x_x=leaf.back().width;
		x_y=leaf.back().high;
		//cout<<"block1=";
		//print_vec(leaf.back().name);
		leaf.pop_back();
		y=leaf.back().name;
		x_x=leaf.back().width;
		x_y=leaf.back().high;
		/*for(int a=0;a<x.size();a++){
			if(x.at(a)!="V"&&x.at(a)!="H"){
				cout<<"block["<<stoi(x.at(a))<<"].code="<<block[stoi(x.at(a))].code<<endl;
				cout<<"block["<<stoi(x.at(a))<<"].high="<<block[stoi(x.at(a))].high<<endl;
				cout<<"block["<<stoi(x.at(a))<<"].width="<<block[stoi(x.at(a))].width<<endl;
				cout<<"block["<<stoi(x.at(a))<<"].lowleft_x="<<block[stoi(x.at(a))].lowleft_x<<endl;
				cout<<"block["<<stoi(x.at(a))<<"].lowleft_y="<<block[stoi(x.at(a))].lowleft_y<<endl;	
			}	
		}
		for(int a=0;a<y.size();a++){
			if(y.at(a)!="V"&&y.at(a)!="H"){
				cout<<"block["<<stoi(y.at(a))<<"].code="<<block[stoi(y.at(a))].code<<endl;
				cout<<"block["<<stoi(y.at(a))<<"].high="<<block[stoi(y.at(a))].high<<endl;
				cout<<"block["<<stoi(y.at(a))<<"].width="<<block[stoi(y.at(a))].width<<endl;
				cout<<"block["<<stoi(y.at(a))<<"].lowleft_x="<<block[stoi(y.at(a))].lowleft_x<<endl;
				cout<<"block["<<stoi(y.at(a))<<"].lowleft_y="<<block[stoi(y.at(a))].lowleft_y<<endl;	
			}	
		}*/
	
		y.insert(y.end(),x.begin(),x.end());
		y.insert(y.end(),A.begin(),A.end());
		//cout<<"block2=";
		//print_vec(leaf.back().name);
		leaf.pop_back();
		master_leaf.name=y;	
		leaf.push_back(master_leaf);
		//cout<<endl; 	
		if(A[0]=="V"){
			xy_change(x,x_x,0);
		}
		else{//A=="H" 
			xy_change(x,0,x_y);
		}
		//cout<<"x_x="<<x_x<<" x_y="<<x_y<<endl;

		/*for(int a=0;a<y.size();a++){
			if(y.at(a)!="V"&&y.at(a)!="H"){
				cout<<"block["<<stoi(y.at(a))<<"].code="<<block[stoi(y.at(a))].code<<endl;
				cout<<"block["<<stoi(y.at(a))<<"].high="<<block[stoi(y.at(a))].high<<endl;
				cout<<"block["<<stoi(y.at(a))<<"].width="<<block[stoi(y.at(a))].width<<endl;
				cout<<"block["<<stoi(y.at(a))<<"].lowleft_x="<<block[stoi(y.at(a))].lowleft_x<<endl;
				cout<<"block["<<stoi(y.at(a))<<"].lowleft_y="<<block[stoi(y.at(a))].lowleft_y<<endl;	
			}	
		}*/
	}
	else{//假設不是LEAF狀態 
		vector <string> b,c;
		vector <string>::iterator iterH = std::find(A.begin(), A.end(),"H"); 
		vector <string>::iterator iterV = std::find(A.begin(), A.end(),"V"); 
		if(iterH!=A.end()&&iterV!=A.end()){
			if(find_first_of_vec(A,"V")<find_first_of_vec(A,"H")){
				//cout<<"V:"<<endl;
				vector <string> v2(A.begin(), A.begin()+find_first_of_vec(A,"V")+1);
				vector <string> v3(A.begin()+find_first_of_vec(A,"V")+1, A.end());
				//print_vec(v2);
				//print_vec(v3);
				combine(v2);	
				combine(v3);	
			}
			else{
				//cout<<"H:"<<endl;
				vector <string> v2(A.begin(), A.begin()+find_first_of_vec(A,"H")+1);
				vector <string> v3(A.begin()+find_first_of_vec(A,"H")+1, A.end());
				//print_vec(v2);
				//print_vec(v3);
				combine(v2);	
				combine(v3);	
			}	
		}
		else if(iterH==A.end()&&iterV!=A.end()){//找不到H 
			//cout<<"V:"<<endl;
			vector <string> v2(A.begin(), A.begin()+find_first_of_vec(A,"V")+1);
			vector <string> v3(A.begin()+find_first_of_vec(A,"V")+1, A.end());
			//print_vec(v2);
			//print_vec(v3);
			combine(v2);	
			combine(v3);			
		}
		else if(iterH!=A.end()&&iterV==A.end()){//找不到V 
			//cout<<"H:"<<endl;
			vector <string> v2(A.begin(), A.begin()+find_first_of_vec(A,"H")+1);
			vector <string> v3(A.begin()+find_first_of_vec(A,"H")+1, A.end());
			//print_vec(v2);
			//print_vec(v3);
			combine(v2);	
			combine(v3);		
		}
	}

	
}

void print_leaf(){
	cout<<endl;
	for(int x=0;x<leaf.size();x++){
		cout<<"leaf.at("<<x<<").name=";
		print_vec(leaf.at(x).name);
		cout<<"leaf.at("<<x<<").width="<<leaf.at(x).width<<endl;
		cout<<"leaf.at("<<x<<").high="<<leaf.at(x).high<<endl;
		cout<<endl;
	}	
}

double cost(vector <string> A){
	double area;
	combine(A);
	//print_leaf();
	//cout<<"cost of "<<A<<"= ";
	//cout<<leaf.back().high*leaf.back().width<<endl;
	area=leaf.back().high*leaf.back().width;
	return area;	
}

void print(int number){
	for(int x=0;x<number;x++){
		cout<<"block["<<x<<"].code="<<block[x].code<<endl;
		cout<<"block["<<x<<"].area="<<block[x].area<<endl;
		cout<<"block["<<x<<"].high="<<block[x].high<<endl;
		cout<<"block["<<x<<"].width="<<block[x].width<<endl;
		cout<<"block["<<x<<"].lowleft_x="<<block[x].lowleft_x<<endl;
		cout<<"block["<<x<<"].lowleft_y="<<block[x].lowleft_y<<endl;
		bound(block[x].area);
		//cout<<"rate="<<block[x].high/block[x].width<<endl;
		//cout<<"rate="<<block[x].width/block[x].high<<endl;
		cout<<"area_count="<<block[x].high*block[x].width<<endl;
		cout<<endl;
	}	
}

vector <string> firstE(int number){
	vector <string> E;
	int z=0;
	for(int x=0;x<number;x++){
		E.push_back(to_string(x));	
		if(z==0){
			E=E;
			z++;
		}
		else if(z==1){
			E.push_back("V");	
			z++;
		}
		else{
			E.push_back("H");
			z=1;	
		}
	}
	return E;
}

vector <string> firstE_2(int number){
	vector <string> E;
	int z=0;
	for(int x=0;x<number;x++){
		
		if(x+1<=4){
			if(z==0||z==2){
					E.push_back(to_string(x));
			z++;
			}
			else if(z==1){
					E.push_back(to_string(x));
			E.push_back("V");	
			z++;
			}
			else if(z==3){
				E.push_back(to_string(x));
			E.push_back("H");
			E.push_back("V");
				z=0;	
			}
		}
		else{
			E.push_back(to_string(x));
		if(z==0){
			E.push_back("V");	
			z++;
		}
		else{
			E.push_back("H");
			z=1;	
		}

		}

	}
	return E;
}

vector <string> M1(vector <string> E){
	int i= rand() %E.size();
	int j= rand() %E.size();
	int m,n;
	string e0,e1;
	vector <string> NewE;
	while(E.at(i)=="V"||E.at(i)=="H"){
		//cout<<"i="<<i<<endl;
		//cout<<"E.at(i)="<<E.at(i)<<endl;
		i= rand() %E.size();
	}
	m=i;
	while(E.at(j)=="V"||E.at(j)=="H"||m==j){
		//cout<<"j="<<j<<endl;
		//cout<<"E.at(i)="<<E.at(j)<<endl;
		j= rand() %E.size();
	}
	/*cout<<"交換："<<endl;	
	cout<<"i="<<i<<endl;
	cout<<"E["<<i<<"]="<<E.at(i)<<endl;
	cout<<"j="<<j<<endl;
	cout<<"E["<<j<<"]="<<E.at(j)<<endl;*/
	n=j;
	if(i>j){//讓i比較小 
		int k;
		k=i;
		i=j;
		j=k;
	}
	e0=E.at(i);
	e1=E.at(j);
	NewE.insert(NewE.end(),E.begin(),E.begin()+i);
	NewE.push_back(e1);
	NewE.insert(NewE.end(),E.begin()+i+1,E.begin()+j);
	NewE.push_back(e0);
	NewE.insert(NewE.end(),E.begin()+j+1,E.end());
	//cout<<"Enew=";
	//print_vec(NewE);	
	return NewE;
}

vector <string> M2(vector <string> E){
	int i= rand() %E.size();
	int m,n;
	//string e0,e1;
	vector <string> NewE;
	while(E.at(i)!="V"&&E.at(i)!="H"){
		//cout<<"i="<<i<<endl;
		//cout<<"Ei="<<E.at(i)<<endl;
		i= rand() %E.size();
	}

	//cout<<"i="<<i<<endl;
	//cout<<"E["<<i<<"]="<<E.at(i)<<endl;
	if(E.at(i)=="V"){	
		NewE.insert(NewE.end(),E.begin(),E.begin()+i);
		NewE.push_back("H");
		NewE.insert(NewE.end(),E.begin()+i+1,E.end());	
	}
	else{//E[i]=H
		NewE.insert(NewE.end(),E.begin(),E.begin()+i);
		NewE.push_back("V");
		NewE.insert(NewE.end(),E.begin()+i+1,E.end());;
	}
	//cout<<"Enew=";
	//print_vec(NewE);	
	return NewE;
}

int violate(vector <string> E,int i){
	int operators=0;
	int yes=0;
	if(i==E.size()-1){
		for(int x=0;x<=i;x++){
		if(E.at(x)=="H"||E.at(x)=="V"){
			operators++;
		}	
	}
	}
	else{
		for(int x=0;x<=i+1;x++){
		if(E.at(x)=="H"||E.at(x)=="V"){
			operators++;
		}	
	}
	}

	//cout<<"i="<<i<<endl;
	//cout<<"operators="<<operators<<endl;
	//cout<<"operators*2="<<operators*2<<endl;
	if(operators*2<i){
		yes=0;
	}
	else{
		yes=1;
	}
	return yes;
}

vector <string> M3(vector <string> E){
	int i= rand() %E.size();
	int counter=0;
	vector <string> NewE;
	string Ei,Ej,Ek;
	int v=violate(E,i);
	//cout<<"E.size()="<<E.size()<<endl;
	//Ei=E.substr(i,1);
	//Ej=E.substr(i+1,1);
	if(i<E.size()-1){
		Ek=E.at(i+1);
	}
	else{
		Ek=" ";	
	}
	if(i==0){
		Ej=" ";	
	}
	else{
		Ej=E.at(i-1);	
	}
	//cout<<"i="<<i<<endl;
	//cout<<" Ej="<<Ej<<"Ei="<<E.at(i)<<" Ek="<<Ek<<endl;
		//cout<<"violate(E,i)="<<violate(E,i)<<endl;
		while(counter<15&&((E.at(i)=="V"&&E.at(i)=="H")||(Ek!="V"&&Ek!="H")||(Ej=="H"&&Ek=="H")||v==1)){//要是英文+數字的組合才能做 ,其他要重找 
		//cout<<"retry:"<<endl;
		i= rand() %E.size();
	if(i<E.size()-1){
		Ek=E.at(i+1);
	}
	else{
		Ek=" ";	
	}
		if(i==0){
		Ej=" ";	
		}
			else{
		Ej=E.at(i-1);	
		}
		//cout<<"counter="<<counter<<endl;
		counter++;
		//cout<<"i="<<i<<endl;
		//cout<<" Ej="<<Ej<<"Ei="<<E.at(i)<<" Ek="<<Ek<<endl;
		v=violate(E,i);
		//cout<<"violate(E,i)="<<v<<endl;
	
	}

	//m=i;
	//n=i+1;

	//cout<<"E[m]="<<E.at(i)<<endl;
	//cout<<"E[n]="<<E.at(i+1)<<endl;
	if(counter==15){
		NewE=E;
	}
	else{
	Ei=E.at(i);
	Ek=E.at(i+1);
	NewE.insert(NewE.end(),E.begin(),E.begin()+i);
	NewE.push_back(Ej);
	NewE.push_back(Ei);
	NewE.insert(NewE.end(),E.begin()+i+2,E.end());
	//cout<<"Enew=";
	//print_vec(NewE);
}
	
	
	return NewE; 
		
}

void clean(int count){
	for(int q=0;q<count;q++){
		block[q].high=0;
		block[q].width=0;
		block[q].lowleft_x=0;
		block[q].lowleft_y=0;
	}
}


int main(int argc, char *argv[]) {
ifstream inFile(argv[1],ios::in);
string line;
fstream outfile;
outfile.open(argv[2],ios::out);//ios::out檔案不在的話創造檔案
string outname;
clock_t start, end;
start = clock();
double best_x;
double best_y;


	if(inFile.fail()){
		cout<<"error";//如果無法開啟輸入檔案輸出錯誤字樣
	}
 	else{//可以開檔案的狀況下
 	srand( time(NULL) );
	int doing=0;//最外面的圈能不能做 
	int MT=0;
	int M=0;
	int upHill=0;
	double T=20;//參數 
	int N;//參數 
	int repeat=1; 
	int reject=0;
	int number;
	int line_count=0;
	int read_end=0;
	int change_stop=0;
	double cost_diff=0;
	

	
	//E= ////預設 
	while(getline(inFile,line)) {
		if(line_count==0){//把STRING 轉INT 
				string A;
				A=line;
				number = stoi(A);
				//cout<<"line="<<line<<endl;
				//cout<<"number="<<number<<endl; 
				line_count++;
			}
		else {
				//cout<<"line="<<line<<endl;
				string w;
				string A;
				w=line.substr(0,line.find_first_of(" ",0));
				//cout<<"   code="<<w<<endl;
				A=line.substr(line.find_first_of(" ",0)+1,line.length()-line.find_first_of(" ",0));
				//cout<<"   area="<<A<<endl;	
				block[line_count-1].code=stoi(w);
				block[line_count-1].area=stoi(A);
				block[line_count-1].high=0;
				block[line_count-1].width=0;
				block[line_count-1].lowleft_x=0;
				block[line_count-1].lowleft_y=0;
	
				line_count++;
			}
			read_end=1;
	}
	//print(number);
	
	E=firstE_2(number);
	best=E;
	//cout<<"E=";
	print_vec(E);

	leaf.clear();
	cout<<endl;
	//cost(E);
	int count=0;
	while(read_end==1&&change_stop==0){//最外面的迴圈 ,注意一下迴圈終止方式 
		//MT=0;
		M=0;
		upHill=0;
		repeat=1;
		int cost_diff=0;
		
		while(repeat==1){//UPHILL>N,MT>2N的時候終止 
			int ran = rand() % 3;//0~2隨機
			clean(number); 
			if(ran==0){//M1
				//cout<<"x="<<ran<<endl;
				//cout<<"M1:"<<endl;
				//cout<<"E=";
				//print_vec(E);
				NE=M1(E);
			}
			else if(ran==1){//M2
				//cout<<"x="<<ran<<endl;
				//cout<<"M2:"<<endl;
				//cout<<"E=";
				//print_vec(E);
				NE=M2(E);
			}
			else if(ran==2){//M3
				//cout<<"x="<<ran<<endl;
				//cout<<"M3:"<<endl;
				//cout<<"E=";
				//print_vec(E);
				NE=M3(E);	
			}
			else {
				//大概不存在的例外 
			}
			MT=MT+1;
			/*cout<<"MT="<<MT<<endl;
			cout<<"NE=";
			print_vec(NE);
			cout<<"  costNE= "<<cost(NE)<<endl;
			cout<<"E=";
			print_vec(E);
			cout<<"  costE= "<<cost(E)<<endl;*/ 
			cost_diff=cost(NE)-cost(E);//新的比舊的好還是差 
			//cout<<"cost_diff="<<cost_diff<<endl;
	
			
			if(cost_diff<=0){//新的比較小 ※RANDOM的地方不知道怎麼寫 
				E=NE;
				if(cost(E)<cost(best)){
					best=E;
				}
			} 
			else{ //cost_diff>0//新的結果比舊的差 
				upHill=upHill+1;
				reject++; 
			 }
			 //cout<<"upHill="<<upHill<<endl;
			if(upHill>20||MT>35){//跳出第二回圈的限制 //※可以改數據 	
				repeat=0;
			} 
			//cout<<"best=";
			//print_vec(best);
			if((double)(clock() - start)>60){
			//	repeat=0;
			//大於限制時間，先輸出檔案 (然後有不一樣的話再更新一次 
			}
		} 
		count+1;
		T=0.9*T;// ※0.5部分是參數可以改 
		double re=reject;
		double MM=MT;
		double k=re/MM;//※要定義成小數 
		//double k=double(long(reject/MT*100+0.5))/100;
		//change_stop=1;
		/*cout<<"k="<<k<<endl;
		cout<<"T="<<T<<endl;
		cout<<"reject="<<reject<<endl;
		cout<<"MT="<<MT<<endl;
		cout<<"leaf=";
		print_vec(best);*/
		//cout << "time consume: " << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
		if((double)(clock() - start)/ CLOCKS_PER_SEC>10){
			//cout<<"time up"<<endl;
			change_stop=1;//大於限制時間，先輸出檔案 (然後有不一樣的話再更新一次 
		}
		if(/*count==1||*/k>0.95||T<0.2){//T<0.2是限制，然後K是算拒絕操作的比例 
			best_x=leaf.back().width;
			best_y=leaf.back().high;
			//cout<<"other"<<endl; 
		//cout<<"k="<<k<<endl;
		//cout<<"T="<<T<<endl;
			change_stop=1;//跳出第一迴圈 	
		}

		//print(number);
		//cout << "time consume: " << (double)(clock() - start) / CLOCKS_PER_SEC << endl;//S
	} 
	//輸出檔案 

		//cout<<endl<<endl<<endl;
		cout<<best_x<<" "<<best_y<<" "<<best_y*best_x<<endl;
		for(int x=0;x<number;x++){
		cout<<block[x].lowleft_x<<" "<<block[x].lowleft_y<<" "<<block[x].width<<" "<<block[x].high<<endl; 
		}
		print_vec(best);
		
		outfile<<best_x<<" "<<best_y<<" "<<best_y*best_x<<endl;
		for(int x=0;x<number;x++){
		outfile<<block[x].lowleft_x<<" "<<block[x].lowleft_y<<" "<<block[x].width<<" "<<block[x].high<<endl; 
		}
		for(int i=0;i<best.size();i++){
		outfile<<best.at(i);
		if(i!=best.size()-1){
		outfile<<" ";
		}
	}
	outfile<<endl;
		
	//print_leaf();
	}//開啟檔案的ELSE結尾
	inFile.close();//把輸入的檔案關起來

  	return 0;
}
