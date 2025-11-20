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

    RunTurnState::RunTurnState() : currentStep(TurnStep::START), expMessageQueued(false), levelUpOccurred(false)
    {
    }

    void RunTurnState::enter(BattleSystem* owner)
    {
        std::cout << "Entering RunTurnState" << std::endl;
        this->battleSystemOwner = owner;
        currentStep = TurnStep::START;
        owner->setPlayerGuarding(false); // Reset guard status at the start of the turn
        owner->getPlayer()->setDefenseMultiplier(1.0f); // Reset defense multiplier
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
        // Mensajes a encolar
        std::queue<std::string> messages;
        bool isCritical = false;

        switch (currentStep)
        {
            case TurnStep::START:
                currentStep = TurnStep::PLAYER_ACTION;
                break;

            case TurnStep::PLAYER_ACTION:
                isCritical = false;
                if(rand() % 100 < 20) isCritical = true;

                int playerDamage;
                switch (owner->getChosenAction())
                {
                    case ActionType::Fight:
                        playerDamage = owner->getEnemy().takeDamage(owner->getPlayer()->getCharacter(), owner->getEnemy().getDefense(), 10, isCritical);
                        messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " attacks for " + std::to_string(playerDamage) + " damage!");
                        if(isCritical) messages.push("A critical hit!");
                        break;
                    case ActionType::Special:
                        playerDamage = owner->getEnemy().takeDamage(owner->getPlayer()->getCharacter(), owner->getEnemy().getDefense(),  50, isCritical);
                        messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " uses a special move and it deals " + std::to_string(playerDamage) + "!");
                        if(isCritical) messages.push("A critical hit!");
                        break;
                    case ActionType::Guard:
                        messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " is guarding! Defense x2!");
                        owner->setPlayerGuarding(true);
                        owner->getPlayer()->setDefenseMultiplier(2.0f);
                        break;
                    case ActionType::Escape:
                        messages.push("Escaped successfully!");
                        owner->getDialogManager().startDialog(new Dialog(messages));
                        result = BattleResult::Escape;
                        currentStep = TurnStep::SHOW_EXP_RESULTS;
                        return;
                    case ActionType::None:
                        break;
                }

                if (!messages.empty()) owner->getDialogManager().startDialog(new Dialog(messages));
                currentStep = TurnStep::ENEMY_CHECK;
                break;

            case TurnStep::ENEMY_CHECK:
                owner->setHasHealthBarUpdated(true);
                if (owner->getEnemy().getCurrentHealth() <= 0)
                {
                    messages.push(owner->getEnemy().getBaseCharacter().getName() + " defeated!");
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    result = BattleResult::Victory;
                    currentStep = TurnStep::SHOW_EXP_RESULTS;
                    return;
                }
                currentStep = TurnStep::ENEMY_ACTION;
                break;

            case TurnStep::ENEMY_ACTION:
            {
                isCritical = false;
                if(rand() % 100 < 20) isCritical = true;
                int enemyDamage = owner->getPlayer()->getCharacter().takeDamage(owner->getEnemy(), owner->getPlayer()->getDefense(), 10, isCritical);
                messages.push(owner->getEnemy().getBaseCharacter().getName() + " attacks for " + std::to_string(enemyDamage) + " damage!");
                if(isCritical) messages.push("A critical hit!");
                owner->getDialogManager().startDialog(new Dialog(messages));
                currentStep = TurnStep::PLAYER_CHECK;
                break;
            }

            case TurnStep::PLAYER_CHECK:
                owner->setHasHealthBarUpdated(true);
                if (owner->getPlayer()->getCharacter().getCurrentHealth() <= 0)
                {
                    messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " defeated!");
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    result = BattleResult::Defeat;
                    currentStep = TurnStep::SHOW_EXP_RESULTS;
                    return;
                }
                currentStep = TurnStep::FINISH_TURN;
                break;

            case TurnStep::FINISH_TURN:
                owner->getPlayer()->setDefenseMultiplier(1.0f);
                owner->setPlayerGuarding(false);
                owner->getStateMachine().changeState(new ActionSelectionState());
                break;
            
            case TurnStep::SHOW_EXP_RESULTS:
                if (owner->getDialogManager().isActive()) break;

                if (!expMessageQueued)
                {
                    int expGained = 0;
                    int oldLevel, newLevel;
                    switch(result)
                    {
                        case BattleResult::Victory:
                            expGained = owner->getEnemy().getBaseCharacter().getExpYield();
                            messages.push("Victory!\n\nPlayer gained " + std::to_string(expGained) + " EXP!");

                            oldLevel = owner->getPlayer()->getCharacter().getLevel();
                            owner->getPlayer()->gainExperience(expGained);
                            newLevel = owner->getPlayer()->getCharacter().getLevel();

                            if (newLevel > oldLevel) levelUpOccurred = true;
                            break;
                        case BattleResult::Defeat:
                            messages.push("Defeat!");
                            break;
                        case BattleResult::Escape:
                            // No message needed, already shown
                            break;
                    }
                    if (!messages.empty()) owner->getDialogManager().startDialog(new Dialog(messages));
                    expMessageQueued = true;
                }
                else
                {
                    currentStep = TurnStep::SHOW_LEVEL_UP_RESULTS;
                }
                break;

            case TurnStep::SHOW_LEVEL_UP_RESULTS:
                if (owner->getDialogManager().isActive()) break;

                if (levelUpOccurred)
                {
                    messages.push("Player leveled up to level " + std::to_string(owner->getPlayer()->getCharacter().getLevel()) + "!");
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    owner->setHasHealthBarUpdated(true);
                    owner->setHasPlayerLeveledUp(true); // Set the flag right before the level up message is shown
                }
                currentStep = TurnStep::FINALIZE_BATTLE;
                break;

            case TurnStep::FINALIZE_BATTLE:
                if (owner->getDialogManager().isActive()) break;

                owner->endBattle();
                
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
