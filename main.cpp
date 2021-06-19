#include "Game.h"
void addSpaces()
{
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}
void mainMenu(Character& boss)
{
	std::cout << "You meet " << boss << std::endl;
	std::cout << "What will you do?" << std::endl;
	std::cout << "1 - > attack him" << std::endl;
	std::cout << "2 - > try to run away (if failed, you will have to fight)" << std::endl;
	std::cout << "3 - > open inventory" << std::endl;
}
void menuFight()
{
	std::cout << "What will you do?" << std::endl;
	std::cout << "1 - > attack him again" << std::endl;
	std::cout << "2 - > open inventory" << std::endl;
}
void eatFromInventory(Player& player, Inventory& inventory)
{
	std::cout << "What would you like to eat?\n";
	for (size_t i = 0; i < inventory.getInventory().size(); i++)
	{
		std::cout << i + 1 << " - >" << inventory.getInventory()[i];
	}
	std::cout << "0 - > go back" << std::endl;
	int index = 0;
	std::cin >> index;
	if (index == 0)
	{
		return;
	}
	
	while (index != 0 && inventory.getInventory().size() != 0)
	{
		Edible e = inventory.getInventory()[index - 1];
		player.increaseStamina(e.getReplenishStamina());
		player.increaseHealth(e.getReplenishHealth());
		inventory.eraseFromInventory(index - 1);
		std::cout << "What would you like to eat?\n";
		for (size_t i = 0; i < inventory.getInventory().size(); i++)
		{
			std::cout << i + 1 << " - >" << inventory.getInventory()[i];
		}
		std::cout << "0 - > go back" << std::endl;
		int index;
		std::cin >> index;
	}
}
void inBossFight(Character &boss, Player &player, Inventory &inventory,Pet &pet)
{
	Character* c;
	Character* p;
	p = &pet;
	c = &player;
	if (boss.getHP() > 0 && player.getStamina() < 2 && inventory.getInventory().size() == 0)
	{
		std::cout << "You are exhausted and have nothing to eat. Game over for you.";
		return;
	}
	boss.wasAttacked(c->attack());
	if (boss.getHP() > 0)
	{
		c->wasAttacked(boss.attack());
	}
	
	while (boss.getHP() > 0)
	{
		player.seeStats();
		menuFight();
		if (pet.getIsPresent() == true)
		{
			std::cout << "3 - > ask " << pet.getName() << " to attack" << std::endl;
		}
		int answer;
		std::cin >> answer;

		if (answer == 1 && player.getStamina() >= 2)
		{
			boss.wasAttacked(c->attack());
			if (boss.getHP() > 0)
			{
				c->wasAttacked(boss.attack());
			}
		}
		else if (answer == 1 && player.getStamina() < 2)
		{
			std::cout << "You are too tired to fight ";
			if (inventory.getInventory().size() == 0 && boss.getHP() > 0)
			{
				std::cout << "and you have nothing to eat... GAME OVER";
				return;
			}
			else
			{
				std::cout << ".\nDo you want to eat something?\n1 - > yes\n2 - > no" << std::endl;
				int answer1;
				std::cin >> answer1;
				if (answer1 == 1)
				{
					eatFromInventory(player, inventory);
				}
				else
				{
					if (boss.getHP() > 0)
					{
						std::cout << "GAME OVER";
						return;
					}
					
				}
				
			}
		}
		if (answer == 2)
		{
			eatFromInventory(player, inventory);
		}
		if (answer == 3)
		{
			int damage;
			damage = p->attack();
			if (damage != 0)
			{
				boss.wasAttacked(damage);
				if (boss.getHP() > 0)
				{
					c->wasAttacked(boss.attack());
				}
				
			}
			pet.setIsPresent(false);
		}
	}
}
std::vector<Character> getAllMonsters()
{
	std::vector<Character> monsters;
	Character mutant("Mutant", 3, 3, 0, 2), goblin("Goblin", 4, 4, 0, 2),
		businessman("Businessman", 5, 5, 0, 1), evilMagician("Evil Magician", 6, 6, 0, 3);
	monsters.push_back(mutant);
	monsters.push_back(goblin);
	monsters.push_back(businessman);
	monsters.push_back(evilMagician);
	return monsters;
}

