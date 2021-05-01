#include "Player.h"

Player::Player(std::string name, int hp, int maxHp, int damage, int maxDamage, int stamina, int maxStamina) : Character(name, hp, maxHp, damage, maxDamage)
{
	this->stamina = stamina;
	this->maxStamina = maxStamina;
}
Player::~Player()
{

}

void Player::increaseStamina(int number)
{
	if (this->stamina + number > this->maxStamina)
	{
		number = this->maxStamina - this->stamina;
	}

	this->stamina += number;
}
void Player::increaseHealth(int number)
{
	if (this->hp + number > this->maxHp)
	{
		number = this->maxHp - this->hp;
	}

	this->hp += number;
}

void Player::rest()
{
	this->stamina = this->maxStamina;
	this->hp = this->maxHp;
}

int Player::attack()
{
	if (this->stamina < 2)
	{
		std::cout << "You are too tired to attack. Stamina  " << this->stamina
			<< "/" << this->maxStamina << std::endl;
		return 0;
	}
	else
	{
		this->stamina -= 2;
		
	}
	return rand() % this->maxDamage + this->damage;
}

int Player::run()
{
	int chance;
	chance = rand() % 2 + 1;
	if (this->stamina > 0)
	{
		std::cout << "You tried to run and ";
		switch (chance)
		{
		case 1:
		{
			std::cout << "failed. :(((( " << std::endl;
		}break;
		case 2:
		{
			std::cout << "succeded! Hooraaaaay!!!" << std::endl;
		}break;
		}
		this->stamina -= 2;
	}
	else
	{
		std::cout << "You are too tired to run. Stamina  " << this->stamina
			<< "/" << this->maxStamina << std::endl;
	}
	return chance;
}

void Player::wasAttacked(int atck)
{
	if (atck > this->hp)
	{
		atck = this->hp;
	}

	this->hp -= atck;
}
void Player::seeStats()
{
	std::cout << "Your Health: " << this->hp << "/" << this->maxHp << "          " << "Stamina: " << this->stamina << "/" << this->maxStamina << std::endl;
}