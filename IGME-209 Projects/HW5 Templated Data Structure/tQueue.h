// Joshua D'Addio
// HW 5 - Templated Data Structure
#pragma once
#include <iostream>

using namespace std;

template <class T>
class tQueue
{
public:
	// VARIABLES
	T* data; // Array of T values that will store the queue data
	int qSize; // Size of the queue itself
	int numData; // Amount of data values stored in the queue

	// CONSTRUCTORS
	tQueue() // Sets the values of the tQueue variables
	{
		//cout << "Created new queue" << endl;
		qSize = 1; // tQueues start with a size of 1
		numData = 0; // 0 stored values
		data = new T[qSize]; // Creates a new T array with a size of 1 and 0 stored values
		for (int i = 0; i < qSize; i++)
		{
			data[i] = NULL;
		}
	}
	tQueue(const tQueue<T> & tQ) // Copies the values of an existing tQueue object to a new tQueue object
	{
		qSize = tQ.qSize;
		numData = tQ.numData;
		data = new T[qSize];
		for (int i = 0; i < qSize; i++)
		{
			data[i] = tQ.data[i];
		}
	}
	~tQueue() // The destructor deletes the data array
	{
		delete[] data;
	}

	// METHODS
	void Push(T newdata) // Pushes a new value to the back of the queue
	{
		numData += 1; // Add 1 to numData to compare with qSize
		if (numData > qSize) // If numData is larger than qSize,
		{
			qSize = qSize * 2; // double qSize
			T* tempData = new T[numData - 1]; // Create a temporary array of T values the size of the data array,
			for (int i = 0; i < numData - 1; i++)
			{
				tempData[i] = NULL;
				tempData[i] = data[i]; // and set all of its values to the values of the data array
			}
			delete[] data; // Delete and recreate the data array with the newly doubled qSize int as its length 
			data = new T[qSize];
			for (int i = 0; i < qSize; i++)
			{
				data[i] = NULL;
			}
			for (int i = 0; i < numData - 1; i++) // Copy all of the values back from tempData to the data array,
			{
				data[i] = tempData[i];
			}
			delete[] tempData; // then delete tempData
		}
		data[numData - 1] = newdata; // Add the new data value to the end of the array
		//cout << "pushed " << newdata << endl; // and print to console to confirm
	}
	void Pop() // Pops the first value stored in the queue off the front
	{
		if (data[0] != NULL) // If the first value is not already NULL,
		{
			//cout << "POP " << data[0] << endl; // print out the value that will be removed, set it to NULL and decrease the int numData by 1
			data[0] = NULL;
			numData -= 1;
			for (int i = 1; i < qSize; i++) // For all of the stored values in the array, 
			{
				data[i - 1] = data[i]; // set the data one index lower to the value of the current index
				data[i] = NULL; // and set the current value to NULL.
			}
		}
	}
	void PopBack() // Pops the last value stored in the queue off the back
	{
		if (data[numData - 1] != NULL) // If the last value is not already NULL,
		{
			//cout << "POPBACK " << data[numData - 1] << endl; // print out the value that will be removed, set it to NULL and decrease the int numData by 1
			data[numData - 1] = NULL;
			numData -= 1;
		}
	}
	void Print() // Print prints out the values stored in the queue on one line
	{
		cout << "Queue contents: ";
		for (int i = 0; i < numData; i++) // For all of the stored values in the queue, print the value to the console
		{
			if (data[i] != NULL)
			{
				cout << data[i] << " ";
			}
		}
		cout << endl;
	}
	int GetSize() // GetSize returns numData, the number of stored data values
	{
		return numData;
	}
	bool IsEmpty() // IsEmpty checks the queue to see if it has any stored data
	{
		if (data[0] == NULL) // If the first index in the queue is NULL, the queue is empty and the function returns true.
		{
			return true;
		}
		else // Otherwise, return false.
		{
			return false;
		}
	}
};

