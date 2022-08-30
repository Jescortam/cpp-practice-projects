#include <iostream>
#include <string>
#include <fstream>
#include "RecordFunctions.h"
#include "subFunctions.h"

int main()
{
	// Giving a number to every function
	enum Function 
	{ Add = 1, Show, Update, Delete, Exit };

	int choice;				// To select a function
	bool isEnded = false;	// Program ended

	while (true)
	{
		// End if the program has been finished
		if (isEnded)		
			break;

		// Title
		OptionsDisplay();

		// Choosing a function
		while ((std::cout << "\n\nEnter your choice: ") && (!(std::cin >> choice) || choice < 1 || choice > 5))
		{
			InvalidInput();
		}

		switch (choice)
		{
		case Add:				// Add a record to the file
			AddRecord();
			break;
		case Show:				// Show a record from the file
			ShowRecord();
			break;
		case Update:			// Update a record from the file
			UpdateRecord();
			break;
		case Delete:			// Delete a record from the file
			DeleteRecord();
			break;
		case Exit:				// Exit the program
			isEnded = true;
			break;
		}
	}
}