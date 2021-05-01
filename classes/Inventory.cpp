#include "Inventory.h"

void Inventory::addToInventory(Edible something)
{
	this->backpack.push_back(something);
}
void Inventory::eraseFromInventory(int index)
{
	this->backpack.erase(this->backpack.begin()+index);
}
void Inventory::inInventory(Player &player)
{
	if (this->backpack.size() == 0)
	{
		std::cout << "You inventory is empty." << std::endl;
		return;
	}
	else
	{
		std::cout << "What would you like to eat?\n";
		for (size_t i = 0; i < this->backpack.size(); i++)
		{
			std::cout << i + 1 << " - >" << this->backpack[i];
		}
		std::cout << "0 - > go back" << std::endl;
		int index;
		std::cin >> index;

		while (index != 0 && this->backpack.size() != 0)
		{
			Edible e = this->backpack[index - 1];
			player.increaseStamina(e.getReplenishStamina());
			player.increaseHealth(e.getReplenishHealth());
			std::cout << "What would you like to eat?\n";
			for (size_t i = 0; i < this->backpack.size(); i++)
			{
				std::cout << i + 1 << " - >" << this->backpack[i];
			}
			std::cout << "0 - > go back" << std::endl;
			int index;;
			std::cin >> index;
		}
	}
}