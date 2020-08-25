#pragma once
#include "CarNode.h"
class Queue
{
public: 	

// member variable
	CarNode * pHead;
	CarNode * pTail;
	CarNode * pCur;
	int size;

// member funciton
	Queue();	
	~Queue();

	void		Push(CarNode * node);			// LOAD
	void		Pop();							
	CarNode *	Search(int num);				// SEARCH
	bool		Print();						// PRINT
	bool		Save(ofstream& fname);
};

