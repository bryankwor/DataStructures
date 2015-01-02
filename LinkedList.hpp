template <class T>
struct ListNode
{
private:
	ListNode* _next;
	T _data;

public:
	ListNode(const T &value) : _next(nullptr), _data(value) {}

	ListNode* getNext() const { return _next; }
	void setNext(ListNode* next) { _next = next; }
	T getData() const { return _data; }
	void setData(const T &data) { _data = data; }
};

template <class T>
class LinkedList
{
private:
	ListNode<T>* _head;

public:
	LinkedList() : _head(nullptr) {}

public:
	void appendAtFront(const T &data);
	void append(const T &data);
	void emptyList();
	bool remove(const T &data);
	bool contains(const T &data) const;
	bool isEmpty() const;
	void printListElements();
};

template <class T>
void LinkedList<T>::appendAtFront(const T &data)
{
	ListNode<T>* newNode = new ListNode<T>(data);
	if (!_head)
	{
		_head = newNode;
	}
	else
	{
		newNode->setNext(_head);
		_head = newNode;
	}
}

template <class T>
void LinkedList<T>::append(const T &data)
{
	ListNode<T>* newNode = new ListNode<T>(data);
	if (_head)
	{
		ListNode<T>* currentNode = _head;

		while (currentNode->getNext())
		{
			currentNode = currentNode->getNext();
		}

		currentNode->setNext(newNode);
	}
	else
	{
		_head = newNode;
	}
}

template <class T>
void LinkedList<T>::emptyList()
{
	if (_head)
	{
		ListNode<T>* currentNode = _head;

		while (currentNode->getNext())
		{
			ListNode<T>* nodeToDelete = currentNode->getNext();
			currentNode->setNext(currentNode->getNext()->getNext());
			delete nodeToDelete;
		}

		delete currentNode;
		_head = nullptr;
	}
}

template <class T>
bool LinkedList<T>::remove(const T &data)
{
	if (_head)
	{
		ListNode<T>* currentNode = _head;

		// List contains only one node.
		if (!currentNode->getNext() && currentNode->getData() == data)
		{
			delete currentNode;
			_head = nullptr;

			return true;
		}
		else
		{
			while (currentNode->getNext())
			{
				if (currentNode->getNext()->getData() == data)
				{
					ListNode<T>* nodeToDelete = currentNode->getNext();

					// Removing the last node in the list.
					if (currentNode->getNext()->getNext() == nullptr)
					{
						delete currentNode->getNext();
						currentNode->setNext(nullptr);
					}
					// Removing a node in the middle of the list.
					else
					{
						currentNode->setNext(currentNode->getNext()->getNext());
						delete nodeToDelete;
					}

					return true;
				}
				else
				{
					currentNode = currentNode->getNext();
				}
			}
		}
	}

	// Nothing removed. Requested data to remove doesn't exist.
	return false;
}

template <class T>
bool LinkedList<T>::contains(const T &data) const
{
	if (_head)
	{
		ListNode<T>* iterator = _head;
		while (iterator)
		{
			if (iterator->getData() == data)
			{
				return true;
			}

			iterator = iterator->getNext();
		}
	}

	return false;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
	return _head == nullptr;
}

template <class T>
void LinkedList<T>::printListElements()
{
	if (_head)
	{
		ListNode<T>* iterator = _head;

		while (iterator)
		{
			printf("%d \n", iterator->getData());
			iterator = iterator->getNext();
		}
	}
}