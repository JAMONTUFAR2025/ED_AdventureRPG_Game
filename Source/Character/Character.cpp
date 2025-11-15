#include "Character.h"
#include <iostream> // Para cout para propositos de depuracion

Character::Character(const BaseCharacter& baseChar, int initialLevel)
    : base(baseChar),
      level(initialLevel),
      currentHealth(baseChar.getMaxHealth()), // Inicializa la vida actual a la maxima
      currentExp(0) // Empieza con 0 de experiencia
{
    calculateStats();
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

void Character::takeDamage(int damage)
{
    currentHealth -= damage;
    if (currentHealth < 0)
    {
        currentHealth = 0;
    }
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