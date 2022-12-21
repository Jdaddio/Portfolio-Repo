// Joshua D'Addio
// HW 3 - Graphical Snake

#define SFML_STATIC
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

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

double targetCount;

b2Vec2* targetLocations; // Dynamic array of b2Vec2 to store the positions of all the targets
b2Vec2 currentLocation; // Position of the current target to seek

int main()
{
    srand(time(0)); // Uses the current time to create a seed for rand
    bool end = false; // If the game has ended, true
    bool paused = false; // If the game is paused, true
    bool continued = false; // If the game has been paused and then continued, true
    hits = 0;

    b2Vec2 gravity(0.0f, 98000.0f); // Vector to represent the constant gravity force
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

    snake->CreateFixture(&fixtureDef); // Fixes the fixture to the snake to give it physics 

    cout << "Welcome to gravity snake!\nUse WASD or the arrow keys to apply forces and move the snake. Try to hit two targets!\nPress ESC to end the game at any time.\n\nPlease enter the number of targets in the game." << endl;
    cin >> targetCount;
    while (targetCount < 1) // Error checks the user's input for number of targets in the game
    {
        cout << targetCount << " is an invalid input! Please enter a number greater than 0." << endl;
        cin.clear(); // Clears the last cin
        cin.ignore(); // Ignores the last cin
        cin >> targetCount;
    }
    setupTargets(targetCount); // Function to create the targets based on user input
    points = 1000; // The possible points start at 1000, and decrease when buttons are pressed

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    while (window.isOpen()) // While the window has not been closed
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); break; } // If ESC is pressed, the game will end
        processInput(*snake); // Function to process the player's input and move the snake
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { ReverseGravity(world); } // If space is pressed, gravity will be reversed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) { StopMoving(*snake); } // If F is pressed, player movement will halt instantaneously

        update(*worldRef); // Updates the physics world by 1 step

        // If the snake position gets close enough to the target,
        if (snake->GetPosition().x <= (currentLocation.x + 30) && snake->GetPosition().x >= (currentLocation.x - 30) && snake->GetPosition().y <= (currentLocation.y + 30) && snake->GetPosition().y >= (currentLocation.y - 30))
        {
            hits++; // Add to the player's hits
            score += points; // Add the remaining points to the player's score
            points = 1000; // Reset points for the next hit
            if (selectNextTarget() == false) // The target is moved, and if the last target is reached,
            {
                window.close(); // The game ends.
            }
        }

        window.clear(sf::Color::Black);

        // Circle shape to represent the snake.
        sf::CircleShape circle(25.0f);
        circle.setFillColor(sf::Color(100, 250, 50));
        circle.setPosition(snake->GetPosition().x + (400 - (8.0f)), snake->GetPosition().y + (300 + (-9.0f)));
        //circle.setPosition(0, 0);
        window.draw(circle);

        // Square shape to represent the target. 
        sf::CircleShape square(20.f, 4);
        square.setFillColor(sf::Color(200, 100, 70));
        square.setPosition(currentLocation.x + (400 + (14.0f)), currentLocation.y + (300 - (14.0f)));
        //square.setPosition(currentLocation.x + (400), currentLocation.y + (300));
        //square.setPosition(14, -14);
        square.setRotation(45.f);
        window.draw(square);

        window.display();
    }
    cout << "Game ended.\nYour final score was " << score << ". \nThank you for playing Gravity Snake!" << endl;
    delete[] targetLocations;
    return 0;
}

