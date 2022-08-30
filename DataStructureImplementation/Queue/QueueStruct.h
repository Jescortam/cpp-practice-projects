#pragma once
#include <iostream>

class QueueStruct
{
private:
	class Node
	{
	private:
		int data = 0;
		Node* next = nullptr;

	public:
		// Constructor
		Node(int init_Data) : data(init_Data) {};

		// Gets a value or an address
		int getData() { return data; }
		Node* getNext() { return next; }

		// Sets a value or an address
		void setData(int p_Data) { data = p_Data; }
		void setNext(Node* p_Next) { next = p_Next; }
	};

public:
	// Nodes used in the program
	Node* head = nullptr;
	Node* tail = nullptr;
	Node* temp = nullptr;

	int size = 0;
	int data = 0;

	// Adds a node at the rear
	void enqueue(int x);

	// Removes the node at the front
	int dequeue();

	// Gets the value at the front of the list
	int front() { return head->getData(); }

	// Checks if the list is empty
	bool isEmpty() { return size == 0; }

	// Prints the whole list like a string
	void toString();
};

