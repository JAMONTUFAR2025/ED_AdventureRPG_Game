#include "RunTurnState.h"
#include <iostream>
#include "ActionSelectionState.h" // Transition back to action selection
#include "../../GameStates/GameMenuState.h"
#include "../../GameController.h"
#include <string>
#include <queue>
#include <cstdlib> // For rand()

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
        owner->setPlayerGuarding(false); // Reset guard status at the start of the turn
        owner->getPlayer().setDefenseMultiplier(1.0f); // Reset defense multiplier
        std::cout << "[DEBUG] RunTurnState::enter - Defense multiplier reset to: " << owner->getPlayer().getDefenseMultiplier() << std::endl;
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
            int playerDamage;
            // --- Player Action Execution ---
            std::queue<std::string> messages;
            switch (owner->getChosenAction())
            {
            case ActionType::Fight:
            {
                playerDamage = owner->getEnemy().takeDamage(owner->getPlayer(), 10);
                messages.push(owner->getPlayer().getBaseCharacter().getName() + " attacks for " + std::to_string(playerDamage) + " damage!");
                break;
            }
            case ActionType::Special:
                playerDamage = owner->getEnemy().takeDamage(owner->getPlayer(), 50);
                messages.push(owner->getPlayer().getBaseCharacter().getName() + " uses a special move and it deals " + std::to_string(playerDamage) + "!");
                // TODO: Implement actual special move logic
                break;
            case ActionType::Guard:
                messages.push(owner->getPlayer().getBaseCharacter().getName() + " is guarding! Defense x2!");
                owner->setPlayerGuarding(true);
                owner->getPlayer().setDefenseMultiplier(2.0f); // Double defense for this turn
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
            std::cout << "[DEBUG] RunTurnState::PLAYER_ACTION - Multiplier is: " << owner->getPlayer().getDefenseMultiplier() << std::endl;
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
            std::cout << "[DEBUG] RunTurnState::ENEMY_ACTION - Multiplier before attack is: " << owner->getPlayer().getDefenseMultiplier() << std::endl;
            int enemyDamage = owner->getPlayer().takeDamage(owner->getEnemy(), 10);
            
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
            owner->getPlayer().setDefenseMultiplier(1.0f); // Reset defense multiplier after turn
            owner->setPlayerGuarding(false); // Reset guarding status after turn
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
