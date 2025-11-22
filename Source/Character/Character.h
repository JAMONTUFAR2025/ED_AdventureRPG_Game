#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseCharacter.h"
#include <string>

using namespace std;

/**
 * Clase que representa a un personaje en el juego
 * Maneja las estadisticas y acciones de un personaje
 */
class Character
{
    private:
        /* BaseCharacter que contiene las estadisticas base del personaje */
        BaseCharacter base;
        /* Nivel del personaje */
        int level;

        /* --- Caracteristicas --- */
        int maxHealth;
        int attack;
        int defense;
        /* Salud actual del personaje */
        int currentHealth;
        
    public:
        /* Constructor */
        Character(const BaseCharacter& baseChar, int initialLevel = 1);
        /* Calcula las estadisticas del personaje basadas en su nivel y base */
        void calculateStats();
        
        /* Metodo para recibir danio */
        int takeDamage(Character& source, int targetDefense, int power, bool isCritical);
        /* Metodo para curar al personaje */
        void heal(int amount);

        /* --- Getters y Setters --- */
        BaseCharacter& getBaseCharacter();
        void setLevel(int newLevel);
        int getLevel();

        int getMaxHealth();
        
        int getAttack();

        virtual int getDefense();

        void setCurrentHealth(int health);
        int getCurrentHealth();
    };

#endif // CHARACTER_H