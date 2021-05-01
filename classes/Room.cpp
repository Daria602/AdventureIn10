#include "Room.h"

Room::Room()
{
	Character mutant("Mutant", 3, 3, 0, 2), goblin("Goblin", 4, 4, 0, 2),
		businessman("Businessman", 5, 5, 0, 1), evilMagician("Evil Magician", 6, 6, 0, 3);
	this->monsters.push_back(mutant);
	this->monsters.push_back(goblin);
	this->monsters.push_back(businessman);
	this->monsters.push_back(evilMagician);

	this->unusedRooms = { 1,2,3,4,5,6,7,8,9,10 };

	Edible apple("Apple", 3,3), caveCarrot("Cave carrot", 2,2), pizza("Pizza", 4,4);
	this->findInRoom.push_back(apple);
	this->findInRoom.push_back(caveCarrot);
	this->findInRoom.push_back(pizza);
	
}
Character Room::chooseMonster()
{
	unsigned int index;
	index = rand() % (this->monsters.size() - 1);
	return this->monsters[index];
}
Edible Room::chooseEdible()
{
	unsigned int index;
	index = rand() % (this->findInRoom.size() - 1);
	return this->findInRoom[index];
}
int Room::chooseRoom()
{
	unsigned int roomNumber;
	roomNumber = this->unusedRooms[0];
	this->unusedRooms.erase(this->unusedRooms.begin() + 0);
	return roomNumber;
}