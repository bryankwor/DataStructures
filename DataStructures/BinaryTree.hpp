#include <iostream>

template <class T>
struct TreeNode
{
private:
	TreeNode* _leftChild;
	TreeNode* _rightChild;
	T _value;

public:
	TreeNode() : _leftChild(nullptr), _rightChild(nullptr), _value(0) {}

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
	BST() : _root(nullptr) {}

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

	// Traverse tree to find the item.
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

	// Traverse tree to find the item.
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
	// Get the item position in the tree and handle 4 deletion cases.
	else
	{
		TreeNode<T>* parent = nullptr;
		TreeNode<T>* current = getItemPositionInTree(item, parent);

		// Case 1: Deleting the root.
		if (current == parent)
		{
			if (!current->getLeftChild() && !current->getRightChild())
			{
				delete _root;
				_root = nullptr;
			}
			else if ((!current->getLeftChild() && current->getRightChild()) ||
					(current->getLeftChild() && !current->getRightChild()))
			{
				TreeNode<T>* temp = _root;
				if (current->getLeftChild())
				{
					_root = current->getLeftChild();
				}
				else
				{
					_root = current->getRightChild();
				}

				delete temp;
			}
			else
			{
				// TODO: Handle case where root has 2 children.
			}
		}

		// Case 2: The item is in a leaf node.
		if (!current->getLeftChild() && !current->getRightChild())
		{
			if (current == parent->getLeftChild())
			{
				parent->setLeftChild(nullptr);
			}
			else if (current == parent->getRightChild())
			{
				parent->setRightChild(nullptr);
			}
			// Deleting the root which has no children, so the tree is now empty.
			

			delete current;
			return;
		}

		// Case 3: The item is in a node with 1 child.
		else if ((!current->getLeftChild() && current->getRightChild()) ||
				(current->getLeftChild() && !current->getRightChild()))
		{
			if (current == parent->getLeftChild())
			{
				if (current->getLeftChild())
				{
					parent->setLeftChild(current->getLeftChild());
				}
				else
				{
					parent->setLeftChild(current->getRightChild());
				}
			}
			else if (current == parent->getRightChild())
			{
				if (current->getLeftChild())
				{
					parent->setRightChild(current->getLeftChild());
				}
				else
				{
					parent->setRightChild(current->getLeftChild());
				}
			}


			delete current;
		}

		// Case 4: The item is in a node with 2 children.
		else
		{
			TreeNode<T>* temp = current->getRightChild();

			if (!temp->getLeftChild() && !temp->getRightChild())
			{
				current->setValue(temp->getValue());
				delete temp;
			}
			else if (temp->getLeftChild())
			{
				while (temp->getLeftChild())
				{
					temp = temp->getLeftChild();
				}

				current->setValue(temp->getValue());
				delete temp;
			}
			else
			{
				current->setValue(temp->getValue());
				current->setRightChild(temp->getRightChild());
				delete temp;
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
		std::cout << "WARNING: Level in tree does not exist."
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

// Left, Root, Right.
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

// Left, Right, Root.
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