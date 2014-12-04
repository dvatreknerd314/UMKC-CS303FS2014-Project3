// David Allen
// 11/30/14
// UMKC CS303 - FS14

#include "MorseTree.h"
#include "Constants.h"
#include <string>


MorseTree::MorseTree()  {
	// Initializes codeTree to have a starting node whose data is the null character
	codeTree = Binary_Tree<char>('\0');
}

MorseTree::MorseTree(istream& theStream)
{
	MorseTree(); // Set up the initial tree as normal
	setTreeCode(theStream); // Add code from theStream
}

void MorseTree::setTreeCode(istream& theStream)
{
	string tempLine; // Container variable for holding individual code entries

	while (!theStream.eof())
	{
		lineCounter++; // Increment the line counter so it starts at one
		getline(theStream, tempLine); // Get a line of code and store it in tempLine
		if (syntaxCheck(tempLine)) // If we pass syntax check, try to add the code
		{
			addCode(tempLine); // Attempt to add the code to the tree
		}
	}
	// Reset variables
	processedSymbols = "";
	lineCounter = 0;
}

bool MorseTree::syntaxCheck(string theInput)
{
	bool returnThis = true;


	if (theInput.length() < 3) { // The line is too short for a variety of possible reasons
		cout << "ERROR: Line " << lineCounter << " is too short. Ensure it is between 3 and 6 characters long." << endl;
		returnThis = false;
	}
	else if (theInput.length() > 6) { // The line is too long for a variety of possible reasons
		cout << "ERROR: Line " << lineCounter << " is too long. Ensure it is between 3 and 6 characters long." << endl;
		returnThis = false;
	}
	else if (theInput[0] == ' ') { // The first character is not a character
		cout << "ERROR: Line " << lineCounter << " does not begin with a symbol." << endl;
		returnThis = false;
	}
	else if (ALPHABET.find(theInput[0]) == string::npos) // The first character is not an alphabetical character
	{
		cout << "ERROR: Line " << lineCounter << " contains an invalid character as the symbol." << endl;
		returnThis = false;
	}
	else if (theInput[1] != ' ') { // The second character is either an illegal second character for the symbol or the beginning of the symbol's code.
		cout << "ERROR: Line " << lineCounter << " has a multi-character symbol or does not separate the symbol and its code by a space." << endl;
		returnThis = false;
	}
	else
	{
		for (int i = 2; i < theInput.length(); i++)
		{
			if (theInput[i] == ' ') { // The code area has one or more illegal spaces
				cout << "ERROR: Line " << lineCounter << " contains spaces in the symbol code." << endl;
				returnThis = false;
			}
			else if (SYMBOLS.find(theInput[i]) == string::npos) { // The code area has an invalid character
				cout << "ERROR: Line " << lineCounter << " has invalid characters in the symbol's code." << endl;
				returnThis = false;
			}
		}
	}
	return returnThis;
}

void MorseTree::addCode(string theInput)
{
	char theData = tolower(theInput[0]); // Convert the data to a lowercase letter to make uppercase and lowercase letters interchangeable
	string theCode = theInput.substr(2, 4); // Isolate the code substring
	if (processedSymbols.find(theData) == string::npos) // If we don't find this character we haven't processed it yet
	{
		if (recursiveAdd(theData, theCode, 0, codeTree.getRoot()))
			processedSymbols += theData; // Add this to the list of processed symbols
	}
	else // We have processed this character before and the current line is a duplicate or attempted rewrite
	{
		cout << "ERROR: Line " << lineCounter << " contains a symbol which has already been added." << endl;
	}
}

bool MorseTree::recursiveAdd(char theData, string theCode, int index, BTNode<char>* theNode)
{
	if (index == theCode.length()) // Meaning we've reached the target node
	{
		if (theNode->data != '\0') // Meaning we already have an item here
		{
			cout << "ERROR: Line " << lineCounter << " contains a code which has already been added." << endl;
			return false;
		}
		else
		{
			theNode->data = theData; // Set the current node's data to the character we passed in
			return true;
		}
	}
	else {
		char partialCode = theCode[index];
		if (DOTS.find(partialCode) != string::npos) // Meaning this is a dot, go left
		{
			if (theNode->left == NULL) // Meaning we haven't traversed this part of the tree yet
			{
				theNode->left = new BTNode<char>('\0'); // Create a temporary node to support the rest of the tree
			}
			theNode = theNode->left;
		}
		else // Meaning this is a dash, go right
		{
			if (theNode->right == NULL) // Meaning we haven't traversed this part of the tree yet
				theNode->right = new BTNode<char>('\0'); // Create a temporary node to support the rest of the tree
			theNode = theNode->right;
		}
		return recursiveAdd(theData, theCode, index + 1, theNode);
	}
}

void MorseTree::outputTree(ostream& theStream)
{
	deque<deque<char>> treeOutputArray; // Deque to store characters for output
	size_t width, temp2; // temp2 is passed by reference from recursiveTreeOutput() but is not needed in this context.

	if (codeTree.is_null()) // the tree is empty
	{
		theStream << "EMPTY TREE" << endl;
	}
	else // Recursively populate the treeOutputArray
	{
		recursiveTreeOutput(0, width, temp2, codeTree.getRoot(), treeOutputArray);
	}

	// Output the treeOutputArray
	for (int i = 0; i < treeOutputArray.size(); i++)
	{
		theStream << endl;
		for (int j = 0; j < width; j++)
		{
			theStream << treeOutputArray[i][j];
		}
	}
	theStream << endl;
}

