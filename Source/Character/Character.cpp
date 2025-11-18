#include "Character.h"
#include <iostream> // Para cout para propositos de depuracion

Character::Character(const BaseCharacter& baseChar, int initialLevel)
    : base(baseChar),
      level(initialLevel),
      currentExp(0) // Empieza con 0 de experiencia
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

void Character::levelUp()
{
    level++;
    currentHealth = base.getMaxHealth();
    calculateStats();
}

void Character::gainExperience(int amount)
{
    currentExp += amount;
    int expToLevelUp = level * 100;
    if (currentExp >= expToLevelUp)
    {
        currentExp -= expToLevelUp;
        levelUp();
    }
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

int Character::getLevel() const { return level; }
int Character::getMaxHealth() const { return maxHealth; }
int Character::getAttack() const { return attack; }
int Character::getDefense() const { return defense; }

int Character::getCurrentHealth() const { return currentHealth; }
int Character::getCurrentExp() const { return currentExp; }
