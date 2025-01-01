#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>//atoi

using namespace std;

class LinkedList;    // ���F�Nclass LinkedList�]��class ListNode��friend,
                     // �ݭn���ŧi
class ListNode{
private:
    int data;
    ListNode *next;
public:
    ListNode():data(0),next(0){}; //�w�q��1
    ListNode(int a):data(a),next(0){}; //�w�q��2

    friend class LinkedList;
};

class LinkedList{
private:
    // int size;                // size�O�ΨӰO��Linked list������, �D���n
    ListNode *first;            // list���Ĥ@��node
public:
    LinkedList():first(0){};	//���=0
    int listempty();
    void PrintList();           // �L�Xlist���Ҧ����
    void Push_front(int x);     // �blist���}�Y�s�Wnode
    void Push_back(int x);      // �blist�����ڷs�Wnode
    void Delete(int x);         // �R��list���� int x
    void Clear();               // ����list�R��
    int ListCompare(int *a,int n,int s);
    int ListCount();
    int onebyone(int x);		//X�N���X�ĴX��
    int find(int x);
};

int LinkedList::listempty(){			//�p�G�O�Ū���X0
	if (first == 0) {                      
        return 0;
    }
	else{
		return 1;
	}
}

void LinkedList::PrintList(){

    if (first == 0) {                      // �p�Gfirst node���VNULL, ���list�S�����
        //cout << "List is empty.\n";
        return;
    }

    ListNode *current = first;             // ��pointer *current�blist������
    while (current != 0) {                 // Traversal
        //cout << current->data << " ";
        current = current->next;
    }
    //cout << endl;
}

int LinkedList::ListCompare(int *a,int n,int s){
	int count=0;
    if (first == 0) {
		s=s;
    }
    ListNode *current = first;             // ��pointer *current�blist������
    while (current != 0) {                 // Traversal
        int A;

        A=current->data;
		for(int y=0;y<n;y++){
			if (a[y]==A){
				//cout<<"a=";
				s++;
				//cout<<a[y]<<" ";
			}

			else
				s=s;
		}
		current = current->next;
    }
    		//cout<<endl;
            return s;
}

int LinkedList::ListCount(){
	int count=0;
   if (first == 0) {
        count=count;
    }
    ListNode *current = first;             // ��pointer *current�blist������
    while (current != 0) {
		count++ ;           // Traversal
        current = current->next;
    }
	return count;
}

void LinkedList::Push_front(int x){

    ListNode *newNode = new ListNode(x);   // �t�m�s���O����
    newNode->next = first;                 // ����first���bnewNode�᭱
    first = newNode;                       // �A��first���VnewNode�ҫ��V���O�����m
}

void LinkedList::Push_back(int x){

    ListNode *newNode = new ListNode(x);   // �t�m�s���O����

    if (first == 0) {                      // �Ylist�S��node, �OnewNode��first
        first = newNode;
        return;
    }

    ListNode *current = first;
    while (current->next != 0) {           // Traversal
        current = current->next;
    }
    current->next = newNode;               // �NnewNode���blist������
}

void LinkedList::Delete(int x){

    ListNode *current = first,
             *previous = 0;
    while (current != 0 && current->data != x) {  // Traversal
        previous = current;                       // �p�Gcurrent���VNULL
        current = current->next;                  // �άOcurrent->data == x
    }                                             // �Y����while loop

    if (current == 0) {                 // list�S���n�R��node, �άOlist��empty
        //std::cout << "There is no " << x << " in list.\n";
         return;
    }
    else if (current == first) {        // �n�R����node��n�blist���}�Y
    	first = current->next;          // ��first����U�@��node
        delete current;                 // �p�Glist�u���@��node, ����first�N�|���VNULL
        current = 0;                    // ����гQdelete��, �N����VNULL, �i�H�קK�����nbug
         return;
    }
    else {                              // ��l���p, list�������R����node,
        previous->next = current->next; // �ӥBnode����first, ����previous����NULL
        delete current;
        current = 0;
         return;
    }
}

void LinkedList::Clear(){
    while (first != 0) {            // Traversal
        ListNode *current = first;
        first = first->next;
        delete current;
        current = 0;
    }
}

