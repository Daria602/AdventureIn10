#pragma once
#include <iostream>
#include <string>
#include <vector>
class Edible
{
private:
	std::string name;
	int replenishStamina;
	int replenishHealth;
	friend std::ostream& operator<<(std::ostream& os, const Edible& go_);

public:
	Edible() { this->name = "NONE"; this->replenishStamina = 0; this->replenishHealth = 0; }
	Edible(std::string name, int replenishStamina, int replenishHealth) { this->name = name; this->replenishStamina = replenishStamina; this->replenishHealth = replenishHealth; }
	Edible(const Edible& go_);
	virtual ~Edible();

	std::string getName() { return this->name; }
	int getReplenishStamina() { return this->replenishStamina; }
	int getReplenishHealth() { return this->replenishHealth; }

};
