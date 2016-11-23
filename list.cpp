#ifndef LIST_HEADER
#define LIST_HEADER

#include <iostream>
using namespace std;

/*
 * TODO document why I don't separate header and source file.
 *
 * (in order to resolve undefined reference errors)
 */

/*
 * Node class.
 */
template<class T>
class Node
{
public:
	Node* prev;
	Node* next;
	T* data;
	int index;

	Node(T* data, int index);
	~Node();
};

template<class T>
Node<T>::Node(T* data, int index)
{
	this->data = data;
	this->index = index;

	this->prev = nullptr;
	this->next = nullptr;
}

template<class T>
Node<T>::~Node()
{
	delete data;
}

/*
 * Iterator class.
 */
template<class T>
class Iterator
{
private:
	typedef Node<T> N;
	N* current;

public:
	bool hasNext();
	T* next();
	T* getCurrent();

	Iterator(N*);
	~Iterator();
};

template<class T>
Iterator<T>::Iterator(N* node)
{
	current = node;
}

template<class T>
Iterator<T>::~Iterator()
{

}

template<class T>
bool Iterator<T>::hasNext()
{
	return current;
}

template<class T>
T* Iterator<T>::next()
{
	N* temp = current;
	current = current->next;
	return temp->data;
}

template<class T>
T* Iterator<T>::getCurrent()
{
	return current->data;
}

/*
 * LinkedList class.
 */
template<class T>
class LinkedList
{
protected:
	typedef Node<T> N;
	N* head;
	N* tail;

	int size;
	int count; //TODO implement without this, use head->index instead.

	void remove(N* node);

public:
	T* getHead();
	T* getTail();
	T* get(int index);

	int getSize();

	void add(T* data);

	void remove(int index);
	void empty();

	Iterator<T>* iterator();

	LinkedList();
	~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList()
{
	size = 0;
	count = 0;

	head = nullptr;
	tail = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	empty();
}

template<class T>
void LinkedList<T>::add(T* data)
{
	N* node = new N(data, count++);

	if (size == 0)
	{
		head = tail = node;
	}else
	{
		node->next = tail;
		tail->prev = node;
		tail = node;
	}

	size++;
}

template<class T>
T* LinkedList<T>::getHead()
{
	if (head)
		return head->data;

	return nullptr;
}

template<class T>
T* LinkedList<T>::getTail()
{
	if (tail)
		return tail->data;

	return nullptr;
}

template<class T>
int LinkedList<T>::getSize()
{
	return size;
}


template<class T>
T* LinkedList<T>::get(int index)
{
	//TODO check this!
	if (index > tail->index || index < head->index)
		return nullptr;

	N* node = tail;

	while (node)
	{
		if (node->index == index)
		{
			return node->data;
		}
		node = node->next;
	}

	return nullptr;
}

template<class T>
void LinkedList<T>::remove(int index)
{

	if (index > tail->index || index < head->index)
		return;

	N* node = tail;

	while (node)
	{
		if (node->index == index)
		{
			remove(node);
			return;
		}
		node = node->next;
	}
}

template<class T>
void LinkedList<T>::remove(N* node)
{
	/* Caution : This implementation assumes that node belongs to the list. */

	if (node)
	{
		if (size == 1)
		{
			head = nullptr;
			tail = nullptr;
		} else if (node->index == head->index)
		{
			head->prev->next = nullptr;
			head = head->prev;
		} else if (node->index == tail->index)
		{
			tail->next->prev = nullptr;
			tail = tail->next;
		} else
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
		}

		size--;

		delete node;
	}
}

template<class T>
void LinkedList<T>::empty()
{
	while (tail)
	{
		remove(tail);
	}
}

template<class T>
Iterator<T>* LinkedList<T>::iterator()
{
	return new Iterator<T>(tail);
}

#endif
