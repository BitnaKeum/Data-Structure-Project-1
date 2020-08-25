#include "Manager.h"
#include <stdlib.h>


using namespace std;

Manager::Manager()	//constructor
{
	ll = new LinkedList();
	bst = new NumberBST();
	queue = new Queue();
}

Manager::~Manager()//destructor
{
	delete ll;
	delete bst;
	delete queue;
}


// Function that execute commands by reading "command.txt"
void Manager::run(const char * command)
{
	fin.open(command);	// open the file
	flog.open("log.txt", ios::app);	// Open file in append format

	char temp[40] = { 0 };


	// repeat until reach the end of file
	while (!fin.eof())
	{
		fin.getline(temp, 40);	// Read a single line from command.txt and save in temp
		if (*temp == '\0')	break; // To filter out whitespace at the end line of "command.txt"
		char * cmd = strtok(temp, " ");	// Save the command in cmd



		if (!strcmp(cmd, "LOAD")){	// if command is "LOAD"

			if (LOAD()) printSuccessCode("LOAD");	// LOAD function is implemented well
			else printErrorCode(100);	// error occurs in LOAD function 

		}

		else if (!strcmp(cmd, "ADD")) {	// if command is "ADD"
			if (ADD("car.txt")) printSuccessCode("ADD");	// ADD function is implemented well
			else printErrorCode(200);	// error occurs in ADD function 
		}

		else if (!strcmp(cmd, "MOVE")) {	// if command is "MOVE"
			char *par_num;
			par_num = strtok(NULL, " ");

			if (MOVE(atoi(par_num))) printSuccessCode("MOVE");	// MOVE function is implemented well
			else printErrorCode(300);	// error occurs in MOVE function 
		}

		else if (!strcmp(cmd, "SAVE")) {	// if command is "SAVE"
			if (SAVE()) printSuccessCode("SAVE");	// SAVE function is implemented well
			else printErrorCode(400);	// error occurs in SAVE function 
		}

		else if (!strcmp(cmd, "SEARCH")) {	// if command is "SEARCH"
			char *par_num;
			par_num = strtok(NULL, " ");
			
			if (!SEARCH(atoi(par_num)))	// implement SEARCH function
				printErrorCode(500);	// error occurs in SEARCH function 
		}

		else if (!strcmp(cmd, "PRINT")) {	// if command is "PRINT"

			char *par_list, *par_order;

			par_list = strtok(NULL, " ");
			par_order = strtok(NULL, " ");
			
			if (!PRINT(par_list, par_order))	// implement PRINT function
				printErrorCode(600);			// error occurs in PRINT function 
		}

		else if (!strcmp(cmd, "COMPLETE")) {	// if command is "COMPLETE"
			char *par_num;
			par_num = strtok(NULL, " ");

			if (!COMPLETE(atoi(par_num)))	// implement COMPLETE function
				printErrorCode(700);		// error occurs in COMPLETE function 
		}

		else   {                      	// if command is "EXIT"
			EXIT();							// implement EXIT function
		}
	}

	// close the file
	fin.close();
	flog.close();
	return;
}


// Function to reproduce data structure by reading data from file
bool Manager::LOAD() 
{
	// open the files as input stream
	ifstream fTotal("total_list_car.txt");
	ifstream fEvent("event_list_car.txt");
	ifstream fComplete("complete_list_car.txt");

	// If any of the three text files does not exist, return false
	if (!fTotal || !fEvent || !fComplete)			return false;
	// If there is data in at least one of the three data structures, return false
	if (ll->pHead || bst->getCnt() || queue->pHead)	return false;

	// If "total_list_car.txt" file exists but no internal data exists, return false
	// remake TOTAL_LIST using ADD function
	if (!ADD("total_list_car.txt"))
		return false;
	rTotal.close();


	// remake EVENT_LIST
	int temp_carnum = 0;
	char temp_state;

	// repeat until reach the end of file
	while (!fEvent.eof())
	{
		// Dynamic memory allocation because it must contain multiple addresses
		char *temp_name = new char[10];	

		// read data from the file
		fEvent >> temp_carnum >> temp_name >> temp_state;

		/* If do not reach the end of the file but it is null character, 
		   the data in the file does not exist. so error occurs*/
		if (temp_carnum == '\0')	return false;
		// To filter out whitespace at the end line of "car.txt"
		if (*temp_name == '\0')		break;
		
		// Create a node with the read information
		CarNode * NewNode = new CarNode(temp_carnum, temp_name, temp_state);

		NumberNode* numNode = bst->Search(temp_carnum / 1000);	// search NumberNode
		numNode->GetBST()->Insert(NewNode);	// insert NewNode to CarBST
		bst->setCnt(bst->getCnt() + 1);
	}
	rEvent.close();

	// remake COMPLETE_LIST
	while (!fComplete.eof())
	{
		// Dynamic memory allocation because it must contain multiple addresses
		char *temp_name = new char[10];

		fComplete >> temp_carnum >> temp_name >> temp_state;

		/* If do not reach the end of the file but it is null character,
		the data in the file does not exist. so error occurs*/
		if (temp_carnum == '\0')	return false;

		// To filter out whitespace at the end line of "car.txt"
		if (*temp_name == '\0')		break;
		
		// Create a node with the read information
		CarNode * NewNode = new CarNode(temp_carnum, temp_name, temp_state);

		queue->Push(NewNode);	// insert NewNode to Queue
	}
	fComplete.close();

	return true;
}

