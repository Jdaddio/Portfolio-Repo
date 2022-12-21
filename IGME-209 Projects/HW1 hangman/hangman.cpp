
#include <iostream>
#include <string>
#include "hangman.h"

using namespace std;

void showGallows(int guessLimit)
{
	switch (guessLimit)
	{
		cout << "\n";
		case 6:
			cout << "___________\n"
				 << "|    |     \n"
				 << "|          \n"
				 << "|          \n"
				 << "|          \n"
				 << "|          \n"
				 << "|          \n";
			break;
		case 5:
			cout << "___________\n"
				 << "|    |     \n"
				 << "|    O     \n"
				 << "|          \n"
				 << "|          \n"
				 << "|          \n"
				 << "|          \n";
			break;
		case 4:
			cout << "___________\n"
				 << "|    |     \n"
				 << "|    O     \n"
				 << "|    |     \n"
			 	 << "|          \n"
				 << "|          \n"
				 << "|          \n";
			break;
		case 3:
			cout << "___________\n"
				 << "|    |     \n"
				 << "|    O     \n"
				 << "|   /|     \n"
				 << "|          \n"
				 << "|          \n"
				 << "|          \n";
			break;
		case 2:
			cout << "___________\n"
				 << "|    |     \n"
				 << "|    O     \n"
				 << "|   /|\\   \n"
				 << "|          \n"
				 << "|          \n"
				 << "|          \n";
			break;
		case 1:
			cout << "___________\n"
				 << "|    |     \n"
				 << "|    O     \n"
				 << "|   /|\\   \n"
				 << "|   /      \n"
				 << "|          \n"
				 << "|          \n";
			break;
		case 0:
			cout << "___________\n"
				 << "|    |     \n"
				 << "|    O     \n"
				 << "|   /|\\   \n"
				 << "|   / \\   \n"
				 << "|          \n"
				 << "|          \n";
			break;
	}
}
void showSolved(char word[], char guesses[])
{
	cout << "Word to solve: ";
	for (int i = 0; i < strlen(word); i++) 
	{
		for (int j = 0; j < strlen(guesses); j++)
		{
			if (word[i] == guesses[j]) 
			{
				cout << guesses[j];
				break;
			}
			else if (j == (strlen(guesses) - 1)) 
			{
				cout << "_";
				break;
			}
		}
	}
	cout << "\n";
}