#include "Fighter.h"
#include <iostream>
using namespace std;

Fighter::Fighter()
{
	weaponSkill = "fists";
}
Fighter::Fighter(const char* name, const char* weaponSkill, int dex, int str, int health):Player(name, dex, str, health)
{
	this->weaponSkill = weaponSkill;
}
Fighter::~Fighter()
{
	cout << "Destroying fighter object" << endl;
}
void Fighter::printFighter()
{	
	cout << "Weapon skill: " << weaponSkill << endl;
	printPlayer();
}
void Fighter::attack(Player* target)
{
	cout << Player::getName() << " attacks " << target->getName() << " using " << weaponSkill << "!" << endl;
}
