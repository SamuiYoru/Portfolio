#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<windows.h>
#include<ctime>
#include<conio.h>

using namespace std;

int arr[21][21];
int change1 = 0, change2 = 0;//���ƻP��ƪ��ˬd�� 
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

void gotoxy(int xpos, int ypos)//�y�Ц�m 
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void Color(int color)//�����C�� http://kowala21.blogspot.tw/2012/01/dev-c-console.html
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void checkstr()//�����ˬd 
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

void checkhor()//����ˬd 
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

void game()//��l�x�} 
{
	for (int i = 0; i< 21; i++)//�гy�@�ӯx�} 
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

void find()//�M�丨�檺-1 
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

void change()//�洫�W�h 
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

void fall()//�H�����U 
{
	for (int i = 1; i< 20; i = i + 2)//�H�����U 
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

void ptrarr()//�L�X�x�} 
{
	gotoxy(0, 0);
	for (int i = 0; i < 21; i++)//��X 
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
				cout << "��";
			}
			else if (arr[i][j] == 1)
			{
				Color(250);
				cout << "��";
			}
			else if (arr[i][j] == 2)
			{
				Color(251);
				cout << "��";
			}
			else if (arr[i][j] == 3)
			{
				Color(252);
				cout << "��";
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
cout << "�ѤU " << secs << "��", secs--;
}
}
*/
void title()//���]�w 
{


}

void getscore()//�b(46,17)�B�L�X�o�� 
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
	cout << "����:" << grade;
	Color(240);
}

void screen()//�C������//���]�w 
{
}

int main()
{
	system("color F9");//�I����+�r�� 
	srand(time(NULL));//�ήɶ���üƺؤl 
	game();
	int count = 0;//�p���Ϊ�COUNT 
	int flag = 1;//���j���~��FLAG 
	int secs = 300;//�p�ɹw�]�ɶ� 

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
		cout << "��J��(X)�C(Y):" << endl;
		cout << "X(��V):";
		cin >> x;
		cout << "Y(���V):";
		cin >> y;
		gotoxy((2 * x - 1) * 2, 2 * y - 1);
		Color(227);
		cout << "��";
		Color(240);
		int c = arr[2 * y - 1][2 * x - 1];
		char key;
		gotoxy(0, 24);
		cout << "��J������V:" << "(W=�W�BA=���BD=�k�BS=�U)";
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
