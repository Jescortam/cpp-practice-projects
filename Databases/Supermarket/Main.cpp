#include <iostream>
#include <string>
#include <fstream>
#include <new>
#include "RecordFunctions.h"

// Declaring the file
std::fstream file;

int main()
{
	// If true, exit the program
	bool is_finished = false;

	// Opening the file for writing and reading in binary
	file.open("records.bin", std::ios::out | std::ios::in | std::ios::binary);

	// Error opening the file
	if (!file.is_open())
	{
		std::cout << "ERROR: File could not be opened.\n";
		return 1;
	}

	while (!is_finished) {

		// Displaying options
		std::cout << "__________________________________________________________________\n";
		std::cout << "\nWELCOME TO BETTER BUY\nWhat would you like to do?\n\n";
		std::cout << "1. Add or replace a product.\n";
		std::cout << "2. Search a product by ID.\n";
		std::cout << "3. Show all products.\n";
		std::cout << "4. Delete a product.\n";
		std::cout << "5. Delete all products.\n";
		std::cout << "6. Exit.\n\n";

		int choice;
		while ((std::cout << "Choose a function: ") && (!(std::cin >> choice) || choice < 1 || choice > 6))
			InvalidInput();

		std::cout << "\n__________________________________________________________________\n\n";

		switch (choice)
		{
		case 1:
			AddProduct(file);
			break;
		case 2:
			SearchProduct(file);
			break;
		case 3:
			ShowProducts(file);
			break;
		case 4:
			DeleteProduct(file);
			break;
		case 5:
			DeleteProducts(file);
			break;
		case 6:
			is_finished = true;
			break;
		}
	}

	// Close the file
	file.close();
}