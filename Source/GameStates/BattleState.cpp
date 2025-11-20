#include "BattleState.h"
#include "../GameController.h"
#include "../GameStates/GameMenuState.h"
#include "../GameStates/GameOverState.h"
#include <iostream>

BattleState::BattleState(GameController& owner, Player* player, Character enemy)
    : player(player), enemyCharacter(enemy), battleSystem(nullptr)
{
}

BattleState::~BattleState()
{
    delete battleSystem;
}

void BattleState::enter(GameController* owner)
{
    this->owner = owner;
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
                owner->getStateMachine().changeState(new GameOverState(true)); // True significa que el juego se perdio
                return; 
            }
            
            owner->getStateMachine().changeState(new GameMenuState());
            return; 
        }
    }
}

void BattleState::draw(sf::RenderWindow& window)
{
    if (battleSystem)
    {
        battleSystem->draw(window, owner->getDialogManager()->isActive());
    }
}

void BattleState::exit()
{
}
