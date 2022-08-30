#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <string>
#include <new>

// lenght of the person's name
const int nameLenght = 40;

// How many slots need to be moved
int numMoves;

// How many objects are there
int numProducts;

// The ID from the user and the ID from the file
int newID;
int copyID;

// Positions
std::streampos putCurrentPosition, getCurrentPosition;	// The one they had
std::streampos putLastPosition, getLastPosition;		// The one from the last record copied
std::streampos putEndPosition, getEndPosition;			// The one from the end of file

// A function to validate user's input
void InvalidInput()
{
	std::cout << "ERROR: Invalid input.\n";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int ConfirmChoice()
{
	// Confirm the replacement and validate the input
	bool confirmation;
	while ((std::cout << "Are you sure? (1 = Yes / 0 = No): ") && (!(std::cin >> confirmation) || (confirmation != 0 && confirmation != 1)))
		InvalidInput();

	// Return values
	if (confirmation)
		return 1;	// Yes
	else
		return 0;	// No
}

// Defining the class and making a object
class Product
{
	int ID = 0;
	char name[nameLenght] = "";
	float price = 0.00;
public:
	// Modify the object's data
	void ChangeData();

	// Tell all the data from the object
	void DisplayData();

	// Return the ID value
	int GetID() { return ID; }

	// Write and read from file
	void WriteData(std::fstream& file) { file.write((char*)this, sizeof(Product)); }
	void ReadData(std::fstream& file) { file.read((char*)this, sizeof(Product)); }
} newProduct, readCopy;

void Product::ChangeData()
{
	// The user gives a positive number and prints error if it is invalid
	while ((std::cout << "ID: ") && (!(std::cin >> ID) || ID <= 0 || ID > 999999.99))
		InvalidInput();

	// The user gives a name to the product
	std::cout << "Product Name: ";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.getline(name, nameLenght);

	// The user gives a valid float number and prints error if it is invalid
	while ((std::cout << "Price: ") && (!(std::cin >> price) || price < 0.0 || price >= 1000000.0))
		InvalidInput();
}

void Product::DisplayData()
{
	std::cout << "| " << std::setfill('0') << std::setw(6) << ID;
	std::cout << " | " << name << std::setfill(' ') << std::setw(44 - strlen(name));
	std::cout << " | $" << std::setfill(' ') << std::setw(9) << std::fixed << std::setprecision(2) << price << " |\n";
}

// Size of the object
std::streampos sizeProduct = (std::streampos) sizeof(Product);

void AddProduct(std::fstream& file)
{
	// End of file for put
	file.seekp(0, std::ios::end);
	putEndPosition = file.tellp();
	file.seekp(0);

	// End of file for get
	file.seekg(0, std::ios::end);
	getEndPosition = file.tellg();
	file.seekg(0);

	// Ask the user for data to fill the object
	newProduct.ChangeData();

	// Save the current position for later
	putCurrentPosition = file.tellp();
	getCurrentPosition = file.tellg();

	while (true)
	{
		// If there is no more objects, write it there
		if (file.tellp() == putEndPosition)
		{
			newProduct.WriteData(file);
			break;
		}

		// Read the next product
		readCopy.ReadData(file);

		// Get the ID of both objects
		newID = newProduct.GetID();
		copyID = readCopy.GetID();

		// Comparing the two IDs
		if (newID < copyID)
		{
			// Set the position it used to have
			file.seekp(putCurrentPosition);
			file.seekg(getCurrentPosition);

			// Determine how many products must be moved
			numMoves = (putEndPosition - putCurrentPosition) / sizeProduct;

			// Start at the end, one by one
			getLastPosition = getEndPosition;
			putLastPosition = putEndPosition;

			for (int i = 0; i < numMoves; i++)
			{
				// Copy the next product
				file.seekg(getLastPosition -= sizeProduct);
				readCopy.ReadData(file);

				// Put it in a slot below
				file.seekp(putLastPosition = getLastPosition + sizeProduct);
				readCopy.WriteData(file);
			}

			// With the slot needed now available, write the new product
			file.seekp(putCurrentPosition);
			newProduct.WriteData(file);
			break;
		}

		// Comparing the two IDs
		else if (newID == copyID)
		{
			// Print the product with the same ID
			std::cout << "\nThere is a product with the same ID:\n";
			std::cout << ".--------.------------------------------------------.------------.\n";
			std::cout << "| ID     | Product Name:                            | Price:     |\n";
			std::cout << "|--------|------------------------------------------|------------| \n";
			readCopy.DisplayData();
			std::cout << "'--------'------------------------------------------'------------'\n";

			// Confirm choice
			if (!ConfirmChoice())
				return;

			// Replace the old product
			file.seekp(file.tellg() - sizeProduct);
			newProduct.WriteData(file);
			break;
		}

		// Comparing the two IDs
		else if (newID > copyID)
		{
			// Read the next record
			file.seekp(putCurrentPosition += sizeProduct);
			file.seekg(getCurrentPosition += sizeProduct);
		}
	}
}

// Returns searchNum if found, 0 if not
int SearchProduct(std::fstream& file)
{
	// End of file for put
	file.seekp(0, std::ios::end);
	putEndPosition = file.tellp();
	file.seekp(0);

	// End of file for get
	file.seekg(0, std::ios::end);
	getEndPosition = file.tellg();
	file.seekg(0);

	int searchNum;
	// The user gives a positive number and prints error if it is invalid
	while ((std::cout << "Search by ID: ") && (!(std::cin >> searchNum) || searchNum <= 0))
		InvalidInput();

	while (true)
	{
		// If there is no more objects, write it there
		if (file.tellp() == putEndPosition)
		{
			std::cout << "Product not found.\n";
			return 0;
		}

		// Saves the current position of the writing and reading
		putCurrentPosition = file.tellp();
		getCurrentPosition = file.tellg();

		// Read the next product
		readCopy.ReadData(file);
		copyID = readCopy.GetID();

		// Returns to the position it had
		file.seekp(putCurrentPosition);
		file.seekg(putCurrentPosition);

		// Comparing the two IDs
		if (searchNum < copyID)
		{
			std::cout << "Product not found.\n";
			return 0;
		}

		// Comparing the two IDs
		else if (searchNum == copyID)
		{
			// Print the product with the same index
			std::cout << "\nProduct found: \n";
			std::cout << ".--------.------------------------------------------.------------.\n";
			std::cout << "| ID     | Product Name:                            | Price:     |\n";
			std::cout << "|--------|------------------------------------------|------------| \n";
			readCopy.DisplayData();
			std::cout << "'--------'------------------------------------------'------------'\n";
			return searchNum;
		}

		// Comparing the two IDs
		else if (searchNum > copyID)
		{
			// Read the next product
			file.seekp(putCurrentPosition += sizeProduct);
			file.seekg(getCurrentPosition += sizeProduct);
		}
	}
}

void ShowProducts(std::fstream& file)
{
	// Storing the position of the end of the file for get
	file.seekg(0, std::ios::end);
	getEndPosition = file.tellg();
	file.seekg(0);

	// Calculating how many objects are in the file
	numProducts = (int)getEndPosition / sizeof(Product);
	std::cout << "Number of Products: " << numProducts << "\n\n";

	// Make an array of all the objects in the file and check for errors
	Product* productArray = new (std::nothrow) Product[numProducts];
	if (productArray == nullptr)
	{
		std::cout << "ERROR: Could not allocate enough memory.\n";
		return;
	}

	// Structure
	std::cout << ".--------.------------------------------------------.------------.\n";
	std::cout << "| ID     | Product Name:                            | Price:     |\n";
	std::cout << "|--------|------------------------------------------|------------| \n";

	// Copy every Person from the file and display their data
	for (int i = 0; i < numProducts; i++)
	{
		productArray[i].ReadData(file);
		productArray[i].DisplayData();
	}

	std::cout << "'--------'------------------------------------------'------------'\n\n";

	// Free the allocated memory
	delete[] productArray;
}

void DeleteProduct(std::fstream& file)
{
	// Search for the product to be deleted
	int deleteNum = SearchProduct(file);

	// Product not found
	if (deleteNum == 0)
		return;

	// Confirm the choice
	if (!ConfirmChoice())
		return;

	// Copy everything except the product chosen
	// Open a temporary file for writing and check if it open
	std::fstream newFile("temp.bin", std::ios::out | std::ios::binary | std::ios::trunc);

	if (!newFile.is_open())
	{
		std::cout << "ERROR: Could not open file.\n";
		return;
	}

	// Get the position of the end of the file
	file.seekg(0, std::ios::end);
	getEndPosition = file.tellg();
	file.seekg(0);
	newFile.seekg(0);

	// While it is not the end of file
	while (getEndPosition != file.tellg())
	{
		readCopy.ReadData(file);
		copyID = readCopy.GetID();

		if (deleteNum != copyID)
			readCopy.WriteData(newFile);
	}

	// Removes the old file
	file.close();
	if (remove("records.bin") != 0)
		std::cout << "\nERROR: Could not delete file.\n\n";

	// Renames the new file to be the original
	newFile.close();
	if (rename("temp.bin", "records.bin") != 0)
		std::cout << "ERROR: Could not rename file.\n\n";

	// Open the file again
	file.open("records.bin", std::ios::in | std::ios::out | std::ios::binary);
}

void DeleteProducts(std::fstream& file)
{
	// Confirm choice
	if (!ConfirmChoice())
		return;

	// Erases all the contents from the file because of std::ios::trunc
	file.close();
	file.open("records.bin", std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);
}