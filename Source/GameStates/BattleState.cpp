#include "BattleState.h"
#include "../GameController.h"
#include "../GameStates/GameMenuState.h" // For transitioning back to game menu
#include <iostream>

BattleState::BattleState(const Character& player, const Character& enemy)
    : playerCharacter(player), enemyCharacter(enemy), battleSystem(nullptr) // Initialize battleSystem to nullptr
{
}

BattleState::~BattleState()
{
    delete battleSystem;
}

void BattleState::enter(GameController* owner)
{
    std::cout << "Entering BattleState" << std::endl;
    battleSystem = new Battle::BattleSystem(owner, playerCharacter, enemyCharacter);
    battleSystem->startBattle();
}

void BattleState::handleEvent(GameController* owner, sf::Event event)
{
    if (battleSystem)
    {
        battleSystem->handleEvent(event);
    }
}

void BattleState::update(GameController* owner)
{
    if (battleSystem)
    {
        battleSystem->update();
        if (battleSystem->isBattleOver())
        {
            owner->stateMachine.changeState(new GameMenuState());
            return; 
        }
    }
}

void BattleState::draw(sf::RenderWindow& window)
{
    if (battleSystem)
    {
        battleSystem->draw(window);
    }
}

void BattleState::exit()
{
    std::cout << "Exiting BattleState" << std::endl;
}
