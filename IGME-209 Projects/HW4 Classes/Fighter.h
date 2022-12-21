#pragma once
#include "Player.h"
class Fighter :
    public Player
{
public:
    Fighter();
    Fighter(const char* name, const char* weaponSkill, int dex, int str, int health);
    ~Fighter();
    
    void printFighter();
    void attack(Player* target);
private:
    const char* weaponSkill;
};

