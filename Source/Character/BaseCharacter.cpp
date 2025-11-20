#include "BaseCharacter.h"

BaseCharacter::BaseCharacter() : name(""), maxHealth(100), attack(10), defense(5), expYield(0), pointsYield(0)
{
}

BaseCharacter::BaseCharacter(std::string name, int maxHealth, int attack, int defense, int expYield, int pointsYield)
    : name(name), maxHealth(maxHealth), attack(attack), defense(defense), expYield(expYield), pointsYield(pointsYield)
{
}

string& BaseCharacter::getName()
{
    return name;
}

int BaseCharacter::getMaxHealth()
{
    return maxHealth;
}

int BaseCharacter::getAttack()
{
    return attack;
}

int BaseCharacter::getDefense()
{
    return defense;
}

int BaseCharacter::getExpYield()
{
    return expYield;
}

int BaseCharacter::getPointsYield()
{
    return pointsYield;
}