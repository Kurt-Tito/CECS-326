#include <iostream>
#include <iomanip>

using namespace std;
const int ARRAY_LENGTH = 20;

struct memory
{
	const char *chara[20];
	int num[20];
};

int main()
{
	memory mem;
	
	mem.num[0] = 2700;
	for (int i = 1; i < ARRAY_LENGTH; i++)
	{
		mem.num[i] = 2 * mem.num[i - 1];
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
			for (int i = 0; i < 20; i++)
			{
				cout << mem.num[i] << endl;
			}
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