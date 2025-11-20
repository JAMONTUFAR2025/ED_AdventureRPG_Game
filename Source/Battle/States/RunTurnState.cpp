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
                if (!owner->getBattleStarted())
                {
                    messages.push("Te has encontrado con un/una " + owner->getEnemy().getBaseCharacter().getName() + "!");
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    owner->setBattleStarted(true);
                    currentStep = TurnStep::POST_INTRO_MESSAGE;
                }
                else
                {
                    currentStep = TurnStep::PLAYER_ACTION;
                }
                break;
            
            case TurnStep::POST_INTRO_MESSAGE:
                if (!owner->getDialogManager().isActive())
                {
                    owner->getStateMachine().changeState(new ActionSelectionState());
                }
                break;

            case TurnStep::PLAYER_ACTION:
            {
                isCritical = false;
                if(rand() % 100 < 20) isCritical = true;

                int playerDamage = 0;
                bool validAction = true;
                switch (owner->getChosenAction())
                {
                    case ActionType::Fight:
                        owner->getPlayer()->gainUltimatePoints(1);
                        playerDamage = owner->getEnemy().takeDamage(owner->getPlayer()->getCharacter(), owner->getEnemy().getDefense(), 50, isCritical);
                        messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " ha usado un ataque basico! \nDanio infligido: " + std::to_string(playerDamage));
                        if(isCritical) messages.push("Un golpe critico!");
                        break;
                    case ActionType::Special:
                        if (owner->getPlayer()->getUltimatePoints() >= 5)
                        {
                            owner->getPlayer()->useUltimate(5);
                            playerDamage = owner->getEnemy().takeDamage(owner->getPlayer()->getCharacter(), owner->getEnemy().getDefense(),  150, isCritical);
                            messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " ha usado un poderoso ataque definitivo! \nDanio infligido: " + std::to_string(playerDamage));
                            if(isCritical) messages.push("Un golpe critico devastador!");
                        }
                        else
                        {
                            messages.push("No tienes suficientes puntos de definitiva!");
                            validAction = false;
                        }
                        break;
                    case ActionType::Guard:
                        owner->getPlayer()->gainUltimatePoints(2);
                        
                        messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " ha fortalecido su cuerpo!");
                        owner->setPlayerGuarding(true);
                        owner->getPlayer()->setDefenseMultiplier(2.0f);
                        break;
                    case ActionType::Escape:
                        messages.push("Escapaste sin problemas!");
                        owner->getDialogManager().startDialog(new Dialog(messages));
                        result = BattleResult::Escape;
                        currentStep = TurnStep::SHOW_EXP_RESULTS;
                        return;
                    case ActionType::None:
                        validAction = false;
                        break;
                }

                if (!messages.empty()) owner->getDialogManager().startDialog(new Dialog(messages));
                
                if (validAction) 
                {
                    currentStep = TurnStep::ENEMY_CHECK;
                }
                else
                {
                    currentStep = TurnStep::INVALID_ACTION;
                }
            }
            break;

            case TurnStep::INVALID_ACTION:
                if (!owner->getDialogManager().isActive())
                {
                    owner->getStateMachine().changeState(new ActionSelectionState());
                }
                break;

            case TurnStep::ENEMY_CHECK:
                // Actualizar la barra de vida del enemigo
                owner->setHasHealthBarUpdated(true);
                // Actualizar los puntos de definitiva del jugador
                owner->setHasUltimatePointsUpdated(true);
                if (owner->getEnemy().getCurrentHealth() <= 0)
                {
                    messages.push(owner->getEnemy().getBaseCharacter().getName() + " ha sido derrotado!");
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
                int enemyDamage = owner->getPlayer()->getCharacter().takeDamage(owner->getEnemy(), owner->getPlayer()->getDefense(), 50, isCritical);
                messages.push(owner->getEnemy().getBaseCharacter().getName() + " lanzo un ataque! \nDanio infligido: " + std::to_string(enemyDamage));
                if(isCritical) messages.push("Un golpe critico!");
                owner->getDialogManager().startDialog(new Dialog(messages));
                currentStep = TurnStep::PLAYER_CHECK;
                break;
            }

            case TurnStep::PLAYER_CHECK:
                owner->setHasHealthBarUpdated(true);
                if (owner->getPlayer()->getCharacter().getCurrentHealth() <= 0)
                {
                    messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " ha sido derrotado...");
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
                    switch(result)
                    {
                        case BattleResult::Victory:
                        {
                            messages.push("Victoria!");
                            int expGained = owner->getEnemy().getBaseCharacter().getExpYield() * (1 + owner->getEnemy().getLevel() / 5);
                            messages.push("Has ganado " + std::to_string(expGained) + " puntos de experiencia!");

                            int enemyPoints = owner->getEnemy().getBaseCharacter().getPointsYield() * (1 + owner->getEnemy().getLevel() / 5);
                            owner->getPlayer()->gainPoints(enemyPoints);
                            messages.push("Tambien has ganado " + std::to_string(enemyPoints) + " puntos de jugador!");

                            int oldLevel = owner->getPlayer()->getCharacter().getLevel();
                            owner->getPlayer()->gainExperience(expGained);
                            int newLevel = owner->getPlayer()->getCharacter().getLevel();

                            if (newLevel > oldLevel) levelUpOccurred = true;
                        }
                        
                        break;

                        case BattleResult::Defeat:
                            messages.push("Estas fuera de combate!");
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
                    messages.push("Has subido al nivel " + std::to_string(owner->getPlayer()->getCharacter().getLevel()) + "!");
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    owner->setHasHealthBarUpdated(true);
                    owner->setHasPlayerLeveledUp(true);
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
