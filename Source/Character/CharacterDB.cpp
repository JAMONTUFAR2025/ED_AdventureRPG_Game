#include "CharacterDB.h"

CharacterDB::CharacterDB()
{
    // Inicializa la base de datos con algunos personajes de ejemplo
    baseCharacters.push_back(BaseCharacter("Jugador", 100, 50, 10, 0, 0));
    baseCharacters.push_back(BaseCharacter("Zombi", 60, 20, 20, 5, 5));
    baseCharacters.push_back(BaseCharacter("Duende", 80, 30, 15, 7, 7));
    baseCharacters.push_back(BaseCharacter("Fenix", 100, 35, 20, 10, 10));
    baseCharacters.push_back(BaseCharacter("Quimera", 120, 30, 20, 12, 15));
    baseCharacters.push_back(BaseCharacter("Dragon", 200, 50, 20, 15, 40));
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