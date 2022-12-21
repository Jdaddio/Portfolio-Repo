// Joshua D'Addio
// Igme209-03
// Exam #1


#include <iostream>
#include "Exam1Methods.h"

using namespace std;

int scoreCount = 0; // Saves the number of scores to be saved
float* scores; // Pointer that will point to the memory allocated for the saved scores

int main()
{
    cout << "How many scores will you be saving? ";
    while (scoreCount <= 0) // Prompts the user to enter a positive number to be saved as the scoreCount
    {
        cin >> scoreCount;
        if (scoreCount <= 0) 
        {
            cout << scoreCount << " is not a valid number! Please choose a higher number. ";
        }
    }

    cout << "\nYou will be saving " << scoreCount << " scores.\n" << endl; 

    scores = new float[scoreCount]; // Allocates memory for however many floats the user specifies

    for (int i = 0; i<scoreCount; i++) // Ask the user to enter scores, then save them to the scores array
    {
        cout << "Please enter score " << i + 1 << ": ";
        cin >> scores[i];
    }

    //for (int i = 0; i < scoreCount; i++){cout << scores[i] << "\n";} // test to display all of the scores written

    AverageScore(scores, scoreCount); // Prints out the average of all the saved scores to the console.
    HighScore(scores, scoreCount); // Prints out the highest saved score to the console.
    LowScore(scores, scoreCount); // Prints out the lowest saved score to the console.

    delete[] scores; // IMPORTANT! Cleans up the memory after allocating it when choosing the number of scores
}

void AverageScore(float* score, int count) // Prints out the average of all the saved scores to the console.
{
    float avg = 0;
    for (int i = 0; i < count; i++)
    {
        avg += (int)score[i]; // Add together all the saved scores,
    }
    avg /= count; // then divide by the number of scores in the array
    cout << "\nThe average score is " << (int)avg << ".\n" << endl;
}

void HighScore(float* score, int count) // Prints out the highest saved score to the console.
{
    float hi = score[0]; // Set hi to one of the scores in the array to make sure you don't accidentally go higher
    for (int i = 0; i < count; i++)
    {
        if (hi < score[i]) // If hi is lower than another score in the score array,
        {
            hi = score[i]; // set hi to that score to find the highest score
        }
    }
    cout << "The highest score is " << (int)hi << ".\n" << endl;
}

void LowScore(float* score, int count) // Prints out the lowest saved score to the console.
{
    float lo = score[0]; // Set lo to one of the scores in the array to make sure you don't accidentally go lower
    for (int i = 0; i < count; i++)
    {
        if (lo > score[i]) // If lo is greater than another score in the score array,
        {
            lo = score[i]; // set lo to that score to find the lowest score
        }
    }
    cout << "The lowest score is " << (int)lo << "." << endl;
}
