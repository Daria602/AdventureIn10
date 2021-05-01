#include "Pet.h"

Pet::Pet(std::string name, int hp, int maxHp, int damage, int maxDamage) : Character(name, hp, maxHp, damage, maxDamage)
{
	this->isPresent = false;
	this->willToAttack = 1;
}

int Pet::attack()
{
	int chance = rand() % 2 + 1;

	this->willToAttack = chance;

	if (this->willToAttack == 1)
	{
		std::cout << this->name << " doesn't want to attack right now." << std::endl;
		return 0;
	}
	else
	{
		int hurt;
		hurt = rand() % this->maxDamage + this->damage;
		std::cout << this->name << " attacks with all its power and makes " << hurt << " damage to the enemy" << std::endl;
		return hurt;
	}
}
