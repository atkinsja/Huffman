
//#include <iostream.h>
#include <iomanip>
#include <iostream>
#include <string>
#ifndef TREE_H__
#define TREE_H__
using namespace std;

//header file for a Binary tree with the ordering property
//BaseData class is assumed to have overloaded relational
//> < == !=  <= >=       operators if not a base type

template <class BaseData>
struct  TreeNode {
			BaseData TreeData;
			TreeNode *left, *right;
			char direction;
		  };

//these are file level because traversals are recursive
//void openOutFile() ;  //probably not the same as yours
//ofstream opf;         //opf is ofstream object used

template <class BaseData>
class  tree
       {      //friend class stated here;
       public  :
		 tree();
		 ~tree();
		 tree(tree<BaseData> &t);
		 tree<BaseData> & operator = (const tree<BaseData> &t);
		 void insert(BaseData &item);
		 void SearchAndDestroy(BaseData target);
		 void writeTree(int) ;
		 int fullTree() const;
		 int emptyTree() const;
		 string encode(BaseData target);
		 

       protected:   //helping functions
		 void remove(TreeNode<BaseData> * &current);
		 void inOrder(TreeNode<BaseData> *);
		 void preOrder(TreeNode<BaseData> *);
		 void postOrder(TreeNode<BaseData> *);
		 void destroy(TreeNode<BaseData> *p);
		 void copyTreeNode (TreeNode <BaseData>** into,
					 TreeNode<BaseData>* from);
		 void insertNode(TreeNode<BaseData>** into,
					  BaseData& item);
		 TreeNode <BaseData>  *getnode(BaseData &item);

       private:
		   TreeNode<BaseData>  *root;

};





//constructor
template <class BaseData>
tree<BaseData>::tree()
{
	root = 0;
}

//destructor
template <class BaseData>
tree<BaseData>::~tree()
{
  if (root)
	destroy (root);
}


//helping function for destructor and copying functions
template <class BaseData>
void tree<BaseData>::destroy(TreeNode<BaseData> *p)
{  if (p)
    { destroy(p->left);
      destroy(p->right);
      delete p;
    }
}

//copy constructor: uses helping function copyTreeNode
template <class BaseData>
tree<BaseData> :: tree(tree<BaseData> &t)
{
    root = 0;
    copyTreeNode(&root,t.root);
}

//copy constructor: uses helping functions destroy and copyTreeNode
template <class BaseData>
tree<BaseData> &  tree<BaseData>:: operator = (const tree<BaseData> &t)
{   if (this == &t) return *this;
    if (root)
	destroy(root);
    root = 0;
    copyTreeNode(&root,t.root);
    return *this;
}

//helping function
template <class BaseData>
void tree<BaseData>::inOrder(TreeNode<BaseData> *p)
{     if (p)
     { inOrder(p->left);
       cout << p->TreeData;
       inOrder(p->right);
     }
}//END InOrder;

//helping function
template <class BaseData>
void tree<BaseData>::preOrder(TreeNode<BaseData> *p)
{
   if (p)
     { 
	   cout << p->TreeData;
       preOrder(p->left);
       preOrder(p->right);
     }
}//END PreOrder;

//helping function
template <class BaseData>
void tree<BaseData>::postOrder(TreeNode<BaseData> *p)
{   if (p)
    { postOrder(p->left);
      postOrder(p->right);
      cout << p->TreeData;
     }
}//END PostOrder; */

//searches for target of the base data type and if found it removes it
//uses helping function remove
template <class BaseData>
void tree<BaseData>::SearchAndDestroy(BaseData target)
{	TreeNode<BaseData> *previous, *current;

	current = root;
	previous = 0;
	while(current && (current->TreeData != target))
	   { 	previous = current;
		if (current->TreeData > target)
			current = current->left;
		else current = current->right;
	   }  //(*while*)
	if (!current)    //target not found
		{ cout << "target not found " << endl;
		  return;
		}

	//remove requires the actual node in the tree
	if (current == root)  remove (root);
	else
		{if (previous->left == current) remove(previous->left);
		 else remove (previous->right);
		}

}//END SearchAndDestroy;





//helping function to search and destroy
//important:  the input is the actual pointer inside the tree

