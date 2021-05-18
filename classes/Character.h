#pragma once
#include "Edible.h"
class Character
{
protected:
	std::string name;
	int hp, maxHp;
	int damage, maxDamage;
	friend std::ostream& operator<<(std::ostream& os, const Character& go_);
public:
	Character();
	Character(std::string name, int hp, int maxHp, int damage, int maxDamage);
	virtual ~Character();
	
	std::string getName() { return this->name; }
	int getHP() { return this->hp; }

	virtual int attack();
	virtual void wasAttacked(int atck);
};

