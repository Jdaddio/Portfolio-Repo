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