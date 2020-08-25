#include "LinkedList.h"
#include <fstream>
using namespace std;

LinkedList::LinkedList()//constructor
{
	pHead = NULL;
	pCur = NULL;
	pPre = NULL;
	nodeCnt = 0;
}

LinkedList::~LinkedList()//destructor
{
	clear();
}




void LinkedList::Insert(CarNode * node)	//LOAD, ADD
{
	if (pHead == NULL)	// Linked List is empty
	{
		pHead = node;
		pCur = pHead;
	}
	else
	{
		pCur = pHead;
		while (pCur->GetNext() != NULL)	//If the node pointed to by pCur is not the end node of L.L
			pCur = pCur->GetNext();
		// After break the loop, pCur points the last node in L.L

		pCur->SetNext(node);
		pCur = node;
	}

	nodeCnt++;

}

// function to delete the node that has car number that is equal to carNum from L.L
CarNode* LinkedList::Delete(int carNum)
{
	pCur = pHead;
	pPre = NULL;

	while (pCur != NULL)
	{
		// if find the node that has carNum, then break the loop
		if (pCur->GetcarNum() == carNum)
			break;

		pPre = pCur;
		pCur = pCur->GetNext();	// pCur points the next node
	}
	// pCur points the node that has carNum

	if (pCur == NULL)	// If a node with carNum does not exist in L.L
		return NULL;

	// Create a pCopy node that copies the information of the pCur node before deletion
	CarNode* pCopy = new CarNode(pCur->GetcarNum(), pCur->GetcarOwner(), pCur->Getstate());

	// Disconnect a pCur node from a linked list
	if (pCur == pHead)		// If the node that pCur points is the first node
		pHead = pCur->GetNext();
	else 
		pPre->SetNext(pCur->GetNext());

	nodeCnt--;

	CarNode* pTemp = pCur->GetNext();
	delete pCur;	// release the memory of pCur
	pCur = pTemp;

	return pCopy;	// return the copy node
}

// function to find the node that has carNum in L.L
CarNode * LinkedList::Search(int carNum)	//SEARCH
{
	pCur = pHead;

	while (pCur != NULL)
	{
		if (pCur->GetcarNum() == carNum)
			return pCur;		// if search the node that has carNum, return the current node
	
		pCur = pCur->GetNext();	// pCur points the next node
	}

	return NULL;		// node with carNum does not exist in L.L
}

// function to print information of all nodes in L.L
bool LinkedList::Print()	//PRINT
{
	if (pHead == NULL)	return false;
	
	ofstream flog("log.txt", ios::app);	// output stream, appendable

	cout << "======== PRINT ========" << endl;
	flog << "======== PRINT ========" << endl;

	pCur = pHead;	// pCur points the first node in L.L
	while (pCur != NULL)	// print information of all nodes in L.L
	{
		cout << pCur->GetcarNum() << " " << pCur->GetcarOwner() << " "
			<< pCur->Getstate() << endl;
		flog << pCur->GetcarNum() << " " << pCur->GetcarOwner() << " "
			<< pCur->Getstate() << endl;	// save in log.txt

		pCur = pCur->GetNext();	// pCur points the next node in L.L
	}

	cout << "=======================" << endl << endl;
	flog << "=======================" << endl << endl;

	flog.close();

	return true;
}

// function to save data of all nodes in L.L
bool LinkedList::Save()	//SAVE
{
	if (pHead == NULL) return false;		// if there is no data in L.L, error occurs

	ofstream wTotal("total_list_car.txt");	

	pCur = pHead;
	while (pCur != NULL) {
		// output the information to output stream
		wTotal << pCur->GetcarNum() << '\t'
			<< pCur->GetcarOwner() << '\t'
			<< pCur->Getstate() << '\n';

		pCur = pCur->GetNext();	// pCur points the next node
	}

	wTotal.close();
	return true;
}

// function used in destructor
void LinkedList::clear()
{
	while (nodeCnt)	// repeat until L.L does not exist
	{
		pCur = pHead;

		pHead = pCur->GetNext();	// disconnect the frontmost node of L.L
		nodeCnt--;
		delete(pCur);				// deallocate the memory of the frontmost node
	}
}
