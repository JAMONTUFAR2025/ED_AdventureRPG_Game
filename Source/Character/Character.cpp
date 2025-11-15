#include "Character.h"

Character::Character() : base(), level(1)
{
}

const BaseCharacter& Character::getBaseCharacter() const
{
    return base;
}

int Character::getLevel() const
{
    return level;
}

int Character::getCurrentExp() const
{
    // Placeholder implementation, assuming exp is level * 100
    return level * 100;
}