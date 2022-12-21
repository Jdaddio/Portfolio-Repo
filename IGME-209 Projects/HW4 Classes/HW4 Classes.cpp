// Joshua D'Addio
// HW 4 - Classes

#include <iostream>
#include "Player.h"
#include "Fighter.h"
using namespace std;

int main()
{
    srand(time(0)); // Uses the current time to create a seed for rand

    // Create four player objects and call printPlayer to display the information
    Player p1 = Player();
    Player p2 = Player("Player2", 3, 12, 10);
    Player* p3 = new Player();
    Player* p4 = new Player("Player4", 15, 4, 5);
    p1.printPlayer();
    p2.printPlayer();
    p3->printPlayer();
    p4->printPlayer();

    // Create two fighter objects and call printFighter to display the information
    Fighter f1 = Fighter();
    Fighter f2 = Fighter("Fighter2", "swords", 10, 8, 12);
    f1.printFighter();
    f2.printFighter();

    Player* battlers[10]; // Array of player objects- can contain fighters as Fighter is a child class of Player
    int pf; // Used for rng
    int fatalities = 0; // Keep track of how many battlers have been eliminated
    for (int i = 0; i < 10; i++)
    {
        pf = rand() % 2; // Randomly decides to create a player or fighter
        if (pf == 0)
        {
            battlers[i] = new Player();
        }
        else
        {
            battlers[i] = new Fighter();
        }
    }

    cout << "The Punch Fighters Tournament has begun!\n" << endl;
    while (fatalities < 9) // While less than 9 battlers have been eliminated, continue the fight
    {
        for (int i = 0; i < 10; i++)
        {
            pf = rand() % 10;
            while (battlers[pf] == nullptr) // Check to make sure the random number doesn't point to an eliminated fighter
            {
                pf = rand() % 10;
            }
            if (battlers[i] != nullptr && i != pf) // If the battler is not already eliminated and is not targeting themself,
            {
                // Attack and delete the target battler, then assign them to nullptr.
                battlers[i]->attack(battlers[pf]);
                delete battlers[pf];
                battlers[pf] = nullptr;
                fatalities++;
            }
            if (fatalities == 9) // If 9 battlers have been eliminated, then the last survivor made the last move, so they are the victor.
            {
                cout << "\n" << battlers[i]->getName() << " (Battler " << i << ") is the victor!!!\n" << endl;
                break;
            }
        }
    }

    delete p3;
    delete p4;
}
