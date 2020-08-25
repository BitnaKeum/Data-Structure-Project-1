#pragma once
#include "NumberNode.h"
#include <iostream>
using namespace std;

class NumberBST
{
public:
	NumberNode * root;
	NumberNode * p;
	NumberNode * q;	// parent of p
	int nodeCnt;

public:
	NumberBST();
	~NumberBST();

	void		Insert(NumberNode * node);			// LOAD, MOVE
	void		Delete(NumberNode* Root);				// COMPLETE
	NumberNode *	Search(int num);				// ADD, COMPLETE, SEARCH
	bool		Print(char * order);					// PRINT
	bool		Save();								// SAVE
	void		Inorder(NumberNode *node);
	void		Preorder(NumberNode *node);
	void		Postorder(NumberNode *node);
	NumberNode * getRoot();
	int			getCnt();
	void		setCnt(int cnt);
	bool		clear();
};
