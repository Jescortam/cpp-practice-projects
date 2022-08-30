#include <iostream>
#include "Functions.h"

int main()
{
	// Welcome text
	std::cout << "  Welcome to TIC-TAC-TOE in C++\n";
		
	// Draw Table	
		const int MAX = 9;				// Number of cells
		int numArray[MAX];				// Cell list
		for (int j = 0; j < MAX; j++)	// Filling the cells with 0s
		{
			numArray[j] = 0;
		}

		DrawTable(numArray);

	for (int i = 0; i < MAX; i++)
	{
		// Ask for player's choice
			int player = (i % 2) + 1;
			int column = 0;
			int row = 0;
			int index;

			do {
				AskPlayer(player, column, row, index);
			} while (numArray[index] != 0);

		// Changes the 0 to Player's number
			numArray[index] = player;		

		// Updates the table
			DrawTable(numArray);

		// Check if he won
			CheckVictory(numArray, player);
	}

	// Tie
	while (true)
	{
		std::cout << "  Tie!" << std::endl;
	}
}