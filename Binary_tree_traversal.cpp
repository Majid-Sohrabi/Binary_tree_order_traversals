#include <iostream>
#include <conio.h>
using namespace std;

class node
{
public:
	int data;
	node* parent;
	node* leftChild;
	node* rightChild;
	node(void);
};

node::node(void)
{
	data = 0;
	parent = NULL;
	leftChild = NULL;
	rightChild = NULL;
}

class bst
{
public:
	node* root;

	bst(void);
	void insert(int);
	void display(node*, int);
	node* search(int);
	void inorder_tree_walk(node*);
	void preorder_tree_walk(node*);
	void postorder_tree_walk(node*);
	node* successor(node*);
	void transplant(node*, node*);
	void deletion(node *);
};

bst::bst(void)
{
	root = NULL;
}

//insert binery search tree
void bst::insert(int d)
{
	node* newNode = new node();
	newNode->data = d;

	if (root == NULL)
	{
		root = newNode;
	}
	else
	{
		node* tempNode = new node();
		node* backTempNode = new node();
		tempNode = root;

		while (tempNode != NULL)
		{
			backTempNode = tempNode;
			if (tempNode->data <= newNode->data)
			{
				tempNode = tempNode->rightChild;
			}
			else
			{
				tempNode = tempNode->leftChild;
			}
		}

		newNode->parent = backTempNode;
		if (backTempNode->data <= newNode->data)
		{
			backTempNode->rightChild = newNode;
		}
		else
		{
			backTempNode->leftChild = newNode;
		}
	}
}
//display binary search tree

void bst::display(node *Node, int level)
{
	if (root == NULL)
	{
		cout << "Tree is empty." << endl;
	}
	else
	{
		if (Node->rightChild != NULL)
		{
			display(Node->rightChild, level + 1);
		}

		if (Node != root)
		{
			for (int i = 0; i < level + 1; i++)
			{
				cout << "      ";
			}
		}
		else
		{
			cout << "Root->";
		}

		cout << Node->data << endl;

		if (Node->leftChild != NULL)
		{
			display(Node->leftChild, level + 1);
		}
	}

}

//Search in BST Tree
node* bst::search(int Data)
{
	node* tempNode = new node();
	tempNode = root;
	while (tempNode != NULL)
	{
		if (tempNode->data == Data)
		{
			return tempNode;
		}
		else
		{
			if (tempNode->data <= Data)
			{
				tempNode = tempNode->rightChild;
			}
			else
			{
				tempNode = tempNode->leftChild;
			}
		}
	}
	return NULL;
}
//inoreder tree walk
void bst::inorder_tree_walk(node* currentNode)
{
	if (root != NULL)
	{
		if (currentNode->leftChild != NULL)
		{
			inorder_tree_walk(currentNode->leftChild);
		}

		cout << currentNode->data << "  ,";

		if (currentNode->rightChild != NULL)
		{
			inorder_tree_walk(currentNode->rightChild);
		}
	}
	else
	{
		cout << "Tree is empty!" << endl;
	}
}
//preoreder tree walk
void bst::preorder_tree_walk(node* currentNode)
{
	if (root != NULL)
	{
		cout << currentNode->data << "  ,";

		if (currentNode->leftChild != NULL)
		{
			preorder_tree_walk(currentNode->leftChild);
		}

		if (currentNode->rightChild != NULL)
		{
			preorder_tree_walk(currentNode->rightChild);
		}
	}
	else
	{
		cout << "Tree is empty!" << endl;
	}
}
//preoreder tree wak
void bst::postorder_tree_walk(node* currentNode)
{
	if (root != NULL)
	{

		if (currentNode->leftChild != NULL)
		{
			postorder_tree_walk(currentNode->leftChild);
		}

		if (currentNode->rightChild != NULL)
		{
			postorder_tree_walk(currentNode->rightChild);
		}

		cout << currentNode->data << "  ,";
	}
	else
	{
		cout << "Tree is empty!" << endl;
	}
}

