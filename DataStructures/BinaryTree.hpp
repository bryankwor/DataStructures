#include <iostream>

template <class T>
struct TreeNode
{
private:
	TreeNode* _leftChild;
	TreeNode* _rightChild;
	T _value;

public:
	// Constructors / Destructors.
	TreeNode() : _leftChild(nullptr), _right(nullptr), _value(0) {}

	// Getters / Setters.
	TreeNode* getLeftChild() const { return _leftChild; }
	void setLeftChild(const TreeNode* newLeftChild) { _leftChild = newLeftChild; }

	TreeNode* getRightChild() const { return _rightChild; }
	void setRightChild(const TreeNode* newRightChild) { _rightChild = newRightChild; }

	T getValue() const { return _value; }
	void setValue(const T &value) { _value = value; }
};

template <class T>
class BST
{
private:
	TreeNode* _root;

private:
	TreeNode* getItemPositionInTree(const T &item, TreeNode* parent);

public:
	// Constructors / Desctructors.
	BST() : root(nullptr) {}

	// Member Functions.
	bool contains(const T &item) const;

	void insertItem(const T &item);
	void removeItem(const T &item);

	void findMaxAtLevel(TreeNode *p, const int &level) const;
	void preOrder(TreeNode *p) const;
	void inOrder(TreeNode *p) const;
	void postOrder(TreeNode *p) const;
};

template <class T>
TreeNode* getItemPositionInTree(const T &item, TreeNode* parent)
{
	bool found = false;
	TreeNode *current = root;

	// Traverse tree to find item.
	while (current)
	{
		if (item == current->getValue())
		{
			found = true;
			break;
		}
		else
		{
			parent = current;
			if (item > current->getValue())
			{
				current = current->getRightChild();
			}
			else
			{
				current = current->getLeftChild();
			}
		}
	}

	if (current == nullptr)
	{
		// TODO: Assert (Attempt to find nonexistent item in tree!)
	}
	return current;
}

template <class T>
bool contains(const T &item) const
{
	// TODO: This can be optimized by having the insert function store the value of each new item added to the tree in a hash table.
	// Then this function can just look up the value in the hash table in constant time, provided there are no collisions.
	TreeNode *current = root;

	// Traverse tree to find item.
	while (current)
	{
		if (item == current->getValue())
		{
			return true;
		}
		else
		{
			if (item > current->getValue())
			{
				current = current->getRightChild();
			}
			else
			{
				current = current->getLeftChild();
			}
		}
	}

	return false;
}

template <class T>
void BST::insertItem(const T &item)
{
	TreeNode* newNode = new TreeNode();
	newNode->setValue(item);

	// Check if the tree is new.
	if (root == nullptr)
	{
		root = newNode;
	}
	else
	{
		// Create a pointer to traverse the tree, starting at the root.
		TreeNode *parent = nullptr;
		TreeNode *current = root;

		// Find correct position for new node; smaller elements go left, larger elements go right.
		while (current)
		{
			parent = current;

			if (item >= current->getValue())
			{
				current = current->getRightChild();
			}
			else
			{
				current = current->getLeftChild();
			}
		}

		if (item >= parent->getValue())
		{
			parent->setRightChild(newNode);
		}
		else
		{
			parent->setLeftChild(newNode);
		}
	}
}

