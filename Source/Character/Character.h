#ifndef CHARACTER_H
#define CHARACTER_H
#include "BaseCharacter.h"

class Character
{
    private:
        BaseCharacter base;
        int level;
    public:
        Character();

        const BaseCharacter& getBaseCharacter() const;
        int getLevel() const;
        int getCurrentExp() const;
};

#endif // CHARACTER_H