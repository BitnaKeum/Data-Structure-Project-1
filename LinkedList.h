#pragma once
#include "CarNode.h"

class LinkedList
{
public:
	CarNode * pHead;
	CarNode * pCur;
	CarNode * pPre;
	int nodeCnt;

	LinkedList();
	~LinkedList();

	void Insert(CarNode * node);	//LOAD, ADD
	CarNode * Search(int carNum);		//SEARCH
	bool Print();	//PRINT
	bool Save(ofstream& fname);	//SAVE
	CarNode* Delete(int carNum);
	void clear();
};