template<class BaseData>
void tree<BaseData>:: remove(TreeNode<BaseData>* &current)
{	TreeNode<BaseData> *previous, *temp;
// (*the pointer sent in is the parent (left or right) in the tree*)
       temp = current;
       if (current->left == 0 && current->right == 0)  //leaf node
	   current = 0;                                //parent is null
       else
	  {
	    if (current->left == 0)       //  no left child
		current = current->right; //  replace with right child
	    else                          //  has left child
	       {  temp = current->left;
		  previous = current;
		  while (temp->right != 0)
		   { previous = temp;     // locate TreeNode that has the
		     temp = temp->right;  // largest value smaller than
		   }                      // the value of TreeNode to be
					  // deleted
		  current->TreeData = temp->TreeData; // replace with
						//that TreeData
		  if (previous == current)      //  replace is left child
		      previous->left = temp->left;
		  else
		      previous->right = temp->left;// replace is down rt
						  // subtree of left child
	       }

	  }
    delete temp;
}//END Delete;

//returns true if the tree is empty   otherwise false
template<class BaseData>
int tree<BaseData> :: emptyTree()  const
{
return !root;
}

//returns true if the tree is full   otherwise false
template<class BaseData>
int tree<BaseData> :: fullTree()   const
{
	TreeNode<BaseData> *temp = new TreeNode<BaseData>;

	if (!temp) return 1;
	delete temp;
	return 0;
}


//inserts a data item of base data type into the tree
//uses helping function insertnode
template <class BaseData>
void tree<BaseData> ::insert(BaseData &item)
{
	insertNode(&root, item);
}


//helping function for insert
//this takes the address of a pointer to a node and inserts
//item into the ordered binary tree headed
//by that node.  This assumes overloaded comparison operators
//for class BaseData.
template <class BaseData>
void tree<BaseData>::insertNode(TreeNode<BaseData>** into, BaseData& item)
{
	//cout << item << " inserted " << endl;
  if (!(*into))
	{*into = getnode(item);
	return;
	}
  if ( item < (*into)->TreeData &&  !((*into)->left))
       (*into)->left = tree<BaseData>::getnode(item);
  else if (item < (*into)->TreeData)
       insertNode (&((*into)->left),item);
  else if (item >= (*into)->TreeData && !((*into)->right))
       (*into)->right = tree<BaseData>::getnode(item);
  else insertNode ( &((*into)->right), item);

}

//gets storage for a new node to be inserted into the tree
template <class BaseData>
TreeNode <BaseData>*  tree<BaseData>::getnode(BaseData &item)
{
	TreeNode<BaseData> *temp = new TreeNode<BaseData>;
	if (temp)
	  {
		temp->TreeData = item;
		temp->left = 0;
		temp->right = 0;
	  }
	  return temp;
}

//helping function for copy constructor and =operator
//it copies the ordered tree pointed to by "from" into
//another ordered binary tree whose root
//node has its address in the "into" pointer.

//helping function for copy constructor and =operator
template <class BaseData>
void tree<BaseData>::copyTreeNode (TreeNode <BaseData>** into,
					TreeNode<BaseData>* from)
{
	if(!from) return;
	insertNode( &(*into), from->TreeData);
	copyTreeNode( &(*into), from->left);
	copyTreeNode(&(*into), from->right);
}

//writes the tree in three different orders: pre,in, post and uses the respective helping functions
//requires input of a choice 1-2-3 for the order desired.
template <class BaseData>
void tree<BaseData>::writeTree(int choice)
{    switch (choice) {
	case 1 : tree<BaseData>::preOrder(root);
		 break;
	case 2 : tree<BaseData>::inOrder(root);
		 break;
	case 3 : tree<BaseData>::postOrder(root);
		 break;
	default :  cout << "tree not written" << endl;
	}//end switch
}//end write Tree

template <class BaseData>
string tree<BaseData>::encode(BaseData target)
{
	cout << "searching for " << target << endl;
	TreeNode<BaseData> *previous, *current;
	string code = "";
	current = root;
	previous = 0;
	
	while (current && (current->TreeData != target))
	{
		previous = current;
		if (current->TreeData > target)
		{
			cout << "current data freq " << current->TreeData.freq << endl;
			cout << "left" << endl;
			code += '0';
			current = current->left;
		}
		else
		{
			cout << "right" << endl;
			code += '1';
			current = current->right;
		}
	}  //(*while*)
	//if (!current)    //target not found
	//{
	//	cout << "target not found " << endl;
	//	return code;
	//}
	if (current == root)
		code = "1";
	cout << "code " << code << endl;
	return code;
	//remove requires the actual node in the tree
	/*if (current == root)  remove(root);
	else
	{
		if (previous->left == current) remove(previous->left);
		else remove(previous->right);
	}
*/
}//END SearchAndDestroy;

#endif