void MorseTree::recursiveTreeOutput(int depth, size_t& width, size_t& rootPos, BTNode<char>* currentNode, deque<deque<char>>& subArray)
{
	// These are subarrays for the left and right subtrees
	deque<deque<char>> leftArray, rightArray;
	// These are the left and right width, as well as the left and right root node indices
	size_t left = 0, right = 0, leftIndex = 0, rightIndex = 0;

	if (currentNode->left != NULL) // If there is a left child, generate a subarray recursively
	{
		recursiveTreeOutput(depth + 1, left, leftIndex, currentNode->left, leftArray);
	}

	if (currentNode->right != NULL) // If there is a right child, generate a subarray recursively
	{
		recursiveTreeOutput(depth + 1, right, rightIndex, currentNode->right, rightArray);
	}

	deque<char> tempQueue; // Empty deque to add to the overall two-dimensional deque
	subArray.push_back(tempQueue);

	// Set overall parameters before they get lost in craziness
	width = left + right + 3;
	rootPos = left + 1;

	//
	// These are for the first row, which will contain only the root node's data, positioned exactly between the two subarrays
	//

	// Add spaces for the entire width of the left subarray
	for (int i = 0; i < left; i++)
	{
		subArray[0].push_back(' ');
	}
	// Add the data with padding spaces
	subArray[0].push_back(' ');
	subArray[0].push_back(currentNode->data == 0 ? '#' : currentNode->data);
	subArray[0].push_back(' ');

	// Add spaces for the entire width of the right subarray
	for (int i = 0; i <= right; i++)
	{
		subArray[0].push_back(' ');
	}

	//
	// These are for any subtrees this node had.
	//

	if (left + right > 0)
	{

		//
		// These are for the second row.  It will contain only the edges of the tree leading to this tree's root node.
		//

		// Add another row
		subArray.push_back(tempQueue);

		// Add spaces until we reach the position of the left sub-tree's root node
		// This loop will not execute if there is an empty left subtree
		for (int i = 0; i < leftIndex; i++)
		{
			subArray[1].push_back(' ');
		}
		// Output a downward bar if a left subtree exists
		if (left) { subArray[1].push_back('|'); }
		// Add dashes until we reach the end of the left subtree.
		// This loop will not execute if there is an empty left subtree
		for (int i = leftIndex + 1; i < left; i++)
		{
			subArray[1].push_back('-');
		}

		// Add center symbols depending on whether left or right subtrees exist
		subArray[1].push_back(left ? '-' : ' ');
		subArray[1].push_back('|');
		subArray[1].push_back(right ? '-' : ' ');

		// Add dashes until we reach the position of the right subtree's root node
		// This loop will not execute if there is an empty right subtree
		for (int i = 0; i < rightIndex; i++)
		{
			subArray[1].push_back('-');
		}
		// Output a downward bar if a right subtree exists
		if (right) { subArray[1].push_back('|'); }
		// Add spaces until we reach the end of the right subtree
		// This loop will not execute if there is an empty right subtree
		for (int i = rightIndex + 1; i < right; i++)
		{
			subArray[1].push_back(' ');
		}

		//
		// These are for all remaining rows.  It will output the data from the left and right subtrees at each row (outputting spaces
		// where no data exists for a subtree on a row), separating both subarrays with three spaces.
		//

		// Find the max length of the two subtrees
		int maxLength = max(leftArray.size(), rightArray.size());

		// Loop over both subarrays until both have been completely traversed.
		for (int i = 0; i < maxLength; i++)
		{
			// Add a new row to the overall array
			subArray.push_back(tempQueue);
			// Loop over the left subarray's width
			for (int j = 0; j < left; j++)
			{
				// If no data exists for the left subarray at this level, output spaces instead
				if (i >= leftArray.size())
				{
					subArray[i + 2].push_back(' ');
				}
				else // Otherwise output the data
				{
					subArray[i + 2].push_back(leftArray[i][j]);
				}
			}
			// Output three spaces to separate the left and right subarrays
			subArray[i + 2].push_back(' ');
			subArray[i + 2].push_back(' ');
			subArray[i + 2].push_back(' ');
			// Loop over the right subarray's width
			for (int j = 0; j < right; j++)
			{
				// If no data exists for the right subarray at this level, output spaces instead
				if (i >= rightArray.size())
				{
					subArray[i + 2].push_back(' ');
				}
				// Otherwise output the data
				else
				{
					subArray[i + 2].push_back(rightArray[i][j]);
				}
			}
		}
	}

}

//Chase Peterson

string MorseTree::decode(string input)
{
	BTNode<char>* current = codeTree.getRoot();
	string solution;

	//We need to add a space to the end of the input for the algorithm
	input += ' ';


	for (string::iterator itr = input.begin(); itr != input.end(); ++itr)
	{
		//Is the character a dash?
		if (DASHES.find(*itr) != -1)
		{
			//we need to move to the right
			current = current->right;
		}
		//Is the character a dot?
		else if (DOTS.find(*itr) != -1)
		{
			//we need to go left
			current = current->left;
		}
		//Is there a space?
		else if (*itr == ' ')
		{
			//Ideally we have reached the end of a coded letter
			//and are not still pointing at the head
			if (current != codeTree.getRoot())
				solution += current->data;
			
			//After a space we'll reset to the head regardless
			current = codeTree.getRoot();
		}
		//After making a move if we are pointing to NULL we had an invalid
		//code so we'll exit with an error
		if (current == NULL)
		{
			cout << endl << "ERROR: Invalid morse character" << endl << endl;
		
			return "ERROR";
		}
	}
	return solution;
	


}
