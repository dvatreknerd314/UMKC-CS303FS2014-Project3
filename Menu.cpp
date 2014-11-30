#include "MorseTree.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	MorseTree theTree;
	ifstream fin;
	string filePath;

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

	cin >> filePath;


	return 0;
}