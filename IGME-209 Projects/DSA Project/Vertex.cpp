#include "pch.h"
#include "Vertex.h"

Vertex::Vertex()
{
	x = 0;
	y = 0;

	heuristic = 0; 
	lowestCost = 0; 
	visited = false;
}
Vertex::Vertex(int x, int y)
{
	this->x = x;
	this->y = y;

	heuristic = 0; 
	lowestCost = 0; 
	visited = false;
}

int Vertex::getX() { return x; }
int Vertex::getY() { return y; }