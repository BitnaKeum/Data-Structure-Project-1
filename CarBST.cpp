#include "CarBST.h"
#include <queue>
#include <stack>
#include <fstream>
using namespace std;

CarBST::CarBST()//constructor
{
	root = NULL;
	p = NULL;
	q = NULL;
}


CarBST::~CarBST()//destructor
{
	while (root)
		clear(root);
}



void		CarBST::Insert(CarNode * node)			// LOAD, MOVE
{
	if (root == NULL)	// if Car BST is empty, connect root to new node
		root = node;	//If Car BST is not yet created, connect root to the new node
	else
	{
		p = root;

		while (1)
		{
			if (p->GetcarNum() < node->GetcarNum())	// if the car number of new node is bigger
			{
				if (p->GetRight() == NULL)
				{
					p->SetRight(node);	//Connect to the lower right of the current node
					break;
				}

				p = p->GetRight();	// pCur points the right node
			}

			else if (p->GetcarNum() > node->GetcarNum())	//  if the car number of new node is smaller
			{
				if (p->GetLeft() == NULL)
				{
					p->SetLeft(node);	// Connect to the lower left of the current node
					break;
				}

				p = p->GetLeft();	// pCur points the left node
			}

			else
				break;	
			// If the node with that number already exists in BST, then exit without adding (no duplicate car number)
		}
	}
}

CarNode *	CarBST::Delete(int num)				// COMPLETE
{
	if (root == NULL)	return NULL;	// if CarBST is empty

	p = root; q = NULL;	// q is the parent node of p

	// Repeats until the node pointed to by p is the node that was passed node
	while (p->GetcarNum() != num)
	{
		q = p;

		// If the number of nodes currently pointing is smaller, p points the left node
		if (p->GetcarNum() < num)
			p = p->GetRight();
		// If the number of nodes currently pointing is bigger, p points the right node
		else
			p = p->GetLeft();

		if (p == NULL)	return NULL;	// If the node is not in the BST, error occurs
	}
	// When exit the while statement, p points node and q is an ancestor of p



	// Create a clone node pCopy that contains information about the node to be deleted
	CarNode *pCopy = new CarNode(p->GetcarNum(), p->GetcarOwner(), p->Getstate());

	// If there are no child nodes
	if (!p->GetLeft() && !p->GetRight())
	{
		if (p == root) 
			root = NULL;
		else if (p == q->GetLeft())	//When p is the lower left node of q
			q->SetLeft(NULL);
		else   //When p is the lower right node of q
			q->SetRight(NULL);

		delete p;
	}

	// If you have only the left child node
	else if (p->GetLeft() && !p->GetRight())
	{
		if (p == root)				// if p is root (q is NULL)
			root = p->GetLeft();
		else if (p == q->GetLeft())	// if p is the left subnode of q
			q->SetLeft(p->GetLeft());
		else   // if p is the right subnode of q
			q->SetRight(p->GetLeft());
		
		delete p;
	}

	// If you have only the right child node
	else if (!p->GetLeft() && p->GetRight())
	{
		if (p == root)				// if p is root (q is NULL)
			root = p->GetRight();
		else if (p == q->GetLeft())	// if p is the left subnode of q
			q->SetLeft(p->GetRight());
		else   // if p is the right subnode of q
			q->SetRight(p->GetRight());

		delete p;
	}

	// If you have both child nodes
	else
	{
		CarNode *prevprev = p, *prev = p->GetLeft(), *curr = p->GetLeft()->GetRight();
		
		while (curr)	// repeat until curr == NULL
		{
			prevprev = prev;
			prev = curr;
			curr = curr->GetRight();
		}
		/*  After the while statement, 
		   curr = 0, 
		   prev = the largest of the left child nodes, prevprev = the parent node of prev */


		//The node pointed to by p stores information about the node pointed to by prev.
		p->SetcarNum(prev->GetcarNum());
		p->SetcarOwner(prev->GetcarOwner());
		p->Setstate(prev->Getstate());

		if (prevprev == p)	// If there is no right child node in the left child node of p
			p->SetLeft(prev->GetLeft());
		else                //If there is right child node in the left child node of p
			prevprev->SetRight(prev->GetLeft());


		delete(prev);	
		// Releasing prev node's memory because we moved the information of prev node to p node
		prev = NULL;
	}

	return pCopy;	// Return pCopy containing deleted information
}

