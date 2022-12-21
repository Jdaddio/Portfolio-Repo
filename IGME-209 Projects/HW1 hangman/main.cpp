
#include <iostream>
#include <string>
#include "hangman.h"
using namespace std;

int main()
{
    char word[100] = "sarsaparilla";
    char correct[100] = "";
    char incorrect[100] = "";
    bool done = false;
    char guess[100];
    int guessLimit = 6;
    int numLetters = strlen(word);

    cout << "Welcome to Hangman!\n"
         << "Your word contains " << strlen(word) << " letters.\n"
         << "What letter do you guess next?  ";
    while (!done)
    {
        cin >> guess;
        while (strlen(guess) > 1) 
        {
            cout << "You can't guess more than one letter!\n"
                 << "What letter do you guess next?  ";
            cin >> guess;
        }
        cout << "Guess: " << guess << "\n";
        while (strchr(correct, guess[0]) || strchr(incorrect, guess[0]))
        {
            cout << "-------------------------------------\n"
                 << "You have already guessed this letter!\n"
                 << "-------------------------------------\n"
                 << "What letter do you guess next?  ";
            cin >> guess;
        }
        
        if (strchr(word, guess[0]))
        {
            strcat_s(correct, guess);
            for (int i = 0; i < strlen(word); i++)
            {
                if (word[i] == guess[0])
                    numLetters--;
            }
        }
        else
        {
            strcat_s(incorrect, guess);
            guessLimit--;
        }
        
        showGallows(guessLimit);
        cout << "Wrong guesses: " << incorrect << "\n";
        showSolved(word, correct);
        cout << "\n" << numLetters << " letters left to guess.";
        
        if (guessLimit == 0)
        {
            cout << "\n\nSorry, you lose!\n";
            done = true;
        }
        else if (numLetters == 0)
        {
            cout << "\n\nCongrats, you win!!!\n";
            done = true;
        }
        else 
        {
            cout << "\nWhat letter do you guess next?  ";
        }
    }
}
