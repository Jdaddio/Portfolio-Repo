#pragma once

//#define DllExport __declspec(dllexport)
#define DllExport extern "C" __declspec(dllexport)

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

//Exports all of the methods so that they can be used by the program
DllExport char* GetTeam();
DllExport bool SetMaze(const int** data, int width, int height);
DllExport int** GetMaze(int& width, int& height);
DllExport bool GetNextPosition(int& xpos, int& ypos);
DllExport bool SetStart(int xpos, int ypos);
DllExport bool GetStart(int& xpos, int& ypos);
DllExport bool SetEnd(int xpos, int ypos);
DllExport bool GetEnd(int& xpos, int& ypos);
DllExport bool Restart();