// Function that creates LinkedList by reading data from "car.txt"
bool Manager::ADD(char *par_txt)
{
	ifstream AddText(par_txt);

	if (!AddText)	return false;	// file does not exist

	int temp_carnum = 0;
	char temp_state = 0;
	
	// repeat until reach the end of file
	while (!AddText.eof())
	{
		// Dynamic memory allocation because it must contain multiple addresses
		char *temp_name = new char[10];

		AddText >> temp_carnum >> temp_name >> temp_state;

		/* If do not reach the end of the file but it is null character,
		the data in the file does not exist. so error occurs*/
		if (temp_carnum == '\0')	return false;

		// To filter out whitespace at the end line of "car.txt"
		if (*temp_name == '\0')		break;

		NumberNode* ptemp = bst->Search(temp_carnum / 1000);
		if (ll->Search(temp_carnum) || ptemp->GetBST()->Search(temp_carnum) || queue->Search(temp_carnum) )			
			continue;


		CarNode * NewNode = new CarNode(temp_carnum, temp_name, temp_state);
		
		ll->Insert(NewNode);	// insert NewNode in Linked List

	}
	AddText.close();

	return true;
}

// function that moves n nodes whose state is 'Y' from the linked list to BST
bool Manager::MOVE(int n)
{
	if( bst->getCnt() + n > 100 ||	// if the number of data of EVENT_LIST and the sum of n exceeds 100
		n < 1 || n > 100	    ||	// if n is not a number between 1 and 100
		ll->pHead == NULL )			// if L.L is empty
		return false;


	int cnt = 0;

	ll->pCur = ll->pHead;
	while (ll->pCur != NULL) {
		if (ll->pCur->Getstate() == 'Y')	cnt++;
		ll->pCur = ll->pCur->GetNext();
	}
	// store the number of nodes with state 'Y' in cnt in L.L

	// The error occurs when the node with state 'Y' in L.L is less than n
	if (cnt < n)	return false;		
		


	cnt = 0;	// Count the number of nodes moved to EVENT_LIST

	ll->pCur = ll->pHead;
	while (ll->pCur != NULL)	// repeat until reach the last node of L.L
	{
		if (cnt == n)	// If cnt is equal to the input number, exit the loop 
			break;

		// Find node with state 'Y' in Total List
		if (ll->pCur->Getstate() == 'Y')	
		{
			// delete the currently pointing node from L.L
			// and return the address of the node that copied the information of the deleted node
			CarNode* pCopy = ll->Delete(ll->pCur->GetcarNum());

			// pNumNode points the corresponding NumberNode in NumberBST
			NumberNode* pNumNode = bst->Search(pCopy->GetcarNum() / 1000);
			// Insert the copy node in CarBST
			pNumNode->GetBST()->Insert(pCopy);

			cnt++;
			bst->setCnt(bst->getCnt() + 1);
			/* node is added to CarBST, 
			  but a variable that counts the number of nodes exists in NumberBST, 
			  so the number is increased in Manager */
		}
		else
			ll->pCur = ll->pCur->GetNext();
	}

	return true;
}

