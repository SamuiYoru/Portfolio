#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<windows.h>
#include<ctime>
#include<conio.h>

using namespace std;

int arr[21][21];
int change1 = 0, change2 = 0;//直排與橫排的檢查數 
int grade = 0;
int again=1;
void gotoxy(int, int);
void Color(int);
void checkstr();
void checkhor();
void game();
void change();
void fall();
void ptrarr();
void countTime(int);
void title();
void getscore();
void select(int, int);
void find();

void gotoxy(int xpos, int ypos)//座標位置 
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void Color(int color)//改變顏色 http://kowala21.blogspot.tw/2012/01/dev-c-console.html
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void checkstr()//直排檢查 
{
	int ch;
	for (int i = 1; i < 20; i = i + 2)
	{
		for (int j = 1; j <= 15; j = j + 2)
		{
			if (arr[i][j] == arr[i][j + 2] && arr[i][j + 2] == arr[i][j + 4])
			{
				ch = 1;
				grade = grade + 10;
				arr[i][j] = -1;
				arr[i][j + 2] = -1;
				arr[i][j + 4] = -1;
				getscore();
			}
		}
	}
	if (ch == 1)
		change1 = 1;
	else
		change1 = 0;
}

void checkhor()//橫排檢查 
{
	int ch;
	for (int i = 1; i <= 15; i = i + 2)
	{
		for (int j = 1; j < 20; j = j + 2)
		{
			if (arr[i][j] == arr[i + 2][j] && arr[i + 2][j] == arr[i + 4][j])
			{
				ch = 1;
				grade = grade + 10;
				arr[i][j] = -1;
				arr[i + 2][j] = -1;
				arr[i + 4][j] = -1;
				getscore();
			}
		}
	}
	if (ch == 1)
		change2 = 1;
	else
		change2 = 0;
}

void game()//原始矩陣 
{
	for (int i = 0; i< 21; i++)//創造一個矩陣 
	{
		for (int j = 0; j< 21; j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
				arr[i][j] = 5;
			else if (i % 2 == 0 && j % 2 != 0)
				arr[i][j] = 6;
			else if (i % 2 != 0 && j % 2 == 0)
				arr[i][j] = 7;
			else//(i%2!=0&&j%2!=0)
				arr[i][j] = rand() % 4;//0~3
		}
	}
}

void find()//尋找落單的-1 
{
	int a;
	int in;
	for (int j = 1; j< 21; j = j + 2)
	{
		for (int i = 1; i< 21; i = i + 2)
		{
			if(arr[i][j]==-1&&i!=1)
			{
				for(int a=i-2;a>0;a=a-2)
				{
					if(arr[a][j]!=-1)
					{
						in=1;
					}
				}
				
			}
			
		}
		if (in==1)
		{
			again=1;
		}
		else
		{
			again=0;
		}
	}
	
}

