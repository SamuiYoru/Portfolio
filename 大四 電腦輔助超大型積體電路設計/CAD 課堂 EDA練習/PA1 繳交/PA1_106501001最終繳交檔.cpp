#include <iostream>
#include <fstream>
#include <string>
#include <sstream>//用istringstream
#include <stdlib.h>// 把STR轉整數

using namespace std;

int main(int argc, char *argv[]) {
ifstream inFile(argv[1],ios::in);
string line;
fstream outfile;
outfile.open(argv[2],ios::out);//ios::out檔案不在的話創造檔案
string modul_name;
string word,words;
int in,out,inv,gate;
int i=1;//輸入行數
int r=1;
string inarr[3000];//存input部分資料
string outarr[3000];//存optput部分資料
string wirearr[3000];//存wire部分資料
string linearr[3000];//gate的輸出部分
int catergory[3000];//存gate種類資料
string l[10000];//存接線資料 //array_count
int linecount[3000];//存總共有幾個輸入
int array_count=0;// 接線累加變數
int g=0;//輸出部分GATE變數
int x=0;//數WIRE數量

	if(inFile.fail()){
		cout<<"error";//如果無法開啟輸入檔案輸出錯誤字樣
	}
 	else{//可以開檔案的狀況下

		while(getline(inFile,line)) {//讀行
			if(line.empty()==1){//如果是空白的話也輸出空白(確認用
			}
  			else{
		  			if (i==1){//module name
						modul_name=line.substr(2); //存進modul_name
						i++;
					}
					else if(i==2){//in參數
						in=atoi (line.substr(2,line.find("i", 0)-1-line.find(" ", 0)).c_str());
						i++;
					}
					else if(i==3){//out參數
						out=atoi (line.substr(2,line.find("o", 0)-1-line.find(" ", 0)).c_str());
						i++;
					}
					else if(i==4){//inv參數
						inv=atoi (line.substr(2,line.find("i", 0)-1-line.find(" ", 0)).c_str());//轉成整數
						i++;
					}
					else if(i==5){//gate參數
						gate=atoi (line.substr(2,line.find("g", 0)-1-line.find(" ", 0)).c_str());//轉成整數
						i++;
					}
          else if(i==5+1){
            i++;
          }
					else if(i>5+1&&i<=5+1+in){//input
		        inarr[i-6]=line.substr(line.find("(", 0)+1,line.find(")", 0)-1-line.find("(", 0));
						i++;
					}
          else if(i==5+1+in+1){
          	i++;
          }
					else if(i>5+1+in+1&&i<=5+in+out+1+1){//output
	           istringstream B(line.substr(line.find("(", 0)+1,line.find(")", 0)-1-line.find("(", 0)));
						 getline(B,word,')');//取)前面
						 outarr[i-(5+1+in+1)]=line.substr(line.find("(", 0)+1,line.find(")", 0)-1-line.find("(", 0));//存進ARRAY中
 						 i++;
					}
          else if(i==5+in+out+1+1+1){
           	i++;
          } 
					else if(i>5+in+out+1+1+1&&i<=5+in+out+gate+inv+3){
						istringstream F(line.substr(line.find("=", 0)+2,line.find("(", 0)-1-line.find("=", 0)+2));//先辨認種類
						getline(F,word,'(');
						int cate=0;

						if(word=="NAND") {
            				cate=1;
	            			catergory[r]=cate;
    	        			r++;
						}

						else if(word=="inv") {
            				cate=2;
            				catergory[r]=cate;
    	        			r++;
						}
						else if(word=="AND") {
            				cate=3;
            				catergory[r]=cate;
            				r++;
						}
						else if(word=="NOR") {
    	        			cate=4;
            				catergory[r]=cate;
            				r++;
						}
						else if(word=="XOR") {
        	    			cate=5;
            				catergory[r]=cate;
            				r++;
						}
						else if(word=="NOT") {
            				cate=6;
            				catergory[r]=cate;
            				r++;
						}
						else if(word=="BUFF") {
    	        			cate=7;
            				catergory[r]=cate;
            				r++;
						}
						else if(word=="OR") {
            				cate=8;
            				catergory[r]=cate;
        	    			r++;
						}
    		    else cout<<"無法辨認的GATE種類"<<endl;

						linearr[i-(5+in+out+1+1+1)]=line.substr(0,line.find(" "));
						string A;
						int count=0;
						int z=1,test=0;//Z和OUT有關，TEST測試是否一樣(TEST=1為有相同)
						while(test==0&&z<=out){//比較輸入輸出的線路名稱是不是相同，辨識出WIRE部分
							if(test==0&&linearr[i-(5+in+out+1+1+1)]==outarr[z]){
								test=1;
						  }
							z++;
						}

						if (test==0){//沒有一樣的話才存進去linearray
							wirearr[x]=linearr[i-(5+in+out+1+1+1)];
							x++;
							//	test=1;
						}
						istringstream T(line.substr(line.find("(", 0)+1));
						getline(T,word,')');
						A =word.substr();
						while(A.find(',')!=string::npos){//找到新的逗號(還沒結束要繼續做 A是剩下的 H是要存起來的
							istringstream H(A.substr());
							getline(H,words,',');
							l[array_count]=words;
							A =A.substr(A.find(",", 0)+2);
							count++;
							array_count++;
						}
						l[array_count]=A;
						count++;
						array_count++;
						linecount[i-(5+in+out+1+1+1)]=count;
						i++;

					} //gate判斷的結尾括號
			}//else的結尾括號
		} //讀行的while結尾

						//輸出

		//cout<<"module "<<modul_name<<"(";// module部分輸出
		outfile<<" `timescale 1ns/1ps"<<endl<<endl;
		outfile<<"module "<<modul_name<<" (";
 		int j=1;// inarr參數
		while (j<=in){
			//cout<<"N"<<inarr[j]<<",";
			outfile<<"N"<<inarr[j]<<",";
			j++;
		}
		j=1;//outarr參數
  		while (j<=out){
			//cout<<"N"<<outarr[j];
			outfile<<"N"<<outarr[j];
  			if (j<out) {
			  	//cout<<",";
			  	outfile<<",";
			}
			else{
				//out<<");"<<endl;
				outfile<<");"<<endl;
			}
	  		j++;
		}

		outfile<<endl;

		j=1;
  		outfile<<"input ";
  		while (j<=in){
	  		outfile<<"N"<<inarr[j];
	  		if (j<in) {
			  	outfile<<",";
			}
			else {
				outfile<<";"<<endl;
			}
	  		j++;
		}

		outfile<<endl;

		j=1;
  		outfile<<"output ";
  		while (j<=out){
	  		outfile<<"N"<<outarr[j];
	  		if (j<out) {
			  	outfile<<",";
			}
			else{
				outfile<<";"<<endl;
			}
	  		j++;
		}

		outfile<<endl;
		j=0;
		outfile<<"wire ";
  		while (j<x){
			outfile<<"N"<<wirearr[j];
	  		if (j<x-1){
			  	outfile<<",";
			  }
			else{
				outfile<<";"<<endl;
			}
	  		j++;
		}

		outfile<<endl;

		int q=1;
		j=1;
		int gate_number=1;
		while (gate_number<=inv+gate){
			if (catergory[gate_number]==1){//NAND
				outfile<<"nand NAND"<<linecount[q]<<"_"<<gate_number<<" (";
				}
			else if (catergory[gate_number]==2){//inv
				outfile<<"inv INV"<<linecount[q]<<"_"<<gate_number<<" (";
				}
			else if (catergory[gate_number]==3){//AND
			    outfile<<"and AND"<<linecount[q]<<"_"<<gate_number<<" (";
			    }
			else if (catergory[gate_number]==4){//NOR
				outfile<<"nor NOR"<<linecount[q]<<"_"<<gate_number<<" (";
				}
			else if (catergory[gate_number]==5){//XOR
				outfile<<"xor XOR"<<linecount[q]<<"_"<<gate_number<<" (";
				}
			else if (catergory[gate_number]==6){//NOT
				outfile<<"not NOT"<<linecount[q]<<"_"<<gate_number<<" (";
				}
			else if (catergory[gate_number]==7){//BUFF
				outfile<<"buf BUFF"<<linecount[q]<<"_"<<gate_number<<" (";
				}
			else if (catergory[gate_number]==8){//OR
				outfile<<"or OR"<<linecount[q]<<"_"<<gate_number<<" (";
				}
			else{
				outfile<<"gate="<<catergory[gate_number]<<endl;
			}

			outfile<<"N"<<linearr[q]<<", ";
			for(int co=0;co<linecount[q];co++){
				outfile<<"N"<<l[g];
				if(co<linecount[q]-1){
					outfile<<", ";
					}
				else{
					outfile<<")";
				}
				g++;
			}

			outfile<<";"<<endl;
			q++;
			gate_number++;
		}

		outfile<<endl;
		outfile<<"endmodule";
	}//開啟檔案的ELSE結尾
	outfile.close();//把輸出的檔案關起來
	inFile.close();//把輸入的檔案關起來

  	return 0;
}
