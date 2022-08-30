#include <iostream>

void DrawTable(int array[9])
{
	std::cout << "\n     |   |\n";							// Top
	for (int i = 0; i < 3; i++) // One for every row
	{
		std::cout << "   " << array[i * 3];					// First
		std::cout << " | " << array[i * 3 + 1];				// Second
		std::cout << " | " << array[i * 3 + 2];				// Third
		if (i != 2)
			std::cout << "\n  ___|___|___\n     |   |\n";	// Division
		else
			std::cout << "\n     |   |\n\n";				// Bottom
	}
}

void AskPlayer(int player, int& column, int& row, int& index)
{
	std::cout << std::endl << "  Player " << player << std::endl; // Displays the player

	// Checks if the input is valid
	while ((std::cout << "  Choose a column: ") && (!(std::cin >> column) || column < 1 || column > 3)) 
	{
		std::cout << "   ERROR: Invalid Number\n";		// Prints the error message
		std::cin.clear();							    // Clears the input
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// Checks if the input is valid
	while ((std::cout << "  Choose a row: ") && (!(std::cin >> row) || row < 1 || row > 3))	
	{
		std::cout << "   ERROR: Invalid Number\n";		// Prints the error message
		std::cin.clear();							    // Clears the input
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	index = (row - 1) * 3 + (column - 1);		// One dimensional value
}

void PlayerWon(int player)
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << "  PLAYER " << player << " WON!" << std::endl;
	}
}

void CheckSides(int a, int b, int c, int player)
{
	if (a == player && b == player && c == player)
	{
		PlayerWon(player);
	}
}

void CheckVictory(int array[], int player)
{
	if (array[4] == player)
	{
		for (int i = 0; i < 4; i++)
		{
			if (array[i] == player && array[8 - i] == player)
			{
				PlayerWon(player);
			}
		}
	}
	CheckSides(array[0], array[1], array[2], player);
	CheckSides(array[0], array[3], array[6], player);
	CheckSides(array[2], array[5], array[8], player);
	CheckSides(array[6], array[7], array[8], player);
}