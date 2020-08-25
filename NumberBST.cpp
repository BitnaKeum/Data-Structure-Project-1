#include "NumberBST.h"
#include <queue>
#include <stack>
#include <string>

using namespace std;

NumberBST::NumberBST()//constructor
{
	root = NULL;
	p = NULL;
	q = NULL;
	nodeCnt = 0;

	// Number BST build
	NumberNode* node0 = new NumberNode(7);
	Insert(node0);
	NumberNode* node1 = new NumberNode(3);
	Insert(node1);
	NumberNode* node2 = new NumberNode(9);
	Insert(node2);
	NumberNode* node3 = new NumberNode(1);
	Insert(node3);
	NumberNode* node4 = new NumberNode(0);
	Insert(node4);
	NumberNode* node5 = new NumberNode(2);
	Insert(node5);
	NumberNode* node6 = new NumberNode(5);
	Insert(node6);
	NumberNode* node7 = new NumberNode(4);
	Insert(node7);
	NumberNode* node8 = new NumberNode(6);
	Insert(node8);
	NumberNode* node9 = new NumberNode(8);
	Insert(node9);
}


NumberBST::~NumberBST()//destructor
{
	if (clear())
		nodeCnt = 0;
}




void		NumberBST::Insert(NumberNode * node)			// LOAD, MOVE
{
	if (root == NULL)	// connects root to the new node if Number BST is not yet created
		root = node;
	else
	{
		p = root;

		while (1)
		{
			if (p->GetNumber() < node->GetNumber())	// if car number of new node is bigger
			{
				if (p->GetRight() == NULL)
				{
					p->SetRight(node);	// Connect to the lower right of the current node
					break;
				}

				p = p->GetRight();	// pCur points the right node
			}

			else if (p->GetNumber() > node->GetNumber())	// if car number of new node is smaller
			{
				if (p->GetLeft() == NULL)
				{
					p->SetLeft(node);	// connect to the lower left of the current node
					break;
				}

				p = p->GetLeft();	// pCur points the left node
			}

			else
				break;	// If the node with that number already exists in BST, exit without inserting
		}
	}
}

void	NumberBST::Delete(NumberNode* Root)				// COMPLETE
{
	// root is not NULL because the delete function is executed when (root != NULL) in the clear function 
	// Delete function of NumberBST unconditionally delete root node of NumberBST

	p = root; q = NULL;

	// if there are no child nodes
	if (!p->GetLeft() && !p->GetRight())
	{
		root = NULL;	// Node no longer exists in NumberBST
		delete(p);
	}

	// If there is only the left child node
	else if (p->GetLeft() && !p->GetRight())
	{
		root = p->GetLeft();
		delete(p);
	}

	// If there is only the right child node
	else if (!p->GetLeft() && p->GetRight())
	{
		root = p->GetRight();
		delete(p);
	}

	// If there are both child nodes
	else
	{
		NumberNode *prevprev = p, *prev = p->GetLeft(), *curr = p->GetLeft()->GetRight();

		while (curr)	// repeat until curr == NULL
		{
			prevprev = prev;
			prev = curr;
			curr = curr->GetRight();
		}
		/* After the while statement, 
		   curr = 0, 
		   prev = the largest of the left child nodes, prevprev = the parent node of prev */


		// The node pointed to by p stores information about the node pointed to by prev
		p->SetNumber(prev->GetNumber());

		if (prevprev == p)	// If there is no right child node in the left child node of p
			p->SetLeft(prev->GetLeft());
		else                // If there is a right child node in the left child node of p
			prevprev->SetRight(prev->GetLeft());

		delete(prev);	// release memory
		prev = NULL;
	}
}

// function to find node that has num
NumberNode *	NumberBST::Search(int num)				// ADD, COMPLETE, SEARCH
{
	p = root;

	while (1)
	{
		// if num is bigger
		if (p->GetNumber() < num)
		{
			// if there is no node that has num 
			if (p->GetRight() == NULL)
				return NULL;

			p = p->GetRight();	// pCur points the right node
		}

		// if num is smaller
		else if (p->GetNumber() > num)
		{
			// if there is no node that has num 
			if (p->GetLeft() == NULL)
				return NULL;

			p = p->GetLeft();		// pCur points the left node
		}

		// if finds the node that has num
		else
			return p;	// return the address of current node
	}

}

