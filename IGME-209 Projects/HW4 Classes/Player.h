#pragma once
class Player
{
public:
	Player();
	Player(const char* name, int dex, int str, int health);
	~Player();

	void printPlayer();
	const char* getName();
	virtual void attack(Player* target);
private:
	const char* name;
	int dex;
	int str;
	int health;
};

