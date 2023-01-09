#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

	int		count;
	BTNode* root;

	// print operation for BST (same as BT)					
	void preOrderPrint2(BTNode*);	// recursive function for preOrderPrint()
	void inOrderPrint2(BTNode*);	// recursive function for inOrderPrint()
	void postOrderPrint2(BTNode*);	// recursive function for postOrderPrint()

	// sample operation (extra functions) - same as BT
	void countNode2(BTNode*, int&);		// recursive function for countNode()
	bool fGS2(type, BTNode*);					// recursive function for findGrandsons(): to find the grandfather
	void fGS3(BTNode*, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found

	// basic functions for BST
	void insert2(BTNode*, BTNode*);		// recursive function for insert() of BST
	void case3(BTNode*);					// recursive function for remove()
	void case2(BTNode*, BTNode*);		// recursive function for remove()
	bool remove2(BTNode*, BTNode*, type);	// recursive function for remove()


	// basic functions for BST
	BST();
	bool empty();
	int size();
	bool insert(type);		// insert an item into a BST
	bool remove(type);			// remove an item from a BST

	// print operation for BST (same as BT)
	void preOrderPrint();			// print BST node in pre-order manner
	void inOrderPrint();			// print BST node in in-order manner
	void postOrderPrint();			// print BST node in post-order manner
	void topDownLevelTraversal();	// print BST level-by-level

	// sample operation (extra functions) - same as BT
	int countNode();		// count number of tree nodes
	bool findGrandsons(type);	// find the grandsons of an input father item

	/********************************************************************************************************************************************************/
	//Our work start here
	//caller in our program usually settle special cases and call the subfunction do undergo recursion

	//Question 1 
	// readfile in app.cpp
	bool checkduplicate(Student stu); //use to check duplicate and return true if found

	//Question 2 
	int height(BTNode*); //calcalate height (also been use in question 6)
	void printdeepest(BTNode*, int, int);//print the level
	bool deepestNodes(); //caller

	//Question 3 
	bool display(int, int); //caller
	void displayAsc(BTNode*, ostream&); //display ascending
	void displayDesc(BTNode*, ostream&); //display descending

	//Question 4
	bool CloneSubtree(BST, type); //caller
	void cs1(BTNode* cur, type item); //search
	void cs2(BTNode* cur); //cloning

	//Question 5 
	bool printAncestor(type item); //caller
	bool pa2(BTNode* cur, type item); //print

	//Question 6
	//also use height which in question 2
	void printlevel(BTNode*, int, bool); //print each level
	bool printSpiral(); //caller
};

#endif