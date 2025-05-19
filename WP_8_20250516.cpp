using namespace std;
#include <iostream>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <io.h>      // _setmode, _fileno
#include <fcntl.h>
#include <conio.h>

struct Node
{
	int x, y;
	Node* next = nullptr;
	Node* shortcut = nullptr;   // 지름길

	Node(int x_, int y_) : x(x_), y(y_) {}
};

struct Player
{
    Node* curr;
    int figure;
    int canMove;
};

wchar_t board[12][12];
vector<Node*> allNodes;
Node* start;

Player p1;
Player p2;

bool isFinished1 = false;
bool isFinished2 = false;

Node* CreateNode(int x, int y) {
    Node* node = new Node{ x, y };
    allNodes.push_back(node);
    return node;
}

void ClearConsole()
{
    system("cls");  // 콘솔 화면 지우기
}

void ClearBoard() {
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            board[i][j] = L' ';
}

void PrintFigure1()
{
    switch (p1.figure)
    {
    case 1:
        wcout << L"1: 도" << endl;
        break;

    case 2:
        wcout << L"1: 개" << endl;
        break;

    case 3:
        wcout << L"1: 걸" << endl;
        break;

    case 4:
        wcout << L"1: 윷" << endl;
        break;

    case 5:
        wcout << L"1: 모" << endl;
        break;
    }

    if (p1.curr && p1.curr->next == start)
    {
        wcout << L"게임 끝!" << endl;
        isFinished1 = true;
    }
}

void PrintFigure2()
{
    switch (p2.figure)
    {
    case 1:
        wcout << L"2: 도" << endl;
        break;

    case 2:
        wcout << L"2: 개" << endl;
        break;

    case 3:
        wcout << L"2: 걸" << endl;
        break;

    case 4:
        wcout << L" 2:윷" << endl;
        break;

    case 5:
        wcout << L" 2:모" << endl;
        break;
    }

    if (p2.curr && p2.curr->next == start)
    {
        wcout << L"게임 끝!" << endl;
        isFinished2 = true;
    }
}

// 보드판에 노드 경로와 말 위치 표시
void DrawBoard() {
    ClearBoard();
    ClearConsole();

    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);

    for (Node* node : allNodes)
        board[node->x][node->y] = L'□';

    for (Node* node : allNodes)
    {
        if (!isFinished1)
        {
            //SetConsoleTextAttribute(hConsole, 12); // 빨강
            board[p1.curr->x][p1.curr->y] = L'●';
        }
    }

    for (Node* node : allNodes)
    {
        if (!isFinished2)
        {
            //SetConsoleTextAttribute(hConsole, 9);
            board[p2.curr->x][p2.curr->y] = L'◆';
        }
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            wcout << board[i][j] << L' ';
        }
        wcout << L'\n';
    }

    PrintFigure1();
    PrintFigure2();
}

Node* BuildBoard() {
    // 중심에서 시작하는 경로를 만들자 (예: 십자가 중심부터 시계 방향)

    start = CreateNode(10, 0);
    Node* n1 = CreateNode(8, 0);
    Node* n2 = CreateNode(6, 0);
    Node* n3 = CreateNode(4, 0);
    Node* n4 = CreateNode(2, 0);
    Node* n5 = CreateNode(0, 0);
    Node* n6 = CreateNode(0, 2);
    Node* n7 = CreateNode(0, 4);
    Node* n8 = CreateNode(0, 6);
    Node* n9 = CreateNode(0, 8);
    Node* n10 = CreateNode(0, 10);
    Node* n11 = CreateNode(2, 10);
    Node* n12 = CreateNode(4, 10);
    Node* n13 = CreateNode(6, 10);
    Node* n14 = CreateNode(8, 10);
    Node* n15 = CreateNode(10, 10);
    Node* n16 = CreateNode(10, 8);
    Node* n17 = CreateNode(10, 6);
    Node* n18 = CreateNode(10, 4);
    Node* n19 = CreateNode(10, 2);

    Node* n20 = CreateNode(2, 2);
    Node* n21 = CreateNode(4, 4);
    Node* n22 = CreateNode(5, 5);   // 중간
    Node* n23 = CreateNode(6, 6);
    Node* n24 = CreateNode(8, 8);

    Node* n25 = CreateNode(2, 8);
    Node* n26 = CreateNode(4, 6);
    Node* n27 = CreateNode(6, 4);
    Node* n28 = CreateNode(8, 2);

    start->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n5->shortcut = n20;

    n6->next = n7;
    n7->next = n8;
    n8->next = n9;
    n9->next = n10;
    n10->next = n11;
    n10->shortcut = n25;

    n11->next = n12;
    n12->next = n13;
    n13->next = n14;
    n14->next = n15;
    n15->next = n16;
    n15->shortcut = n24;

    n16->next = n17;
    n17->next = n18;
    n18->next = n19;
    n19->next = start;

    n20->next = n21;
    n21->next = n22;
    n22->next = n23;
    n22->shortcut = n27;

    n23->next = n24;
    n24->next = n15;
    n24->shortcut = n23;

    n10->shortcut = n25;
    n25->next = n26;
    n26->next = n22;

    n27->next = n28;
    n28->next = start;

    p1.curr = start;
    p2.curr = start;

    return start;
}

void SetFigure1()
{
    p1.figure = rand() % 5 + 1;
    p1.canMove = p1.figure;
}

