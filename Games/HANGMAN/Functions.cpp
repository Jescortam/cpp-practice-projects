#include <iostream>

//Draws the hangman
void DrawHangman(int aFailedGuesses) {

	// Structure's top
	std::cout << "   __________		\n";
	std::cout << "   |_________|		\n";
	if (aFailedGuesses >= 1)
	{
		// First fail
		std::cout << "     ||//   _|_		\n";
		std::cout << "     ||/   |x x|		\n";
		std::cout << "     ||    |_'_|		\n";
		if (aFailedGuesses >= 2)
		{
			// Second fail
			std::cout << "     ||      |		\n";
			std::cout << "     ||    __|__		\n";
			if (aFailedGuesses >= 3)
			{
				// Third fail
				std::cout << "     ||   |  |  |	\n";
				std::cout << "     ||   |  |  |	\n";
				if (aFailedGuesses >= 4)
				{
					// Fourth fail
					std::cout << "     ||      |		\n";
					std::cout << "     ||    __|__		\n";
					if (aFailedGuesses >= 5)
					{
						// Fifth fail, GAME OVER
						std::cout << "     ||   |     |	\n";
						std::cout << "     ||   |     |	\n";
					}
				}
			}
		}
	}
	// Structure's base
	for (int i = 0; i < 12 - aFailedGuesses * 2; i++)
	{
		// Making it the same height
		std::cout << "     ||				\n";
	}
	std::cout << "  ___||______			\n";
	std::cout << " |___________|	  \n\n";
}

// If lowercase, make uppercase
void MakeUppercase(char& lowCase)
{
	if (lowCase >= 97 && lowCase <= 122)
		lowCase -= 32;
}