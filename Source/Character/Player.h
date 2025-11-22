#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "CharacterDB.h"

/**
 * Clase que representa al jugador
 * Maneja la experiencia, puntos y el personaje del jugador
 */
class Player
{
private:
    /* Personaje del jugador */
    Character playerCharacter;
    /* Experiencia actual del jugador */
    int currentExp;
    /* Puntos de definitiva actuales */
    int ultimatePoints;
    /* Multiplicador de defensa */
    float defenseMultiplier;
    /* Puntos del jugador */
    int points;

    /* Metodo para subir de nivel */
    void levelUp();
public:
    /* Constructor que recibe el nivel inicial, por defecto es 5 */
    Player(int initialLevel = 5);
    /* Metodo para ganar experiencia */
    void gainExperience(int amount);
    
    /* --- Puntos de definitiva --- */
    int getUltimatePoints();
    void gainUltimatePoints(int amount);
    bool useUltimate(int cost);
    
    /* --- Multiplicador de defensa --- */
    void setDefenseMultiplier(float multiplier);
    float getDefenseMultiplier();
    int getDefense();

    /* --- Acceso a Character --- */
    Character& getCharacter();

    /* --- Experiencia y puntos --- */
    int getCurrentExp();
    int getNextLevelExp();
    int getPoints();
    void gainPoints(int amount);

};

#endif // PLAYER_H