CarNode *	CarBST::Search(int num)				// ADD, COMPLETE, SEARCH
{
	p = root;
	if (p == NULL)	return NULL;	// CarBST does not exist

	while (1)
	{
		// if num is bigger
		if (p->GetcarNum() < num)
		{
			// if there is no node that has num
			if (p->GetRight() == NULL)
				return NULL;

			p = p->GetRight();	// pCur points the right node
		}

		// if num is smaller
		else if (p->GetcarNum() > num)
		{
			// if there is no node that has num
			if (p->GetLeft() == NULL)
				return NULL;

			p = p->GetLeft();		// pCur points the left node
		}

		// If there is a node with num
		else
			return p;	// return the address of current node
	}

}

bool		CarBST::Print(const char * order)		// PRINT
{
	if (root == NULL)	return false;	// CarBST does not exist

	ofstream flog("log.txt", ios::app);


	stack<CarNode*> S;

	if (!strcmp(order, "R_PRE"))	// recursive pre-order
	{
		Preorder(root);
	}

	else if (!strcmp(order, "I_PRE"))	// iterative pre-order
	{
		CarNode* curNode = root;
		S.push(curNode);	// push root into stack

		// repeat until stack S is empty
		while (!S.empty())
		{
			// initialize curNode to the value at the top of the stack
			curNode = S.top();
			// then pop the top of the stack
			S.pop();

			// print the information of CarNode
			cout << curNode->GetcarNum() << " " << curNode->GetcarOwner() << " "
				<< curNode->Getstate() << endl;
			// save in log.txt
			flog << curNode->GetcarNum() << " " << curNode->GetcarOwner() << " "
				<< curNode->Getstate() << endl;


			if (curNode->GetRight())
				S.push(curNode->GetRight());	// push the right element into stack
			if (curNode->GetLeft())
				S.push(curNode->GetLeft());		// push the left element into stack

		}
	}

	else if (!strcmp(order, "R_IN"))	// recursive in-order
	{
		Inorder(root);
	}

	else if (!strcmp(order, "I_IN"))	//iterative in-order
	{
		CarNode* curNode = root;

		// The while statement ends only if curNode points to NULL and stack is empty 
		while (curNode != NULL || !S.empty())
		{
			// move to the leftmost node connected to the current node and push into stack
			while (curNode != NULL)
			{
				S.push(curNode);
				curNode = curNode->GetLeft();
			}

			// curNode is NULL, so initialize curNode to the value at the top of the stack
			curNode = S.top();
			// then pop the top of the stack
			S.pop();

			// print the information of CarNode as inorder
			cout << curNode->GetcarNum() << " " << curNode->GetcarOwner() << " "
				<< curNode->Getstate() << endl;
			// save in log.txt
			flog << curNode->GetcarNum() << " " << curNode->GetcarOwner() << " "
				<< curNode->Getstate() << endl;

			// Now we have reached the left node, move to the right node
			curNode = curNode->GetRight();

		}
	}

	else if (!strcmp(order, "R_POST"))	// recursive post-order
	{
		Postorder(root);
	}

	else if (!strcmp(order, "I_POST"))	// iterative post-order
	{
		stack<CarNode*> S2;

		CarNode* curNode = root;
		S.push(curNode);

		// repeat until stack S is empty
		while (!S.empty())
		{
			/* In the below if statement, the right element is pushed into the stack after the left element, 
			so top points to the right element.
			Since curNode points to the right element and this process is repeated, 
			the stack contains elements from right to left of BST */
			curNode = S.top();
			S.pop();	// pop the top of the S
			S2.push(curNode);	// Push the element popped from S to S2

			if (curNode->GetLeft())
				S.push(curNode->GetLeft());		// push the left element into stack
			if (curNode->GetRight())
				S.push(curNode->GetRight());	// push the right element into stack
		}

		// repeat until stack S2 is empty
		while (!S2.empty())
		{
			curNode = S2.top();	// curNode points the element that is returned from S2
			S2.pop();	// pop the top of the S2

			// print the information of CarNode
			cout << curNode->GetcarNum() << " " << curNode->GetcarOwner() << " "
				<< curNode->Getstate() << endl;
			// save in log.txt
			flog << curNode->GetcarNum() << " " << curNode->GetcarOwner() << " "
				<< curNode->Getstate() << endl;
		}
	}

	else                   // iterative level-order
	{
		queue<CarNode*> Q;
		CarNode* curNode = root;

		while (curNode)	// repeat until curNode is not NULL
		{
			// print the information of CarNode as levelorder
			cout << curNode->GetcarNum() << " " << curNode->GetcarOwner() << " "
				<< curNode->Getstate() << endl;
			// save in log.txt
			flog << curNode->GetcarNum() << " " << curNode->GetcarOwner() << " "
				<< curNode->Getstate() << endl;

			// if left subnode exists, push that in queue
			if (curNode->GetLeft()) Q.push(curNode->GetLeft());
			// if right subnode exists, push that in queue
			if (curNode->GetRight()) Q.push(curNode->GetRight());

			if (Q.empty())	break;		// if queue is empty, then quit

			curNode = Q.front();	// curNode points the frontmost element in queue
			Q.pop();
		}
	}

	flog.close();
	return true;
}

