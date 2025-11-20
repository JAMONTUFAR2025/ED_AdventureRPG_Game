#include "CharacterDB.h"

CharacterDB::CharacterDB()
{
    // Inicializa la base de datos con algunos personajes de ejemplo
    baseCharacters.push_back(BaseCharacter("Jugador", 50, 50, 50, 0, 0));
    baseCharacters.push_back(BaseCharacter("Moscarron", 1, 1, 1, 1, 1));
    baseCharacters.push_back(BaseCharacter("Zombi", 30, 40, 20, 20, 5));
    baseCharacters.push_back(BaseCharacter("Quimera", 80, 40, 50, 40, 10));
    baseCharacters.push_back(BaseCharacter("Dragon", 200, 70, 80, 100, 25));
}

BaseCharacter CharacterDB::getPlayerBaseCharacter() const
{
    return baseCharacters[0]; // Asume que el primer personaje es el jugador
}

BaseCharacter CharacterDB::getRandomBaseCharacter() const
{
    int randomIndex = 1 + (rand() % (baseCharacters.size() - 1)); // Evita el primer personaje (jugador)
    return baseCharacters[randomIndex];
}