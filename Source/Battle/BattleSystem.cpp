#include "BattleSystem.h"
#include "../GameController.h" // For GameController functions if needed
#include "States/ActionSelectionState.h" // Initial state for battle
#include "States/RunTurnState.h"
#include <iostream>

namespace Battle
{
    BattleSystem::BattleSystem(GameController* owner, Player* playerCharacter, const Character& enemyCharacter)
        : owner(owner), stateMachine(this), player(playerCharacter), enemy(enemyCharacter), battleUI(), chosenAction(ActionType::None), battleIsOver(false), isPlayerGuarding(false), hasHealthBarUpdated(false), hasPlayerLeveledUp(false), hasUltimatePointsUpdated(false), battleStarted(false)
    {
    }

    void BattleSystem::startBattle()
    {
        std::cout << "Battle started! Player: " << player->getCharacter().getBaseCharacter().getName()
                  << " vs Enemy: " << enemy.getBaseCharacter().getName() << std::endl;
        
        battleUI.setup(player->getCharacter(), enemy); // Setup the battle UI
        battleUI.updateHealthBars(player->getCharacter(), enemy); // Initial health bar update
        battleUI.updatePlayerUltimatePoints(player->getUltimatePoints()); // Initial ultimate points update

        // Set the initial state for the battle (e.g., player selects action)
        stateMachine.changeState(new RunTurnState());
    }

    void BattleSystem::handleEvent(sf::Event event)
    {
        if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::E)
            {
                if (dialogManager.isActive())
                {
                    dialogManager.nextLine();
                    return; // Don't pass to state machine if UI handled it
                }
            }
        }
        stateMachine.handleEvent(event);
    }

    void BattleSystem::update()
    {
        dialogManager.update();
        stateMachine.update();

        // Actualizar las barras de vida si es necesario
        if(hasHealthBarUpdated)
        {
            battleUI.updateHealthBars(player->getCharacter(), enemy);
            hasHealthBarUpdated = false;
        }
        
        // Cambiar el texto de subida de nivel
        if(hasPlayerLeveledUp)
        {
            battleUI.updatePlayerLevelText(player->getCharacter().getLevel());
            hasPlayerLeveledUp = false;
        }

        // Actualizar puntos de definitiva
        if(hasUltimatePointsUpdated)
        {
            battleUI.updatePlayerUltimatePoints(player->getUltimatePoints());
            hasUltimatePointsUpdated = false;
        }
    }

    void BattleSystem::draw(sf::RenderWindow& window)
    {
        stateMachine.draw(window);
        dialogManager.draw(window);
        battleUI.draw(window, static_cast<int>(chosenAction));
    }

    bool BattleSystem::isBattleOver() const
    {
        return battleIsOver;
    }

    void BattleSystem::endBattle()
    {
        battleIsOver = true;
    }

    bool BattleSystem::getPlayerGuarding() const
    {
        return isPlayerGuarding;
    }

    void BattleSystem::setPlayerGuarding(bool guarding)
    {
        isPlayerGuarding = guarding;
    }

    bool BattleSystem::getHasHealthBarUpdated() const
    {
        return hasHealthBarUpdated;
    }

    void BattleSystem::setHasHealthBarUpdated(bool updated)
    {
        hasHealthBarUpdated = updated;
    }

    bool BattleSystem::getHasPlayerLeveledUp() const
    {
        return hasPlayerLeveledUp;
    }

    void BattleSystem::setHasPlayerLeveledUp(bool leveledUp)
    {
        hasPlayerLeveledUp = leveledUp;
    }

    bool BattleSystem::getHasUltimatePointsUpdated() const
    {
        return hasUltimatePointsUpdated;
    }

    void BattleSystem::setHasUltimatePointsUpdated(bool updated)
    {
        hasUltimatePointsUpdated = updated;
    }

    bool BattleSystem::getBattleStarted() const
    {
        return battleStarted;
    }

    void BattleSystem::setBattleStarted(bool started)
    {
        battleStarted = started;
    }
} // namespace Battle
