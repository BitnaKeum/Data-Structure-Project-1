#pragma once
#include "LinkedList.h"
#include "NumberBST.h"
#include "Queue.h"
#include<utility>


class Manager
{
public:
	LinkedList * ll;
	NumberBST * bst;
	Queue * queue;

	ifstream fin;
	ofstream flog;

	ofstream wTotal;
	ofstream wEvent;
	ofstream wComplete;
	ifstream rTotal;
	ifstream rEvent;
	ifstream rComplete;

public:
	Manager();
	~Manager();

	void run(const char * command);
	bool LOAD();
	bool ADD(char *par_txt);
	bool MOVE(int n);
	bool SAVE();
	bool SEARCH(int num);
	bool PRINT(char *par_list, char *par_order);
	bool COMPLETE(int num);
	void EXIT();

	void printErrorCode(int n);
	void printSuccessCode(const char * cmdname);

};