bool		CarBST::Save()							// SAVE
{
	if (root == NULL) return false;

	ofstream fEvent("event_list_car.txt");

	stack<CarNode*> S;
	CarNode* curNode = new CarNode(); 
	curNode = root;
	S.push(curNode);	// push root into stack

	// repeat until stack S is empty
	while (!S.empty())
	{
		//curNode = new CarNode();

		// initialize curNode to the value at the top of the stack
		curNode = S.top();
		// then pop the top of the stack
		S.pop();

		// Output string to output stream fEvent
		// save as iterative pre-order
		fname << curNode->GetcarNum() << " " << curNode->GetcarOwner() << " "
			<< curNode->Getstate() << endl;


		if (curNode->GetRight())
			S.push(curNode->GetRight());	// push the right element into stack
		if (curNode->GetLeft())
			S.push(curNode->GetLeft());		// push the left element into stack

	}

	fEvent.close();
	return true;
}

void		CarBST::Inorder(CarNode *node)	// for recursive inorder
{
	ofstream flog("log.txt", ios::app);

	if (node)
	{
		Inorder(node->GetLeft());	// Move to leftmost node using recursive function

		cout << node->GetcarNum() << " " << node->GetcarOwner() << " "
			<< node->Getstate() << endl;	// print the information of CarNode as inorder
		flog << node->GetcarNum() << " " << node->GetcarOwner() << " "
			<< node->Getstate() << endl;	// print in flog

		Inorder(node->GetRight());	// Move to the right node connected to the node on the left line
	}
	flog.close();
}

void		CarBST::Preorder(CarNode *node)	// for recursive preorder
{
	ofstream flog("log.txt", ios::app);

	if (node)
	{
		cout << node->GetcarNum() << " " << node->GetcarOwner() << " "
			<< node->Getstate() << endl;	// print the information of CarNode as preorder
		flog << node->GetcarNum() << " " << node->GetcarOwner() << " "
			<< node->Getstate() << endl;	// print in flog

		Preorder(node->GetLeft());	// Move to leftmost node using recursive function
		Preorder(node->GetRight());	// Move to the right node connected to the node on the left line
	}
	flog.close();
}

void		CarBST::Postorder(CarNode *node)	// for recursive postorder
{
	ofstream flog("log.txt", ios::app);

	if (node)
	{
		Postorder(node->GetLeft());		// Move to leftmost node using recursive function
		Postorder(node->GetRight());	// Move to the right node connected to the node on the left line

		cout << node->GetcarNum() << " " << node->GetcarOwner() << " "
			<< node->Getstate() << endl;	// print the information of CarNode as postorder
		flog << node->GetcarNum() << " " << node->GetcarOwner() << " "
			<< node->Getstate() << endl;	// print in flog
	}
	flog.close();
}


// function to be used in destructor
void		CarBST::clear(CarNode* Root)
{
	p = root; q = NULL;	// q is the parent node of p

	// If there are no child nodes
	if (!p->GetLeft() && !p->GetRight())
	{
		root = NULL;
		delete p;
	}

	// If there is only the left child node
	else if (p->GetLeft() && !p->GetRight())
	{
		root = p->GetLeft();
		delete p;
	}

	// If there is only the right child node
	else if (!p->GetLeft() && p->GetRight())
	{
		root = p->GetRight();
		delete p;
	}

	//If there are both child nodes
	else
	{
		CarNode *prevprev = p, *prev = p->GetLeft(), *curr = p->GetLeft()->GetRight();

		while (curr)	// repeat until curr == NULL
		{
			prevprev = prev;
			prev = curr;
			curr = curr->GetRight();
		}
		/* After the while statement, 
		   curr = 0, 
		   prev = the largest of the left child nodes, prevprev = the parent node of prev */


		//  The node pointed to by p stores information about the node pointed to by prev
		p->SetcarNum(prev->GetcarNum());
		p->SetcarOwner(prev->GetcarOwner());
		p->Setstate(prev->Getstate());

		if (prevprev == p)	// If there is no right child node in the left child node of p
			p->SetLeft(prev->GetLeft());
		else                //If there is right child node in the left child node of p
			prevprev->SetRight(prev->GetLeft());

		delete prev;	
		// Because we moved the information of the prev node to the node p, release the memory of prev
		prev = NULL;
	}
}