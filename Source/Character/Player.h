#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "CharacterDB.h"
class Player
{
private:
    Character playerCharacter;
    int currentExp;
    int ultimatePoints;
    float defenseMultiplier;
    int points;

    void levelUp();

public:
    Player(int initialLevel = 5);

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
    int getCurrentExp();
    int getNextLevelExp();
    int getPoints();
    void gainPoints(int amount);

};

#endif // PLAYER_H
