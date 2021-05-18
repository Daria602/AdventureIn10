#pragma once
#include "Character.h"
class Pet :
    public Character
{
private:
    bool isPresent;
    int willToAttack;
public:
    Pet(std::string name, int hp, int maxHp, int damage, int maxDamage);
    virtual ~Pet() {}

    bool getIsPresent() { return this->isPresent; }

    void setIsPresent(bool alive) { this->isPresent = alive; }

    int attack();

};

