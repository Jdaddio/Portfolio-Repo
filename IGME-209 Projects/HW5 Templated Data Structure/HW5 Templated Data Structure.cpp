// Joshua D'Addio
// HW 5 - Templated Data Structure
#include <iostream>
#include "tQueue.h"

int main()
{
    cout << "Joshua D'Addio\nHW 5 - Templated Data Structure" << endl;
    cout << "\nCreate new tQueue<int> object called myqueue with the default constructor\n\nPush 10 to myqueue with Push()" << endl;
    tQueue<int> myqueue; // Create the tQueue to push values to (Constructor)                                                                               <--
    myqueue.Push(10); // Pushes data to the tQueue object myqueue (Push)                                                                                    <--
    if (myqueue.IsEmpty()) // Checks to see if myqueue is empty, it is not (IsEmpty)                                                                        <--
        cout << "myqueue is empty" << endl;
    if (!myqueue.IsEmpty())
        cout << "myqueue is NOT empty" << endl; 
    cout << "(myqueue) ";
    myqueue.Print(); // Prints out all of the values in myqueue (Print)                                                                                     <--
    cout << "\nPush 5 and 9 to myqueue" << endl;
    myqueue.Push(5);
    myqueue.Push(9);
    cout << "(myqueue) ";
    myqueue.Print();
    cout << "myqueue size: " << myqueue.GetSize() << endl; // Returns the size value of the tQueue object, which is passed into cout to print (GetSize)     <--
    cout << "\nPop the first and last values off of the queue with Pop() and PopBack()" << endl;
    myqueue.Pop();
    myqueue.PopBack(); // Pops a value off the back of the tQueue
    cout << "myqueue size: " << myqueue.GetSize() << endl;
    cout << "(myqueue) ";
    myqueue.Print();
    cout << "\nPush 7, 15 and 1 to myqueue" << endl;
    myqueue.Push(7);
    myqueue.Push(15);
    myqueue.Push(1);
    cout << "myqueue size: " << myqueue.GetSize() << endl;
    cout << "(myqueue) ";
    myqueue.Print();
    cout << "\nCopy the data from myqueue to a newly created tQueue object using the copy constructor\n" << endl;
    tQueue<int> copyqueue = myqueue; // Copied the data from myqueue to a new tQueue object (Copy Constructor)                                              <--
    cout << "(myqueue) ";
    myqueue.Print();
    cout << "(Copied Queue) ";
    copyqueue.Print();
    cout << "\nPop all of the values in myqueue to clear it, the copied queue remains the same" << endl;
    myqueue.Pop();
    myqueue.Pop();
    myqueue.Pop();
    myqueue.Pop();
    myqueue.Pop();
    cout << "(myqueue) ";
    myqueue.Print();
    cout << "(Copied Queue) ";
    copyqueue.Print();
    cout << "myqueue size: " << myqueue.GetSize() << endl;
    if (myqueue.IsEmpty())
        cout << "myqueue is empty" << endl;
    if (!myqueue.IsEmpty())
        cout << "myqueue is NOT empty" << endl;

    cout << "\nProgram ends, destructors are called" << endl;

    // The destructors should then be called automatically when the program ends (Destructor)                                                               <--
}