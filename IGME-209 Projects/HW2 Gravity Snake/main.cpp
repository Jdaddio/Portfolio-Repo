// Joshua D'Addio
// HW 2 - Gravity Snake

#include <iostream>
#include <conio.h>;
#include <stdlib.h>;
#include <ctime>;
#include "Box2D\Box2D.h";
#include "snake.h";

using namespace std;

int key; // Tracks which key was pressed last
float targetX; // the X value of the target
float targetY; // the Y value of the target
int hits; // How many hits the player has
int points; // How many points the next hit will be worth
int score; // All of the player's points added together

int main()
{
    srand(time(0)); // Uses the current time to create a seed for rand
    bool end = false; // If the game has ended, true
    bool paused = false; // If the game is paused, true
    bool continued = false; // If the game has been paused and then continued, true
    hits = 0;

    b2Vec2 gravity(0.0f, -9.8f); // Vector to represent the constant gravity force
    b2World world(gravity); // Creates a physics world with gravity as its constant force
    b2World* worldRef = &world; // A pointer to the world

    b2BodyDef bodyDef; // Defines the physics body to be created
    bodyDef.type = b2_dynamicBody; // Make it a dynamic body
    bodyDef.position.Set(0.0f, 0.0f); // Set the position to the center
    b2Body* snake = world.CreateBody(&bodyDef); // Create a pointer to the body created by the world called Snake

    b2PolygonShape dynamicBox; // Creates shape to attach to the snake
    dynamicBox.SetAsBox(1.0f, 1.0f); // Sets the shape as a box

    b2FixtureDef fixtureDef; // Creates a fixture to attach to the snake body
    fixtureDef.shape = &dynamicBox; // Sets the fixture to the box shape
    fixtureDef.density = 1.0f; // Density and friction affect the movement of the snake
    fixtureDef.friction = 0.3f;

    snake->CreateFixture(&fixtureDef); // Fixes the fixture to the snake to give it physics :)
    
    // randomly sets the 
    targetX = (float)(((rand() % 1001) - 500.0f) / 100.0f);
    targetY = (float)(((rand() % 1001) - 500.0f) / 100.0f);

    cout << "Welcome to gravity snake!\nUse WASD or the arrow keys to apply forces and move the snake. Try to hit two targets!\nPress ESC to end the game at any time.\n\nPress SPACE to begin" << endl;
    while (key != 32) 
    {
        key = _getch();
    }
    points = 1000; // The possible points start at 1000, and decrease when buttons are pressed
    while (!end) 
    {
        while (!paused) 
        {
            if (_kbhit()) //If a key is pressed
            {
                key = _getch(); // Get the key input
                if (key == 27) { end = true; break; } // If ESC is pressed, end the game
                applyForces(snake, key); // Applies forces on the snake based on key inputs
                points--; // Subtract from points whenever a force is applied
            }

            update(*worldRef); // Updates the physics world by 1 step
            display(snake, targetX, targetY); // Displays the X and Y positions of the Snake and the Target

            //If the snake position intersects the target position
            if (snake->GetPosition().x <= (targetX + 0.3) && snake->GetPosition().x >= (targetX - 0.3) && snake->GetPosition().y <= (targetY + 0.3) && snake->GetPosition().y >= (targetY - 0.3))
            {
                cout << "HIT TARGET!!!\n";
                hits++; // Add to the player's hits
                score += points; // Add the remaining points to the player's score
                points = 1000; // Reset points for the next hit
                moveTarget(targetX, targetY); // Move the target to a new random position
            }
            // If the player gets 2 or 10 hits, pause the game
            if (hits == 2 && continued == false) { paused = true; }
            if (hits == 10 && continued == true) { paused = true; }
        }
        while (paused) //If the player gets 2 or 10 hits, they will be shown their score and be allowed to input keys to choose what happens next
        {
            if (continued == false) // If they have not already continued after being shown this screen, show them this screen
            {
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNicely done! You got " << hits << " hits, and your score is " << score << "." << endl;
                cout << "To play to 10 hits, press SPACE.   To quit the game, press ESC.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
                while (key != 32 && key != 27) // If the player presses ESC, the game will end. If they press SPACE, the game will continue.
                {
                    key = _getch();
                }
                if (key == 32) { paused = false; continued = true; }
                if (key == 27) { paused = false; end = true; }
            }
            else // If they have previously continued, and gotten 10 hits, show them this screen
            {
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNicely done! You got " << hits << " hits, and your score is " << score << "." << endl;
                cout << "You are a very talented and dedicated player! Congratulations on your victory! \nTo quit the game, press ESC.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
                while (key != 27) // If the player presses ESC, the game will end.
                {
                    key = _getch();
                }
                if (key == 27) { paused = false; end = true; }
            }
        }
    }
    cout << "Game ended.\nThank you for playing Gravity Snake!" << endl;
}
