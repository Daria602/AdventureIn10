#include "Edible.h"
std::ostream& operator<<(std::ostream& os, const Edible& go_)
{
	os << go_.name << ". Restores " << go_.replenishStamina << " of your stamina and " << go_.replenishHealth << " of your health.\n";
	return os;
}

Edible::~Edible()
{

}

Edible::Edible(const Edible& go_)
{
	this->name = go_.name;
	this->replenishStamina = go_.replenishStamina;
	this->replenishHealth = go_.replenishHealth;
}