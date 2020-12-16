/**************************************************************************************************
*
*   File name :			P4Driver.cpp
*
*	Programmer:  		Jeremy Atkins
*
*   Driver file that creates a huffman tree and allows the user options to encode, decode, print
*	the tree, or print the code values.
*
*   Date Last Revised:	3/14/2019
****************************************************************************************************/
#include <iostream>
#include "Huffman.h"
using namespace std;

int main()
{
	Huffman huff;		//huffman tree
	int choice;			//input

	do
	{
		//menu options
		cout << "1. Encode a file" << endl;
		cout << "2. Decode a file" << endl;
		cout << "3. Print the tree" << endl;
		cout << "4. Print the code table" << endl;
		cout << "5. Exit Program" << endl;
		cout << "Enter the number of the option to be selected: ";
		cin >> choice;

		//menu switch
		switch (choice)
		{
		//encode
		case 1:
			huff.encode();
			break;

		//decode
		case 2:
			huff.decode();
			break;

		//print the tree
		case 3:
			huff.printTree();
			break;

		//print the code table
		case 4:
			huff.printTable();
			break;

		//exit
		case 5:
			cout << "Exitting Program" << endl;
			break;

		//default
		default:
			break;
		}		//end menu switch
	} while (choice != 5);		//end do-while

	return 0;
}