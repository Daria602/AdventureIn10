#include "Character.h"
std::ostream& operator<<(std::ostream& os, const Character& go_)
{
	os << go_.name << ". HP " << go_.hp << "/" << go_.maxHp;
	return os;
}
Character::Character()
{
	this->name = "NONE";
	this->hp = 0;
	this->maxHp = 0;
	this->damage = 0;
	this->maxDamage = 0;
}
Character::Character(std::string name,int hp, int maxHp, int damage, int maxDamage)
{
	this->name = name;
	this->hp = hp;
	this->maxHp = maxHp;
	this->damage = damage;
	this->maxDamage = maxDamage;
}
Character::~Character()
{

}

int Character::attack()
{
	int hurt;
	hurt = rand() % this->maxDamage + this->damage;
	if (this->name == "Mutant")
	{
		std::cout << "Mutant spits acid. You recieve " << hurt << " damage." << std::endl;
	}
	else if (this->name == "Goblin")
	{
		std::cout << "Goblin goes for a cringe joke. You recieve " << hurt << " damage." << std::endl;
	}
	else if (this->name == "Businessman")
	{
		std::cout << "Businessman tell you about stocks...boring. You recieve " << hurt << " damage." << std::endl;
	}
	else
	{
		std::cout << "Evil Magician puts a curse on you. You recieve " << hurt << " damage." << std::endl;
	}
	return hurt;
	
}

void Character::wasAttacked(int atck)
{
	if (atck > this->hp)
	{
		atck = hp;
	}
	this->hp -= atck;
	std::cout << this->name << " was attacked. " << this->name << "'s hp: " << this->hp << "/" << this->maxHp << std::endl;
	
	if (this->hp == 0)
	{
		std::cout << "The " << this->name << " was defeated." << std::endl;
	}
	
}