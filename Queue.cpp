#include "Queue.h"

using namespace std;

Queue::Queue()//constructor
{
	pHead = NULL;
	pTail = NULL;
	pCur = NULL;
	size = 0;
}


Queue::~Queue()//destructor
{
	// implemente Pop function until (size == 0)
	while (size)
		Pop();
}



void		Queue::Push(CarNode * node)			// LOAD
{
	// if there is node that has same number, return
	if (Search(node->GetcarNum()) != NULL) return;

	if (pHead == NULL)
	{
		pHead = node;
		pTail = node;
		// If there is only one node in the queue, both pHead and pTail refer to that node.
	}
	else
	{
		pTail->SetNext(node);	// Connect the new node to the last node in the queue
		pTail = node;
	}

	size++;
}

// function to pop the frontmost element
void	Queue::Pop()
{
	pCur = pHead;

	pHead = pCur->GetNext();	
	// disconnect the first element from the queue

	if (pHead == NULL) pTail = NULL;	//  queue is empty

	size--;		// decrement the size of queue
	delete(pCur);
}

CarNode *	Queue::Search(int num)				// SEARCH
{
	pCur = pHead;

	while (pCur != NULL) {	// repeat until pCur is NULL 
		if (pCur->GetcarNum() == num)	// if finds the node that has num, exit the loop
			break;

		pCur = pCur->GetNext();	// pCur points the next node
	}

	return pCur;	// return the address pCur points
}

// function to print the information of all nodes in queue
bool		Queue::Print()						// PRINT
{
	if (pHead == NULL)	return false;

	ofstream flog("log.txt", ios::app);

	cout << "======== PRINT ========" << endl;
	flog << "======== PRINT ========" << endl;

	pCur = pHead;
	while (pCur != NULL)
	{
		// print information of all nodes in queue 
		cout << pCur->GetcarNum() << " " << pCur->GetcarOwner() << " "
			<< pCur->Getstate() << endl;
		// save in log.txt
		flog << pCur->GetcarNum() << " " << pCur->GetcarOwner() << " "
			<< pCur->Getstate() << endl;

		pCur = pCur->GetNext();	// pCur points the next node
	}

	cout << "=======================" << endl << endl;
	flog << "=======================" << endl << endl;

	flog.close();

	return true;
}

// function to save the data of all nodes 
bool		Queue::Save(ofstream& fname)
{
	if (pHead == NULL)	return false;		// if there is no data in Queue, error occurs

	pCur = pHead;
	while (pCur != NULL) {
		// save data in output stream
		fname << pCur->GetcarNum() << '\t' << pCur->GetcarOwner() << '\t'
			<< pCur->Getstate() << '\n';

		pCur = pCur->GetNext();	// pCur points the next node
	}

	return true;
}