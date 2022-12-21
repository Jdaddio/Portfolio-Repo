// Course: IGME 209-02
// Student Name: Joshua D'Addio
// Assignment Number: 01

#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	int number;
	int playerGuess = 0;
	int guessCount = 0; // Number of player guesses
	char replay = 'Y'; // Player has the option to change replay to 'N' after one game to end the loop

	srand(time(NULL)); // Random seed using the current time
	while (replay == 'Y' || replay == 'y') // Will loop as long as replay is set to 'Y' or 'y'
	{
		number = rand() % 100 + 1; // Generate a random number 1-100

		cout << "\nGuess the number! Type a number 1-100: ";

		while (playerGuess != number) // While the player's guess is incorrect, repeatedly prompt them to input numbers until it is correct 
		{
			cin >> playerGuess; // Receive the player's input for their guess. While their input is not an int, loop and clear cin until they input an int value 
			while (cin.fail()) {
				cout << "Please type a number: ";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> playerGuess;
			}
			if (playerGuess < number) { cout << "Too low! Try again: "; }
			if (playerGuess > number) { cout << "Too high! Try again: "; }
			guessCount++; // Increase the guess count for each guess 
		}

		// Display the number of guesses to the player, and prompt them to enter Y or N to continue or end the game
		cout << "Congratulations! the number was " << playerGuess << ". It took you " << guessCount << " guesses to find the correct number." << endl << "Try again? (Y/N)" << endl;
		cin >> replay; // Receive the player's input to continue or end the loop. While their input is not Y or N, loop and clear cin until it is
		while (replay != 'Y' && replay != 'y' && replay != 'N' && replay != 'n')
		{
			cout << replay << " is an invalid input! Please type Y for yes or N for no: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> replay;
		}
		guessCount = 0; // Set the number of guesses back to 0
		playerGuess = 0; // Set the player's guess to 0 so it is not equal to the new random number
	}
	return 0;
}