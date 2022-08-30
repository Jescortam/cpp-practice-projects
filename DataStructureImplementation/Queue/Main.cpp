#include "QueueStruct.h"

int main()
{
	bool isOver = false;
	QueueStruct queue;

	while (!isOver)
	{
		// Choosing a function
		std::cout << "\n\n1. Enqueue\n2. Dequeue\n3. Print\n4. Exit\n\nChoose a function: ";

		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:		// Enqueue (Adds a node at the rear)
			std::cout << "Enter the value: ";
			int x;
			std::cin >> x;
			queue.enqueue(x);
			break;

		case 2:		// Dequeue (Removes a node from the front)
			std::cout << "\nValue removed: " << queue.dequeue();
			break;

		case 3:		// Print every node from the queue
			queue.toString();
			break;

		case 4:		// Exit
			isOver = true;
			break;

		default:	// Wrong input
			std::cout << "Function does not exist.\n";
		}
	}
	return 0;
}


// Adds a node at the rear
void QueueStruct::enqueue(int x)
{
	// The tail and head point to the same node
	if (isEmpty())
	{
		tail = head = new Node(x);
		size++;
		return;
	}

	// Make the tail and the last node update its next pointer
	temp = new Node(x);
	tail->setNext(temp);
	tail = temp;
	size++;
	return;
}

// Removes the node at the front
int QueueStruct::dequeue()
{
	// The list is empty
	if (isEmpty())
	{
		std::cout << "Error: The list is empty.\n";
		return 0;
	}

	// Saves the data, deletes the head node and updates the head
	data = head->getData();
	temp = head->getNext();
	delete head;
	head = temp;
	size--;
	return data;
}

// Prints the whole list like a string
void QueueStruct::toString()
{
	// Shows the size of the list
	std::cout << "\nSize: " << size << "\n";

	// The list is empty
	if (isEmpty())
	{
		std::cout << "[]\n";
		return;
	}

	// Print every node
	for (temp = head; temp != nullptr; temp = temp->getNext())
		std::cout << "[" << temp->getData() << "]";

	std::cout << "\n\n";
	return;
}