// Function that outputs the value 
bool		NumberBST::Print(char * order)					// PRINT
{
	if (nodeCnt == 0)	return false;	// if no CarNode is linked with NumberBST return false

	ofstream flog("log.txt", ios::app);	// output stream, appendable

	cout << "======== PRINT ========" << endl;
	flog << "======== PRINT ========" << endl;


	stack<NumberNode*> S;

	if (!strcmp(order, "R_PRE"))	// recursive pre-order
	{
		Preorder(root);
	}

	else if (!strcmp(order, "I_PRE"))	// iterative pre-order
	{
		NumberNode* curNode = root;
		S.push(curNode);	// push root into stack

		// repeat until stack S is empty			
		while (!S.empty())
		{
			// initialize curNode to the value at the top of the stack
			curNode = S.top();
			// then pop the top of the stack
			S.pop();


			curNode->GetBST()->Print("I_PRE");	// print the information of CarBST

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
		NumberNode* curNode = root;

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

			curNode->GetBST()->Print("I_IN");	// print the information of CarBST as inorder

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
		stack<NumberNode*> S2;

		NumberNode* curNode = root;
		S.push(curNode);
		
		// repeat until stack S is empty
		while (!S.empty())
		{
			/* In the below if statements, the right element is pushed into the stack after the left element,
			so top points to the right element.
			Since curNode points to the right element and this process is repeated,
			the stack contains elements from right to left of BST */
			curNode = S.top();
			S.pop();			// pop the top of the S
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
			S2.pop();			// pop the top of the S2

			curNode->GetBST()->Print("I_POST");	// print the information of CarBST as postorder
		}
	}

	else                             // iterative level-order
	{
		queue<NumberNode*> Q;
		NumberNode* curNode = root;

		while (curNode)	// repeat until cunNode is not NULL
		{
			curNode->GetBST()->Print("I_LEVEL");	// print the information of CarBST as levelorder

			// if left subnode exists, push that in queue
			if (curNode->GetLeft()) Q.push(curNode->GetLeft());
			// if right subnode exists, push that in queue
			if (curNode->GetRight()) Q.push(curNode->GetRight());

			if (Q.empty())	break;		// if queue is empty, then quit

			curNode = Q.front();	// curNode points the frontmost element in queue
			Q.pop();				// pop the top element of queue
		}
	}

	cout << "=======================" << endl << endl;
	flog << "=======================" << endl << endl;

	flog.close();

	return true;
}

bool		NumberBST::Save(ofstream& fname)								// SAVE
{
	if (root == NULL)	return false;	// if NumberBST does not exist


	stack<NumberNode*> S;
	NumberNode* curNode = root;
	S.push(curNode);	// push root into stack

						// repeat until stack S is empty			
	while (!S.empty())
	{
		// initialize curNode to the value at the top of the stack
		curNode = S.top();
		// then pop the top of the stack
		S.pop();

		if (curNode->GetBST() != NULL)
		{
			curNode->GetBST()->Save(fname);	// save as iterative pre-order
		}
		if (curNode->GetRight())
			S.push(curNode->GetRight());	// push the right element into stack
		if (curNode->GetLeft())
			S.push(curNode->GetLeft());		// push the left element into stack
	}

	return true;
}

void		NumberBST::Inorder(NumberNode *node)
{
	if (node)
	{
		Inorder(node->GetLeft());	// Move to leftmost node using recursive function

		node->GetBST()->Print("R_IN");

		Inorder(node->GetRight());	// Move to the right node connected to the node on the left line
	}
}

void		NumberBST::Preorder(NumberNode *node)
{
	if (node)
	{
		node->GetBST()->Print("R_PRE");	// print the information of CarBST as preorder

		Preorder(node->GetLeft());	// Move to leftmost node using recursive function
		Preorder(node->GetRight());	// Move to the right node connected to the node on the left line
	}

}

void		NumberBST::Postorder(NumberNode *node)
{
	if (node)
	{
		Postorder(node->GetLeft());		// Move to leftmost node using recursive function
		Postorder(node->GetRight());	// Move to the right node connected to the node on the left line

		node->GetBST()->Print("R_POST");	// print the information of CarBST as postorder
	}
}



NumberNode *	NumberBST::getRoot()
{
	return root;
}

int			NumberBST::getCnt()
{
	return nodeCnt;
}

void		NumberBST::setCnt(int cnt)
{
	nodeCnt = cnt;
}

bool		NumberBST::clear()
{
	while (root)	// Repeat until NumberBST does not exist
	{		
		// Delete CarBST associated with current NumberNode
		root->GetBST()->~CarBST();	
		if (root->GetBST()->root != NULL)	return false;
		
		Delete(root);	// delete root node of NumberBST
	}

	return true;
}