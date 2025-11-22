#ifndef CHARACTERDB_H
#define CHARACTERDB_H

#include "BaseCharacter.h"
#include <vector>
using namespace std;

/**
 * Clase que maneja la base de datos de personajes
 * Permite obtener personajes base para crear personajes en el juego
 */
class CharacterDB
{
    private:
        /* Vector que almacena los personajes base */
        vector<BaseCharacter> baseCharacters;

    public:
        /* Constructor */
        CharacterDB();

        /* Obtiene al jugador */
        BaseCharacter getPlayerBaseCharacter();

        /* Obtiene un BaseCharacter aleatorio */
        BaseCharacter getRandomBaseCharacter();
};

#endif // CHARACTERDB_H