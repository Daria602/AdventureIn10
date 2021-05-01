#pragma once

#include "Inventory.h"

class Room
{
	std::vector<Character> monsters;
	std::vector<Edible> findInRoom;
	std::vector<int> unusedRooms;
public:
	Room();
	virtual ~Room() {}

	
	Character chooseMonster();
	Edible chooseEdible();

	int chooseRoom();
};

