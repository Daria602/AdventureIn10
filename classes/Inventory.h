#pragma once
#include "Player.h"
class Inventory
{
private:
	std::vector<Edible> backpack;

public:
	Inventory() { this->backpack = {}; }
	virtual ~Inventory(){}

	std::vector<Edible> const getInventory() { return this->backpack; }
	void addToInventory(Edible something);
	void eraseFromInventory(int index);
	void inInventory(Player &player);
};

