#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include <string>
using namespace std;

class BaseCharacter
{
    private:
        string name;
        int maxHealth;
        int attack;
        int defense;
        int expYield;
        int pointsYield;
    public:
        BaseCharacter();
        BaseCharacter(string name, int maxHealth, int attack, int defense, int expYield, int pointsYield);

        const string& getName() const;
        int getMaxHealth() const;
        int getAttack() const;
        int getDefense() const;
        int getExpYield() const;
        int getPointsYield() const;
};

#endif // BASECHARACTER_H