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
        int getMaxHealth() const;
        int getAttack() const;
        int getDefense() const;
        int getExpYield() const;
};

#endif // BASECHARACTER_H