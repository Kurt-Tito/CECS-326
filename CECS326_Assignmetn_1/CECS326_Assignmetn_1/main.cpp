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
		
		//Initialize int array of increasing "sizes"
		mem._charLength[0] = 2700;
		for (int i = 1; i < ARRAY_LENGTH; i++)
		{
			mem._charLength[i] = 2 * mem._charLength[i - 1];
		}

		//Allocate memory for each element in the character pointer array using the values in the integer array
		for (int i = 0; i < ARRAY_LENGTH; i++)
		{
			mem._char[i] = new char[mem._charLength[i]];

			//INSERT random upper case letter
			for (int j = 0; j < mem._charLength[i]; j++)
			{
				mem._char[i][j] = randomLetter();
			}
		}

		bool terminate = false;

		while (!terminate)
		{
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
			
					int index;
					int subchoice; 

					cout << "Enter the index of the array to manipulate." << endl;

					cin >> index;

					cout << "(1) Print the first 10 char's in the chosen array." << endl;
					cout << "(2) Delete all the char's associated with this pointer." << endl;
					cout << "(3) Return to main menu." << endl;

					cin >> subchoice;

					switch (subchoice)
					{
						case 1:

							if (mem._char[index] == NULL)
							{	
								cout << "This memory index has been deallocated. Reallocating memory..." << endl;

								for (int i = 0; i < ARRAY_LENGTH; i++)
								{
									mem._char[i] = new char[mem._charLength[i]];

									//INSERT random upper case letter
									for (int j = 0; j < mem._charLength[i]; j++)
										mem._char[i][j] = randomLetter();
						
								}

							}
							else
							{
								cout << endl;

								for (int i = 0; i < 10; i++)
									cout << mem._char[index][i];

								cout << endl;

							}
							break;
						case 2:

							cout << endl;
							cout << "Deallocating this index... " << endl;

							mem._char[index] = NULL;
							delete mem._char[index];
							break;
						case 3:
							break;
					}

				case 2:
					cout << "Deallocated Memory (index) " << endl;
					for (int i = 0; i < ARRAY_LENGTH; i++)
					{
						if (mem._char[i] == NULL)
							cout << i << endl;
					}
					break;
				case 3:

					for (int i = 0; i < ARRAY_LENGTH; i++)
					{
						mem._char[i] = NULL;
						delete mem._char[i];
					}
					break;

				case 4:
					cout << "Exiting Program... " << endl;
					terminate = true;
			}
		}

		cout << "Program Exited." << endl;
		system("pause");
		return 0;
	}