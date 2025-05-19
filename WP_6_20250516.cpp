using namespace std;
#include <iostream>
#include <vector>
#include <string>      // getline 함수 사용에 필요
#include <sstream>

vector<int> nums;
vector<char> opers;

// 사용자에게 숫자와 피연산자를 입력 받음
void Input()
{
	nums.clear();
	opers.clear();

	cout << "숫자와 연산자를 입력 하세요 (예: 12 + 5 * 3 - 8 / 4): ";

    string line;
    getline(cin >> ws, line); // 앞 공백 무시하면서 한 줄 전체 입력 받기, cin >> ws (앞의 남은 공백 제거)
    stringstream ss(line);    // 띄어쓰기 기준으로 쪼갬
    int num;
    char op;

    ss >> num;                // 맨 앞은 무조건 숫자
    nums.push_back(num);

    // 연산자 하나 읽고, 숫자 하나 읽고를 반복하며 연산자는 opers에 저장, 숫자는 nums에 저장
    while (ss >> op >> num) 
    {
        opers.push_back(op);
        nums.push_back(num);
    }
}

int CalLeft()
{
    vector<int> tempNums = nums;
    vector<char> tempOpers = opers;
    int result = 0;

    for (int i = 0; i < tempOpers.size(); i++)
    {
        int a = tempNums[i];
        int b = tempNums[i + 1];
        char oper = tempOpers[i];

        switch (oper)
        {
        case '+':
            result = a + b;
            break;

        case '-':
            result = a - b;
            break;

        case '*':
            result = a * b;
            break;

        case '/':
            result = a / b;
            break;
        }

        tempNums[i] = result;
        tempNums.erase(tempNums.begin() + i + 1);
        tempOpers.erase(tempOpers.begin() + i);
        i--;
    }

    return result;
}

int CalRight()
{
    vector<int> tempNums;
    int index = nums.size();
    for (int i = 0; i < nums.size(); i++)
    {
        tempNums.push_back(nums[index - i - 1]);
    }

    vector<char> tempOpers;
    int index2 = opers.size();
    for (int i = 0; i < opers.size(); i++)
    {
        tempOpers.push_back(opers[index2 - i - 1]);
    }

    int result = 0;

    for (int i = 0; i < tempOpers.size(); i++)
    {
        int a = tempNums[i];
        int b = tempNums[i + 1];
        char oper = tempOpers[i];

        switch (oper)
        {
        case '+':
            result = a + b;
            break;

        case '-':
            result = a - b;
            break;

        case '*':
            result = a * b;
            break;

        case '/':
            result = a / b;
            break;
        }

        tempNums[i] = result;
        tempNums.erase(tempNums.begin() + i + 1);
        tempOpers.erase(tempOpers.begin() + i);
        i--;
    }

    return result;
}

int CalOrigin()
{
    vector<int> tempNums = nums;
    vector<char> tempOpers = opers;
    int result = 0;

    for (int i = 0; i < tempOpers.size(); i++)
    {
        char oper = tempOpers[i];

        if (oper == '*' || oper == '/')
        {
            int a = tempNums[i];
            int b = tempNums[i + 1];
            result = (oper == '*') ? a * b : a / b;

            tempNums[i] = result;
            tempNums.erase(tempNums.begin() + i + 1);
            tempOpers.erase(tempOpers.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < tempOpers.size(); i++)
    {
        int a = tempNums[i];
        int b = tempNums[i + 1];
        char oper = tempOpers[i];
        result = (oper == '+') ? a + b : a - b;

        tempNums[i] = result;
        tempNums.erase(tempNums.begin() + i + 1);
        tempOpers.erase(tempOpers.begin() + i);
        i--;
    }

    return tempNums[0];
}

// 명령어 입력
void Choose()
{
    int choose;

    cout << "명령어 입력: ";
    cin >> choose;

    switch (choose)
    {
    case 1:
        cout << "result: " << CalOrigin() << endl;
        break;

    case 2:
        cout << "result: " << CalLeft() << endl;
        break;

    case 3:
        cout << "result: " << CalRight() << endl;
        break;

    default:
        break;
    }
}

int main()
{
    Input();

    while (true)
    {
        Choose();
    }
}


