#ifndef LIST_HEADER_FILE
#define LIST_HEADER_FILE

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
class Iterator
{
private:
	typedef Node<T> N;
	N* current;

public:
	bool hasNext();
	N* next();

	Iterator(N*);
	~Iterator();
};

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

	void add(T* data);

	void remove(int index);
	void empty();

	Iterator<T>* iterator();

	LinkedList();
	~LinkedList();
};

#endif
