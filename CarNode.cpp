#include "CarNode.h"
#include<cstring>

CarNode::CarNode()	//default constructor
{
	carNumber = 0;
	name = NULL;
	state = 0;

	pLeft = NULL;
	pRight = NULL;
	pNext = NULL;
}

CarNode::CarNode(int carNum, char* carOwner, char state)	//constructor that has parameters
{
	carNumber = carNum;
	name = carOwner;	// convey the address pointed by carOwner to name
	this->state = state;

	pLeft = NULL;
	pRight = NULL;
	pNext = NULL;
}

CarNode::~CarNode()//destructor
{
	/* You must fill here */
}




int CarNode::GetcarNum()		// Get car number
{
	return carNumber;
}
char * CarNode::GetcarOwner()	// Get car owner
{
	return name;
}
char CarNode::Getstate()		// Get state
{
	return state;
}

CarNode * CarNode::GetLeft()	// Get BST Left Pointer
{
	return pLeft;
}
CarNode * CarNode::GetRight()	// Get BST Right Pointer
{
	return pRight;
}
CarNode * CarNode::GetNext()	// Get Queue Next Pointer
{
	return pNext;
}

void CarNode::SetcarNum(int carNum)			// Set car number
{
	carNumber = carNum;
}
void CarNode::SetcarOwner(char * carOwner)	// Set car owner
{
	name = carOwner;
}
void CarNode::Setstate(char state)			// Set car state
{
	this->state = state;
}
void CarNode::SetLeft(CarNode * node)		// Set BST Left Pointer
{
	pLeft = node;
}
void CarNode::SetRight(CarNode * node)		// Set BST Right Pointer
{
	pRight = node;
}
void CarNode::SetNext(CarNode * node)		// Set Queue Next Pointer
{
	pNext = node;
}