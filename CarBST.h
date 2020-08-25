#pragma once
#include "CarNode.h"
#include <iostream>
#include <fstream>// header file declare
using namespace std;
class CarBST
{
public:
	CarNode * root;	
	CarNode * p;
	CarNode * q;	// parent of p

public:
	CarBST();
	~CarBST();

	void		Insert(CarNode * node);			// LOAD, MOVE
	CarNode *	Delete(int num);				// COMPLETE
	CarNode *	Search(int num);				// ADD, COMPLETE, SEARCH
	bool		Print(const char * order);		// PRINT
	bool		Save();							// SAVE
	void		Inorder(CarNode *node);
	void		Preorder(CarNode *node);
	void		Postorder(CarNode *node);
	void		clear(CarNode* Root);
};

