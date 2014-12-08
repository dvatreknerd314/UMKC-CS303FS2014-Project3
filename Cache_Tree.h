//Gretchen Gilbreath
#pragma once
#include "Binary_Tree.h"
#include "BTNode.h"
#include <iostream>

class Cache_Tree
{
public:
	Cache_Tree();
	~Cache_Tree();
	bool find(char letter);
	void insert(char letter, std::string coded);
	std::string getCode(char letter);
	void deleteTree(BTNode<char>* root);

private:
	Binary_Tree<char> cacheTree;
	std::string codeValues[128];
	bool Cache_Tree::find(BTNode<char>* root, char letter);
	void insert(BTNode<char>* root, char letter);

};

