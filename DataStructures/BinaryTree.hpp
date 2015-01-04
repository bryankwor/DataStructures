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
	TreeNode() : _leftChild(nullptr), _rightChild(nullptr), _value(0) {}

	// Getters / Setters.
	TreeNode* getLeftChild() const { return _leftChild; }
	void setLeftChild(TreeNode* newLeftChild) { _leftChild = newLeftChild; }

	TreeNode* getRightChild() const { return _rightChild; }
	void setRightChild(TreeNode* newRightChild) { _rightChild = newRightChild; }

	T getValue() const { return _value; }
	void setValue(const T &value) { _value = value; }
};

template <class T>
class BST
{
private:
	TreeNode<T>* _root;

private:
	TreeNode<T>* getItemPositionInTree(const T &item, TreeNode<T>* parent);
	void preOrder(const TreeNode<T>* p) const;
	void inOrder(const TreeNode<T>* p) const;
	void postOrder(const TreeNode<T>* p) const;

public:
	// Constructors / Desctructors.
	BST() : _root(nullptr) {}

	// Member Functions.
	bool contains(const T &item) const;
	bool isEmpty() const { return _root == nullptr; }

	void insertItem(const T &item);
	void removeItem(const T &item);

 	T findMaxAtLevel(TreeNode<T> *p, const int &level) const;
	void printPreOrder() const;
	void printInOrder() const;
	void printPostOrder() const;
};

template <class T>
TreeNode<T>* BST<T>::getItemPositionInTree(const T &item, TreeNode<T>* parent)
{
	TreeNode<T> *current = _root;

	// Traverse tree to find item.
	while (current)
	{
		if (item == current->getValue())
		{
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

	if (!current)
	{
		// TODO: Assert (Attempt to find nonexistent item in tree!)
	}
	return current;
}

template <class T>
bool BST<T>::contains(const T &item) const
{
	// TODO: This can be optimized by having the insert function store the value of each new item added to the tree in a hash table.
	// Then this function can just look up the value in the hash table in constant time, provided there are no collisions.
	TreeNode<T> *current = _root;

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
void BST<T>::insertItem(const T &item)
{
	TreeNode<T>* newNode = new TreeNode<T>();
	newNode->setValue(item);

	// Check if the tree is new.
	if (!_root)
	{
		_root = newNode;
	}
	else
	{
		// Create a pointer to traverse the tree, starting at the root.
		TreeNode<T> *parent = nullptr;
		TreeNode<T> *current = _root;

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
void BST<T>::removeItem(const T &item)
{
	// Check if the tree is empty or doesn't contain the item.
	if (!_root || !contains(item))
	{
		return;
	}
	// Item exists. Get its position in the tree and handle 3 deletion cases.
	else
	{
		TreeNode<T>* parent = nullptr;
		TreeNode<T>* current = getItemPositionInTree(item, parent);

		// Case 1: The item is in a leaf node.
		if (!current->getLeftChild() && !current->getRightChild())
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
		else if ((!current->getLeftChild() && current->getRightChild()) ||
				(current->getLeftChild() && !current->getRightChild()))
		{
			// Is the node's 1 child in the right?
			if (!current->getLeftChild())
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
			// Node's 1 child is in the left.
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
			TreeNode<T> *check;
			check = current->getRightChild();

			// Does right child have any children?
			if (!check->getLeftChild() && !check->getRightChild())
			{
				current = check;
				delete check;
				current->setRightChild(nullptr);
			}
			// Right child has children
			else
			{
				// If the right child has a left child, move all the way down left to locate smallest item
				if (current->getRightChild()->getLeftChild())
				{
					TreeNode<T> *leftCurrent;
					TreeNode<T> *leftCurrentPtr;
					leftCurrentPtr = current->getRightChild();
					leftCurrent = (current->getRightChild())->getLeftChild();

					while (leftCurrent->getLeftChild())
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
					TreeNode<T> *temp;
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
T BST<T>::findMaxAtLevel(TreeNode<T> *p, const int &level) const
{
	if (level == 0)
	{
		return p->getValue();
	}

	if (_root)
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
		return 0;
	}
}

template <class T>
void BST<T>::printPreOrder() const
{
	if (_root)
	{
		preOrder(_root);
	}
	else
	{
		std::cout << "WARNING: Attempt to print empty tree.\n";
	}
}

// Root, Left, Right.
template <class T>
void BST<T>::preOrder(const TreeNode<T> *p) const
{
	std::cout << " " << p->getValue() << " \n";

	if (p->getLeftChild())
	{
		preOrder(p->getLeftChild());
	}

	if (p->getRightChild())
	{
		preOrder(p->getRightChild());
	}
}

template <class T>
void BST<T>::printInOrder() const
{
	if (_root)
	{
		inOrder(_root);
	}
	else
	{
		std::cout << "WARNING: Attempt to print empty tree.\n";
	}
}

// Left, Root, Right
template <class T>
void BST<T>::inOrder(const TreeNode<T> *p) const
{
	if (p->getLeftChild())
	{
		inOrder(p->getLeftChild());
	}
		
	std::cout << " " << p->getValue() << " \n";

	if (p->getRightChild())
	{
		inOrder(p->getRightChild());
	}
}

template <class T>
void BST<T>::printPostOrder() const
{
	if (_root)
	{
		postOrder(_root);
	}
	else
	{
		std::cout << "WARNING: Attempt to print empty tree.\n";
	}
}

// Left, Right, Root
template <class T>
void BST<T>::postOrder(const TreeNode<T> *p) const
{
	if (p->getLeftChild())
	{
		postOrder(p->getLeftChild());
	}

	if (p->getRightChild())
	{
		postOrder(p->getRightChild());
	}

	std::cout << " " << p->getValue() << " \n";
}