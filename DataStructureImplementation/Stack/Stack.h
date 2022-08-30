#pragma once
#include <iostream>
class Stack
{
private: 
	class Node
	{
	private:
		int data = 0;
		Node* next = nullptr;
	public:
		Node(int x) { data = x; }

		int getData() { return data; }
		Node* getNext() { return next; }

		void setData(int x) { data = x; }
		void setNext(Node* p_Next) { next = p_Next; }
	};

	int size = 0;
	Node* top = nullptr;
	Node* temp = nullptr;
	int popData = 0;

public:

	int getTop() { return top->getData(); }
	bool isEmpty() { return top == nullptr; }

	void push(int x) 
	{
		temp = new Node(x);
		temp->setNext(top);
		top = temp;
		return;
	}

	int pop() 
	{
		if (top == nullptr) return 0;
		temp = top;
		popData = getTop();
		top = top->getNext();
		delete temp;
		return popData;
	}

	void print()
	{
		if (isEmpty())
		{
			std::cout << "The list is empty.\n";
			return;
		}

		std::cout << "\nStack: ";
		for (temp = top; temp != nullptr; temp = temp->getNext())
			std::cout << temp->getData() << " ";

		return;
	}

	void popAll()
	{
		if (isEmpty())
		{
			std::cout << "The list is empty.\n";
			return;
		}

		std::cout << "Values erased: ";
		while (top != nullptr)
			std::cout << pop() << " ";

		return;
	}
};