int LinkedList::onebyone(int x){ //�]��list���ઽ�����w�u��γo�Ӥ覡 
	int i=0;
    if (first == 0) {                      // �p�Gfirst node���VNULL, ���list�S�����
        //cout << "List is empty.\n";
        return 0;
    }

    ListNode *current = first;             // ��pointer *current�blist������
    while (current != 0) {                 // Traversal
		i++;

		if (current == 0) {                      // �p�Gfirst node���VNULL, ���list�S�����
        cout << "empty";
        return 0;
    	}
		while (i==x){
    	i++;
    	//cout << current->data;
    	return current->data;
	}
        current = current->next;

    }

    //cout << endl;

}

int LinkedList::find(int x){
    ListNode *current = first,
             *previous = 0;
    while (current != 0 && current->data != x) {  // Traversal
        previous = current;                       // �p�Gcurrent���VNULL
        current = current->next;                  // �άOcurrent->data == x
    }                                             // �Y����while loop
    if (current == 0) {                 //�䤣�� �^��0 
		return 0;
    }
    else {		//���N�^��1 
    	return 1;
    }
}

	LinkedList listchild[10000];
	LinkedList listmother[10000];
	LinkedList listCanDoADD;
	LinkedList listCanDoMUX;
	
typedef struct {
	int type;//NODE����
	LinkedList *child;//�llist��m 
	LinkedList *parent;//��list��m 
	int delay;//��node��delay 
	int doing;
	int done;//�����F�S 
}NODE;

	NODE node[10000];

typedef struct {
	int type;//�����A2(adder)3(mux) 
	int clk;
	int empty;//���S���� 
}Block;

	Block block_add[10000];
	Block block_mux[10000];
	
int delaycompare(int x,int y){//x�ONODE�s���A y�OLIST�ƥ�
	int delay=0;
	int b;
	for(int k=1;k<=y;k++){

		b=listchild[x].onebyone(k);//�@�����@��
		//cout<<"b="<<b<<endl;
		if (k==1){
			delay=node[b].delay;
		}
		else{
			if(delay>=node[b].delay)
				delay=delay;
			else
				delay=node[b].delay;
		}
		//cout<<"delay"<<b<<"="<<node[b].delay<<endl;
	}	
	return delay;
}

int delaymaxADD(int y){//y�OlistCanDoADD���X�Ӥ��e 
	int delay=0;
	int b;
	int max;
	for(int k=1;k<=y;k++){
		//cout<<"y="<<y<<endl;
		b=listCanDoADD.onebyone(k);//�@�����@��
		//cout<<"b="<<b<<endl;
		//cout<<"node["<<b<<"].delay="<<node[b].delay<<endl;
		if (k==1){
			delay=node[b].delay;
			max=b;
		}
		else{
			if(delay>=node[b].delay){
				delay=delay;
				max=max;
			}
			else{
				delay=node[b].delay;
				max=b;
			}
		}
	}	
	return max;
}

int delaymaxMUX(int y){//y�OlistCanDoMUX���X�Ӥ��e 
	int delay=0;
	int b;
	int max;
	for(int k=1;k<=y;k++){
		b=listCanDoMUX.onebyone(k);//�@�����@��
		//cout<<"b="<<b<<endl;
		if (k==1){
			delay=node[b].delay;
			max=b;
		}
		else{
			if(delay>=node[b].delay){
				delay=delay;
				max=max;
			}
			else{
				delay=node[b].delay;
				max=b;
			}
		}
	}	
	return b;
}

int emptyADD(int y){//Y�O���X�� 
	int empty=0;
	for(int k=1;k<=y;k++){
			if (block_add[k].empty==1){
				empty=empty+1;
			}
			else {
				empty=empty;
			}
	}
	return empty;
}

int emptyMUX(int y){//Y�O���X�� 
	int empty=0;
	for(int k=1;k<=y;k++){
			if (block_mux[k].empty==1){
				empty=empty+1;
			}
			else {
				empty=empty;
			}
	}
	return empty;
}


