#include <iostream>
using namespace std;

struct TreeNode;

class BST
{
public:
	BST();

	void insertItem(int item);
	void removeItem(int item);
	void preOrder(TreeNode *p);
	void inOrder(TreeNode *p);
	void postOrder(TreeNode *p);
	void findMaxAtLevelK(TreeNode *p, int level);

	TreeNode *root;
};

struct TreeNode
{
	int value;
	TreeNode *left;
	TreeNode *right;
};

BST::BST()
{
	root = NULL;
}

void BST::insertItem(int item)
{
	TreeNode *newNode = new TreeNode;
	newNode->value = item;
	newNode->left = NULL;
	newNode->right = NULL;

	// Check if the tree is new
	if (root == NULL)
		root = newNode;
	else
	{
		// Create a pointer to traverse the tree, starting at the root
		TreeNode *parent = nullptr;
		TreeNode *current = root;

		// Find correct position for new node; smaller elements go left, larger elements go right
		while (current)
		{
			parent = current;

			if (item >= current->value)
				current = current->right;
			else
				current = current->left;
		}

		if (item >= parent->value)
			parent->right = newNode;
		else
			parent->left = newNode;
	}
}


void BST::removeItem(int item)
{
	bool found = false;

	// Check if the tree is empty
	if (root == NULL)
	{
		cout << "Tree is empty." << endl;
		return;
	}

	TreeNode *parent = nullptr;
	TreeNode *current = root;

	// Traverse tree to find item
	while (current)
	{
		if (current->value == item)
		{
			found = true;
			break;
		}
		else
		{
			parent = current;
			if (item > current->value)
				current = current->right;
			else
				current = current->left;
		}
	}

	// Return if the item was not found
	if (!found)
	{
		cout << "Item does not exist." << endl;
		return;
	}

	// If the item was found there are 3 cases to handle

	// Case 1: The item is in a leaf node
	if (current->left == NULL && current->right == NULL)
	{
		if (parent->left == current)
			parent->left = NULL;
		else
			parent->right = NULL;

		delete current;
		return;
	}

	// Case 2: The item is in a node with 1 child
	else if ((current->left == NULL && current->right != NULL) ||
		(current->left != NULL && current->right == NULL))
	{
		// Is the node's 1 child in the right?
		if (current->left == NULL)
		{
			// Is the node a left child?
			if (parent->left == current)
			{
				parent->left = current->right;
				delete current;
			}
			// Node is a right child
			else
			{
				parent->right = current->right;
				delete current;
			}
		}
		// Node's 1 child is in the left
		else
		{
			if (parent->left == current)
			{
				parent->left = current->left;
				delete current;
			}
			else
			{
				parent->right = current->left;
				delete current;
			}
		}

		return;
	}

	// Case 3: The item is in a node with 2 children.
	else
	{
		TreeNode *check;
		check = current->right;

		// Does right child have any children?
		if ((check->left == NULL) && (check->right == NULL))
		{
			current = check;
			delete check;
			current->right = NULL;
		}
		// Right child has children
		else
		{
			// If the right child has a left child, move all the way down left to locate smallest item
			if ((current->right)->left != NULL)
			{
				TreeNode *leftCurrent;
				TreeNode *leftCurrentPtr;
				leftCurrentPtr = current->right;
				leftCurrent = (current->right)->left;

				while (leftCurrent->left != NULL)
				{
					leftCurrentPtr = leftCurrent;
					leftCurrent = leftCurrent->left;
				}
				current->value = leftCurrent->value;
				delete leftCurrent;
				leftCurrentPtr->left = NULL;
			}

			else
			{
				TreeNode *temp;
				temp = current->right;
				current->value = temp->value;
				current->right = temp->right;
				delete temp;
			}
		}

		return;
	}
}

// Root, Left, Right

void BST::preOrder(TreeNode *p)
{
	if (root != NULL)
	{
		cout << " " << p->value << " ";

		if (p->left)
			preOrder(p->left);

		if (p->right)
			preOrder(p->right);
	}
	else
		return;
}

// Left, Root, Right

void BST::inOrder(TreeNode *p)
{
	if (p != NULL)
	{
		if (p->left)
			inOrder(p->left);

		cout << " " << p->value << " ";

		if (p->right)
			inOrder(p->right);
	}
	else
		return;
}

// Left, Right, Root

void BST::postOrder(TreeNode *p)
{
	if (p != NULL)
	{
		if (p->left)
			postOrder(p->left);

		if (p->right)
			postOrder(p->right);

		cout << " " << p->value << " ";
	}
	else
		return;
}


void BST::findMaxAtLevelK(TreeNode *p, int level)
{
	if (level == 0)
	{
		cout << "Max element at this level is: " << p->value << endl;;
		return;
	}

	if (root != NULL)
	{
		if (p->right)
		{
			--level;
			return findMaxAtLevelK(p->right, level);
		}
		if (p->left)
		{
			--level;
			return findMaxAtLevelK(p->left, level);
		}
	}
	else
	{
		cout << "Level does not exist!";
		return;
	}
}