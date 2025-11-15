#include "BaseCharacter.h"

BaseCharacter::BaseCharacter() : name("Unnamed"), maxHealth(100), attack(10), defense(5)
{
}

const string& BaseCharacter::getName() const
{
    return name;
}

const int BaseCharacter::getMaxHealth() const
{
    return maxHealth;
}

const int BaseCharacter::getAttack() const
{
    return attack;
}

const int BaseCharacter::getDefense() const
{
    return defense;
}