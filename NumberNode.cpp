#include "NumberNode.h"
NumberNode::NumberNode()	//constructor
{
	number = 0;
	bst = new CarBST();
	pLeft = NULL;
	pRight = NULL;
}

NumberNode::NumberNode(int num)//constructor
{
	number = num;
	bst = new CarBST();
	pLeft = NULL;
	pRight = NULL;
}

NumberNode::~NumberNode()//destructor
{
	delete bst;
}



int			NumberNode::GetNumber()						// Get Number
{
	return number;
}

NumberNode *	NumberNode::GetLeft()						// Get BST Left Pointer
{
	return pLeft;
}

NumberNode *	NumberNode::GetRight()						// Get BST Right Pointer
{
	return pRight;
}

CarBST *		NumberNode::GetBST()						// Get Car BST
{
	return bst;
}


void			NumberNode::SetNumber(int num)				// Set Alphabet
{
	number = num;
}

void			NumberNode::SetLeft(NumberNode * node)		// Set BST Left Pointer
{
	pLeft = node;
}

void			NumberNode::SetRight(NumberNode * node)	// Set BST Right Pointer
{
	pRight = node;
}

void 			NumberNode::SetBST(CarBST * node)			// Set Car BST
{
	bst = node;
}
