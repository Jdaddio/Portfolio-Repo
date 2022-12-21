// Joshua D'Addio
// Igme209-03
// Final Exam

// DSACoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include "Coin.h"
#include "Wallet.h"
using namespace std;

/// <summary>
/// global variables
/// </summary>
std::chrono::high_resolution_clock clockTimer; 
std::chrono::high_resolution_clock::time_point start_time;
ifstream cryptoFile("cryptoFile.txt");;
ofstream walletFile("walletFile.txt");;


/// <summary>
/// Generates an 80 charater long string with random numbers in each such as
/// "01234567890123456789012345678901234567890123456789012345678901234567890123456789"
/// but with random numbers for each one
/// </summary>
/// <returns></returns>
string mineKey()
{
	string key;

	// TODO DSA1
	key = "";
	for (int i = 0; i < 80; i++) // For 80 characters, generates a random int to add to the key which is then returned
	{
		key = key + std::to_string(rand() % 10);
	}

	return key;
}

/// <summary>
/// reads the next crypto key from the keybank file
/// </summary>
/// <returns>returns new crypto to use or "" if the file was completely read</returns>
string readNextCrypto()
{
	string crypto = "";

	// TODO DSA1
	if (!cryptoFile.eof()) // If the end of the file has not been reached,
	{
		cryptoFile >> crypto; // Save the line as "crypto" and return it
	}

	return crypto;
}

/// <summary>
/// Generate the value of the coin mined (random)
/// </summary>
/// <returns>return a dollar amount to return for the coin</returns>
double calculateValue()
{
	double coinValue = 0.0;
	
	// TODO DSA1
	std::chrono::duration<double> elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(clockTimer.now() - start_time); // Tracks the elapsed time for calculation
	coinValue = (3.0 - elapsedTime.count()) * 100;
	if (coinValue < 0.0) // If the value is less than zero, set it to zero
	{
		coinValue = 0.0;
	}

	return coinValue;
}

void checkKeys(string &crypto, int& cnt, Wallet& myWallet, double& value) // Method to check the keys when run in a thread, accepts the addresses of cnt, myWallet and value
{
	srand(time(0));
	bool found = false;
	string key;
	while (!found && (value > 0.0)) // While value is greater than 0 and the key has not been found,
	{
		cnt++; // increase cnt for each loop
		key = mineKey(); // generate a new key to check

		if (key.find(crypto) != std::string::npos) // If the key contains the crypto code,
		{
			found = true;
			value = calculateValue(); // calculate the value of the key
			if (value > 0.0) // If the key's value is above 0,
			{
				Coin* newCoin = new Coin(key, value); // create a new coin and add it to the myWallet object and the wallet File
				myWallet.AddCoin(newCoin);
				walletFile << key << "\n";
			}
		}
	}
}

int main()
{
	start_time = clockTimer.now();
	srand(time(0));
	Wallet myWallet;
	int cnt = 0;

	// TODO DSA1
	// write the main loop
	//   read the crypto data (a line) from the file
	//   mine keys until you find a "good one"
	//     "good one" contains the crypto data from the file
	//   create a coin for the good keys and add it to your wallet

	/*thread thread1(mineKey);
	thread thread2(mineKey);
	thread1.join();
	thread2.join();*/

	string* crypto = new string[100]; // Create an array of strings to store the crypto values
	int counter = 0; // Int to track which crypto code we are on
	//string key;
	double value = calculateValue();
	//bool found;
	vector<thread*> threads; // Vector of threads, can be added to dynamically as the program runs
	while ((!cryptoFile.eof()) /*&& (value > 0.0)*/)
	{
		crypto[counter] = readNextCrypto(); // Save the crypto codes to indices in the crypto array
		//cout << crypto << endl;
		thread *t = new thread(checkKeys, ref(crypto[counter]), ref(cnt), ref(myWallet), ref(value)); // Dynamically create a new thread and push to the vector of threads
		threads.push_back(t);
		counter += 1;
		//found = false;

		//while (!found)
		//{
		//	cnt++;
		//	key = mineKey();

		//	if (key.find(crypto) != std::string::npos)
		//	{
		//		//cout << "FOUND" << endl;
		//		found = true;
		//		value = calculateValue();
		//		if (value > 0.0)
		//		{
		//			Coin *newCoin = new Coin(key, value);
		//			myWallet.AddCoin(newCoin);
		//			walletFile << key << "\n";
		//		}
		//	}
		//}
		//if (found) break;
	}
	for (int i = 0; i < threads.size(); i++)
	{
		threads[i]->join(); // Join all of the threads to synchronize them
	}
	for (int i = 0; i < threads.size(); i++)
	{
		delete threads[i]; // Delete the threads once they have all been run
	}
	delete[] crypto; // Delete the string array of crypto codes & close the file reader & writer
	cryptoFile.close();
	walletFile.close();

	cout << "keys searched: " << cnt << endl;
	cout << "Wallet value: " << myWallet.GetValue() << endl;
}