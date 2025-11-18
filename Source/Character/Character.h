#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseCharacter.h"
#include <string>
using namespace std;

class Character
{
    private:
        BaseCharacter base;
        int level;

        int maxHealth;
        int attack;
        int defense;

        int currentHealth;
        int currentExp;
    public:
        Character(const BaseCharacter& baseChar, int initialLevel = 1);
        
        void calculateStats();
        void levelUp();
        void gainExperience(int amount);
        
        int takeDamage(Character& attacker, int power);
        void heal(int amount);
        
        const BaseCharacter& getBaseCharacter() const;

        int getLevel() const;
        int getMaxHealth() const;
        int getAttack() const;
        virtual int getDefense() const;

        int getCurrentHealth() const;
        int getCurrentExp() const;
    };

#endif // CHARACTER_H