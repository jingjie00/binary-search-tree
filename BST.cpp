#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode* cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode* cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode* pre, BTNode* cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

/*************************************************************************************************************************************************************/
// our work start here

//Question 1 sub function
bool BST::checkduplicate(Student stu)
{
	BTNode* cur = root;
	while (cur != NULL)
		if (cur->item.compare2(stu)) {//if same
			cur->item = stu;//for update purpuse
			return true;
		}
		else if (cur->item.compare1(stu))
			cur = cur->left;
		else
			cur = cur->right;
	return false;
}

/*============================================================================================================================================================*/
//Question 2 and 5 sub function
int BST::height(BTNode* cur)
{
	if (cur == NULL)return 0;//if node is null mean that is ald end of a tree, return 0. Following max() will given result 1, indicate 1 node is proceed
	return max(height(cur->left), height(cur->right)) + 1; //if left is more deeper than right, the function will return height of the left and +1. +1 indicate it self
}// max also can be replaced by if else statement by creating 2 variable. But since already included algorithm header so just use it.

/*============================================================================================================================================================*/
//Question 2
void BST::printdeepest(BTNode* cur, int deep, int level)
{
	if (cur == NULL) return;//if until last row
	printdeepest(cur->left, deep, level + 1);//repeat call until target level
	printdeepest(cur->right, deep, level + 1);
	if (level == deep) //if match target level
		cur->item.print(cout);
	return;
}

bool BST::deepestNodes()
{
	if (empty()) return false; 	// special case
	printdeepest(root, height(root), 1); //caller
	return true;
}

/*============================================================================================================================================================*/
//Question 3
bool BST::display(int order, int source)
{
	ofstream file;
	file.open("student-info.txt");
	if (empty()) return false;	// special case when the tree is empty
	if (order == 1)			// Normal case, We didnt combined the displayAsc and dispayDesc funtion because we needed to reduce the time for compute.
		if (source == 1)	// If do so the program need to check is it Asceding or descending every call
			displayAsc(root, cout);
		else
			displayAsc(root, file);
	else
		if (source == 1)
			displayDesc(root, cout);
		else
			displayDesc(root, file);
	file.close();
	return true;
}

void BST::displayAsc(BTNode* cur, ostream& outt) //print ascending different with descending only left first or right first
{
	if (cur == NULL) return;
	displayAsc(cur->left, outt);
	cur->item.print(outt);
	displayAsc(cur->right, outt);
}

void BST::displayDesc(BTNode* cur, ostream& outt) //similar with ascending, different with right first or left first
{
	if (cur == NULL) return;
	displayDesc(cur->right, outt);
	cur->item.print(outt);
	displayDesc(cur->left, outt);
}

/*============================================================================================================================================================*/
//Question 4
bool BST::CloneSubtree(BST t1, type target)
{
	if (t1.empty()) return false;	// special case when the t1 is empty
	cs1(t1.root, target);
	return true;
}

void BST::cs1(BTNode* cur, type target) { //searching the target nodes

	if (cur == NULL) {
		cout << "The student id-" << target.id << " is not found in the tree" << endl; //cannot find
		return;	//terminate when the traversal reaches the last node and yet the target is not found
	}
	if (cur->item.compare2(target))	//when the target is found, proceed to next function and start cloning
		cs2(cur);
	else if (cur->item.compare1(target))	//if the target is smaller then the current item, proceed to left node
		cs1(cur->left, target);
	else 	//if the target is greater then the current item, proceed to right node
		cs1(cur->right, target);

}

void BST::cs2(BTNode* cur) //cloning
{
	if (!insert(cur->item))	// clone and insert the current nodes 
		return;
	if (cur->left != NULL)	// check and clone if the left son exist
		cs2(cur->left);
	if (cur->right != NULL)	// check and clone if the right son exist
		cs2(cur->right);
}

