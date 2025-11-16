#include "CharacterDB.h"

CharacterDB::CharacterDB()
{
    // Inicializa la base de datos con algunos personajes de ejemplo
    baseCharacters.push_back(BaseCharacter("Goblin", 50, 8, 2, 20));
    baseCharacters.push_back(BaseCharacter("Orc", 80, 12, 4, 40));
    baseCharacters.push_back(BaseCharacter("Dragon", 200, 25, 10, 100));
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