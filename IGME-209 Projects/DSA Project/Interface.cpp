//Braden Flanders, Noah Flanders, & Josh D'Addio

#include "pch.h" 
#include <utility>
#include <limits.h>
#include "Interface.h"
#include <stdlib.h>
#include "Graph.h"

//Variables 
const int** Data;
int Width, Height, startx, starty, endx, endy, xarray[20], yarray[20]; 
const char* teamNames = "Braden Flanders, Noah Flanders, and Joshua D'Addio";
Graph* mazeGraph;

char* GetTeam() // Returns a char with the team names to be printed out by the program
{
	return (char*)teamNames;
}
bool SetMaze(const int** data, int width, int height) // Saves the values for the maze data from parameters to local variables, and creates a mazeGraph object
{
	if (width > 0 && height > 0)
	{
		Data = data;
		Width = width;
		Height = height;
		mazeGraph = new Graph(data, width, height);
		return true;
	}
	return false;
}
int** GetMaze(int& width, int& height) // returns the saved values for width, height & data to be used by the program
{
	width = Width;
	height = Height;
	if (Data != NULL)
	{
		return (int**)Data;
	}
	else
	{
		return nullptr;
	}
}
bool GetNextPosition(int& xpos, int& ypos) // Calls the AStarSearch() method, which returns the X and Y positions for the pathfinder to travel one step each call
{
	mazeGraph->AStarSearch();
	xpos = mazeGraph->xStep;
	ypos = mazeGraph->yStep;
	return true;
}
bool SetStart(int xpos, int ypos) // Saves the values of x start position and y start position from parameters to local variables, then calls SetStart on the maze graph
{
	if (xpos >= 0 && ypos >= 0) {
		startx = xpos;
		starty = ypos;
		mazeGraph->SetStart(xpos, ypos);
		return true;
	}
	return false;
}
bool GetStart(int& xpos, int& ypos) // Returns the local values of x and y start position to the program for use
{
	if (startx && starty)
	{
		xpos = startx;
		ypos = starty;
		return true;
	}
	else
	{ return false; }
}

bool SetEnd(int xpos, int ypos) // Saves the values of x end position and y end position from parameters to local variables, then calls SetEnd on the maze graph
{
	if (xpos >= 0 && ypos >= 0) {
		endx = xpos;
		endy = ypos;
		mazeGraph->SetEnd(xpos, ypos);
		return true;
	}
	return false;
}
bool GetEnd(int& xpos, int& ypos)  // Returns the local values of x and y start position to the program for use
{
	if (endx && endy)
	{
		xpos = endx;
		ypos = endy;
		return true;
	}
	else
	{ return false; }
}
bool Restart() // Calls Reset() on the maze graph
{
	mazeGraph->Reset();
	return true;
}