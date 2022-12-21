//Braden Flanders, Noah Flanders, & Josh D'Addio

#include "pch.h"
#include "Graph.h"

using namespace std;
using std::vector;

Graph::Graph() // Default graph constructor
{
	foundEnd = false; // Set foundEnd to false
}
Graph::Graph(const int** data, int width, int height) // Graph constructor that creates the adjacency matrix to be used by the A* pathfinding algorithm
{
	foundEnd = false; // Set foundEnd to false

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (data[i][j] > 0) // If the piece of data is greater than 0, it is a vertex
			{
				Vertex vert = Vertex(i, j); // Create a new vertex object with the given x(i) and j(y) values
				vert.weight = data[i][j]; // Set the vert's weight to the value of the data at this position
				vertices.push_back(vert); // Push the vert to vertices
			}
		}
	}
	
	int cnt = vertices.size();
	adjMatrix = new int* [cnt]; // Create the adjacency matrix based on the size of the vertex list
	for (int i = 0; i < cnt; i++)
	{
		adjMatrix[i] = new int[cnt]; // Add a 2nd dimension to the matrix
		for (int j = 0; j < cnt; j++)
		{
			adjMatrix[i][j] = 0; // Set all of the values in the adjMatrix to 0 by default
		}
	}
	// Compares all of the vertices against the other vertices in the list, checks to see if they are adjacent and if they are, sets the respective ints to 1 in adjMatrix
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (data[i][j] > 0)
			{
				for (int k = 0; k < cnt; k++)
				{
					if (vertices[k].getX() == i && vertices[k].getY() == j)
					{
						if (i < width - 1 && data[i + 1][j] > 0) // 1 to the right
						{
							for (int l = 0; l < cnt; l++)
							{
								if (vertices[l].getX() == i + 1 && vertices[l].getY() == j)
								{
									adjMatrix[k][l] = 1;
									adjMatrix[l][k] = 1;
								}
							}
						}
						if (i > 0 && data[i - 1][j] > 0) // 1 to the left
						{
							for (int l = 0; l < cnt; l++)
							{
								if (vertices[l].getX() == i - 1 && vertices[l].getY() == j)
								{
									adjMatrix[k][l] = 1;
									adjMatrix[l][k] = 1;
								}
							}
						}
						if (j < height - 1 && data[i][j + 1] > 0) // 1 below
						{
							for (int l = 0; l < cnt; l++)
							{
								if (vertices[l].getX() == i && vertices[l].getY() == j + 1)
								{
									adjMatrix[k][l] = 1;
									adjMatrix[l][k] = 1;
								}
							}
						}
						if (j > 0 && data[i][j - 1] > 0) // 1 above
						{
							for (int l = 0; l < cnt; l++)
							{
								if (vertices[l].getX() == i && vertices[l].getY() == j - 1)
								{
									adjMatrix[k][l] = 1;
									adjMatrix[l][k] = 1;
								}
							}
						}
					}
				}
			}
		}
	}
}	
Graph::~Graph() // Destructor which is called at the end of the program
{
	int cnt = vertices.size();
	for (int i = 0; i < cnt; i++) // Delete all of the values stored in adjMatrix
	{
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
}

void Graph::PrintMatrix() // Prints the matrix to the console to be read
{
	if (vertices.size() > 0) // If there are stored vertices, print all of the values in the matrix to the console
	{
		cout << "Matrix:" << endl;
		int cnt = vertices.size();
		for (size_t i = 0; i < cnt; i++)
		{
			for (size_t j = 0; j < cnt; j++)
			{
				cout << adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else // If there are no stored vertices, print to console
	{
		cout << "No saved vertices" << endl;
	}
}

void Graph::SetStart(int x, int y) // Takes an X and a Y value to check all of the vertices and set the start to the vertex with the given x and y
{
	for (int i = 0; i < vertices.size(); i++) // Checks through all of the vertices
	{
		if (vertices[i].getX() == x && vertices[i].getY() == y) // If a vertex's X and Y values match the ones given by the function,
		{
			start = &vertices[i]; // Set start to point to that vertex
			break;
		}
	}
	start->lowestCost = 0; // Set the lowestCost of start to 0

	openList.push_back(start); // Add the start vertex to the open list

	currentVert = start; // Set currentVert to point to start

}
void Graph::SetEnd(int x, int y) // Takes an X and a Y value to check all of the vertices and set the end to the vertex with the given x and y
{
	for (int i = 0; i < vertices.size(); i++) // Checks through all of the vertices
	{
		if (vertices[i].getX() == x && vertices[i].getY() == y) // If a vertex's X and Y values match the ones given by the function,
		{
			end = &vertices[i]; // set end to point to that vertex
			break;
		}
	}
	for (int i = 0; i < vertices.size(); i++) // Runs through the list of vertices and calculates the heuristic value (rough distance from the end point)
	{
		vertices[i].heuristic = (abs(end->getX() - vertices[i].getX()) + abs(end->getY() - vertices[i].getY()));
	}
}
void Graph::AStarSearch() // Uses the A* pathfinding algorithm to find a path from the start point to the end point
{
	if (!foundEnd) // Only runs if the end has not been found
	{
		while (openList.size() > 0 && !foundEnd) // While the open list is greater than zero AND the end has not been found, run this
		{
			Vertex* tempVertex = openList[0]; // Set a temporary vertex to point to the first value in the open list
			for (int i = 0; i < openList.size(); i++) // Check the open list and point currentVert to the vert with the lowest F score (heuristic + lowestcost + weight)
			{
				if ((openList[i]->heuristic + openList[i]->lowestCost + openList[i]->weight) <= (tempVertex->heuristic + tempVertex->lowestCost + tempVertex->weight))
				{
					tempVertex = openList[i]; 
					currentVert = openList[i];
				}
			}

			closedList.push_back(*currentVert); // Add the current vertex to the closed list

			if (currentVert == end) // If the current vertex is the end of the maze,
			{
				foundEnd = true; // set foundEnd to true
				
				// Push the current node's X and Y values to lists of ints
				allX.push(currentVert->getX());
				allY.push(currentVert->getY());
				while (currentVert != start) // Then, work backwards through the path and push all of the X and Y values to the lists to be returned to the program
				{
					allX.push(currentVert->parentNode->getX());
					allY.push(currentVert->parentNode->getY());
					currentVert = currentVert->parentNode; // Set the currentVert to its own parent in order to work backwards to the start
				}
			}
			
			// If the end is found, or the open list becomes empty, break out of the loop
			if (foundEnd == true)
			{
				break;
			}
			if (openList.size() == 0)
			{
				break;
			}

			for (int i = 0; i < openList.size(); i++) // For every value in the open list
			{
				if (openList[i] == currentVert) // If a vertex equals currentVert
				{
					openList.erase(openList.begin() + i); // Erase the vertex in the open list at that index to remove the currentVert from the ol
					break;
				}
			}

			for (int i = 0; i < vertices.size(); i++) // For all of the vertices in the vertex list
			{
				for (int j = 0; j < vertices.size(); j++)
				{
					if (currentVert == &vertices[j])
					{
						if (adjMatrix[i][j] == 1) // If a vertex is adjacent to the current vertex,
						{
							adjacentVerts.push_back(&vertices[i]); // Add it to adjacentVerts
							break;
						}
					}
				}
			}

			// Bools to track whether an adjacent vert is in the open or closed list
			bool isincl = false;
			bool isinol = false;
			for (int i = 0; i < adjacentVerts.size(); i++) // For all of the adjacent vertices,
			{
				for (int j = 0; j < closedList.size(); j++) // Check through the entire closed list
				{
					if (adjacentVerts[i]->getX() == closedList[j].getX() && adjacentVerts[i]->getY() == closedList[j].getY()) // there is a match in the cl,
					{
						isincl = true; // set isincl to true and break
						break;
					}
				}
				if (!isincl) // If the vert isn't already in the closed list,
				{
					for (int k = 0; k < openList.size(); k++) // check through the entire open list
					{
						if (adjacentVerts[i]->getX() == openList[k]->getX() && adjacentVerts[i]->getY() == openList[k]->getY()) // If there is a match in the ol,
						{
							isinol = true; // Set isinol to true and break
							break;
						}
					}
				}
				if (!isincl && !isinol) // If the adjacent vertex is not already in the closed list or open list
				{
					adjacentVerts[i]->parentNode = currentVert; // Set the vert's parent to the currentvert,

					// All of the adjacent verts have a cost 1 higher than the current position plus the weight of the space
					adjacentVerts[i]->lowestCost = (adjacentVerts[i]->parentNode->lowestCost + 1 + adjacentVerts[i]->weight);
					openList.push_back(adjacentVerts[i]); // and add it to the open list
				}
				// Set isincl and isinol to false so that we can check the next adjacent vertex
				isincl = false;
				isinol = false;
			}
			adjacentVerts.clear(); // Finally, clear the adjacent Vertices as they should all now be part of the open list
		}
	}
	if (!foundEnd) // If the end has not been found by the time the while loop has exited and the open list is empty, return the start pos for every call of this function
	{
		xStep = start->getX();
		yStep = start->getY();
	}
	if (foundEnd) // If the end has been found, return the x and y positions of the next step to take every call of this function
	{
		xStep = allX.top();
		allX.pop();
		yStep = allY.top();
		allY.pop();
	}
}
void Graph::Reset() // Sets all of the values changed by the A* pathfinding back to their given defaults
{
	for (int i = 0; i < vertices.size(); i++) // For all of the vertices,
	{
		vertices[i].parentNode = NULL; // set their parent nodes to NULL
	}
	for (int i = 0; i < allX.size(); i++) // Remove all of the X and Y values in the found path
	{
		allX.pop();
		allY.pop();
	}
	// Set foundEnd to false, and clear all of the lists, then call setStart again to set the pathfinder back to the beginning
	foundEnd = false;
	openList.clear();
	closedList.clear();
	adjacentVerts.clear();
	SetStart(start->getX(), start->getY());

}