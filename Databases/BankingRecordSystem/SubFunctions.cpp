#include <iostream>
#include <string>
#include <fstream>

// Displays the functions
void OptionsDisplay()
{
	std::cout << "**Acount Information System**\nSelect one option below: \n";
	std::cout << "	1. Add record\n";
	std::cout << "	2. Show record\n";
	std::cout << "	3. Update record\n";
	std::cout << "	4. Delete record\n";
	std::cout << "	5. Exit\n";
}

// What to do when a input is invalid
void InvalidInput()
{
	std::cout << "ERROR: Invalid input\n";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// Message that shows when the file cannot be opened
void OpenFileError()
{
	std::cout << "ERROR: Could not open file.\n";
}

// Check if the account number is valid
void AccountNumInput(int& account)
{
	while ((std::cout << "  Enter account number: #") && (!(std::cin >> account) || account < 1 || account > 100))
	{
		InvalidInput();
	}
}

// Checks if the name is valid, and gives it a format
void NameInput(std::string& name, std::string typeName)
{
	bool isWord;
	while (true)
	{
		isWord = true;  // Default value
		std::cout << "  Enter " << typeName << " name: ";
		std::cin >> name;

		// Checking the word
		for (int i = 0; i < name.size(); i++)
		{
			if (!(name[i] >= 65 && name[i] <= 90) && !(name[i] >= 97 && name[i] <= 122))
			{
				// The word is not valid
				std::cout << "Error: " << name[i] << " is not a letter\n";
				isWord = false;
				break;
			}

			// Making the letters lowercase
			if (name[i] >= 65 && name[i] <= 90)
				name[i] += 32;
		}

		// First letter uppercase
		if (name[0] >= 97 && name[0] <= 122)
			name[0] -= 32;

		// If it is valid, break the loop
		if (isWord)
			break;

		// If not, ask for the word again and clear the last input
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

// Searchs a record from the file
int SearchRecord(std::istream& file, int searchNumber)
{
	int accountNumber;

	// Gets a number from the file
	file >> accountNumber;

	// If that number matches, return 0
	while (accountNumber != searchNumber)
	{
		// Ignores the rest of the data
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (file.eof())
		{
			// The record does not exist
			return 1;
		}
		file >> accountNumber;
	}
	return 0;
}

