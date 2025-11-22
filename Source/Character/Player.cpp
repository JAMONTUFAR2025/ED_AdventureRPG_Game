#include "Player.h"

/**
 * Constructor que recibe el nivel inicial, por defecto es 5
 * Inicializa los atributos del jugador
 */
Player::Player(int initialLevel)
    : playerCharacter(CharacterDB().getPlayerBaseCharacter(), initialLevel),
        currentExp(0),
        ultimatePoints(0),
        defenseMultiplier(1.0f),
        points(0)
{
}

/* Metodo para ganar experiencia */
void Player::gainExperience(int amount)
{
    // Incrementa la experiencia actual
    currentExp += amount;
    // Calcula la experiencia necesaria para subir de nivel
    int expToLevelUp = playerCharacter.getLevel() * 10;
    // Verifica si se puede subir de nivel
    if (currentExp >= expToLevelUp)
    {
        // Resta la experiencia necesaria y sube de nivel
        currentExp -= expToLevelUp;
        levelUp();
    }
}

/* Metodo para subir de nivel */
void Player::levelUp()
{
    // Guarda la salud maxima antes de subir de nivel
    int oldHealth = playerCharacter.getMaxHealth();
    // Sube de nivel y recalcula las estadisticas
    playerCharacter.setLevel(playerCharacter.getLevel() + 1);
    playerCharacter.calculateStats();
    // Restaura la salud actual proporcionalmente al aumento de salud maxima
    int healthDifference = playerCharacter.getMaxHealth() - oldHealth;
    // Aumenta la salud actual en la diferencia
    playerCharacter.setCurrentHealth(playerCharacter.getCurrentHealth() + healthDifference);
}

/* Metodo para obtener los puntos de definitiva */
int Player::getUltimatePoints() { return ultimatePoints; }

/* Metodo para ganar puntos de definitiva */
void Player::gainUltimatePoints(int amount)
{
    // Incrementa los puntos de definitiva
    ultimatePoints += amount;
    // Limita los puntos de definitiva a un maximo de 10
    if (ultimatePoints > 10)
    {
        ultimatePoints = 10;
    }
}

/* Metodo para usar puntos de definitiva */
bool Player::useUltimate(int cost)
{
    // Verifica si hay suficientes puntos de definitiva para usar la habilidad
    if (ultimatePoints >= cost)
    {
        // Resta los puntos de definitiva y retorna true
        ultimatePoints -= cost;
        return true;
    }
    // No hay suficientes puntos de definitiva, retorna false
    return false;
}

/* Metodo para establecer el multiplicador de defensa */
void Player::setDefenseMultiplier(float multiplier) 
{
    // Establece el nuevo multiplicador de defensa
    defenseMultiplier = multiplier; 
}

/* Metodo para obtener el multiplicador de defensa */
float Player::getDefenseMultiplier() 
{ 
    return defenseMultiplier; 
}

/* Metodo para obtener la defensa */
int Player::getDefense() 
{ 
    // Aplica el multiplicador de defensa a la defensa base del personaje
    return static_cast<int>(playerCharacter.getDefense() * defenseMultiplier); 
}

/* Metodo para obtener el personaje */
Character& Player::getCharacter() 
{ 
    return playerCharacter; 
}

/* Metodo para obtener la experiencia actual */
int Player::getCurrentExp() 
{
    return currentExp;
}

/* Metodo para obtener la experiencia necesaria para el siguiente nivel */
int Player::getNextLevelExp() 
{
    return playerCharacter.getLevel() * 10;
}

/* Metodo para obtener los puntos del jugador */
int Player::getPoints() 
{
    return points;
}

/* Metodo para ganar puntos */
void Player::gainPoints(int amount)
{
    points += amount;
}