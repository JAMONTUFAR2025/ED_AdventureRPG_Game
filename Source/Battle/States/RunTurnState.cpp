#include "RunTurnState.h"
#include <iostream>
#include "ActionSelectionState.h" // Transition back to action selection
#include "BattleEndState.h" // To be implemented for battle end
#include <cstdlib> // For rand()

namespace Battle
{
    RunTurnState::RunTurnState()
    {
    }

    RunTurnState::~RunTurnState()
    {
    }

    void RunTurnState::enter(BattleSystem* owner)
    {
        std::cout << "Entering RunTurnState" << std::endl;

        // --- Player Action Execution ---
        switch (owner->getChosenAction())
        {
            case ActionType::Fight:
            {
                int playerDamage = owner->getPlayer().getAttack();
                owner->getEnemy().takeDamage(playerDamage);
                std::cout << owner->getPlayer().getBaseCharacter().getName() << " attacks "
                          << owner->getEnemy().getBaseCharacter().getName() << " for "
                          << playerDamage << " damage!" << std::endl;
                owner->getBattleUI().displayBattleMessage(owner->getPlayer().getBaseCharacter().getName() + " ataca!");
                break;
            }
            case ActionType::Special:
                std::cout << owner->getPlayer().getBaseCharacter().getName() << " uses a special move!" << std::endl;
                owner->getBattleUI().displayBattleMessage(owner->getPlayer().getBaseCharacter().getName() + " usa especial!");
                // TODO: Implement actual special move logic
                break;
            case ActionType::Guard:
                std::cout << owner->getPlayer().getBaseCharacter().getName() << " is guarding!" << std::endl;
                owner->getBattleUI().displayBattleMessage(owner->getPlayer().getBaseCharacter().getName() + " se pone en guardia!");
                // TODO: Implement guard status (e.g., damage reduction flag)
                break;
            case ActionType::Escape:
            {
                std::cout << owner->getPlayer().getBaseCharacter().getName() << " attempts to escape!" << std::endl;
                owner->getBattleUI().displayBattleMessage(owner->getPlayer().getBaseCharacter().getName() + " intenta escapar!");
                // Simple 50% chance to escape
                if (rand() % 2 == 0) // C++11 way to get a random number
                {
                    std::cout << owner->getPlayer().getBaseCharacter().getName() << " escaped successfully!" << std::endl;
                    owner->getStateMachine().changeState(new BattleEndState(BattleResult::Escape));
                    return; // Exit enter() as battle is over
                }
                else
                {
                    std::cout << owner->getPlayer().getBaseCharacter().getName() << " failed to escape!" << std::endl;
                }
                break;
            }
            case ActionType::None:
                // Should not happen, but handle defensively
                break;
        }

        // Check if enemy is defeated after player action
        if (owner->getEnemy().getCurrentHealth() <= 0)
        {
            std::cout << owner->getEnemy().getBaseCharacter().getName() << " defeated! Player wins!" << std::endl;
            owner->getStateMachine().changeState(new BattleEndState(BattleResult::Victory));
            return; // Exit enter() as battle is over
        }

        // --- Enemy Action Execution (Simple AI: always attack) ---
        int enemyDamage = owner->getEnemy().getAttack();
        owner->getPlayer().takeDamage(enemyDamage);
        std::cout << owner->getEnemy().getBaseCharacter().getName() << " attacks "
                  << owner->getPlayer().getBaseCharacter().getName() << " for "
                  << enemyDamage << " damage!" << std::endl;
        owner->getBattleUI().displayBattleMessage(owner->getEnemy().getBaseCharacter().getName() + " ataca!");

        // Check if player is defeated after enemy action
        if (owner->getPlayer().getCurrentHealth() <= 0)
        {
            std::cout << owner->getPlayer().getBaseCharacter().getName() << " defeated! Game Over!" << std::endl;
            owner->getStateMachine().changeState(new BattleEndState(BattleResult::Defeat));
            return; // Exit enter() as battle is over
        }
        
        // If battle continues, transition back to ActionSelectionState for the next turn
        owner->getStateMachine().changeState(new ActionSelectionState());
    }

    void RunTurnState::handleEvent(BattleSystem* owner, sf::Event event)
    {
        // No input handling needed in this state as it's an immediate action sequence
    }

    void RunTurnState::update(BattleSystem* owner)
    {
        // No update logic needed as actions are executed immediately in enter()
    }

    void RunTurnState::draw(sf::RenderWindow& window)
    {
        // Drawing handled by BattleSystem's draw() and BattleUI
        // owner->getBattleUI().draw(window, selectedOption, owner->getPlayer(), owner->getEnemy()); // Removed owner from draw
    }

    void RunTurnState::exit()
    {
        std::cout << "Exiting RunTurnState" << std::endl;
    }
} // namespace Battle
