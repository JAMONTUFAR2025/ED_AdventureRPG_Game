#include "RunTurnState.h"
#include <iostream>
#include "ActionSelectionState.h" // Transition back to action selection
#include "../../GameStates/GameMenuState.h"
#include "../../GameController.h"
#include <string>
#include <queue>

namespace Battle
{

    RunTurnState::RunTurnState() : currentStep(TurnStep::START), finalMessageQueued(false)
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
                messages.push("Escaped successfully!");
                owner->getDialogManager().startDialog(new Dialog(messages));
                result = BattleResult::Escape;
                currentStep = TurnStep::BATTLE_END;
                return; // Battle is over
                
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
                result = BattleResult::Victory;
                currentStep = TurnStep::BATTLE_END;
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
                result = BattleResult::Defeat;
                currentStep = TurnStep::BATTLE_END;
                return; // Battle is over
            }
            currentStep = TurnStep::FINISH_TURN;
            break;

        case TurnStep::FINISH_TURN:
            owner->getStateMachine().changeState(new ActionSelectionState());
            break;
        
        case TurnStep::BATTLE_END:
            {
                if (!finalMessageQueued)
                {
                    std::queue<std::string> messages;
                    switch(result)
                    {
                        case BattleResult::Victory:
                        {
                            int expGained = owner->getEnemy().getBaseCharacter().getExpYield();
                            owner->getPlayer().gainExperience(expGained);
                            messages.push("Victory!\n\nPlayer gained " + std::to_string(expGained) + " EXP!");
                            break;
                        }
                        case BattleResult::Defeat:
                            messages.push("Defeat!");
                            break;
                        case BattleResult::Escape:
                            // This message is already pushed when escaping, so we might not need a duplicate.
                            // However, to keep the logic consolidated, we'll handle it here.
                            // The escape message will be shown, then this one.
                            // Let's just transition. The "Escaped!" message is sufficient.
                            break;
                    }
                    if (!messages.empty())
                    {
                        owner->getDialogManager().startDialog(new Dialog(messages));
                    }
                    finalMessageQueued = true;
                }
                else
                {
                    if (!owner->getDialogManager().isActive())
                    {
                        // Now that the final message is done, signal that the battle is over
                        owner->endBattle();
                    }
                }
            }
            break;
        }
    }

    void RunTurnState::draw(sf::RenderWindow& window)
    {
    }

    void RunTurnState::exit()
    {
        std::cout << "Exiting RunTurnState" << std::endl;
    }
} // namespace Battle