/*============================================================================================================================================================*/
//Question 5
bool BST::printAncestor(type target)
{
	if (empty()) return false;		// special case

	if (root->item.compare2(target)) {	// case: if the target item is the root 
		cout << "There are no Ancestor (as student ID entered is root of the tree) for student ID:" << target.id << endl;
		return true;
	}
	return pa2(root, target); //run the recursive and print out ancestor or print out not in the tree
}

bool BST::pa2(BTNode* cur, type target) //print ancestor
{
	if (cur == NULL)	// return false when the traversal reaches the end node
		return false;   // mean the target is not found
	if (cur->item.compare2(target))	// return true when the target is found
	{
		cout << "The detail for the id: " << target.id << " as below" << endl;
		cur->item.print(cout);
		cout << "\n\n***********************************************************************************" << endl << endl;
		cout << "The ancestor(s) of above record as below:" << endl;
		return true;
	}
	if (cur->item.compare1(target)) {	// when the target is smaller than current item, proceed the searching to left node
		if (pa2(cur->left, target)) {// when the target is found in the subsequent nodes, print the current item
			cur->item.print(cout);
			return true;
		}
	}
	else if (cur->item.id < target.id) {	// when the target is smaller than current item, proceed the searching to right node
		if (pa2(cur->right, target)) {	// when the target is found in the subsequent nodes, print the current item
			cur->item.print(cout);
			return true;
		}
	}
	return false;//Once after exit the if else statement above with cant find the match node, it will go onto this statement and continue return false to first caller (findAncestor)
}

/*============================================================================================================================================================*/
//Question 6
void BST::printlevel(BTNode* cur, int level, bool flag)
{
	if (cur == NULL) return;
	if (level == 1)  //when the function go by recursive call the level will decrease, when it until 1 mean that the target level is reach and print out
		cur->item.print(cout);
	else if (flag) {//indicate by the flag, either proceed to left or right
		printlevel(cur->left, level - 1, flag);
		printlevel(cur->right, level - 1, flag);
	}
	else {
		printlevel(cur->right, level - 1, flag);
		printlevel(cur->left, level - 1, flag);
	}
}

bool BST::printSpiral()
{
	if (empty()) return false; 	// special case
	int deep = height(root);
	bool flag = false;
	for (int i = 1; i <= deep; i++) {
		cout << "************************* " << i << " layer *************************" << endl; //**this line can be removed
		printlevel(root, i, flag); //flag can be replaced by !(i/2) for optimise purpose
		flag = !flag;
	}
	return true;
}

//alternate solution(without recursive)
/*
bool BST::printSpiral()
{
	BTNode* cur1, * cur2;
	Queue q1, q2;
	bool flag = false;
	int  curlayer = 1, nextlayer = 0;

	if (empty()) return false; 	// special case
	q1.enqueue(root);
	q2.enqueue(root);	// Step 1: enqueue the first node
	while (!q1.empty())
	{
		q1.dequeue(cur1);
		q2.dequeue(cur2);
		curlayer--;
		if (cur1 != NULL && cur2 != NULL) {
			if (flag)
				cout << cur1->item.id << "\t";
			else
				cout << cur2->item.id << "\t";

			// enqueue the nodes from the left
			if (cur1->left != NULL)		// check and enqueue if the left son exist
			{
				q1.enqueue(cur1->left);
				nextlayer++;		// update the number of nodes in next level
			}
			if (cur1->right != NULL)	// check and enqueue if the right son exist
			{
				q1.enqueue(cur1->right);
				nextlayer++;		// update the number of nodes in next level
			}

			// enqueue the nodes from the right
			if (cur2->right != NULL)
				q2.enqueue(cur2->right);
			if (cur2->left != NULL)
				q2.enqueue(cur2->left);
		}
		if (curlayer == 0)
		{
			cout << endl;
			flag = !flag;	// reverse the printing direction
			curlayer = nextlayer;		// update the total nodes in next level when proceed to next level
			nextlayer = 0;		// reset the next level node counter
		}
	}
	cout << endl;
	return true;
}
*/
