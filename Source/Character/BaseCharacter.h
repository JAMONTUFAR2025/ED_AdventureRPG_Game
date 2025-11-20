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

        string& getName();
        int getMaxHealth();
        int getAttack();
        int getDefense();
        int getExpYield();
        int getPointsYield();
};

#endif // BASECHARACTER_H