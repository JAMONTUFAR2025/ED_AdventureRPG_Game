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
        BaseCharacter getPlayerBaseCharacter();

        /* Obtiene un BaseCharacter aleatorio */
        BaseCharacter getRandomBaseCharacter();
};

#endif // CHARACTERDB_H