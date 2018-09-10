#include <iostream>
#include <iomanip>

using namespace std;
const int ARRAY_LENGTH = 20;

struct memory
{
	char *_char[20];
	int _charLength[20];
};

char randomLetter()
{
	char letters[26] = { 'A' , 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	
	int randInt = rand() % sizeof(letters);
	char randomLetter = letters[randInt];
	return randomLetter;
}

int main()
{
	memory mem;
	
	mem._charLength[0] = 2700;
	for (int i = 1; i < ARRAY_LENGTH; i++)
	{
		mem._charLength[i] = 2 * mem._charLength[i - 1];
	}

	for (int i = 0; i < ARRAY_LENGTH; i++)
	{
		mem._char[i] = new char[mem._charLength[i]];

		//INSERT random upper case letter
		for (int j = 0; j < ARRAY_LENGTH; j++)
		{
			mem._char[i][j] = randomLetter();
		}
	}

	int choice;

	cout << "Main Menu " << endl;
	cout << "(1) Access a Pointer" << endl;
	cout << "(2) List deallocated memory (index)" << endl;
	cout << "(3) Deallocate all memory" << endl;
	cout << "(4) Exit Program" << endl;

	cin >> choice;

	switch (choice)
	{
		case 1:
			cout << "Accessing pointer... " << endl;
			cout << mem._char[1] << endl;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
	}

	system("pause");
	return 0;
}

//memory **mem;
//mem = new memory *[1];
//mem[0] = new memory;

//mem[0]->num; //??

//for (int n = 1; n < 20; n++)
//{
//	mem[0]->num[n] = 2 * mem[0]->num[n - 1];
//}