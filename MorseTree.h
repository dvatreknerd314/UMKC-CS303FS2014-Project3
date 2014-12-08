// David Allen
// 11/30/14
// UMKC CS303 - FS14

#ifndef MORSETREE_H
#define MORSETREE_H

#include <iostream>
#include <deque>
#include "Binary_Tree.h"
#include "BTNode.h"
#include "CacheTree.h"
using namespace std;

class MorseTree
{
public:
	MorseTree();
	MorseTree(istream& theStream);
	void setTreeCode(istream& theStream);
	void outputTree(ostream& theStream);

	//Chase Peterson
	//Decode function
		//Takes a string of dots and dashes seperated by spaces
		//Returns decoded string of letters
	string decode(string input);
	
	//Gretchen Gilbreath
	//Encode function
		//Takes a word
		//Returns a string of dots and dashes separated by spaces
		
	string encode(string input);

private:
	Binary_Tree<char> codeTree;
	void addCode(string theInput);
	bool syntaxCheck(string theInput);
	bool recursiveAdd(char theData, string theCode, int index, BTNode<char>* theNode);
	int lineCounter = 0;
	string processedSymbols = "";
	void recursiveTreeOutput(int depth, size_t& width, size_t& rootPos, BTNode<char>* currentNode, deque<deque<char>>& subArray);
	
	bool encoder(string& input, BTNode<char>* root, char letter);//used with encode function
	CacheTree cacheTree;//checks to see if a letter has already been searched in encode
};

#endif
