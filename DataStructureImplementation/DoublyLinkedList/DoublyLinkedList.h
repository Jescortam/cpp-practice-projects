#pragma once
#include <iostream>

class DoublyLinkedList
{
private:

	// Inside the data structure, there are nodes
	class Node
	{
	private:
		int data = 0;			// Data contained
		Node* prev = nullptr;	// Pointer to the previous node
		Node* next = nullptr;	// Pointer to the next node
	public:
		Node(int p_Data, Node* p_Prev, Node* p_Next)
		{
			data = p_Data;
			prev = p_Prev;
			next = p_Next;
		}

		// Gets the data and previous and next address
		int getData() { return data; }
		Node* getPrev() { return prev; }
		Node* getNext() { return next; }

		// Sets the data and previous and next address
		void setData(int newData) { data = newData; }
		void setPrev(Node* prevNode) { prev = prevNode; }
		void setNext(Node* nextNode) { next = nextNode; }
	};

	// Starting size of the data structure
	int size = 0;

	// Position in the linked list
	Node* head = nullptr;
	Node* tail = nullptr;
	Node* trav = nullptr;

public:

	// Returns the data structure's size
	int getSize() { return size; }

	// Checks if the list is empty
	bool isEmpty() { return size == 0; }

	// Adds a node to the list
	void add(int elem) { addLast(elem); }		// Default
	void addFirst(int elem);					// Head
	void addLast(int elem);						// Tail
	void addAtIndex(int index, int elem);		// With Index

	// Gets the data stored at the head or tail of the list
	int peekFirst();	// Head
	int peekLast();		// Tail

	// Removes a node from the list
	int removeFirst();							// Head
	int removeLast();							// Tail
private: int remove(Node* node); public:		// With Node Pointer (private)
	int removeAt(int index);					// With Index
	bool remove(int elem);						// With Value

	// Returns the index that has said value, if not, returns -1
	int indexOf(int elem);

	// Returns the data at said index
	int getDataAt(int index);

	// Returns if the element was found or not
	bool contains(int elem) { return indexOf(elem) != -1; }

	// Clears the linked list of all nodes
	void clear();

	// Prints the entire list
	void toString();

	// User inputs an index or value parameter
	int inputValue();

	// User inputs an index
	int inputIndex();
};

// Adds at the start of the list
void DoublyLinkedList::addFirst(int elem)
{
	// Makes the new element the head and the tail
	if (isEmpty()) head = tail = new Node(elem, nullptr, nullptr);

	else
	{
		// Makes the "head"'s previous node address point to the actual head
		head->setPrev(new Node(elem, nullptr, head));

		// Updates the head's address
		head = head->getPrev();
	}

	// Updates size
	size++;

	return;
}

// Adds at the end of the list
void DoublyLinkedList::addLast(int elem)
{
	// Makes the new element the head and the tail
	if (isEmpty()) head = tail = new Node(elem, nullptr, nullptr);

	else
	{
		// Makes the "tail"'s previous node address point to the actual tail
		tail->setNext(new Node(elem, tail, nullptr));

		// Updates the tail's address
		tail = tail->getNext();
	}

	// Updates size
	size++;

	return;
}

// Adds at a certain position
void DoublyLinkedList::addAtIndex(int index, int elem)
{
	try
	{
		// Invalid index
		if (index < 0 || index > size) throw 1;

		// Adds at the head
		if (index == 0) 
		{ 
			addFirst(elem); 
			return; 
		}

		// Adds at the tail
		if (index == size)
		{
			addLast(elem);
			return;
		}

		// Starts at the head
		trav = head;

		// Traverses the list until it is at the node before the specified index
		for (int i = 0; i < index - 1; i++) trav = trav->getNext();

		// Creates the node between the two
		Node* newNode = new Node(elem, trav, trav->getNext());

		// Goes to the next node, updates its previous address
		trav->getNext()->setPrev(newNode);

		// Updates the next address of the previous node
		trav->setNext(newNode);

		// Resetting trav pointer
		trav = nullptr;

		// Updates size
		size++;
	}
	catch (int x) { std::cerr << "Index is out of bounds. Error no. " << x << std::endl; return; }
}

// Gets the data stored at the head of the list
int DoublyLinkedList::peekFirst()
{
	try
	{
		if (isEmpty()) throw 2;		// If the list is empty, throw an exception
		return head->getData();		// If not, return the data stored at the head
	}
	catch (int x) { std::cerr << "The list is empty. Error no. " << x << std::endl; return 0; }
}

// Gets the data stored at the tail of the list
int DoublyLinkedList::peekLast()
{
	try
	{
		if (isEmpty()) throw 2;		// If the list is empty, throw an exception
		return tail->getData();		// If not, return the data stored at the tail
	}
	catch (int x) { std::cerr << "The list is empty. Error no. " << x << std::endl; return 0; }
}

