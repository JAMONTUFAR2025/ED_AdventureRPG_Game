#include "Player.h"

Player::Player(const BaseCharacter& baseChar, int initialLevel)
    : Character(baseChar, initialLevel),
      ultimatePoints(0),
      defenseMultiplier(1.0f)
{
}

int Player::getUltimatePoints() const
{
    return ultimatePoints;
}

void Player::gainUltimatePoints(int amount)
{
    ultimatePoints += amount;
    if (ultimatePoints > 100)
    {
        ultimatePoints = 100; // Cap at 100
    }
}

bool Player::useUltimate(int cost)
{
    if (ultimatePoints >= cost)
    {
        ultimatePoints -= cost;
        return true;
    }
    return false;
}

void Player::setDefenseMultiplier(float multiplier)
{
    defenseMultiplier = multiplier;
}

float Player::getDefenseMultiplier() const
{
    return defenseMultiplier;
}

int Player::getDefense() const
{
    return static_cast<int>(Character::getDefense() * defenseMultiplier);
}
