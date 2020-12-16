/**************************************************************************************************
*
*   File name :			Huffman.cpp
*	Programmer:  		Jeremy Atkins
*
*	Implementation of the Huffman tree as defined in Huffman.h. Contains the Huffman class
*	which constructs a Huffman tree and encodes a message from a file according to that tree
*	as well as allowing for decoding the message or any message encoded using that same tree.
*
*   Date Written:		in the past
*
*   Date Last Revised:	5/15/19
****************************************************************************************************/
#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

/*******************************************************************************************
*	Function Name:			Huffman				the constructor
*	Purpose:				This constructor creates a Huffman object and initialized a
*							boolean determining whether the tree has data in it or not
*	Input Parameters:		none
*	Return value:			none
********************************************************************************************/
Huffman::Huffman()
{
	populated = false;
}

/*******************************************************************************************
*	Function Name:			makeTree			
*	Purpose:				Constructs the Huffman tree and sets all of the pointers
*	Input Parameters:		none
*	Return value:			none
********************************************************************************************/
void Huffman::makeTree()
{
	int pos = 0;
	huffNode newNode;	//node to be added
	huffNode curr;		//current node
	//constructs inner nodes
	for (int i = 0; i < 25; i++)
	{
		newNode.name = "T";
		newNode.name += to_string(i);	
		newNode.freq = nodes[pos].freq + nodes[pos + 1].freq;	//set frequency of inner nodes

		//initialize pointers to null
		newNode.left = NULL;
		newNode.right = NULL;
		newNode.parent = NULL;
		pos += 2;

		//add inner node to vector and resort with new node added
		nodes.push_back(newNode);
		sort(nodes.begin(), nodes.end());
	}
	pos = 0;
	
	//assign pointers to children
	for (unsigned i = 0; i < nodes.size(); i++)
	{
		//only inner nodes have child pointers to assign
		if (nodes[i].name.length() > 1)
		{
			//point at the correct children
			nodes[i].left = &nodes[pos];
			nodes[i].right = &nodes[pos + 1];
			nodes[i].left->parent = &nodes[i];
			nodes[i].right->parent = &nodes[i];
			pos += 2;

			//set codes, 0 for left and 1 for right
			nodes[i].left->code += "0";
			nodes[i].right->code += "1";
			
		}
	}
	
	//sets parent pointers
	for (unsigned i = 0; i < nodes.size(); i++)
	{
		//find leaf node
		if (nodes[i].name.length() == 1)
		{
			curr = nodes[i];
			//go back up tree until hitting the root assigning parents
			while (curr.parent->code != "")
			{
				curr = *curr.parent;
				nodes[i].code.insert(0, curr.code);
			}
		}
	}
}

/*******************************************************************************************
*	Function Name:			encode
*	Purpose:				Encodes an input string as a string of 0s and 1s according
*							to the constructed Huffman tree
*	Input Parameters:		none
*	Return value:			none
********************************************************************************************/
void Huffman::encode()
{
	//reading the file and constructing the tree
	readFile();
	countChars();
	makeTree();

	//get the code for each character in the input string
	for (unsigned i = 0; i < inString.size(); i++)
	{
		for (unsigned j = 0; j < nodes.size(); j++)
		{
			if (inString.substr(i, 1) == nodes[j].name)
				fullCode += nodes[j].code;
		}
	}

	cout << "The encoded message:" << endl;
	cout << fullCode << endl;

	//save the code to a file
	string fileName;
	cout << "Enter the name of the file to save the code to: ";
	cin >> fileName;
	ofstream outFile;
	outFile.open(fileName);

	//append terminating character
	outFile << fullCode << '*';
	outFile.close();
	cout << "\n\nFile encoded in " << fileName << endl;
}

/*******************************************************************************************
*	Function Name:			decode
*	Purpose:				Decodes an input string of 0s and 1s according to
*							the constructed Huffman tree
*	Input Parameters:		none
*	Return value:			none
********************************************************************************************/
void Huffman::decode()
{
	//input file to be decoded
	string fileName;
	cout << "Enter the name of the file you would like to decode: ";
	cin >> fileName;
	ifstream inFile;
	inFile.open(fileName);
	if (!inFile)
	{
		cout << "Error opening file " << fileName << endl;
		return;
	}

	//code starts empty
	fullCode = "";

	//read code from file, terminating at *
	inFile >> fullCode;
	for (unsigned i = 0; i < fullCode.size(); i++)
	{
		if (fullCode[i] == '*')
		{
			fullCode.erase(i, fullCode.size());
			break;
		}
	}	
	
	inFile.close();

	//current node starts at the root
	huffNode curr = nodes[nodes.size() - 1];

	//decoded message starts empty
	string ans = "";

	//decode the message
	for (unsigned i = 0; i < fullCode.size(); i++)
	{
		//if 0 go left
		if (fullCode[i] == '0')
			curr = *curr.left;

		//if 1 go right
		else
			curr = *curr.right;

		//if current is a leaf node
		if (curr.left == NULL && curr.right == NULL)
		{

			//get the current character value
			ans += curr.name;

			//reset current to the root
			curr = nodes[nodes.size() - 1];
		}
	}
	cout << "\n\nMessage Decoded: " << endl;
	cout << ans << endl;
	
}