// A function that finds a node with num as the car number
bool Manager::SEARCH(int num)
{
	CarNode* getCarAdd = NULL;
	NumberNode* getNumAdd = NULL;

	getCarAdd =	ll->Search(num);	// Search in L.L
	if (getCarAdd == NULL) {	// not in L.L
		getNumAdd = bst->Search(num/1000);
		getCarAdd = getNumAdd->GetBST()->Search(num);	// Search in CarBST
	
		if (getCarAdd == NULL)	// not in carBST
		{
			getCarAdd = queue->Search(num);	// Search in Queue

			if (getCarAdd == NULL)	return false;	
			// if there is no information in all data structures, error occurs
		}
	}

	// print the information of CarNode
	cout << "======== SEARCH ========" << endl;
	cout << getCarAdd->GetcarNum() << " " 
		<< getCarAdd->GetcarOwner() << " " 
		<< getCarAdd->Getstate() << endl;
	cout << "========================" << endl << endl;

	// save in log.txt
	flog << "======== SEARCH ========" << endl;
	flog << getCarAdd->GetcarNum() << " " << getCarAdd->GetcarOwner() << " "
		<< getCarAdd->Getstate() << endl;
	flog << "========================" << endl << endl;

	return true;
}

// Function that prints all the data in the desired list
bool Manager::PRINT(char *par_list, char *par_order)
{
	if (!strcmp(par_list, "TOTAL_LIST"))	// if par_list is "TOTAL_LIST" 
	{
		if (!ll->Print())
			return false;	// if L.L does not exists, error occurs
	}

	else if (!strcmp(par_list, "EVENT_LIST"))	// if par_list is "EVENT_LIST"
	{
		if (!bst->Print(par_order))	
			return false;	// if NumberBST does not exists, error occurs
	}

	else     // if par_list is "COMPLETE_LIST"
	{
		if (!queue->Print())	
			return false;	// if Queue does not exits, error occurs
	}

	return true;
}

// A function that moves a node whose car number is num in CarBST to Queue
bool Manager::COMPLETE(int num) 
{
	NumberNode* getNumAdd = NULL;
	CarNode* getCarAdd = NULL;

	getNumAdd = bst->Search(num/1000);	// save the address of NumberNode
	if (getNumAdd == NULL)	return false;	// if there is no corresponding NumberNode, error occurs
	
	// delete the CarNode from CarBST
	// returns the address of the node that stored the information of the deleted node
	getCarAdd = getNumAdd->GetBST()->Delete(num);
	if (getCarAdd == NULL)	return false;	// If the corresponding CarNode does not exist, error occurs
	
	bst->setCnt(bst->getCnt() - 1);	// decrement nodeCnt of bst

	getCarAdd->Setstate('C');	// change state from 'Y' to 'C'

	// print the updated information of CarNode
	cout << "====== COMPLETE ======" << endl;
	cout << getCarAdd->GetcarNum() << " " << getCarAdd->GetcarOwner() << " " << getCarAdd->Getstate() << endl;
	cout << "======================" << endl << endl;
	// save in log.txt
	flog << "====== COMPLETE ======" << endl;
	flog << getCarAdd->GetcarNum() << " " << getCarAdd->GetcarOwner() << " " << getCarAdd->Getstate() << endl;
	flog << "======================" << endl << endl;

	queue->Push(getCarAdd);	// push the CarNode in Queue

	return true;
}

/* A function that stores the information of the data structures 
   implemented up to now in a file */
bool Manager::SAVE()
{
	//If there is no data in any of the three data structures, return false
	if (!ll->Save(fTotal) || !bst->Save() || !queue->Save(fComplete))
		return false;


	return true;
}

// function to release all memories used in program and quit the program
void Manager::EXIT()
{
	ll->~LinkedList();	// implement destructor of L.L
	bst->~NumberBST();	// implement destructor of NumberBST
	queue->~Queue();	// implement destructor of Queue

	// if L.L and BST and Queue are all empty, print success code
	if (!ll->nodeCnt && !bst->getCnt() && !queue->size)
		printSuccessCode("EXIT");
	else
		printErrorCode(0);	// print error code
}







void Manager::printErrorCode(int n) {				//ERROR CODE PRINT 
	cout << "======== ERROR ========" << endl;
	cout << n << endl;
	cout << "=======================" << endl << endl;

	// save in log.txt
	flog << "======== ERROR ========" << endl;
	flog << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode(const char * cmdname) {//SUCCESS CODE PRINT 
		cout << "======== " << cmdname << " ========" << endl;
		cout << "Success" << endl;
		cout << "=======================" << endl << endl;

		// save in log.txt
		flog << "======== " << cmdname << " ========" << endl;
		flog << "Success" << endl;
		flog << "=======================" << endl << endl;
}