#pragma once
#include "Vertex.h"
#include <iostream>
#include <vector>
#include <stack>
#include <list>
class Graph
{
public:
	Graph();
	Graph(const int** data, int width, int height);
	~Graph();

	void PrintMatrix();

	void Reset();
	void SetStart(int x, int y);
	void SetEnd(int x, int y);
	void AStarSearch();
	int xStep;
	int yStep;

	bool foundEnd;

private:
	std::vector<Vertex> vertices;
	
	std::vector<Vertex*> openList;
	std::vector<Vertex> closedList;
	std::vector<Vertex*> adjacentVerts;

	int** adjMatrix;

	Vertex* start;
	Vertex* end;
	Vertex* currentVert;

	std::stack<int> allX;
	std::stack<int> allY;
	
};

