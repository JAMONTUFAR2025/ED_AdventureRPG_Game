#ifndef CHARACTERDB_H
#define CHARACTERDB_H

#include "BaseCharacter.h"
#include <vector>
using namespace std;

class CharacterDB
{
    private:
        vector<BaseCharacter> baseCharacters;

    public:
        CharacterDB();

        /* Obtiene al jugador */
        BaseCharacter getPlayerBaseCharacter() const;

        /* Obtiene un BaseCharacter aleatorio */
        BaseCharacter getRandomBaseCharacter() const;
};

#endif // CHARACTERDB_H