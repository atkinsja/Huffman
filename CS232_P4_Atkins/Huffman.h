/**************************************************************************************************
*
*   File name :			Huffman.h
*
*	Programmer:  		Jeremy Atkins
*
*   Header file for the Huffman class, implemented in Huffman.cpp
*
*   Date Written:		in the past
*
*   Date Last Revised:	5/15/19
*
*	Class Name:		Huffman
*
*	Structs:
*		huffNode					a struct holding the name of a node, the assigned huffman code
*									and pointers to left and right children as well as the parent
*									node; includes operator overloads for < and <<
*		
*	Private data members:
*		bool populated				determines whether a tree has data in it or not
*		vector<huffNode> nodes		vector of nodes representing the huffman tree
*		vector<char> input			the input string which gets reordered
*		string inString				the original string
*		string fullCode				the encoded input or output
*	
*	Private member function:
*		void makeTree				constructs the huffman tree
*		void readFile				reads the input file to make the tree from
*		void countChars				counts the characters and assigns a frequency to each node
*
*	Public member functions:
*		Huffman				constructor for a Huffman tree
*		
*		void encode			encodes a string according to the huffman tree
*		void decode			decodes a string according to the huffman tree
*		printTree			prints out each node with their corresponding
*							child and parent pointers
*		printTable			prints out the table of codes for each character
*
****************************************************************************************************/
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//huffNode struct to hold each character
struct huffNode
{
	string name;
	int freq;
	string code;
	huffNode* left;
	huffNode* right;
	huffNode* parent;
	
	//< overload for sorting
	bool operator<(const huffNode node)
	{
		
		if (this->freq < node.freq)
			return true;
		else
			return false;
	}

	//<< overload for printing
	friend ostream& operator<<(ostream& os, const huffNode& node)
	{
		cout << "Node: " << node.name << " Frequency: " << node.freq << " Code: " << node.code;
		return os;
	}
};

//huffman tree class
class Huffman
{
public:
	Huffman();	
	void encode();
	void decode();
	void printTree();
	void printTable();
	
	
private:
	void makeTree();
	void readFile();
	void countChars();
	vector<huffNode> nodes;
	vector<char> input;
	string inString;
	string fullCode;
	bool populated;
	
};
#endif // !HUFFMAN_H
