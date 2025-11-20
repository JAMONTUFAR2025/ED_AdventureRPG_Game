#include "Character.h"
#include <iostream> // Para cout para propositos de depuracion

Character::Character(const BaseCharacter& baseChar, int initialLevel)
    : base(baseChar),
      level(initialLevel)
{
    calculateStats();
    currentHealth = maxHealth; // Salud inicial al maximo
}

void Character::calculateStats()
{
    maxHealth = (base.getMaxHealth() * 2 * level) / 100 + level + 10;
    attack = (base.getAttack() * 2 * level) / 100 + 5;
    defense = (base.getDefense() * 2 * level) / 100 + 5;
}

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
    if (isCritical) 
    {
        // Multiplicador de 1.5 (50% más de daño)
        calculatedDamage *= 1.5f; 
        std::cout << source.getBaseCharacter().getName() << " lands a CRITICAL HIT!" << std::endl; // O el mensaje de tu motor
    }
    
    int finalDamage = static_cast<int>(calculatedDamage);
    // El danio al menos es 1
    if (finalDamage < 1) {
        finalDamage = 1;
    }

    // Aplicar danio
    currentHealth -= finalDamage;
    if (currentHealth < 0)
    {
        currentHealth = 0;
    }

    return finalDamage;
}

void Character::heal(int amount)
{
    currentHealth += amount;
    if (currentHealth > maxHealth)
    {
        currentHealth = maxHealth;
    }
}

const BaseCharacter& Character::getBaseCharacter() const { return base; }

void Character::setLevel(int newLevel) { level = newLevel; }
int Character::getLevel() const { return level; }
int Character::getMaxHealth() const { return maxHealth; }
int Character::getAttack() const { return attack; }
int Character::getDefense() const { return defense; }

void Character::setCurrentHealth(int health) { currentHealth = health; }
int Character::getCurrentHealth() const { return currentHealth; }
