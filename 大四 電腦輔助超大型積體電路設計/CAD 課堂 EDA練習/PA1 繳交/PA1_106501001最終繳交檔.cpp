#include <iostream>
#include <fstream>
#include <string>
#include <sstream>//��istringstream
#include <stdlib.h>// ��STR����

using namespace std;

int main(int argc, char *argv[]) {
ifstream inFile(argv[1],ios::in);
string line;
fstream outfile;
outfile.open(argv[2],ios::out);//ios::out�ɮפ��b���ܳгy�ɮ�
string modul_name;
string word,words;
int in,out,inv,gate;
int i=1;//��J���
int r=1;
string inarr[3000];//�sinput�������
string outarr[3000];//�soptput�������
string wirearr[3000];//�swire�������
string linearr[3000];//gate����X����
int catergory[3000];//�sgate�������
string l[10000];//�s���u��� //array_count
int linecount[3000];//�s�`�@���X�ӿ�J
int array_count=0;// ���u�֥[�ܼ�
int g=0;//��X����GATE�ܼ�
int x=0;//��WIRE�ƶq

	if(inFile.fail()){
		cout<<"error";//�p�G�L�k�}�ҿ�J�ɮ׿�X���~�r��
	}
 	else{//�i�H�}�ɮת����p�U

		while(getline(inFile,line)) {//Ū��
			if(line.empty()==1){//�p�G�O�ťժ��ܤ]��X�ť�(�T�{��
			}
  			else{
		  			if (i==1){//module name
						modul_name=line.substr(2); //�s�imodul_name
						i++;
					}
					else if(i==2){//in�Ѽ�
						in=atoi (line.substr(2,line.find("i", 0)-1-line.find(" ", 0)).c_str());
						i++;
					}
					else if(i==3){//out�Ѽ�
						out=atoi (line.substr(2,line.find("o", 0)-1-line.find(" ", 0)).c_str());
						i++;
					}
					else if(i==4){//inv�Ѽ�
						inv=atoi (line.substr(2,line.find("i", 0)-1-line.find(" ", 0)).c_str());//�ন���
						i++;
					}
					else if(i==5){//gate�Ѽ�
						gate=atoi (line.substr(2,line.find("g", 0)-1-line.find(" ", 0)).c_str());//�ন���
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
						 getline(B,word,')');//��)�e��
						 outarr[i-(5+1+in+1)]=line.substr(line.find("(", 0)+1,line.find(")", 0)-1-line.find("(", 0));//�s�iARRAY��
 						 i++;
					}
          else if(i==5+in+out+1+1+1){
           	i++;
          } 
					else if(i>5+in+out+1+1+1&&i<=5+in+out+gate+inv+3){
						istringstream F(line.substr(line.find("=", 0)+2,line.find("(", 0)-1-line.find("=", 0)+2));//����{����
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
    		    else cout<<"�L�k��{��GATE����"<<endl;

						linearr[i-(5+in+out+1+1+1)]=line.substr(0,line.find(" "));
						string A;
						int count=0;
						int z=1,test=0;//Z�MOUT�����ATEST���լO�_�@��(TEST=1�����ۦP)
						while(test==0&&z<=out){//�����J��X���u���W�٬O���O�ۦP�A���ѥXWIRE����
							if(test==0&&linearr[i-(5+in+out+1+1+1)]==outarr[z]){
								test=1;
						  }
							z++;
						}

						if (test==0){//�S���@�˪��ܤ~�s�i�hlinearray
							wirearr[x]=linearr[i-(5+in+out+1+1+1)];
							x++;
							//	test=1;
						}
						istringstream T(line.substr(line.find("(", 0)+1));
						getline(T,word,')');
						A =word.substr();
						while(A.find(',')!=string::npos){//���s���r��(�٨S�����n�~�� A�O�ѤU�� H�O�n�s�_�Ӫ�
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

					} //gate�P�_�������A��
			}//else�������A��
		} //Ū�檺while����

						//��X

		//cout<<"module "<<modul_name<<"(";// module������X
		outfile<<" `timescale 1ns/1ps"<<endl<<endl;
		outfile<<"module "<<modul_name<<" (";
 		int j=1;// inarr�Ѽ�
		while (j<=in){
			//cout<<"N"<<inarr[j]<<",";
			outfile<<"N"<<inarr[j]<<",";
			j++;
		}
		j=1;//outarr�Ѽ�
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
	}//�}���ɮת�ELSE����
	outfile.close();//���X���ɮ����_��
	inFile.close();//���J���ɮ����_��

  	return 0;
}
