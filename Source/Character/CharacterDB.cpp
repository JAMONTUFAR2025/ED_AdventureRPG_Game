#include "CharacterDB.h"

CharacterDB::CharacterDB()
{
    // Inicializa la base de datos con algunos personajes de ejemplo
    baseCharacters.push_back(BaseCharacter("Jugador", 50, 50, 50, 0));
    baseCharacters.push_back(BaseCharacter("Moscarron", 1, 1, 1, 1));
    baseCharacters.push_back(BaseCharacter("Zombi", 30, 40, 20, 20));
    baseCharacters.push_back(BaseCharacter("Quimera", 80, 40, 50, 40));
    baseCharacters.push_back(BaseCharacter("Dragon", 200, 70, 80, 100));
}

BaseCharacter CharacterDB::getBaseCharacter(int index) const
{
    if (index >= 0 && index < static_cast<int>(baseCharacters.size()))
    {
        return baseCharacters[index];
    }
    // Return a default BaseCharacter if index is out of range
    return BaseCharacter();
}