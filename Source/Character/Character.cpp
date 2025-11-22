#include "Character.h"

/**
 * Constructor
 * Inicializa el personaje con su BaseCharacter y nivel inicial
 * Calcula las estadisticas y establece la salud actual al maximo
 */
Character::Character(const BaseCharacter& baseChar, int initialLevel)
    : base(baseChar),
      level(initialLevel)
{
    calculateStats();
    currentHealth = maxHealth;
}

/* Calcula las estadisticas del personaje basadas en su nivel y base */
void Character::calculateStats()
{
    // --- Formula de estadisticas basada en Pokemon ---
    maxHealth = (base.getMaxHealth() * 2 * level) / 100 + level + 10;
    attack = (base.getAttack() * 2 * level) / 100 + 5;
    defense = (base.getDefense() * 2 * level) / 100 + 5;
}

/* Metodo para recibir danio */
int Character::takeDamage(Character& source, int targetDefense, int power, bool isCritical)
{
    // --- Formula de danio basada en Pokemon ---
    float levelFactor = (2.0f * source.getLevel() / 5.0f) + 2.0f;
    float attackDefenseRatio = static_cast<float>(source.getAttack()) / static_cast<float>(targetDefense);
    
    float baseDamage = (levelFactor * power * attackDefenseRatio / 50.0f) + 2.0f;

    // Modificador aleatorio (entre 0.85 y 1.0)
    float randomModifier = (rand() % 16 + 85) / 100.0f;
    float calculatedDamage = baseDamage * randomModifier;
    
    // Si es golpe critico
    if(isCritical) 
    {
        // Multiplicador de 1.5 (50% mas de danio)
        calculatedDamage *= 1.5f; 
    }
    
    int finalDamage = static_cast<int>(calculatedDamage);
    // El danio al menos es 1
    if(finalDamage < 1) {
        finalDamage = 1;
    }

    // Aplicar danio
    currentHealth -= finalDamage;
    if(currentHealth < 0)
    {
        currentHealth = 0;
    }

    return finalDamage;
}

/* Metodo para curar al personaje */
void Character::heal(int amount)
{
    currentHealth += amount;
    if(currentHealth > maxHealth)
    {
        currentHealth = maxHealth;
    }
}

/* Getters y Setters */
BaseCharacter& Character::getBaseCharacter() { return base; }

void Character::setLevel(int newLevel) { level = newLevel; }
int Character::getLevel() { return level; }

int Character::getMaxHealth() { return maxHealth; }

int Character::getAttack() { return attack; }
int Character::getDefense() { return defense; }

void Character::setCurrentHealth(int health) { currentHealth = health; }
int Character::getCurrentHealth() { return currentHealth; }
