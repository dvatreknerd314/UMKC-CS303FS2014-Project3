#include "MorseTree.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	
	MorseTree theTree;
	ifstream fin;
	string filePath;
	char input[256];

	int choice;

	cout << "Specify file path: " << endl;
	cin >> filePath;
	fin.open(filePath);

	while (!fin.good())
	{
		cout << "Invalid path, please re-enter:" << endl;
		cin >> filePath;
		fin.open(filePath);
	}

	theTree.setTreeCode(fin);


	theTree.outputTree(cout);


	cin.ignore();

	//The following tests decode
	while (true)
	{
		//Print menu
		cout << endl;
		cout << "What would you like to do?  (please enter number of option)" << endl;
		cout << "1. Decode a message" << endl;
		cout << "2. Encode a message" << endl;
		cout << "3. Exit" << endl;

		cin >> choice;

		switch (choice)
		{
		//Case 1 Decode a message
		case 1:
			cin.ignore();
			cout << endl << "Please enter a morse code message (use spaces between morse characters): ";
			cin.getline(input, 256);

			cout << endl << "Translation: " << theTree.decode(input) << endl;
			break;
		//Case 2 Encode a message
		case 2:
			cin.ignore();
			cout << endl << "Please enter a word to encode: ";
			cin.getline(input, 256);

			cout << endl << "Code: " << theTree.encode(input) << endl;
			break;
		//Case 3 Quit
		case 3:
			return 0;
		//Default, ask for valid input
		default:
			cout << endl << "Please enter a valid command  (1,2, or 3)" << endl << endl;
			break;

		}
	}
}
