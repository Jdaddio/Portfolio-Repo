#include "Player.h"
#include <cstring>
#include <iostream>
using namespace std;

Player::Player()
{
	name = "Unknown";
	dex = 10;
	str = 10;
	health = 10;
}
Player::Player(const char* name, int dex, int str, int health)
{
	this->name = name;
	this->dex = dex;
	this->str = str;
	this->health = health;
}
Player::~Player()
{
	cout << "Destroying player object" << endl;
}
void Player::printPlayer()
{
	cout << "Name: " << name << endl;
	cout << "Dexterity: " << dex << endl;
	cout << "Strength: " << str << endl;
	cout << "Health: " << health << "\n" << endl;
}
const char* Player::getName()
{
	return name;
}
void Player::attack(Player* target)
{
	cout << name << " attacks " << target->getName() << "!" << endl;
}