/*******************************************************************************************
*	Function Name:			printTree
*	Purpose:				Prints all of the nodes with their respective child and parent
*							values as well as code values
*	Input Parameters:		none
*	Return value:			none
********************************************************************************************/
void Huffman::printTree()
{

	//print each node name, left child, right child, and parent if applicable, as well as the code value
	for (unsigned i = 0; i < nodes.size(); i++)
	{
		cout << "-------------------------------------------------" << endl;
		cout << "name " << nodes[i].name << endl;

		if (nodes[i].left)
			cout << "left " << nodes[i].left->name << endl;
		if (nodes[i].right)
			cout << "right " << nodes[i].right->name << endl;
		if (nodes[i].parent)
			cout << "parent " << nodes[i].parent->name << endl;
		cout << "code " << nodes[i].code << endl;
		cout << "-------------------------------------------------" << endl;
	}
}

/*******************************************************************************************
*	Function Name:			printTable
*	Purpose:				Prints the table of code values for each character
*	Input Parameters:		none
*	Return value:			none
********************************************************************************************/
void Huffman::printTable()
{
	//save table to output file
	string fileName = "code_table.txt";
	ofstream outFile;
	outFile.open(fileName);
	if (!outFile)
	{
		cout << "Error opening file " << fileName << endl;
		return;
	}

	//print table
	for (unsigned i = 0; i < nodes.size(); i++)
	{
		//only print characters, not inner nodes
		if (nodes[i].name.length() == 1)
		{
			cout << nodes[i].name << "\t" << nodes[i].code << endl;
			outFile << nodes[i].name << "\t" << nodes[i].code << endl;
		}
	}
	outFile.close();
	cout << "Code table written to " << fileName << endl << endl;
}

/*******************************************************************************************
*	Function Name:			readFile
*	Purpose:				Reads a file and initializes the input string
*	Input Parameters:		none
*	Return value:			none
********************************************************************************************/
void Huffman::readFile()
{

	//if the tree already has data in it
	if (populated)
	{
		//reset all of the data
		input.erase(input.begin(), input.end());
		nodes.erase(nodes.begin(), nodes.end());
		inString = "";
		fullCode = "";
	}

	//input file
	string fileName;
	ifstream inFile;
	char temp;
	cout << "Enter the input file from which to construct the Huffman tree " << endl;
	cin >> fileName;
	inFile.open(fileName);
	if (!inFile)
	{
		cout << "Error opening file " << fileName << endl;
		return;
	}

	//while the file still has data
	while (inFile)
	{
		//read into character
		inFile >> temp;

		//make everything lowercase
		temp = tolower(temp);

		//push into input vector
		input.push_back(temp);

		//break on terminating character
		if (inFile.peek() == '*')
			break;
	}
	inFile.close();

	//copy input into string to save original ordering
	for (unsigned i = 0; i < input.size(); i++)
		inString.push_back(input[i]);

	//sort input vector
	sort(input.begin(), input.end());

	//the tree now has data
	populated = true;

}


/*******************************************************************************************
*	Function Name:			countChars
*	Purpose:				Counts the characters in the input vector and assignes a 
*							frequency to them, adding them to a vector of nodes
*	Input Parameters:		none
*	Return value:			none
********************************************************************************************/
void Huffman::countChars()
{
	int count = 1;
	huffNode newNode;
	
	//start at a
	char curr = 'a';

	//loop from a to z
	for (int i = 0; i < 26; i++)
	{
		//set node information for each character
		newNode.name = curr;
		newNode.freq = 0;
		newNode.code = "";
		newNode.left = NULL;
		newNode.right = NULL;
		newNode.parent = NULL;
		nodes.push_back(newNode);
	
		curr++;
	}
	
	//count each character
	for (unsigned i = 0; i < input.size(); i++)
	{
		nodes[input[i] - 97].freq++;
	}
	
	//sort the array of nodes
	sort(nodes.begin(), nodes.end());

}
