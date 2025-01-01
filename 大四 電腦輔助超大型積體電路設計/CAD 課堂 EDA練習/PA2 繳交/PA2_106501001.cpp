#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>//atoi

using namespace std;

class LinkedList;    // 為了將class LinkedList設成class ListNode的friend,
                     // 需要先宣告
class ListNode{
private:
    int data;
    ListNode *next;
public:
    ListNode():data(0),next(0){}; //定義式1
    ListNode(int a):data(a),next(0){}; //定義式2

    friend class LinkedList;
};

class LinkedList{
private:
    // int size;                // size是用來記錄Linked list的長度, 非必要
    ListNode *first;            // list的第一個node
public:
    LinkedList():first(0){};	//初值=0
    int listempty();
    void PrintList();           // 印出list的所有資料
    void Push_front(int x);     // 在list的開頭新增node
    void Push_back(int x);      // 在list的尾巴新增node
    void Delete(int x);         // 刪除list中的 int x
    void Clear();               // 把整串list刪除
    int ListCompare(int *a,int n,int s);
    int ListCount();
    int onebyone(int x);		//X代表輸出第幾個
    int find(int x);
};

int LinkedList::listempty(){			//如果是空的輸出0
	if (first == 0) {                      
        return 0;
    }
	else{
		return 1;
	}
}

void LinkedList::PrintList(){

    if (first == 0) {                      // 如果first node指向NULL, 表示list沒有資料
        //cout << "List is empty.\n";
        return;
    }

    ListNode *current = first;             // 用pointer *current在list中移動
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
    ListNode *current = first;             // 用pointer *current在list中移動
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
    ListNode *current = first;             // 用pointer *current在list中移動
    while (current != 0) {
		count++ ;           // Traversal
        current = current->next;
    }
	return count;
}

void LinkedList::Push_front(int x){

    ListNode *newNode = new ListNode(x);   // 配置新的記憶體
    newNode->next = first;                 // 先把first接在newNode後面
    first = newNode;                       // 再把first指向newNode所指向的記憶體位置
}

void LinkedList::Push_back(int x){

    ListNode *newNode = new ListNode(x);   // 配置新的記憶體

    if (first == 0) {                      // 若list沒有node, 令newNode為first
        first = newNode;
        return;
    }

    ListNode *current = first;
    while (current->next != 0) {           // Traversal
        current = current->next;
    }
    current->next = newNode;               // 將newNode接在list的尾巴
}

