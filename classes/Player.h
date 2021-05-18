#pragma once
#include "Pet.h"
class Player : public Character
{
    int stamina, maxStamina;
public:
    Player(std::string name, int hp, int maxHp, int damage, int maxDamage, int stamina, int maxStamina);
    virtual ~Player();

    int getStamina() { return this->stamina; }

    void increaseStamina( int number);
    void increaseHealth(int number);
    void rest();
    int run();
    int attack();
    void wasAttacked(int atck);
    void seeStats();
};

