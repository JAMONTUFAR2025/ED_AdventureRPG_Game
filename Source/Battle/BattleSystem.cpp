#include "BattleSystem.h"
#include "../GameController.h" // For GameController functions if needed
#include "States/ActionSelectionState.h" // Initial state for battle
#include <iostream>

namespace Battle
{
    BattleSystem::BattleSystem(GameController* owner, const Player& playerCharacter, const Character enemyCharacter)
        : owner(owner), stateMachine(this), player(playerCharacter), enemy(enemyCharacter), battleUI(), chosenAction(ActionType::None), battleIsOver(false), isPlayerGuarding(false)
    {
    }

    void BattleSystem::startBattle()
    {
        std::cout << "Battle started! Player: " << player.getCharacter().getBaseCharacter().getName()
                  << " vs Enemy: " << enemy.getBaseCharacter().getName() << std::endl;
        
        battleUI.setup(player.getCharacter(), enemy); // Setup the battle UI
        battleUI.updateHealthBars(player.getCharacter(), enemy); // Initial health bar update

        // Set the initial state for the battle (e.g., player selects action)
        stateMachine.changeState(new ActionSelectionState());
    }

    void BattleSystem::handleEvent(sf::Event event)
    {
        if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Z)
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
        battleUI.updateHealthBars(player.getCharacter(), enemy); // Keep health bars updated
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
} // namespace Battle
