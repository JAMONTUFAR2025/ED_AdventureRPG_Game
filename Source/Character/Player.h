#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "CharacterDB.h"
class Player
{
public:
    Player(int initialLevel = 1);

    void gainExperience(int amount);
    
    // --- Ultimate Points ---
    int getUltimatePoints();
    void gainUltimatePoints(int amount);
    bool useUltimate(int cost);
    
    // --- Defense Multiplier ---
    void setDefenseMultiplier(float multiplier);
    float getDefenseMultiplier();
    int getDefense();

    // --- Character Access ---
    Character& getCharacter();

private:
    Character playerCharacter;
    int currentExp;
    int ultimatePoints;
    float defenseMultiplier;

    void levelUp();
};

#endif // PLAYER_H
