#include "RunTurnState.h"
#include <iostream>
#include "ActionSelectionState.h" // Transition back to action selection
#include "BattleEndState.h"       // To be implemented for battle end
#include <cstdlib>                // For rand()
#include <string>
#include <queue>

namespace Battle
{

    RunTurnState::RunTurnState() : currentStep(TurnStep::START)
    {
    }

    RunTurnState::~RunTurnState()
    {
    }

    void RunTurnState::enter(BattleSystem* owner)
    {
        std::cout << "Entering RunTurnState" << std::endl;
        this->battleSystemOwner = owner;
        currentStep = TurnStep::START;
    }

    void RunTurnState::handleEvent(BattleSystem* owner, sf::Event event)
    {
        // Input is handled by BattleSystem to advance the dialog
    }

    void RunTurnState::update(BattleSystem* owner)
    {
        if (owner->getDialogManager().isActive())
        {
            return; // Wait for messages to finish displaying
        }

        switch (currentStep)
        {
        case TurnStep::START:
            currentStep = TurnStep::PLAYER_ACTION;
            break;

        case TurnStep::PLAYER_ACTION:
        {
            // --- Player Action Execution ---
            std::queue<std::string> messages;
            switch (owner->getChosenAction())
            {
            case ActionType::Fight:
            {
                int playerDamage = owner->getPlayer().getAttack();
                owner->getEnemy().takeDamage(playerDamage);
                messages.push(owner->getPlayer().getBaseCharacter().getName() + " attacks for " + std::to_string(playerDamage) + " damage!");
                break;
            }
            case ActionType::Special:
                messages.push(owner->getPlayer().getBaseCharacter().getName() + " uses a special move!");
                // TODO: Implement actual special move logic
                break;
            case ActionType::Guard:
                messages.push(owner->getPlayer().getBaseCharacter().getName() + " is guarding!");
                // TODO: Implement guard status (e.g., damage reduction flag)
                break;
            case ActionType::Escape:
            {
                if (rand() % 2 == 0)
                {
                    messages.push("Escaped successfully!");
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    owner->getStateMachine().changeState(new BattleEndState(BattleResult::Escape));
                    return; // Battle is over
                }
                else
                {
                    messages.push("Failed to escape!");
                }
                break;
            }
            case ActionType::None:
                // Should not happen, but handle defensively
                break;
            }
            if (!messages.empty())
            {
                owner->getDialogManager().startDialog(new Dialog(messages));
            }
            currentStep = TurnStep::ENEMY_CHECK;
            break;
        }

        case TurnStep::ENEMY_CHECK:
            if (owner->getEnemy().getCurrentHealth() <= 0)
            {
                std::queue<std::string> messages;
                messages.push(owner->getEnemy().getBaseCharacter().getName() + " defeated!");
                owner->getDialogManager().startDialog(new Dialog(messages));
                owner->getStateMachine().changeState(new BattleEndState(BattleResult::Victory));
                return; // Battle is over
            }
            currentStep = TurnStep::ENEMY_ACTION;
            break;

        case TurnStep::ENEMY_ACTION:
        {
            // --- Enemy Action Execution (Simple AI: always attack) ---
            std::queue<std::string> messages;
            int enemyDamage = owner->getEnemy().getAttack();
            owner->getPlayer().takeDamage(enemyDamage);
            messages.push(owner->getEnemy().getBaseCharacter().getName() + " attacks for " + std::to_string(enemyDamage) + " damage!");
            owner->getDialogManager().startDialog(new Dialog(messages));
            currentStep = TurnStep::PLAYER_CHECK;
            break;
        }

        case TurnStep::PLAYER_CHECK:
            if (owner->getPlayer().getCurrentHealth() <= 0)
            {
                std::queue<std::string> messages;
                messages.push(owner->getPlayer().getBaseCharacter().getName() + " defeated!");
                owner->getDialogManager().startDialog(new Dialog(messages));
                owner->getStateMachine().changeState(new BattleEndState(BattleResult::Defeat));
                return; // Battle is over
            }
            currentStep = TurnStep::FINISH_TURN;
            break;

        case TurnStep::FINISH_TURN:
            owner->getStateMachine().changeState(new ActionSelectionState());
            break;
        }
    }

    void RunTurnState::draw(sf::RenderWindow& window)
    {
        if (battleSystemOwner && !battleSystemOwner->getDialogManager().isActive())
        {
            battleSystemOwner->getBattleUI().draw(window, -1); // -1 indicates no selection
        }
    }

    void RunTurnState::exit()
    {
        std::cout << "Exiting RunTurnState" << std::endl;
    }
} // namespace Battle
