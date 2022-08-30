#include "DoublyLinkedList.h"
#include <iostream>

int main()
{
	// If true, exit the program
	bool is_finished = false;

	// Constructing the data structure
	DoublyLinkedList dataStruct;

	while (!is_finished) {

		// Displaying options
		std::cout << "\n__________________________________________________________________\n";
		std::cout << "\n\tWhat would you like to do?\n\n";
		std::cout << "1. Add an element.\n";
		std::cout << "2. Add an element at a specified index.\n";
		std::cout << "3. Search the value of an element with its index.\n";
		std::cout << "4. Search the index of an element with its value.\n";
		std::cout << "5. Show all elements.\n";
		std::cout << "6. Delete an element at a specified index.\n";
		std::cout << "7. Delete an element with a certain value.\n";
		std::cout << "8. Delete all elements.\n";
		std::cout << "9. Exit.\n\n";

		// Chooses a function and validates the input
		int choice;
		while ((std::cout << "Choose a function: ") && (!(std::cin >> choice) || choice < 1 || choice > 9))
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

		// Adds an element to the end of the array
		case 1:		
			dataStruct.add(dataStruct.inputValue());
			break;

		// Adds an element at the specified index
		case 2:		
			dataStruct.addAtIndex(dataStruct.inputIndex(), dataStruct.inputValue());
			break;

		// Searches an element by its index and returns the value
		case 3:		
			std::cout << "\nValue found: " << dataStruct.getDataAt(dataStruct.inputIndex()) << std::endl;
			break;

		// Searches an element by its value and prints the index
		case 4:
			data = dataStruct.indexOf(dataStruct.inputValue());
			if (data != -1)
				std::cout << "Element found at index: " << data << std::endl;
			else std::cout << "Element not found\n";
			break;

		// Prints the entire list in a string
		case 5:
			dataStruct.toString();
			break;

		// Removes an element of the list with its index and prints the value it had
		case 6:
			data = dataStruct.removeAt(dataStruct.inputIndex());
			std::cout << "Value deleted: " << data << std::endl;
			break;

		// Removes an element of the list with a certain value and prints the value it had
		case 7:	
			if (dataStruct.remove(dataStruct.inputValue())) 
				std::cout << "\nElement removed from the list.\n";
			else std::cout << "\nElement not found.\n";
			break;

		// Clears all the values the list had
		case 8:
			dataStruct.clear();
			std::cout << "Succesfully cleared the array.\n";
			break;

		// Breaks the loop and frees the memory
		case 9:
			is_finished = true;
			dataStruct.clear();
			break;
		}
	}
}