#include "Player.h"

Player::Player(int initialLevel)
    : playerCharacter(CharacterDB().getBaseCharacter(0), initialLevel),
        currentExp(0),
        ultimatePoints(0),
        defenseMultiplier(1.0f)
{
}

void Player::gainExperience(int amount)
{
    currentExp += amount;
    int expToLevelUp = playerCharacter.getLevel() * 10;
    if (currentExp >= expToLevelUp)
    {
        currentExp -= expToLevelUp;
        levelUp();
    }
}

void Player::levelUp()
{
    int oldHealth = playerCharacter.getMaxHealth();
    playerCharacter.setLevel(playerCharacter.getLevel() + 1);
    playerCharacter.calculateStats();
    int healthDifference = playerCharacter.getMaxHealth() - oldHealth;
    playerCharacter.setCurrentHealth(playerCharacter.getCurrentHealth() + healthDifference);
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