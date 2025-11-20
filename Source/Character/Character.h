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
        
    public:
        Character(const BaseCharacter& baseChar, int initialLevel = 1);
        
        void calculateStats();
        
        int takeDamage(Character& attacker, int power);
        void heal(int amount);
        
        const BaseCharacter& getBaseCharacter() const;

        void setLevel(int newLevel);
        int getLevel() const;
        int getMaxHealth() const;
        int getAttack() const;
        virtual int getDefense() const;

        void setCurrentHealth(int health);
        int getCurrentHealth() const;
    };

#endif // CHARACTER_H