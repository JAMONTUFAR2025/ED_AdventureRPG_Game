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

        /* Obtiene un BaseCharacter por su indice */
        BaseCharacter getBaseCharacter(int index) const;
};

#endif // CHARACTERDB_H