template <class T>
void BST::removeItem(const T &item)
{
	// Check if the tree is empty or doesn't contain the item.
	if (root == nullptr || !contains(item))
	{
		return;
	}
	// Item exists. Get its position in the tree and handle 3 deletion cases.
	else
	{
		TreeNode* parent = nullptr;
		TreeNode* current = getItemPositionInTree(item, parent);

		// Case 1: The item is in a leaf node.
		if (current->getLeftChild() == nullptr && current->getRightChild() == nullptr)
		{
			if (current == parent->getLeftChild())
			{
				parent->getLeftChild() = nullptr;
			}
			else
			{
				parent->getRightChild() = nullptr;
			}

			delete current;
			return;
		}

		// Case 2: The item is in a node with 1 child.
		else if ((current->getLeftChild() == nullptr && current->getRightChild() != nullptr) ||
			(current->getLeftChild() != nullptr && current->getRightChild() == nullptr))
		{
			// Is the node's 1 child in the right?
			if (current->getLeftChild() == nullptr)
			{
				// Is the node a left child?
				if (parent->getLeftChild() == current)
				{
					parent->setLeftChild(current->getRightChild());
					delete current;
				}
				// Node is a right child
				else
				{
					parent->setRightChild(current->getRightChild());
					delete current;
				}
			}
			// Node's 1 child is in the left
			else
			{
				if (parent->getLeftChild() == current)
				{
					parent->setLeftChild(current->getLeftChild());
					delete current;
				}
				else
				{
					parent->setRightChild(current->getLeftChild());
					delete current;
				}
			}

			return;
		}

		// Case 3: The item is in a node with 2 children.
		else
		{
			TreeNode *check;
			check = current->getRightChild();

			// Does right child have any children?
			if ((check->getLeftChild() == nullptr) && (check->getRightChild() == nullptr))
			{
				current = check;
				delete check;
				current->setRightChild(nullptr);
			}
			// Right child has children
			else
			{
				// If the right child has a left child, move all the way down left to locate smallest item
				if ((current->getRightChild())->getLeftChild() != nullptr)
				{
					TreeNode *leftCurrent;
					TreeNode *leftCurrentPtr;
					leftCurrentPtr = current->getRightChild();
					leftCurrent = (current->getRightChild())->getLeftChild();

					while (leftCurrent->getLeftChild() != nullptr)
					{
						leftCurrentPtr = leftCurrent;
						leftCurrent = leftCurrent->getLeftChild();
					}
					current->setValue(leftCurrent->getValue());
					delete leftCurrent;
					leftCurrentPtr->setLeftChild(nullptr);
				}

				else
				{
					TreeNode *temp;
					temp = current->getRightChild();
					current->setValue(temp->getValue());
					current->setRightChild(temp->getRightChild());
					delete temp;
				}
			}
		}
	}
}

template <class T>
void BST::findMaxAtLevel(TreeNode *p, const int &level) const
{
	// TODO: Fix base case.
	if (level == 0)
	{
		cout << "Max element at this level is: " << p->getValue() << endl;;
		return;
	}

	if (root != nullptr)
	{
		if (p->getRightChild())
		{
			--level;
			return findMaxAtLevelK(p->getRightChild(), level);
		}
		if (p->getLeftChild())
		{
			--level;
			return findMaxAtLevelK(p->getLeftChild(), level);
		}
	}
	else
	{
		cout << "Level does not exist!";
		return;
	}
}

// Root, Left, Right.
template <class T>
void BST::preOrder(TreeNode *p) const
{
	if (root != nullptr)
	{
		std::cout << " " << p->getValue() << " ";

		if (p->left)
		{
			preOrder(p->getLeftChild());
		}

		if (p->right)
		{
			preOrder(p->getRightChild());
		}
	}
	else
	{
		return;
	}
}

// Left, Root, Right
template <class T>
void BST::inOrder(TreeNode *p) const
{
	if (p != nullptr)
	{
		if (p->getLeftChild())
		{
			inOrder(p->getLeftChild());
		}
		
		std::cout << " " << p->getValue() << " ";

		if (p->right)
		{
			inOrder(p->getRightChild());
		}
	}
	else
	{
		return;
	}
}

// Left, Right, Root
template <class T>
void BST::postOrder(TreeNode *p) const
{
	if (p != nullptr)
	{
		if (p->getLeftChild())
		{
			postOrder(p->getLeftChild());
		}

		if (p->getRightChild())
		{
			postOrder(p->getRightChild());
		}

		std::cout << " " << p->getValue() << " ";
	}
	else
	{
		return;
	}
}