void change()//交換上去 
{
	find();		
	for (int j = 1; j< 21; j = j + 2)
	{
		for (int i = 1; i< 21; i = i + 2)
		{
			if (arr[i][j] == -1&&again==1)
			{
					if (i == 3)
					{
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					else if (i == 5)
					{
						arr[5][j] = arr[3][j];
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					else if (i == 7)
					{
						arr[7][j] = arr[5][j];
						arr[5][j] = arr[3][j];
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					else if (i == 9)
					{
						arr[9][j] = arr[7][j];
						arr[7][j] = arr[5][j];
						arr[5][j] = arr[3][j];
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					else if (i == 11)
					{
						arr[11][j] = arr[9][j];
						arr[9][j] = arr[7][j];
						arr[7][j] = arr[5][j];
						arr[5][j] = arr[3][j];
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					else if (i == 13)
					{
						arr[13][j] = arr[11][j];
						arr[11][j] = arr[9][j];
						arr[9][j] = arr[7][j];
						arr[7][j] = arr[5][j];
						arr[5][j] = arr[3][j];
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					else if (i == 15)
					{
						arr[15][j] = arr[13][j];
						arr[13][j] = arr[11][j];
						arr[11][j] = arr[9][j];
						arr[9][j] = arr[7][j];
						arr[7][j] = arr[5][j];
						arr[5][j] = arr[3][j];
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					else if (i == 17)
					{
						arr[17][j] = arr[15][j];
						arr[13][j] = arr[11][j];
						arr[11][j] = arr[9][j];
						arr[9][j] = arr[7][j];
						arr[7][j] = arr[5][j];
						arr[5][j] = arr[3][j];
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					else if (i == 19)
					{
						arr[19][j] = arr[17][j];
						arr[17][j] = arr[15][j];
						arr[13][j] = arr[11][j];
						arr[11][j] = arr[9][j];
						arr[9][j] = arr[7][j];
						arr[7][j] = arr[5][j];
						arr[5][j] = arr[3][j];
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					else if (i == 21)
					{
						arr[21][j] = arr[19][j];
						arr[19][j] = arr[17][j];
						arr[17][j] = arr[15][j];
						arr[13][j] = arr[11][j];
						arr[11][j] = arr[9][j];
						arr[9][j] = arr[7][j];
						arr[7][j] = arr[5][j];
						arr[5][j] = arr[3][j];
						arr[3][j] = arr[1][j];
						arr[1][j] = -1;
					}
					find();
			}
		}
	}
}

void fall()//隨機落下 
{
	for (int i = 1; i< 20; i = i + 2)//隨機落下 
	{
		for (int j = 1; j< 20; j = j + 2)
		{
			if (arr[i][j] == -1)
			{
				arr[i][j] = rand() % 4;
			}
		}
	}
}

void ptrarr()//印出矩陣 
{
	gotoxy(0, 0);
	for (int i = 0; i < 21; i++)//輸出 
	{
		for (int j = 0; j < 21; j++)
		{
			if (arr[i][j] == 5)
			{
				Color(240);
				cout << " ";
			}
			else if (arr[i][j] == 6)
			{
				Color(240);
				cout << "---" << "";
			}
			else if (arr[i][j] == 7)
			{
				Color(240);
				cout << "|" << " ";
			}
			else if (arr[i][j] == 0)
			{
				Color(249);
				cout << "★";
			}
			else if (arr[i][j] == 1)
			{
				Color(250);
				cout << "★";
			}
			else if (arr[i][j] == 2)
			{
				Color(251);
				cout << "★";
			}
			else if (arr[i][j] == 3)
			{
				Color(252);
				cout << "★";
			}
			else
			{
				cout << arr[i][j];
			}
		}
		cout << endl;
	}

	for (int m = 0; m < 21; m += 2)
	{
		Color(244);
		gotoxy(20, m);
		cout << "@";
	}
	for (int n = 0; n < 41; n += 4)
	{
		Color(244);
		gotoxy(n, 10);
		cout << "@";
	}
}


/*void counTime(int secs)
{
while (secs >= 0)
{
system("cls");
gotoxy(15, 20);
cout << "剩下 " << secs << "秒", secs--;
}
}
*/
void title()//未設定 
{


}

void getscore()//在(46,17)處印出得分 
{
	Color(244);
	gotoxy(45, 15);
	cout << "----------";
	gotoxy(45, 16);
	cout << "|        |";
	gotoxy(45, 17);
	cout << "|        |";
	gotoxy(45, 18);
	cout << "|        |";
	gotoxy(45, 19);
	cout << "----------";
	gotoxy(46, 17);
	cout << "分數:" << grade;
	Color(240);
}

void screen()//遊戲介面//未設定 
{
}

int main()
{
	system("color F9");//背景白+字藍 
	srand(time(NULL));//用時間當亂數種子 
	game();
	int count = 0;//計分用的COUNT 
	int flag = 1;//讓迴圈繼續的FLAG 
	int secs = 300;//計時預設時間 

	int x = 0, y = 0;

	getscore();
	checkstr();
	checkhor();
	getscore();
	while (change1 == 1 || change2 == 1)
	{
		change();
		fall();
		ptrarr();
		checkstr();
		checkhor();
		getscore();
	}

	ptrarr();
	grade=0; 
	getscore();
	
	while (flag == 1)
	{
		
		ptrarr();
		gotoxy(0, 21);
		Color(240);
		cout << "輸入行(X)列(Y):" << endl;
		cout << "X(橫向):";
		cin >> x;
		cout << "Y(直向):";
		cin >> y;
		gotoxy((2 * x - 1) * 2, 2 * y - 1);
		Color(227);
		cout << "★";
		Color(240);
		int c = arr[2 * y - 1][2 * x - 1];
		char key;
		gotoxy(0, 24);
		cout << "輸入互換方向:" << "(W=上、A=左、D=右、S=下)";
		cin >> key;

		int stop = 0;
		while (stop == 0)
		{

			switch (key)
			{
			case'a':
			case'A':
			{
				arr[2 * y - 1][2 * x - 1] = arr[2 * y - 1][2 * x - 3];
				arr[2 * y - 1][2 * x - 3] = c;
			}
			case'w':
			case'W':
			{
				arr[2 * y - 1][2 * x - 1] = arr[2 * y - 3][2 * x - 1];
				arr[2 * y - 3][2 * x - 1] = c;
			}
			case'd':
			case'D':
			{
				arr[2 * y - 1][2 * x - 1] = arr[2 * y - 1][2 * x + 1];
				arr[2 * y - 1][2 * x + 1] = c;
			}
			case's':
			case'S':
			{
				arr[2 * y - 1][2 * x - 1] = arr[2 * y + 1][2 * x - 1];
				arr[2 * y + 1][2 * x - 1] = c;
			}
			}
			ptrarr();
			checkstr();
			checkhor();
			getscore();
			while (change1 == 1 || change2 == 1)
			{
				change();
				fall();
				ptrarr();
				checkstr();
				checkhor();
				getscore();
			}
			ptrarr();
			getscore();
			stop = 1;
		}

	}
}
