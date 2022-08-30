#pragma once
#include<iostream>

const int INIT_CAPACITY = 8;

class PriorityQueue
{
private:
	int size = 0;		// Number of elements
	int index = 0;		// Position of next element

	// The initial array capacity
	int capacity = INIT_CAPACITY;
	int* arr = new int [INIT_CAPACITY];

public:
	int getSize() { return size; }
	bool isEmpty() { return size == 0; }
	
	// Gets the value at the root of the heap
	int peek();

	// Checks if a value is there or not
	bool contains(int value);

	// Checks how many nodes are left
	int childNodes() { return (size - 1) - (index * 2); }

	// Gets the parents and left and right children
	int parentNode() { return (index - 1) / 2; }
	int leftChildNode() { return (index * 2) + 1; }
	int rightChildNode() { return (index * 2) + 2; }
	
	// Swaps two elements
	void swapWith(int& x);

	// Adds an element
	void add(int value);

	// Removes the element at the root
	int poll() { return removeAt(0); }
	void pollAll();

	// Removes an element at a certain index
	int removeAt(int delIndex);

	// Removes an element with a certain value
	void remove(int value);

	// Updates size and index
	void removeAll() { index = size = 0; }

	// Frees the allocated memory
	void deleteArr() { delete[] arr; }

	// Prints the whole heap in order
	void toString();

	// User inputs an index or value parameter
	int inputValue();
	int inputIndex();
};

// Gets the value at the root of the heap
int PriorityQueue::peek()
{
	if (isEmpty())
	{
		std::cout << "Error: The queue is empty.\n";
		return 0;
	}

	return arr[0];
}

// Checks if a value is there or not
bool PriorityQueue::contains(int value)
{
	for (int i = 0; i < size; i++)
		if (arr[i] == value)
			return true;

	return false;
}

// Swaps two elements
void PriorityQueue::swapWith(int& x)
{
	int temp = arr[index];
	arr[index] = x;
	x = temp;
}

// Adds an element
void PriorityQueue::add(int value)
{
	// If the array is full, double the size
	if (index == capacity)
	{
		capacity *= 2;
		int* newArr = new int[capacity];
		for (int i = 0; i < index; i++)
			newArr[i] = arr[i];
		delete[] arr;
		arr = newArr;
	}

	// (Did this if statement for a buffer overrun warning)
	if (index < capacity)
	{
		arr[index] = value;
		int parent;

		// If it is less than the parent, swap them
		while (index != 0 && arr[index] < arr[parent = parentNode()])
		{
			swapWith(arr[parent]);
			index = parent;
		}
	}

	// Update the size
	index = ++size;
}

// Removes all the elements and prints them in order
void PriorityQueue::pollAll()
{
	std::cout << "\nSize: " << getSize() << "\n";
	if (isEmpty())
		std::cout << "[]";
	else while (size != 0)
		std::cout << "[" << poll() << "]";
	std::cout << "\n";
}

// Removes an element at a certain index
int PriorityQueue::removeAt(int delIndex)
{
	// Invalid index
	if (delIndex < 0 || delIndex >= size)
	{
		std::cout << "Error: Index not valid.\n";
		return 0;
	}

	// Saves data, replaces element and updates size
	int data = arr[delIndex];
	index = --size;
	arr[delIndex] = arr[index];
	index = delIndex;

	// Starts sinking the replaced element
	int leftChild, rightChild;
	while (childNodes() >= 1)
	{
		if (arr[index] > arr[leftChild = leftChildNode()])
		{
			if (childNodes() == 1)
			{
				swapWith(arr[leftChild]);
				index = leftChild;
			}
			else if (arr[leftChild] > arr[rightChild = rightChildNode()])
			{
				swapWith(arr[rightChild]);
				index = rightChild;
			}
			else
			{
				swapWith(arr[leftChild]);
				index = leftChild;
			}
		}
		else if (childNodes() >= 2 && arr[index] > arr[rightChild = rightChildNode()])
		{
			swapWith(arr[rightChild]);
			index = leftChild;
		}
		else break;
	}

	// Returns the index to the desired position
	index = size;
	return data;
}

// Removes an element with a certain value
void PriorityQueue::remove(int value)
{
	// Does a linear search through the array
	for (int i = 0; i < size; i++)
		if (arr[i] == value)
		{
			removeAt(i);
			std::cout << "Value removed.\n";
			return;
		}

	// The value is not in the heap
	std::cout << "Value not found.\n";
	return;
}

// Prints the whole heap in order
void PriorityQueue::toString()
{
	// Shows the size of the heap
	std::cout << "Size: " << getSize() << std::endl;

	if (isEmpty())
	{
		std::cout << "[]";
		return;
	}

	for (int i = 0; i < size; i++)
		std::cout << "[" << arr[i] << "]";

	std::cout << "\n\n";
}

// User inputs a valid value
int PriorityQueue::inputValue()
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

// User inputs a valid index
int PriorityQueue::inputIndex()
{
	if (isEmpty()) return 0;

	int index;
	while ((std::cout << "Enter the index: ") && (!(std::cin >> index) || index >= size || index < 0))
	{
		std::cerr << "\tError: Invalid index.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return index;
}