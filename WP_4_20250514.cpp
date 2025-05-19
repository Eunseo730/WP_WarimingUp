using namespace std;
#include <iostream>
#include <windows.h>
#include <conio.h>

int board[10][21];

struct Player
{
	int x;
	int y;
	int shape;
};

Player p1;
Player p2;

void ClearConsole()
{
	system("cls");  // 콘솔 화면 지우기
}

// 돌 모양 정하기
void Shape1()
{
	p1.shape = rand() % 5;
}

void Shape2()
{
	p2.shape = rand() % 5;
}

// 충돌 체크
void CheckPos1()
{
	if (p1.x == p2.x && p1.y == p2.y)
	{
		p2.shape = p1.shape;

		Shape1();
	}
}

void CheckPos2()
{
	if (p1.x == p2.x && p1.y == p2.y)
	{
		p1.shape = p2.shape;

		Shape2();
	}
}

// 키보드 키 입력 받기
void InputKey()
{
	char key = _getch();

	Player prev1;
	Player prev2;

	prev1.x = p1.x;
	prev1.y = p1.y;
	prev2.x = p2.x;
	prev2.y = p2.y;

	switch (key)
	{
	case 'w':
		if (p1.y == 0)
		{
			p1.y = 9;
			Shape1();
		}
		else p1.y -= 1; 
		board[prev1.y][p1.x] = 0;
		CheckPos1();
		break;
	case 's':
		if (p1.y == 9) 
		{			
			p1.y = 0;
			Shape1();			
		} 
		p1.y += 1;
		board[prev1.y][p1.x] = 0;
		CheckPos1();
		break;
	case 'a':
		if (p1.x == 1) 
		{
			p1.x = 19;
			Shape1();
		}
		else p1.x -= 2; 
		board[p1.y][prev1.x] = 0;
		CheckPos1();
		break;
	case 'd':
		if (p1.x == 19)
		{
			p1.x = 1;
			Shape1();
		}
		else p1.x += 2; 
		board[p1.y][prev1.x] = 0; 
		CheckPos1();
		break;

	case 'i':
		if (p2.y == 0) 
		{
			p2.y = 9;
			Shape2();
		}
		else p2.y -= 1; 
		board[prev2.y][p2.x] = 0;
		CheckPos2();
		break;
	case 'k':
		if (p2.y == 9)
		{
			p2.y = 0;
			Shape2();
		}
		else p2.y += 1; 
		board[prev2.y][p2.x] = 0;
		CheckPos2();
		break;
	case 'j':
		if (p2.x == 1)
		{			
			p2.x = 19;
			Shape2();			
		}
		else p2.x -= 2; 
		board[p2.y][prev2.x] = 0; 
		CheckPos2();
		break;
	case 'l':
		if (p2.x == 19) 
		{
			p2.x = 1;
			Shape2();
		}
		else p2.x += 2; 
		board[p2.y][prev2.x] = 0; 
		CheckPos2();
		break;

	case 'q':
		exit(0);
	}
}

// 처음 플레이어 위치 정하기
void SetPos()
{
	p1.x = rand() % 21;

	while (p1.x % 2 == 0)
	{
		p1.x = rand() % 21;
	}

	p1.y = rand() % 10;

	p2.x = rand() % 21;

	while (p2.x % 2 == 0 && p2.x != p1.x)
	{
		p2.x = rand() % 21;
	}

	p2.y = rand() % 10;
}

void Init()
{
	SetPos();
	Shape1();
	Shape2();

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 21; i++)
		{
			if (i % 2 == 0)
				board[j][i] = 1;
			else if (i % 2 == 1)
				board[j][i] = 0;
		}
	}
}

void Print()
{
	for (int j = 0; j < 10; j++)
	{
		cout << "------------------------------------------------------------" << endl;

		for (int i = 0; i < 21; i++)
		{
			if (board[j][i] == 1)
				cout << "|";
			else if (board[j][i] == 0)
				cout << " ";
			else if (board[j][i] == 2)
			{
				switch (p1.shape)
				{
				case 0:
					cout << "o";
					break;

				case 1:
					cout << "x";
					break;

				case 2:
					cout << "#";
					break;

				case 3:
					cout << "@";
					break;

				case 4:
					cout << "*";
					break;

				default:
					break;
				}
			}

			else if (board[j][i] == 3)
			{
				switch (p2.shape)
				{
				case 0:
					cout << "o";
					break;

				case 1:
					cout << "x";
					break;

				case 2:
					cout << "#";
					break;

				case 3:
					cout << "@";
					break;

				case 4:
					cout << "*";
					break;

				default:
					break;
				}
			}
		}
		cout << endl;
	}
}

void Update()
{
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 21; i++)
		{
			if (i == p1.x && j == p1.y)
				board[j][i] = 2;

			if (i == p2.x && j == p2.y)
				board[j][i] = 3;
		}
	}

	board[p1.y][p1.x] = 2;
	board[p2.y][p2.x] = 3;

	ClearConsole();
	Print();
}

int main()
{
	srand(unsigned(time(NULL)));

	Init();
	Print();
	Update();

	while (true)
	{
		InputKey();

		Update();
	}
}