std::vector<Edible> getAllEdible()
{
	std::vector<Edible> edibles;
	Edible apple("Apple", 3, 3), caveCarrot("Cave carrot", 2, 2), pizza("Pizza", 4, 4);
	edibles.push_back(apple);
	edibles.push_back(caveCarrot);
	edibles.push_back(pizza);
	return edibles;
}


bool inRoom = true;
int main()
{
	srand((unsigned int)time(NULL));

	Game game;
	std::vector<Character> all_monsters = getAllMonsters();
	std::vector<Edible> all_edible = getAllEdible();
	std::vector<Room> all_rooms;
	for (int i = 1; i <= 10; i++)
	{
		RoomBuilder rb;
		int indexMonster = rand() % (all_monsters.size() - 1);
		int indexEdible = rand() % (all_edible.size() - 2);
		Room r = rb.indexRoom(i).monsterInRoom(all_monsters[indexMonster]).edibleInRoom(all_edible[indexEdible]).build();
		all_rooms.push_back(r);
	}


	Inventory inventory;
	Pet pet("Barsik", 5, 5, 1, 4);

	std::cout << "Welcome to the ADVENTURE IN 10!" << std::endl;
	std::cout << "What is your name?" << std::endl;
	std::string name;
	std::cin >> name;
	Player player(name, 10, 10, 1, 2, 10, 10);
	
	std::cout << "Hello, " << player.getName() << "!" << std::endl;
	std::cout << "The goal is to get to the treasure room in 10 days. \nEvery action you take will drain your stamina. \nAfter you rest, your stamina will be back to max, but the day count will increase.\n";

	int i = 0;
	while (i < all_rooms.size() && game.getDayCount() <= 10 && player.getHP() > 0)
	{
		Room room = all_rooms[i];
		std::cout << "You enter the room number " << room.getRoomIndex() << "." << std::endl;
		if (i == 3)
		{
			std::cout << "You see a cat. It seems to like you. You pet him and it decides to stick around." << std::endl;
			pet.setIsPresent(true);
		}
		if (room.getRoomIndex() == 10)
		{
			std::cout << "IT'S A TREASURE ROOM!\nCongratulations!!! You won!" << std::endl;
			return 0;
		}
		Character boss = room.getMonster();
		mainMenu(boss);
		inRoom = true;
		while (inRoom == true)
		{
			int answer;
			std::cin >> answer;
			switch (answer)
			{
				case 1:
				{
					if (room.getRoomIndex() > 3)
					{
						pet.setIsPresent(true);
					}
					
					inBossFight(boss, player, inventory, pet);
					if (boss.getHP() > 0)
					{
						return 0;
					}

					int answer2;
					std::cout << "Press 1 to continue to the next room.\nPress 2 to scope the room." << std::endl;
					std::cin >> answer2;
					if (answer2 == 1)
					{
						inRoom = false;
					}
					else
					{
						Edible eat = room.getEdible();

						std::cout << "You found " << eat << "\nWould you like to add it to the inventory?\n1 - > yes\n2 - > no" << std::endl;
						std::cin >> answer2;

						if (answer2 == 1)
						{
							inventory.addToInventory(eat);
							std::cout << "The " << eat.getName() << " has been added to your inventory." << std::endl;
						}
						inRoom = false;
					}



				}break;
				case 2:
				{
					int chance;
					chance = player.run();
					if (chance == 1)
					{
						//Character* c;
						std::cout << "The " << boss.getName() << " is approaching. You raise your weapon." << std::endl;
						inBossFight(boss, player, inventory, pet);
						if (boss.getHP() > 0)
						{
							return 0;
						}
					}
					else
					{
						inRoom = false;
					}
				}break;
				case 3:
				{
					eatFromInventory(player, inventory);
					std::cout << boss.getName() << " is patiently waiting for you. But everybody has their limits..." << std::endl;
					std::cout << "What will you do?" << std::endl;
					std::cout << "1 - > attack him" << std::endl;
					std::cout << "2 - > try to run away (if failed, you will have to fight)" << std::endl;
					std::cout << "3 - > open inventory" << std::endl;
				} break;
			}
		}

		std::cout << "Would you like to rest?\n1 - > yes\n2 - > no" << std::endl;
		int answer;
		std::cin >> answer;
		if (answer == 1)
		{
			player.rest();
			game.incrementDayCount();
		}
		

		i++;
	}

}
