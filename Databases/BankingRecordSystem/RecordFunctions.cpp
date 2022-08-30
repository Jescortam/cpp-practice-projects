#include <iostream>
#include <string>
#include <fstream>
#include "subFunctions.h"

int accNum;					// Account number to be written
int searchNum;				// Account number to be searched
std::string firstName;		// Record's first name
std::string lastName;		// Record's last name
int balance;				// Record's balance

void AddRecord()
{
	// Is the record's number not repeated
	bool isNewAccount;

	// Opens file for writing (appending) and reading
	std::ofstream writeFile;
	writeFile.open("records.txt", std::ofstream::app);
	std::ifstream readFile("records.txt");

	// Checks if the file opens
	if (writeFile.is_open())
	{
		// Account number
		while (true)
		{
			isNewAccount = true;
			AccountNumInput(searchNum);			// Verifies the input
			readFile.seekg(0, std::ios::beg);	// Reads from the beginning

			// Reads the next account number
			while (readFile >> accNum)			
			{
				// If the search number is repeated, try another number
				if (searchNum == accNum)
				{
					isNewAccount = false;
					std::cout << "  ERROR: This account already exists.\n\n";
					break;
				}

				// Ignore the rest
				readFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			// If the number is not repeated, move on
			if (isNewAccount)
				break;
		}

		// The number will be the search number
		accNum = searchNum;

		// First name
		NameInput(firstName, "first");

		// Last name
		NameInput(lastName, "last");

		// Balance
		while ((std::cout << "  Enter balance: $") && !(std::cin >> balance))
		{
			InvalidInput();
		}

		// Writes all the data in the file
		writeFile << accNum << " " << firstName << " " << lastName << " " << balance << "\n";
		std::cout << "\n\n";

		// Closes all the files
		readFile.close();
		writeFile.close();
	}
	else
		OpenFileError(); // Could not read the file
}

void ShowRecord()
{
	// Opens the file for reading
	std::ifstream myFile("records.txt");

	// Validates the input
	AccountNumInput(searchNum);	

	// Checks if the file opens
	if (myFile.is_open())
	{
		// Gets a number from the file
		myFile >> accNum;

		// If the number matches
		while (accNum != searchNum)
		{
			// Ignore the rest of the line
			myFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// Checks if the file has reached the end
			if (myFile.eof())
			{
				std::cout << "    ERROR: Could not find account number #" << searchNum << "\n\n";
				myFile.close();
				return;
			}

			// Gets another number from the file
			myFile >> accNum;
		}
		
		// Gets the rest of the data from the number you searched
		myFile >> firstName >> lastName >> balance;

		// Puts the data in the terminal
		std::cout << "\n  First name: " << firstName << "\n  Last name: " << lastName << "\n  Balance: $" << balance << "\n\n";
	}
	else
		OpenFileError();	// Could not read the file

	// Closes the file
	myFile.close();
}

void UpdateRecord()
{
	// Opens the old file for reading and the new file for writing
	std::ifstream oldFile("records.txt");
	std::ofstream newFile("temp.txt");
	
	std::string line;		// Makes a string to read line by line
	char confirmation;		// To make sure you want to change the record

	while (true)
	{
		// Shows the record to be changed
		ShowRecord();

		// Confirmation to change the record
		while ((std::cout << "Do you want to modify this record? (Y/N) ") && (!(std::cin >> confirmation)
			|| (confirmation != 89 && confirmation != 78 && confirmation != 121 && confirmation != 110)))
		{
			InvalidInput();
		}

		// If the user types "Y" or "y", moves on
		if (confirmation == 89 || confirmation == 121)
			break;
	}

	// First name
	NameInput(firstName, "first");

	// Last name
	NameInput(lastName, "last");

	// Balance
	while ((std::cout << "  Enter balance: $") && !(std::cin >> balance))
	{
		InvalidInput();
	}

	// If the old file could be opened
	if (oldFile.is_open())
	{
		// Gets a number from the old file
		while (oldFile >> accNum)
		{
			// Inserts it in the new file
			newFile << accNum;
			if (accNum == searchNum)
			{
				// Inserts the updated data and ignores the old
				newFile << " " << firstName << " " << lastName << " " << balance << "\n";
				oldFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			// For the rest of the records, get the whole line in the new record
			getline(oldFile, line);
			newFile << line << "\n";
		}
	}
	else
		OpenFileError();	// Could not read the file

	// Closes all the files
	oldFile.close();
	newFile.close();

	// Removes the old file
	if (remove("records.txt") != 0)
		std::cout << "\nERROR: Could not delete file.\n\n";

	// Renames the new file to be the original
	if (rename("temp.txt", "records.txt") != 0)
		std::cout << "ERROR: Could not rename file.\n\n";
}

void DeleteRecord()
{
	// Opens the old file for reading and the new file for writing
	std::ifstream oldFile("records.txt");
	std::ofstream newFile("temp.txt");

	std::string line;		// Makes a string to read line by line
	char confirmation;		// To make sure you want to change the record

	while (true)
	{
		// Shows the record to be changed
		ShowRecord();

		// Confirmation to change the record
		while ((std::cout << "Do you want to modify this record? (Y/N) ") && (!(std::cin >> confirmation)
			|| (confirmation != 89 && confirmation != 78 && confirmation != 121 && confirmation != 110)))
		{
			InvalidInput();
		}

		// If the user types "Y" or "y", moves on
		if (confirmation == 89 || confirmation == 121)
			break;
	}
	
	// Checks if the file could open
	if (oldFile.is_open())
	{
		// Gets a number from the old file
		while (oldFile >> accNum)
		{
			// Ignores the record you want to discard
			if (accNum == searchNum)
				oldFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			else
				newFile << accNum;

			// Puts every other piece of data in the new file
			getline(oldFile, line);
			newFile << line << "\n";
		}
	}
	else
		OpenFileError();	// Could not read the file

	// Closes all the files
	oldFile.close();
	newFile.close();

	// Removes the old file
	if (remove("records.txt") != 0)
		std::cout << "\nERROR: Could not delete file.\n\n";

	// Renames the new file to be the original
	if (rename("temp.txt", "records.txt") != 0)
		std::cout << "ERROR: Could not rename file.\n\n";
}