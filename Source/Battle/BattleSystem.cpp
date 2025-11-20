#include "BattleSystem.h"
#include "../GameController.h"
#include "States/ActionSelectionState.h"
#include "States/RunTurnState.h"

namespace Battle
{
    BattleSystem::BattleSystem(GameController* owner, Player* playerCharacter, Character& enemyCharacter)
        : owner(owner), stateMachine(this), player(playerCharacter), enemy(enemyCharacter), battleUI(), chosenAction(ActionType::None), battleIsOver(false), isPlayerGuarding(false), hasHealthBarUpdated(false), hasPlayerLeveledUp(false), hasUltimatePointsUpdated(false), battleStarted(false)
    {
    }

    void BattleSystem::startBattle()
    {
        battleUI.setup(player->getCharacter(), enemy);
        battleUI.updateHealthBars(player->getCharacter(), enemy);
        battleUI.updatePlayerUltimatePoints(player->getUltimatePoints());

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
                    return;
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

    void BattleSystem::draw(sf::RenderWindow& window, bool isDialogActive)
    {
        stateMachine.draw(window);
        dialogManager.draw(window);
        battleUI.draw(window, static_cast<int>(chosenAction), dialogManager.isActive());
    }

    bool BattleSystem::isBattleOver()
    {
        return battleIsOver;
    }

    void BattleSystem::endBattle()
    {
        battleIsOver = true;
    }

    bool BattleSystem::getPlayerGuarding()
    {
        return isPlayerGuarding;
    }

    void BattleSystem::setPlayerGuarding(bool guarding)
    {
        isPlayerGuarding = guarding;
    }

    bool BattleSystem::getHasHealthBarUpdated()
    {
        return hasHealthBarUpdated;
    }

    void BattleSystem::setHasHealthBarUpdated(bool updated)
    {
        hasHealthBarUpdated = updated;
    }

    bool BattleSystem::getHasPlayerLeveledUp()
    {
        return hasPlayerLeveledUp;
    }

    void BattleSystem::setHasPlayerLeveledUp(bool leveledUp)
    {
        hasPlayerLeveledUp = leveledUp;
    }

    bool BattleSystem::getHasUltimatePointsUpdated()
    {
        return hasUltimatePointsUpdated;
    }

    void BattleSystem::setHasUltimatePointsUpdated(bool updated)
    {
        hasUltimatePointsUpdated = updated;
    }

    bool BattleSystem::getBattleStarted()
    {
        return battleStarted;
    }

    void BattleSystem::setBattleStarted(bool started)
    {
        battleStarted = started;
    }
} // namespace Battle
