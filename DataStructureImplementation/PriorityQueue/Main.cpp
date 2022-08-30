#include "PriorityQueue.h"

int main()
{
	// If true, exit the program
	bool is_finished = false;

	// Constructing the data structure
	PriorityQueue dataStruct;

	while (!is_finished) {

		// Displaying options
		std::cout << "\n__________________________________________________________________\n";
		std::cout << "\n\tWhat would you like to do?\n\n";
		std::cout << "1. Add an element.\n";
		std::cout << "2. Peek the next element in the queue.\n";
		std::cout << "3. Poll the next element in the queue.\n";
		std::cout << "4. Poll all elements in the queue.\n";
		std::cout << "5. Remove an element at a certain index.\n";
		std::cout << "6. Remove an element with a specificed value.\n";
		std::cout << "7. Remove all the elements in the queue.\n";
		std::cout << "8. Delete the queue and exit.\n\n";

		// Chooses a function and validates the input
		int choice;
		while ((std::cout << "Choose a function: ") && (!(std::cin >> choice) || choice < 1 || choice > 8))
		{
			std::cerr << "\tError: Invalid input.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cout << "\n__________________________________________________________________\n\n";

		int data;

		// Selecting the chosen function
		switch (choice)
		{
		case 1: // Add an element
			dataStruct.add(dataStruct.inputValue());
			break;
		case 2: // Peek the next element in the queue
			data = dataStruct.peek();
			std::cout << "\nNext element: " << data << "\n";
			break;
		case 3: // Poll the next element in the queue
			data = dataStruct.poll();
			std::cout << "\nNext element: " << data << "\n";
			break;
		case 4: // Poll all elements in the queue
			dataStruct.pollAll();
			break;
		case 5: // Remove an element at a certain index
			data = dataStruct.removeAt(dataStruct.inputIndex());
			std::cout << "\nElement removed: " << data << "\n";
			break;
		case 6: // Remove an element with a specificed value
			dataStruct.remove(dataStruct.inputValue());
			break;
		case 7: // Delete the queue
			dataStruct.removeAll();
			break;
		case 8:
			dataStruct.deleteArr();
			is_finished = true;
			break;
		}
	}
}