//successor
node* bst::successor(node* currentNode)
{
	node* tempNode = new node();
	node* backTempNode = new node();
	tempNode = currentNode;

	if (tempNode->rightChild != NULL)
	{
		tempNode = tempNode->rightChild;
		while (tempNode != NULL)
		{
			backTempNode = tempNode;
			tempNode = tempNode->leftChild;
		}
		return backTempNode;
	}
	else
	{
		backTempNode = tempNode;
		tempNode = tempNode->parent;
		while (tempNode != NULL && tempNode->rightChild == backTempNode)
		{
			backTempNode = tempNode;
			tempNode = tempNode->parent;
		}
		return tempNode;
	}
}

//transplant

void bst::transplant(node* u, node* v)
{
	if (u->parent == NULL)
	{
		root = v;
	}
	else
	{
		if (u == u->parent->leftChild)
		{
			u->parent->leftChild = v;
		}
		else
		{
			u->parent->rightChild = v;
		}
	}
	if (v != NULL)
	{
		v->parent = u->parent;
	}
}
//remove node from tree
void bst::deletion(node *z)
{
	if (z->leftChild == NULL)
	{
		transplant(z, z->rightChild);
	}
	else
	{
		if (z->rightChild == NULL)
		{
			transplant(z, z->leftChild);
		}
		else
		{
			node* succesor = new node();
			succesor = successor(z);
			if (succesor->parent != z)
			{
				transplant(succesor, succesor->rightChild);
				succesor->rightChild = z->rightChild;
				succesor->rightChild->parent = succesor;
			}
			transplant(z, succesor);
			succesor->leftChild = z->leftChild;
			succesor->leftChild->parent = succesor;
		}
	}
	delete z;
}
//------------------------------------------
//menu
void menu()
{
	char ch;
	int inttemp;
	node *temp = new node();
	bst myTree;
	int select;
	do
	{
		system("CLS");
		cout << "0. Exit" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Display" << endl;
		cout << "3. Search" << endl;
		cout << "4. Inorder" << endl;
		cout << "5. preorder" << endl;
		cout << "6. postorder" << endl;
		cout << "7. Delete" << endl;
		cout << endl << "Enter your selection:" << endl;
		cin >> select;
		system("CLS");

		switch (select)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			do
			{

				int data;
				cout << "Enter Data: ";
				cin >> data;
				myTree.insert(data);
				cout << endl << "Do you want another node?[y/n]" << endl;
				cin >> ch;
			} while (ch != 'n');
			break;
		}
		case 2:
		{
			myTree.display(myTree.root, 0);
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}

		case 3:
		{

			cout << "Enter key of node:";
			cin >> inttemp;
			temp = myTree.search(inttemp);
			if (temp != NULL)
			{
				cout << "Node with key (" << temp->data << ") exist in tree." << endl;
			}
			else
			{
				cout << "It isn't in tree!" << endl;
			}

			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 4:
		{
			cout << "inorder :" << endl;
			myTree.inorder_tree_walk(myTree.root);
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 5:
		{
			cout << "preorder :" << endl;
			myTree.preorder_tree_walk(myTree.root);
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 6:
		{
			cout << "postorder :" << endl;
			myTree.postorder_tree_walk(myTree.root);
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}

		case 7:
		{
			cout << "Enter key(Data) of node that you want to delete: ";
			cin >> inttemp;
			temp = myTree.search(inttemp);
			if (temp == NULL)
			{
				cout << "There isn't any node with key (" << inttemp << ") in our tree." << endl;
			}
			else
			{
				myTree.deletion(temp);
				cout << "Node with key (" << inttemp << ") removed from tree." << endl;
			}
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		default:
			break;
		}

	} while (select != 0);
}
//------------------------------------------
int main()
{
	menu();
	return 0;
}