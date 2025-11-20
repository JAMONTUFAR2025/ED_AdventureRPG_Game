#include "Player.h"

Player::Player(BaseCharacter& baseChar, int initialLevel)
    : playerCharacter(baseChar, initialLevel),
        currentExp(0),
        ultimatePoints(0),
        defenseMultiplier(1.0f)
{
}

void Player::gainExperience(int amount)
{
    currentExp += amount;
    int expToLevelUp = playerCharacter.getLevel() * 100;
    if (currentExp >= expToLevelUp)
    {
        currentExp -= expToLevelUp;
        levelUp();
    }
}

void Player::levelUp()
{
    playerCharacter.setLevel(playerCharacter.getLevel() + 1);
    playerCharacter.setCurrentHealth(playerCharacter.getMaxHealth());
}


int Player::getUltimatePoints() { return ultimatePoints; }

void Player::gainUltimatePoints(int amount)
{
    ultimatePoints += amount;
    if (ultimatePoints > 10)
    {
        ultimatePoints = 10; // Cap at 10
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

float Player::getDefenseMultiplier() 
{ 
    return defenseMultiplier; 
}

int Player::getDefense() 
{ 
    return static_cast<int>(playerCharacter.getDefense() * defenseMultiplier); 
}

Character& Player::getCharacter() 
{ 
    return playerCharacter; 
}