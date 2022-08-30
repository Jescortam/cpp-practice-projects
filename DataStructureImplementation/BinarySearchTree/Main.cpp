#include "BinarySearchTree.h"

int main()
{
	// If true, exit the program
	bool is_finished = false;

	// Constructing the data structure
	BinarySearchTree dataStruct;

	while (!is_finished) {

		// Displaying options
		std::cout << "\n__________________________________________________________________\n";
		std::cout << "\n\tWhat would you like to do?\n\n";
		std::cout << "1. Add an element.\n";
		std::cout << "2. Search for an element with a value.\n";
		std::cout << "3. Remove an element with a value.\n";
		std::cout << "4. Traverse the tree.\n";
		std::cout << "5. Clear the tree.\n";
		std::cout << "6. Delete the tree and exit.\n\n";
		std::cout << "\n__________________________________________________________________\n\n";
		
		// Chooses a function and validates the input
		// Selecting the chosen function
		switch (inputChoice(6))
		{
		case 1: // Add an element
			if (dataStruct.add(inputValue())) std::cout << "\nValue added successfully.\n";
			else std::cout << "\nERROR: Value already existed.\n";
			break;
		case 2: // Search for an element with a value
			if (dataStruct.contains(inputValue())) std::cout << "\nValue found.\n";
			else std::cout << "\nValue not found.\n";
			break;
		case 3: // Remove an element with a value
			if (dataStruct.remove(inputValue())) std::cout << "\nValue removed successfully.\n";
			else std::cout << "\nERRPR: Value not found.\n";
			break;
		case 4:	//Traverse the tree
			dataStruct.traverse();
			break;
		case 5: // Clears the tree
			dataStruct.clearTree();
			break;
		case 6:	// Delete the tree and exit
			dataStruct.clearTree();
			is_finished = true;
			break;
		}
	}
}