#include "Stack.h"

int main()
{
	bool isOver = false;
	Stack stack;

	while (!isOver)
	{
		// Choosing a function
		std::cout << "\n\n1. Push\n2. Pop\n3. Print\n4. Pop All\n5. Exit\n\nChoose a function: ";

		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:		// Push (Enter a node at the top)
			std::cout << "Enter the value: ";
			int x;
			std::cin >> x;
			stack.push(x);
			break;

		case 2:		// Pop (Take a node from the top)
			std::cout << "\nValue popped: " << stack.pop();
			break;

		case 3:		// Print every node from the stack
			stack.print();
			break;

		case 5:		// Exit (Also does what 4 did)
			isOver = true;

		case 4:		// Pops every node
			stack.popAll();
			break;

		default:	// Wrong input
			std::cout << "Function does not exist.\n";
		}
	}
	return 0;
}