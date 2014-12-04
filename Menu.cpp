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
		cout << "Enter a code to decode: " << endl;
		cin.getline(input, 256);

		if (input == "quit")
			return 0;

		cout << endl << "Solution: " << theTree.decode(input) << endl;

	}

}