void LinkedList::Delete(int x){

    ListNode *current = first,
             *previous = 0;
    while (current != 0 && current->data != x) {  // Traversal
        previous = current;                       // 如果current指向NULL
        current = current->next;                  // 或是current->data == x
    }                                             // 即結束while loop

    if (current == 0) {                 // list沒有要刪的node, 或是list為empty
        //std::cout << "There is no " << x << " in list.\n";
         return;
    }
    else if (current == first) {        // 要刪除的node剛好在list的開頭
    	first = current->next;          // 把first移到下一個node
        delete current;                 // 如果list只有一個node, 那麼first就會指向NULL
        current = 0;                    // 當指標被delete後, 將其指向NULL, 可以避免不必要bug
         return;
    }
    else {                              // 其餘情況, list中有欲刪除的node,
        previous->next = current->next; // 而且node不為first, 此時previous不為NULL
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

int LinkedList::onebyone(int x){ //因為list不能直接指定只能用這個方式 
	int i=0;
    if (first == 0) {                      // 如果first node指向NULL, 表示list沒有資料
        //cout << "List is empty.\n";
        return 0;
    }

    ListNode *current = first;             // 用pointer *current在list中移動
    while (current != 0) {                 // Traversal
		i++;

		if (current == 0) {                      // 如果first node指向NULL, 表示list沒有資料
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
        previous = current;                       // 如果current指向NULL
        current = current->next;                  // 或是current->data == x
    }                                             // 即結束while loop
    if (current == 0) {                 //找不到 回傳0 
		return 0;
    }
    else {		//找到就回傳1 
    	return 1;
    }
}

	LinkedList listchild[10000];
	LinkedList listmother[10000];
	LinkedList listCanDoADD;
	LinkedList listCanDoMUX;
	
typedef struct {
	int type;//NODE種類
	LinkedList *child;//子list位置 
	LinkedList *parent;//母list位置 
	int delay;//該node的delay 
	int doing;
	int done;//完成了沒 
}NODE;

	NODE node[10000];

typedef struct {
	int type;//種類，2(adder)3(mux) 
	int clk;
	int empty;//有沒有空 
}Block;

	Block block_add[10000];
	Block block_mux[10000];
	
int delaycompare(int x,int y){//x是NODE編號， y是LIST數目
	int delay=0;
	int b;
	for(int k=1;k<=y;k++){

		b=listchild[x].onebyone(k);//一次取一個
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

int delaymaxADD(int y){//y是listCanDoADD有幾個內容 
	int delay=0;
	int b;
	int max;
	for(int k=1;k<=y;k++){
		//cout<<"y="<<y<<endl;
		b=listCanDoADD.onebyone(k);//一次取一個
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

int delaymaxMUX(int y){//y是listCanDoMUX有幾個內容 
	int delay=0;
	int b;
	int max;
	for(int k=1;k<=y;k++){
		b=listCanDoMUX.onebyone(k);//一次取一個
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

int emptyADD(int y){//Y是有幾個 
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

int emptyMUX(int y){//Y是有幾個 
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

	ifstream inFile(/*"C:\\Users\\User\\Desktop\\testcase1"*/argv[1],ios::in);//要用"\\"
	fstream outfile(/*"C:\\Users\\User\\Desktop\\testcase1.txt",ios::out*/argv[2],ios::out);
	//outfile.open("C:\\Users\\User\\Desktop\\PA2out_test.txt",ios::out);//ios::out檔案不在的話創造檔案
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
	int innum=0;//算有幾個INPUT NODE
	int comparr[1000]={0};
	int readDone=0;
	int Done=0;
	int countzero=0;
	int u=0;//compar的參數

	if(inFile.fail()){
		cout<<"OPENING error";//如果無法開啟輸入檔案輸出錯誤字樣
	}
	
 	else{//可以開檔案的狀況下
		while(getline(inFile,line)) {//讀行
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

			else if(i>4&&i<=4+n){// node資料

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
	            		else cout<<"無法辨認的種類"<<endl;
	            		//cout<<"  nodetype "<<nodenum<<"="<<node[nodenum].type<<endl;
			}

			else if(i>4+n&&i<=4+n+m){//edge資料
			int X,Y;
			i++;
			//cout<<"edge="<<i-4-n-1<<endl;
			X=atoi(line.substr(0,line.length()-line.find(" ", 0)).c_str());//來源
			Y=atoi(line.substr(line.find(" ", 0)+1,line.length()-line.find(" ", 0)-1).c_str());//目的地
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

		}//讀行WLILE結束 
		
			
			for(int k=n;k>=1;k--){//歸零 	
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
					node[k].done=1;//input output不用做所以預設是1 
					node[k].parent=&listmother[k];
					node[k].child=&listchild[k];
				}
			}
			
			for(int k=1;k<=add;k++){
				block_add[k].empty=1;//預設是空的
				block_add[k].type=2;//(adder)
				block_add[k].clk=0;
			}
			for(int k=1;k<=mux;k++){
				block_mux[k].empty=1;//預設是空的
				block_mux[k].type=3;//MUX
				block_mux[k].clk=0;
			}
	
		int same1,same2;
		int countmo;//算listmother有幾個元素
		int ch;
		int dl=0;
		int del=0;
				
			/*	for (int k=1;k<=n;k++){//檢查用
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
					countmo=listmother[k].ListCount();//算有幾個
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
				//計圈 
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
					if(node[k].done==0){//是未完成才做，減少次數 						
						same1=listmother[k].ListCompare(&arr[0],innum,0);
						same2=listmother[k].ListCompare(&comparr[0],u,0);
						count=listmother[k].ListCount();
						if(count<=(same1+same2)&&node[k].done==0&&node[k].doing==0){//排除IN OUT
							if(node[k].type==2){//屬於ADDER 
								find=listCanDoADD.find(k);
							//	cout<<"ADD k="<<k<<endl;
								if(listCanDoADD.find(k)==0){
									listCanDoADD.Push_back(k);
								}	
							}
							else if(node[k].type==3){//屬於MUX				
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

				while(emptyadd>0){//有空的ADD可以做 
					//cout<<"emptyadd="<<emptyadd<<endl;
					int addmax;
						for(int k=1;k<=add;k++){
						//cout<<listCanDoADD.listempty()<<endl;
						if(block_add[k].empty==1&&listCanDoADD.listempty()!=0){//listCanDoADD不為空(有東西可以做 
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
				
				//while(emptymux>0){//有空的mux可以做 
				int muxmax;
				//cout<<"test"<<endl;
				//cout<<"mux="<<mux<<endl;
					for(int k=1;k<=mux;k++){
						//cout<<listCanDoMUX.listempty()<<endl;
						if(block_mux[k].empty==1&&listCanDoMUX.listempty()!=0){//listCanDoMUX不為空(有東西可以做 
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
					//如果有其中一個不是1的話就不能變成零
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
					
			} //WHILE結尾

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
		}		//else的結尾

    return 0;
}//MAIN結尾 







