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
        
        int takeDamage(Character& source, int targetDefense, int power, bool isCritical);
        void heal(int amount);
        
        BaseCharacter& getBaseCharacter();

        void setLevel(int newLevel);
        int getLevel();
        int getMaxHealth();
        int getAttack();
        virtual int getDefense();

        void setCurrentHealth(int health);
        int getCurrentHealth();
    };

#endif // CHARACTER_H