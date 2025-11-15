#include "BaseCharacter.h"

BaseCharacter::BaseCharacter() : name(""), maxHealth(100), attack(10), defense(5), expYield(0)
{
}

BaseCharacter::BaseCharacter(std::string name, int maxHealth, int attack, int defense, int expYield)
    : name(name), maxHealth(maxHealth), attack(attack), defense(defense), expYield(expYield)
{
}

const string& BaseCharacter::getName() const
{
    return name;
}

int BaseCharacter::getMaxHealth() const
{
    return maxHealth;
}

int BaseCharacter::getAttack() const
{
    return attack;
}

int BaseCharacter::getDefense() const
{
    return defense;
}

int BaseCharacter::getExpYield() const
{
    return expYield;
}