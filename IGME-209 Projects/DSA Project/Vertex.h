#pragma once
class Vertex
{
public:
	Vertex();
	Vertex(int x, int y);
	int getX();
	int getY();

	Vertex* parentNode;

	int heuristic;
	int lowestCost;
	int weight;
	bool visited;

private:
	int x;
	int y;

};