#include "BattleState.h"
#include "../GameController.h"
#include "../GameStates/GameMenuState.h" // For transitioning back to game menu
#include "../GameStates/GameOverState.h" // For transitioning to GameOverState
#include <iostream>

BattleState::BattleState(GameController& owner, Player* player, Character enemy)
    : player(player), enemyCharacter(enemy), battleSystem(nullptr) // Initialize battleSystem to nullptr
{
}

BattleState::~BattleState()
{
    delete battleSystem;
}

void BattleState::enter(GameController* owner)
{
    std::cout << "Entering BattleState" << std::endl;
    battleSystem = new Battle::BattleSystem(owner, player, enemyCharacter);
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
            if(battleSystem->getPlayer()->getCharacter().getCurrentHealth() <= 0)
            {
                std::cout << "Player has been defeated!" << std::endl;
                owner->stateMachine.changeState(new GameOverState(true)); // true indicates the game is lost
                return; 
            }
            
            std::cout << "Battle is over, returning to GameMenuState." << std::endl;
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