int main(int argc, char *argv[]) {

	ifstream inFile(/*"C:\\Users\\User\\Desktop\\testcase1"*/argv[1],ios::in);//�n��"\\"
	fstream outfile(/*"C:\\Users\\User\\Desktop\\testcase1.txt",ios::out*/argv[2],ios::out);
	//outfile.open("C:\\Users\\User\\Desktop\\PA2out_test.txt",ios::out);//ios::out�ɮפ��b���ܳгy�ɮ�
	int i=1;
	int type;
	int nodenum=1;
	int add,mux,n,m;

	
	LinkedList listDone;

	LinkedList ADD;
	LinkedList MUX;
	string line;
	string word;
	int arr[1000];
	int same=0;
	int innum=0;//�⦳�X��INPUT NODE
	int comparr[1000]={0};
	int readDone=0;
	int Done=0;
	int countzero=0;
	int u=0;//compar���Ѽ�

	if(inFile.fail()){
		cout<<"OPENING error";//�p�G�L�k�}�ҿ�J�ɮ׿�X���~�r��
	}
	
 	else{//�i�H�}�ɮת����p�U
		while(getline(inFile,line)) {//Ū��
			if(i==1){//adder
				add=atoi(line.c_str());
				//cout<<"    add="<<add<<endl;
				i++;
			}
			else if(i==2){//mux
				mux=atoi(line.c_str());
				//cout<<"    mux="<<mux<<endl;
				i++;
			}
			else if(i==3){//n nodes
				n=atoi(line.c_str());
				//cout<<"    nodes="<<n<<endl;
				i++;
			}
			else if(i==4){//m edges
				m=atoi(line.c_str());
				//cout<<"    edges="<<m<<endl;
				i++; 
			}

			else if(i>4&&i<=4+n){// node���

						string A=line.substr(line.find(" ", 0)+1,line.length()-line.find(" ", 0)-1);
						type=0;
						nodenum=atoi(line.substr(0,line.length()-line.find(" ", 0)+1).c_str());
						//cout<<"nodenum="<<nodenum<<endl;
						//cout<<"A="<<A<<endl;
						if(A=="i") {
            				type=1;
            				i++;
            				node[nodenum].type=type;
            				arr[innum]=nodenum;
            				innum++;	
						}
						else if(A=="+") {
            				type=2;
            				i++;
            				node[nodenum].type=type;
						}
						else if(A=="*") {
            				type=3;
            				i++;
            				node[nodenum].type=type;
						}
						else if(A=="o") {
    	        			type=4;
    	        			i++;
    	        			node[nodenum].type=type;
						}
	            		else cout<<"�L�k��{������"<<endl;
	            		//cout<<"  nodetype "<<nodenum<<"="<<node[nodenum].type<<endl;
			}

			else if(i>4+n&&i<=4+n+m){//edge���
			int X,Y;
			i++;
			//cout<<"edge="<<i-4-n-1<<endl;
			X=atoi(line.substr(0,line.length()-line.find(" ", 0)).c_str());//�ӷ�
			Y=atoi(line.substr(line.find(" ", 0)+1,line.length()-line.find(" ", 0)-1).c_str());//�ت��a
			//cout<<"X="<<X<<endl;
			//cout<<"Y="<<Y<<endl;
			listchild[X].Push_back(Y);
			listmother[Y].Push_back(X);
			//cout<<endl;
				if(i==4+n+m+1) {
					readDone=1;
				}
				else readDone=0;
			}

		}//Ū��WLILE���� 
		
			
			for(int k=n;k>=1;k--){//�k�s 	
				if(node[k].type==2) {//+
					node[k].done=0;
					node[k].doing=0;
					node[k].delay=delaycompare(k,listchild[k].ListCount())+1;	
				}
				else if(node[k].type==3){//*
					node[k].done=0;
					node[k].doing=0;
					node[k].delay=delaycompare(k,listchild[k].ListCount())+3;	
				} 
				else {
					node[k].doing=0;
					node[k].delay=0;
					node[k].done=1;//input output���ΰ��ҥH�w�]�O1 
					node[k].parent=&listmother[k];
					node[k].child=&listchild[k];
				}
			}
			
			for(int k=1;k<=add;k++){
				block_add[k].empty=1;//�w�]�O�Ū�
				block_add[k].type=2;//(adder)
				block_add[k].clk=0;
			}
			for(int k=1;k<=mux;k++){
				block_mux[k].empty=1;//�w�]�O�Ū�
				block_mux[k].type=3;//MUX
				block_mux[k].clk=0;
			}
	
		int same1,same2;
		int countmo;//��listmother���X�Ӥ���
		int ch;
		int dl=0;
		int del=0;
				
			/*	for (int k=1;k<=n;k++){//�ˬd��
					cout<<k<<" child= ";
					listchild[k].PrintList();
					cout<<k<<" mother= ";
					listmother[k].PrintList();
					cout<<"inarr=";
					for(int j=0;j<innum;j++){
						cout<<arr[j]<<" ";
					}
					cout<<endl;
					cout<<"compare arr=";
					for(int j=0;j<u;j++){
						cout<<comparr[j]<<" ";
					}
					cout<<endl;
					countmo=listmother[k].ListCount();//�⦳�X��
					cout<<"countmother="<<countmo<<endl;
					ch=listchild[k].ListCount();
					same1=listmother[k].ListCompare(&arr[0],innum,0);
					same2=listmother[k].ListCompare(&comparr[0],u,0);
					cout<<"same1="<<same1<<endl;
					cout<<"same2="<<same2<<endl;
					cout<<"countchild="<<ch<<endl;
					cout<<"delay="<<node[k].delay<<endl;
					cout<<endl;
				}*/

		
			int comparrcount=0;
			int canuseadd;
			int canusemux;
			int undonetask_add;
			int undonetask_mux;
			int lock=2;
			int count=0;

			LinkedList listDoingADD[1000];
			LinkedList listDoingMUX[1000];
			int time=0;
			
					//int addarr_num[300];
					int addarr_node[100][300];
					//int muxarr_num[300];
					int muxarr_node[100][300];
					int addnum=1,addcount=1;
					int muxnum=1,muxcount=1;
					int addertime;
					int muxtime;
			
			
			while(Done!=1&&readDone==1){
				//�p�� 
				//cout<<endl<<"time="<<time<<endl;	
				int emptyadd=0,emptymux=0;
				/*cout<<"comparr=";
				for(int k=0;k<u;k++){
					cout<<comparr[k]<<" ";	
			}
					cout<<endl;*/
					
				emptyadd=emptyADD(add);
				//cout<<"emptyadd="<<emptyadd<<endl;
				emptymux=emptyMUX(mux);
				//cout<<"emptymux="<<emptymux<<endl;

				for(int k=1;k<=n;k++){
					int find=0;	
					if(node[k].done==0){//�O�������~���A��֦��� 						
						same1=listmother[k].ListCompare(&arr[0],innum,0);
						same2=listmother[k].ListCompare(&comparr[0],u,0);
						count=listmother[k].ListCount();
						if(count<=(same1+same2)&&node[k].done==0&&node[k].doing==0){//�ư�IN OUT
							if(node[k].type==2){//�ݩ�ADDER 
								find=listCanDoADD.find(k);
							//	cout<<"ADD k="<<k<<endl;
								if(listCanDoADD.find(k)==0){
									listCanDoADD.Push_back(k);
								}	
							}
							else if(node[k].type==3){//�ݩ�MUX				
								find=listCanDoMUX.find(k);
								//cout<<"MUX k="<<k<<endl;
								if(listCanDoMUX.find(k)==0){
									listCanDoMUX.Push_back(k);
								}	
							}
						} 	
					}
				}
				
			/*	cout<<"listCanDoADD="; 
				listCanDoADD.PrintList();
				cout<<"listCanDoMUX="; 
				listCanDoMUX.PrintList();*/

				while(emptyadd>0){//���Ū�ADD�i�H�� 
					//cout<<"emptyadd="<<emptyadd<<endl;
					int addmax;
						for(int k=1;k<=add;k++){
						//cout<<listCanDoADD.listempty()<<endl;
						if(block_add[k].empty==1&&listCanDoADD.listempty()!=0){//listCanDoADD������(���F��i�H�� 
							//if(listCanDoADD.ListCount()>1){
								addmax=delaymaxADD(listCanDoADD.ListCount());
							//	cout<<"delaymaxADD="<<delaymaxADD(listCanDoADD.ListCount())<<endl;							
							//}
							//block_add[k].empty=0;
							emptyadd--;
							//cout<<"k ADD="<<k<<endl;
							//cout<<"addmax="<<addmax<<endl;
							//addarr_num[time]=k;
							addarr_node[k][time]=addmax;
							//cout<<"emptyadd="<<emptyadd<<endl;
							listCanDoADD.Delete(addmax);
							listCanDoADD.PrintList();
							node[addmax].done=1;
							comparr[u]=addmax;
							u++;
						}
						else if(block_add[k].empty==1&&listCanDoADD.listempty()==0){
							//addarr_num[time]=k;
							addarr_node[k][time]=0;
							emptyadd--;	
						}

					}
				
				}
				
				//while(emptymux>0){//���Ū�mux�i�H�� 
				int muxmax;
				//cout<<"test"<<endl;
				//cout<<"mux="<<mux<<endl;
					for(int k=1;k<=mux;k++){
						//cout<<listCanDoMUX.listempty()<<endl;
						if(block_mux[k].empty==1&&listCanDoMUX.listempty()!=0){//listCanDoMUX������(���F��i�H�� 
							block_mux[k].empty=0;
							block_mux[k].clk=2;
							//if(listCanDoMUX.ListCount()>1){
								muxmax=delaymaxMUX(listCanDoMUX.ListCount());
								//cout<<"delaymaxMUX="<<delaymaxMUX(listCanDoMUX.ListCount())<<endl;										
							//}
							block_mux[k].empty=0;
							emptymux--;
							muxarr_node[k][time]=muxmax;
							//cout<<"emptymux="<<emptymux<<endl;
							listCanDoMUX.Delete(muxmax);
							node[muxmax].doing=1;
						}
						else if(block_mux[k].empty==1&&listCanDoMUX.listempty()==0){
							block_mux[k].clk=1;
							block_mux[k].empty=1;
							//muxarr_num[time]=k;
							muxarr_node[k][time]=0;
							//cout<<"emptymux="<<emptymux<<endl;
							emptymux--;
						}
						else if(block_mux[k].empty==0){
							//cout<<"block_mux["<<k<<"].empty==0"<<endl;
							if(block_mux[k].clk==2&&block_mux[k].empty==0){
								//cout<<"block_mux["<<k<<"].clk=2"<<endl;
								block_mux[k].clk=1;
								block_mux[k].empty=0;
								//muxarr_num[time]=k;
								muxarr_node[k][time]=muxarr_node[k][time-1];	
							}
						else if(block_mux[k].clk==1&&block_mux[k].empty==0){
							//cout<<"last stage"<<endl;
							block_mux[k].empty=1;
							comparr[u]=muxarr_node[k][time-1];
							muxarr_node[k][time]=muxarr_node[k][time-1];
							node[muxarr_node[k][time-1]].done=1;
							u++;							
						}
					}
				}
					//�p�G���䤤�@�Ӥ��O1���ܴN�����ܦ��s
					countzero=0;
					if(time>=200){
						
						Done=1;
					}
					else{
						for(int k=1;k<=n;k++){
						if(node[k].done==0){
							countzero++;
						}
						else countzero=countzero;
					}
					//cout<<"countzero="<<countzero<<endl;
						if(countzero!=0){
								Done=0;
								time=time+1;
						}
						else Done=1;
		
					}
					
			} //WHILE����

			outfile<<time+1<<endl;
			int counter;
			int countline=time+1;
			int out[10000];
			for(int k=0;k<=time;k++){
				counter=0;
					for(int j=1;j<=mux;j++){
						if(muxarr_node[j][k]!=0){
							counter=counter+1;
					}

					}
					for(int i=1;i<=add;i++){
						if(addarr_node[i][k]!=0){
							counter=counter+1;		
						}

					}
					out[k]=counter;
				//	cout<<"out["<<k<<"]="<<out[k]<<endl;
			}
			
			for(int k=0;k<=time;k++){
				int num=out[k];
					for(int j=1;j<=mux;j++){
						if(muxarr_node[j][k]!=0){
							outfile<<muxarr_node[j][k];
							num=num-1;
							if(num!=0)
								outfile<<" ";
					}

					}
					for(int i=1;i<=add;i++){
						if(addarr_node[i][k]!=0){
						outfile<<addarr_node[i][k];
						num=num-1;
						if(num!=0)
								outfile<<" ";		
						}
					}
					countline=countline-1;
					if (countline!=0)
						outfile<<endl;
			}
		}		//else������

    return 0;
}//MAIN���� 







