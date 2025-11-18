#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character
{
public:
    Player(const BaseCharacter& baseChar, int initialLevel = 1);

    // --- Ultimate Points ---
    int getUltimatePoints() const;
    void gainUltimatePoints(int amount);
    bool useUltimate(int cost);

    // --- Defense Multiplier ---
    void setDefenseMultiplier(float multiplier);
    float getDefenseMultiplier() const;
    int getDefense() const;

private:
    int ultimatePoints;
    float defenseMultiplier;
};

#endif // PLAYER_H
