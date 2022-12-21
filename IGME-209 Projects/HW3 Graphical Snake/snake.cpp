#define SFML_STATIC
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include <iostream>
#include <iomanip>
#include <conio.h>;
#include <stdlib.h>
#include "Box2D\Box2D.h";
#include "snake.h";

using namespace std;

float timeStep = 1.0f / 10000.0f; // Time for the simulation- needs to be VERY small
int32 velocityIterations = 6;
int32 positionIterations = 2;

int currentTarget = 0;

extern b2Vec2* targetLocations; // Dynamic array of b2Vec2 to store the positions of all the targets
extern b2Vec2 currentLocation; // Position of the current target to seek
extern int points;
float gravityForce = (98000.0f);

typedef void (*myFunc)(b2Body&); // Typedef to point to the movement functions

void update(b2World& world) // Method to update the physics world
{
	world.Step(timeStep, velocityIterations, positionIterations); // Updates the physics world by 1 step
}


void display(b2Body* snake, float targetX, float targetY) // Method to display the X and Y positions of the Target and the Snake
{
	std::cout << std::fixed << std::setprecision(1); // Sets cout to only display floats to the second decimal position
	b2Vec2 snakePos = snake->GetPosition();
	cout << "Target " << targetX << ", " << targetY << " --> ";
	cout << "snake " << snakePos.x << ", " << snakePos.y << endl;
}


void applyForces(b2Body* snake, int key) // Method to apply forces to move the snake
{
	if (key == 119 || key == 72) // W key and up arrow key
	{
		snake->ApplyForce(b2Vec2(0, 10000), snake->GetWorldCenter(), true); //cout << "w" << endl; // Applies an upward force greater than gravity
	}
	if (key == 97 || key == 75) // A key and left arrow key
	{
		snake->ApplyForce(b2Vec2(-5000, 0), snake->GetWorldCenter(), true); //cout << "a" << endl; // Applies a constant force to the left
	}
	if (key == 115 || key == 80) // S key and down arrow key
	{
		snake->ApplyForce(b2Vec2(0, -5000), snake->GetWorldCenter(), true); //cout << "s" << endl; // Applies a downward force to accelerate faster
	}
	if (key == 100 || key == 77) // D key and right arrow key
	{
		snake->ApplyForce(b2Vec2(5000, 0), snake->GetWorldCenter(), true); //cout << "d" << endl; // Applies a constant force to the right
	}
}


void moveTarget(float& xPos, float& yPos) // Method to move the target to a random position
{
	float newX = (float)(((rand() % 1001) - 500.0f) / 100.0f);
	float newY = (float)(((rand() % 1001) - 500.0f) / 100.0f);
	xPos = newX;
	yPos = newY;
}

void processInput(b2Body& player)
{
	myFunc move; // Pointer to point to a movement function
	// Depending on the user's input, the pointer will point at a different function to move the player in different ways.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move = &ApplyForceUp;
		if (points > 0) { points--; }
		move(player);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move = &ApplyForceLeft;
		if (points > 0) { points--; }
		move(player);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move = &ApplyForceDown;
		if (points > 0) { points--; }
		move(player);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move = &ApplyForceRight;
		if (points > 0) { points--; }
		move(player);
	}
}
// Functions to apply forces to the player object, which are referenced with the typedef pointer
void ApplyForceUp(b2Body& player)
{
	player.ApplyForceToCenter(b2Vec2(0, -1000000), true);
}
void ApplyForceLeft(b2Body& player)
{
	player.ApplyForceToCenter(b2Vec2(-500000, 0), true);
}
void ApplyForceDown(b2Body& player)
{
	player.ApplyForceToCenter(b2Vec2(0, 500000), true);
}
void ApplyForceRight(b2Body& player)
{
	player.ApplyForceToCenter(b2Vec2(500000, 0), true);
}

void StopMoving(b2Body& player) // Function to stop the player's movement
{
	const b2Vec2 zeroVel = b2Vec2(0, 0); // A zero vector is created and the player's movement is instantaneously frozen.
	player.SetLinearVelocity(zeroVel);
}

void ReverseGravity(b2World& world) // Function to reverse gravity
{
	gravityForce = -(gravityForce); // Whenever the function is called, the gravitational force is set to the negative of itself
	world.SetGravity(b2Vec2(0, -gravityForce));
}

void setupTargets(int cnt) // Function to create the targets based on user input
{
	targetLocations = new b2Vec2[cnt + 1]; // Creates an array with a size one larger than the user specifies
	for (int i = 0; i < cnt; i++)
	{
		targetLocations[i] = b2Vec2(((float)((rand() % 781) - 390.0f)), ((float)((rand() % 581) - 290.0f))); // Random b2Vec2s are created to store position values
	}
	targetLocations[cnt] = b2Vec2(-1000, -1000); // At the end of the array, a target is created that will end the game when reached

	currentLocation = targetLocations[currentTarget]; // Sets the current target to the first target in the array
}

bool selectNextTarget()
{
	if (!(targetLocations[currentTarget + 1].x == -1000 && targetLocations[currentTarget + 1].y == -1000)) // If the final target has not been reached,
	{
		currentTarget++; // Each time this function is called, the next target will be loaded
		currentLocation = targetLocations[currentTarget];
		return true; // and True is returned
	}
	else // If the final target has been reached,
	{
		return false; // False will be returned, ending the game
	}
}