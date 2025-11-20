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

int Character::takeDamage(Character& attacker, int power)
{
    // --- Formula de daño estilo Pokemon ---
    // ((2 * Nivel / 5 + 2) * Poder * Ataque / Defensa / 50) + 2
    
    // Usamos float para la precision
    float level_factor = (2.0f * attacker.getLevel() / 5.0f) + 2.0f;
    float attack_defense_ratio = static_cast<float>(attacker.getAttack()) / static_cast<float>(defense);
    
    // Calculo base del daño
    float base_damage = (level_factor * power * attack_defense_ratio / 50.0f) + 2.0f;

    // Modificador aleatorio (entre 0.85 y 1.0)
    float random_modifier = (rand() % 16 + 85) / 100.0f; // Numero entre 0.85 y 1.00
    
    int final_damage = static_cast<int>(base_damage * random_modifier);

    // Asegurarse de que el daño sea al menos 1 si el calculo es muy bajo
    if (final_damage < 1) {
        final_damage = 1;
    }

    currentHealth -= final_damage;
    if (currentHealth < 0)
    {
        currentHealth = 0;
    }

    return final_damage;
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

void Character::setLevel(int newLevel) { level = newLevel; calculateStats(); }
int Character::getLevel() const { return level; }
int Character::getMaxHealth() const { return maxHealth; }
int Character::getAttack() const { return attack; }
int Character::getDefense() const { return defense; }

void Character::setCurrentHealth(int health) { currentHealth = health; }
int Character::getCurrentHealth() const { return currentHealth; }
