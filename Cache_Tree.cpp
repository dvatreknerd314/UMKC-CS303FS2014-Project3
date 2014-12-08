//Gretchen Gilbreath

#include"Cache_Tree.h"

//constructor
Cache_Tree::Cache_Tree()
{
	cacheTree = Binary_Tree<char>('\0');
}

Cache_Tree::~Cache_Tree()
{
	BTNode<char>* root = cacheTree.getRoot();
	deleteTree(root);
}

bool Cache_Tree::find(char letter)
{
	BTNode<char>* root = cacheTree.getRoot();
	return find(root, letter);
}

bool Cache_Tree::find(BTNode<char>* root, char letter)
{
	if (root->data == letter)
	{
		return true;
	}
	else if (root->right == NULL && root->left == NULL)
	{
		return false;
	}
	else if (root->right != NULL && root->left != NULL)
	{
		if (find(root->left, letter))
			return true;
		else
			return find(root->right, letter);
	}
	else if (root->left != NULL)
	{
		return find(root->left, letter);
	}
	else if (root->right != NULL)
	{
		if (root->right->data == letter)
			return true;
		else
			return find(root->right, letter);
	}
}

void Cache_Tree::insert(char letter, std::string coded)
{
	codeValues[letter] = coded;
	BTNode<char>* root = cacheTree.getRoot();
	insert(root, letter);
}

void Cache_Tree::insert(BTNode<char>* root, char letter)
{
	if (root->left == NULL)
	{
		BTNode<char>* aTree = new BTNode<char>(letter);
		root->left = aTree;
	}
	else if (root->right == NULL)
	{
		BTNode<char>* aTree = new BTNode<char>(letter);
		root->right = aTree;
	}
	else if (root->data > letter)
	{
		insert(root->right, letter);
	}
	else
	{
		insert(root->left, letter);
	}
}

std::string Cache_Tree::getCode(char letter)
{
	return codeValues[letter];
}

void Cache_Tree::deleteTree(BTNode<char>* root)
{

	if (root->left == NULL && root->right == NULL)
	{
		std::cout << "i";
		delete[] root;
		return;
	}
	if (root->left != NULL)
	{
		deleteTree(root->left);
	}
	if (root->right != NULL)
	{
		deleteTree(root->right);
	}
}
