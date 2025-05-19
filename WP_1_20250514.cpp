using namespace std;
#include <iostream>

enum
{
	MAX_SIZE = 60
};

char sentence[MAX_SIZE];

// 문장 출력
void PrintSentence(char* _sentence)
{
	cout << _sentence << endl;
}

// 문장을 입력받음
void InputSentence(char* _sentence)
{
	cout << "문장을 입력하세요: ";
	// cin >> _sentence;
	cin.getline(_sentence, MAX_SIZE + 1);

	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (_sentence[i] == ' ' && _sentence[i + 1] == ' ')
		{
			for (int j = i + 1; j < MAX_SIZE; j++)
			{
				_sentence[j] = _sentence[j + 1];
				i--;
			}
		}
	}

	PrintSentence(_sentence);
}


void Input(char* _sentence)
{
	char choice;
	cout << "명령어를 입력하세요: ";
	cin >> choice;
	cout << "\n입력하신 명령어: " << choice << endl;

	if (isalpha(choice))
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (_sentence[i] != ' ' && _sentence[i] != '\0')
			{
				_sentence[i] = '*';
			}
		}

		PrintSentence(_sentence);
	}

	else if (choice == '1')
	{
		for (int i = 0; _sentence[i] != '\0'; i++)
		{
			int random = rand() % 4;

			if (_sentence[i] == ' ')
			{
				if (random == 0)
					_sentence[i] = '@';
				else if (random == 1)
					_sentence[i] = '%';
				else if (random == 2)
					_sentence[i] = '#';
				else if (random == 3)
					_sentence[i] = '.';
			}
		}

		PrintSentence(_sentence);
	}

	else if (choice == '2')
	{
		int count = 0;

		for (int i = 0; _sentence[i] != '\0'; i++)
		{
			if (_sentence[i] == ' ' && _sentence[i + 1] != '\0')
				count++;
		}

		if (_sentence[0] != ' ')
		    count++;

		cout << "단어 개수: " << count << endl;
	}

	else if (choice == '3')
	{
		for (int i = 0; _sentence[i] != '\0'; i++)
		{
			if (isupper(_sentence[i]))
				_sentence[i] = tolower(_sentence[i]);
			else if (islower(_sentence[i]))
				_sentence[i] = toupper(_sentence[i]);
		}

		PrintSentence(_sentence);
	}

	else if (choice == '4')
	{
		for (int i = 1; _sentence[i] != '\0'; i++)
		{
			_sentence[i - 1] = _sentence[i];

			if (_sentence[i + 1] == '\0')
				_sentence[i] = '\0';
		}

		PrintSentence(_sentence);
	}

	else if (choice == '5')
	{
		int len = strlen(_sentence);

		for (int i = len; i >= 0; i--)
		{
			_sentence[i + 1] = _sentence[i];
		}

		_sentence[0] = ' ';

		PrintSentence(_sentence);
	}

	else if (choice == '0')
	{
		cout << "프로그램 종료" << endl;
		exit(0);
	}
}

int main()
{
	srand(unsigned(time(NULL)));

	InputSentence(sentence);

	while (true)
	{
		Input(sentence);
	}
}