// Removes the node located at the head
int DoublyLinkedList::removeFirst()
{
	try
	{
		// If the list is empty, throw an exception
		if (isEmpty()) throw 2;

		// Saves the data erased
		int data = head->getData();

		// Erases the only node and updates pointers
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
		}

		else
		{
			// Updates head address
			head = head->getNext();

			// Deallocates memory and updates head's previous address
			delete head->getPrev();
			head->setPrev(nullptr);
		}

		// Updates size
		size--;

		return data;
	}
	catch (int x) { std::cerr << "The list is empty. Error no. " << x << std::endl; return 0; }
}

// Removes the node located at the tail
int DoublyLinkedList::removeLast()
{
	try
	{
		// If the list is empty, throw an exception
		if (isEmpty()) throw 2;

		// Saves the data erased
		int data = tail->getData();

		// Erases the only node and updates pointers
		if (head == tail)
		{
			delete tail;
			head = tail = nullptr;
		}

		else
		{
			// Updates tail address
			tail = tail->getPrev();

			// Deallocates memory and updates head's previous address
			delete tail->getNext();
			tail->setNext(nullptr);
		}

		// Updates size
		size--;

		return data;
	}
	catch (int x) { std::cerr << "The list is empty. Error no. " << x << std::endl; return 0; }
}

// Removes the specified node
int DoublyLinkedList::remove(Node* node)
{
	// If the node is located at the head or tail of the list
	if (node->getPrev() == nullptr)
		return removeFirst();
		
	if (node->getNext() == nullptr) 
		return removeLast();

	// Make the adjacent nodes ignore this node
	node->getPrev()->setNext(node->getNext());
	node->getNext()->setPrev(node->getPrev());

	// Saves the data about to be erased
	int data = node->getData();

	// Deletes the node
	delete node;

	// Updates size
	size--;

	trav = nullptr;

	// Returns the data erased
	return data;
}

// Removes a node at a certain index
int DoublyLinkedList::removeAt(int index)
{
	try
	{
		// Invalid index
		if (index < 0 || index >= size) throw 1;

		// For the for loop
		int i;
		trav = nullptr;

		// Removes at first or second half
		if (index < size / 2)
			for (i = 0, trav = head; i != index; i++)
				trav = trav->getNext();
		else
			for (i = size - 1, trav = tail; i != index; i--)
				trav = trav->getPrev();

		// Deletes the node 
		return remove(trav);
	}
	catch (int x) { std::cerr << "Index is out of bounds. Error no. " << x << std::endl; return 0; }
}

// Removes a node with that value
bool DoublyLinkedList::remove(int elem)
{
	// Start the trav pointer at the head and if there is a match, remove the node
	for (trav = head; trav != nullptr; trav = trav->getNext())
		if (elem == trav->getData())
		{
			remove(trav); 
			return true;
		}	

	// If the value was not found, return false
	return false;
}

// Returns the index that has said value, if not, returns -1
int DoublyLinkedList::indexOf(int elem)
{
	int i;

	// Starts trav at head and index at 0, goes until there is no more nodes
	for (i = 0, trav = head; trav != nullptr; trav = trav->getNext(), i++)
		if (trav->getData() == elem)
			return i;

	// Element not found
	return -1;
}

// Returns the data at said index
int DoublyLinkedList::getDataAt(int index)
{
	try
	{
		// Invalid index
		if (index < 0 || index >= size) throw 1;

		int i;
		
		if (index < size / 2)										// Index found at the first half
			for (i = 0, trav = head; i < index; i++)
				trav = trav->getNext();
		else														// Index found at the second half
			for (i = size - 1, trav = tail; i > index; i--)
				trav = trav->getPrev();

		// Returns the data found
		return trav->getData();
	}
	catch (int x) { std::cerr << "Index is out of bounds. Error no. " << x << std::endl; return 0; }
}

// Clears the linked list of all nodes
void DoublyLinkedList::clear()
{
	// Starts at the head
	trav = head;

	// If there is a node there
	while (trav != nullptr)
	{
		Node* next = trav->getNext();	// Save the address of the next one
		delete trav;					// Frees the memory of the current one
		trav = next;					// Goes to the next node
	}
	head = tail = trav = nullptr;		// Clears every pointer
	size = 0;							// Updates the size
}

// Prints the entire list
void DoublyLinkedList::toString()
{
	std::cout << "\nSize: " << getSize() << std::endl;
	if (isEmpty()) std::cout << "[]";
	for (trav = head; trav != nullptr; trav = trav->getNext())
		std::cout << "[" << trav->getData() << "]";
	std::cout << "\n\n";
}

// User inputs an index or value parameter
int DoublyLinkedList::inputValue()
{
	int value;
	while ((std::cout << "Enter the value: ") && (!(std::cin >> value)))
	{
		std::cerr << "\tError: Invalid value.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return value;
}

// User inputs an index
int DoublyLinkedList::inputIndex()
{
	if (isEmpty()) return 0;

	int index;
	while ((std::cout << "Enter the index: ") && (!(std::cin >> index) || index > size || index < 0))
	{
		std::cerr << "\tError: Invalid index.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return index;
}