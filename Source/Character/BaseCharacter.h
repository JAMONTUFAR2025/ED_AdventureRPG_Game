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
    public:
        BaseCharacter();

        const string& getName() const;
        const int getMaxHealth() const;
        const int getAttack() const;
        const int getDefense() const;
};

#endif // BASECHARACTER_H