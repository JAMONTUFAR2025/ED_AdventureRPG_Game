#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include <string>

using namespace std;

/**
 * Clase que representa las estadisticas base de un personaje
 */
class BaseCharacter
{
    private:
        /* Nombre del personaje base */
        string name;
        /* Estadisticas base */
        int maxHealth;
        int attack;
        int defense;
        /* Multiplicador de experiencia y puntos otorgados al derrotar */
        int expYield;
        int pointsYield;
    public:
        /* Constructor */
        BaseCharacter();
        /* Constructor con parametros */
        BaseCharacter(string name, int maxHealth, int attack, int defense, int expYield, int pointsYield);

        /* Getters */
        string& getName();

        int getMaxHealth();
        int getAttack();
        int getDefense();
        
        int getExpYield();
        int getPointsYield();
};

#endif // BASECHARACTER_H