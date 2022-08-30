#include <iostream>
#include <string>
#include "Functions.h"

int main()
{
	// Max letters
	const int MAX = 50;			// The limit of letters in the word(s)
	int failedGuesses = 0;		// Increases with each wrong answer
	int numGuesses = 0;			// Total number of guesses
	char charGuess[26];			// All the letters in the alphabet to guess
	bool charMatches;			// Does the input matches a letter?
	bool wordMatches = false;	// Is the word fully discovered?

	//Title
	std::cout << "  HANGMAN IN C++\n";

	//Asks for a valid word to be guessed
	std::string word;
	bool isWord;
	while (true) 
	{
		isWord = true;  // Default value
		std::cout << "  Word(s): ";
		getline(std::cin, word);  // Gets multiple words

		// Searching for a non alphabetical letter
		for (int i = 0; i < word.size(); i++)
		{
			if (word[i] != 32 && !(word[i] >= 65 && word[i] <= 90) && !(word[i] >= 97 && word[i] <= 122))
			{
				// The word is not valid
				std::cout << "Error: " << word[i] << " is not a letter\n";
				isWord = false;
				break;
			}
		}

		// If it is valid, break the loop
		if (isWord)
			break;

		// If not, ask for the word again and clear the last input
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// Make the hidden version of the word
	char hiddenWord[MAX];
	for (int i = 0; i < word.size(); i++)
	{
		// Spaces
		if (word[i] == 32)
			hiddenWord[i] = 32;

		// Letters
		else
			hiddenWord[i] = '_';
	}

	// Make every letter uppercase
	for (int i = 0; i < word.size(); i++)
	{
		MakeUppercase(word[i]);
	}

	// Game begins
	while (failedGuesses < 5) 
	{
		charMatches = false;
		wordMatches = true;

		// Draws the hangman
		DrawHangman(failedGuesses);

		// Show the hidden version of the word
		std::cout << "  ";
		for (int i = 0; i < word.size(); i++)
		{
			std::cout << " " << hiddenWord[i];
		}
		std::cout << "\n\n";

		// Show the last guesses
		std::cout << "  Last guesses: ";
		for (int i = 0; i < numGuesses; i++)
		{
			std::cout << charGuess[i] << ", ";
		}
		std::cout << "\n\n";

		// If a letter is not discovered yet, then the word is not finished
		for (int i = 0; i < word.size(); i++)
		{
			if (hiddenWord[i] != word[i])
				wordMatches = false;
		}
		
		// If every letter is shown, end the game
		if (wordMatches)
			break;

		//Asks the user for a valid letter
		while ((std::cout << "  Letter: ") &&
			(!(std::cin >> charGuess[numGuesses]) ||
				!((charGuess[numGuesses] >= 65 && charGuess[numGuesses] <= 90)
					|| (charGuess[numGuesses] >= 97 && charGuess[numGuesses] <= 122))))
		{
			// If the input is invalid, print error and ask again
			std::cout << "ERROR: Not a letter\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		// Division line
		std::cout << "\n\n====================================\n\n";

		// Make the letter uppercase
		MakeUppercase(charGuess[numGuesses]);

		// Shows the letters that match the user's new input
		for (int i = 0; i < word.size(); i++)
		{
			// numGuesses is the current guess
			if (charGuess[numGuesses] == word[i])
			{
				charMatches = true;
				hiddenWord[i] = word[i];
			}
		}

		// If it doesn't match with any letter, it's a fail
		// A fail is another part of the body drawn
		if (!charMatches)
			failedGuesses++;

		// One more guess has been done
		numGuesses++;
	}

	// If the word doesn't match after the 5 fails, you lost
	if (!wordMatches)
	{
		DrawHangman(failedGuesses);
		std::cout << "\n\n  You lost!\n\n";
		return 0;
	}

	// If the word matches perfectly, you won
	std::cout << "  You won!\n\n";
	return 0;
}