void SetFigure2()
{
    p2.figure = rand() % 5 + 1;
    p2.canMove = p2.figure;
}

bool IsDirection(Node* from, Node* to, char direction)
{
    if (!to) return false;

    switch (direction)
    {
    case 'w': 
        return from->x > to->x;
    case 'a': 
        return from->y > to->y;
    case 's':
        return from->x < to->x;
    case 'd':
        return from->y < to->y;
    default:
        return false;
    }
}

// 1이 움직여서 2와 충돌체크
void Collider1()
{
    if (p1.curr != start && p1.curr == p2.curr && p1.canMove == 0)
    {
        p2.curr = start;
    }
}

void Collider2()
{
    if (p2.curr != start && p1.curr == p2.curr && p2.canMove == 0)
    {
        p1.curr = start;
    }
}

void MoveUp1()
{
    if (p1.canMove <= 0) return;

    Collider1();

    Node* next = p1.curr->next;

    if (p1.curr->next && IsDirection(p1.curr, next, 'w'))
    {
        p1.curr = p1.curr->next;
        p1.canMove--;
    }

    else if (p1.curr->shortcut && IsDirection(p1.curr, p1.curr->shortcut, 'w'))
    {
        p1.curr = p1.curr->shortcut;
        p1.canMove--;
    }
}

void MoveLeft1()
{
    if (p1.canMove <= 0) return;

    Collider1();

    Node* next = p1.curr->next;

    if (p1.curr->next && IsDirection(p1.curr, next, 'a'))
    {
        p1.curr = p1.curr->next;
        p1.canMove--;
    }

    else if (p1.curr->shortcut && IsDirection(p1.curr, p1.curr->shortcut, 'a'))
    {
        p1.curr = p1.curr->shortcut;
        p1.canMove--;
    }
}

void MoveDown1()
{
    if (p1.canMove <= 0) return;

    Collider1();

    Node* next = p1.curr->next;

    if (p1.curr->next && IsDirection(p1.curr, next, 's'))
    {
        p1.curr = p1.curr->next;
        p1.canMove--;
    }

    else if (p1.curr->shortcut && IsDirection(p1.curr, p1.curr->shortcut, 's'))
    {
        p1.curr = p1.curr->shortcut;
        p1.canMove--;
    }
}

void MoveRight1()
{
    if (p1.canMove <= 0) return;

    Collider1();

    Node* next = p1.curr->next;

    if (p1.curr->next && IsDirection(p1.curr, next, 'd'))
    {
        p1.curr = p1.curr->next;
        p1.canMove--;
    }

    else if (p1.curr->shortcut && IsDirection(p1.curr, p1.curr->shortcut, 'd'))
    {
        p1.curr = p1.curr->shortcut;
        p1.canMove--;
    }
}

void MoveUp2()
{
    if (p2.canMove <= 0) return;

    Collider2();

    Node* next = p2.curr->next;

    if (p2.curr->next && IsDirection(p2.curr, next, 'w'))
    {
        p2.curr = p2.curr->next;
        p2.canMove--;
    }

    else if (p2.curr->shortcut && IsDirection(p2.curr, p2.curr->shortcut, 'w'))
    {
        p2.curr = p2.curr->shortcut;
        p2.canMove--;
    }
}

void MoveLeft2()
{
    if (p2.canMove <= 0) return;

    Collider2();

    Node* next = p2.curr->next;

    if (p2.curr->next && IsDirection(p1.curr, next, 'a'))
    {
        p2.curr = p2.curr->next;
        p2.canMove--;
    }

    else if (p2.curr->shortcut && IsDirection(p2.curr, p2.curr->shortcut, 'a'))
    {
        p2.curr = p2.curr->shortcut;
        p2.canMove--;
    }
}

void MoveDown2()
{
    if (p2.canMove <= 0) return;

    Collider2();

    Node* next = p2.curr->next;

    if (p2.curr->next && IsDirection(p2.curr, next, 's'))
    {
        p2.curr = p2.curr->next;
        p2.canMove--;
    }

    else if (p2.curr->shortcut && IsDirection(p2.curr, p2.curr->shortcut, 's'))
    {
        p2.curr = p2.curr->shortcut;
        p2.canMove--;
    }
}

void MoveRight2()
{
    if (p2.canMove <= 0) return;

    Collider2();

    Node* next = p2.curr->next;

    if (p2.curr->next && IsDirection(p2.curr, next, 'd'))
    {
        p2.curr = p2.curr->next;
        p2.canMove--;
    }

    else if (p2.curr->shortcut && IsDirection(p2.curr, p2.curr->shortcut, 'd'))
    {
        p2.curr = p2.curr->shortcut;
        p2.canMove--;
    }
}

// 명령어 입력 받기
void Choose()
{
    char choose;
    choose = _getch();

    switch (choose)
    {
    case 'p':
        BuildBoard();
        break;

    case '1':
        SetFigure1();
        break;

    case '2':
        SetFigure2();
        break;

    case 'w':
        MoveUp1();
        break;

    case 'a':
        MoveLeft1();
        break;

    case 's':
        MoveDown1();
        break;

    case 'd':
        MoveRight1();
        break;

    case 'i':
        MoveUp2();
        break;

    case 'j':
        MoveLeft2();
        break;

    case 'k':
        MoveDown2();
        break;

    case 'l':
        MoveRight2();
        break;
    }
}

int main()
{
    while (true)
    {
        DrawBoard();
        Choose();
    }
}

