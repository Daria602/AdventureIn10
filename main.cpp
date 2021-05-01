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




bool inRoom = true;
int main()
{
	srand(time(NULL));

	Game game;
	Room rooms;
	Inventory inventory;
	Pet pet("Barsik", 5, 5, 1, 4);

	std::cout << "Welcome to the ADVENTURE IN 10!" << std::endl;
	std::cout << "What is your name?" << std::endl;
	std::string name;
	std::cin >> name;
	Player player(name, 10, 10, 1, 2, 10, 10);
	
	std::cout << "Hello, " << player.getName() << "!" << std::endl;
	std::cout << "The goal is to get to the treasure room in 10 days. \nEvery action you take will drain your stamina. \nAfter you rest, your stamina will be back to max, but the day count will increase.\n";

	int ri = 0;

	while (game.getRunning() && game.getDayCount()!=11 && ri != 10 && player.getHP() > 0)
	{
		
		ri = rooms.chooseRoom();
		std::cout << "You enter the room number " << ri << "." << std::endl;

		if (ri == 3)
		{
			std::cout << "You see a cat. It seems to like you. You pet him and it decides to stick around." << std::endl;
			pet.setIsPresent(true);
		}

		
		
		Character boss = rooms.chooseMonster();
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
					if (ri > 3)
					{
						pet.setIsPresent(true);
					}
					int answer2;
					inBossFight(boss, player, inventory,pet);
					if (boss.getHP() > 0)
					{
						return 0;
					}
					
					std::cout << "Press 1 to continue to the next room.\nPress 2 to scope the room." << std::endl;
					std::cin >> answer2;
					if (answer2 == 1)
					{
						inRoom = false;
					}
					else
					{
						Edible eat = rooms.chooseEdible();

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
						Character* c;
						std::cout << "The " << boss.getName() << " is approaching." << std::endl;
						inBossFight(boss, player, inventory,pet);
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
		
		
	}

	if (ri == 10)
	{
		std::cout << "IT'S A TREASURE ROOM!\nCongratulations!!! You won!" << std::endl;
		return 0;
	}

	

}