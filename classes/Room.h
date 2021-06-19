#pragma once

#include "Inventory.h"

class Room
{
	Character monster;
	Edible edible;
	int roomIndex;
	friend class RoomBuilder;
public:
	Room() = default;
	virtual ~Room() {}

	int getRoomIndex() { return this->roomIndex; }
	Character getMonster() { return this->monster; }
	Edible getEdible() { return this->edible; }
};

class RoomBuilder
{
	Room r;

public:
	RoomBuilder() = default;
	RoomBuilder& monsterInRoom(Character c)
	{
		r.monster = c;
		return *this;
	}
	RoomBuilder& edibleInRoom(Edible e)
	{
		r.edible = e;
		return *this;
	}
	RoomBuilder& indexRoom(int index)
	{
		r.roomIndex = index;
		return *this;
	}
	Room build()
	{
		return this->r;
	}

};
