#include "ActionSelectionState.h"
#include <iostream>
#include "RunTurnState.h"
#include "../UI/ActionSelectionUI.h"

namespace Battle
{
    ActionSelectionState::ActionSelectionState() : selectedOption(0), battleSystemOwner(nullptr)
    {
    }

    void ActionSelectionState::enter(BattleSystem* owner)
    {
        this->battleSystemOwner = owner;
        this->battleSystemOwner->getBattleUI().setup(this->battleSystemOwner->getPlayer()->getCharacter(), this->battleSystemOwner->getEnemy());
        this->battleSystemOwner->getBattleUI().updatePlayerUltimatePoints(this->battleSystemOwner->getPlayer()->getUltimatePoints());
        actionSelectionUI.setup();
    }

    void ActionSelectionState::handleEvent(BattleSystem* owner, sf::Event event)
    {
        if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::A)
            {
                selectedOption = (selectedOption - 1 + 4) % 4;

            }
            else if (keyPressed->code == sf::Keyboard::Key::D)
            {
                selectedOption = (selectedOption + 1) % 4;
            }
            else if (keyPressed->code == sf::Keyboard::Key::E)
            {
                switch (selectedOption)
                {
                    case 0: // Luchar
                        owner->setChosenAction(ActionType::Fight);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                    case 1: // Especial
                        owner->setChosenAction(ActionType::Special);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                    case 2: // En Guardia
                        owner->setChosenAction(ActionType::Guard);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                    case 3: // Escapar
                        owner->setChosenAction(ActionType::Escape);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                }
            }
        }
    }

    void ActionSelectionState::update(BattleSystem* owner)
    {
        actionSelectionUI.updateDialogBoxDescription(selectedOption);
    }

    void ActionSelectionState::draw(sf::RenderWindow& window)
    {
        actionSelectionUI.draw(window, selectedOption);
    }

    void ActionSelectionState::exit()
    {
    }
} // namespace Battle

