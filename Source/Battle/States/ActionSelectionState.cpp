#include "ActionSelectionState.h"
#include <iostream>
#include "RunTurnState.h" // Transition to RunTurnState after action selection
#include "../UI/ActionSelectionUI.h" // For ActionSelectionUI

namespace Battle
{
    ActionSelectionState::ActionSelectionState() : selectedOption(0), battleSystemOwner(nullptr)
    {
    }

    void ActionSelectionState::enter(BattleSystem* owner)
    {
        this->battleSystemOwner = owner;
        std::cout << "Entering ActionSelectionState" << std::endl;
        this->battleSystemOwner->getBattleUI().setup(this->battleSystemOwner->getPlayer()->getCharacter(), this->battleSystemOwner->getEnemy()); // Setup BattleUI with current characters
        this->battleSystemOwner->getBattleUI().updatePlayerUltimatePoints(this->battleSystemOwner->getPlayer()->getUltimatePoints());
        actionSelectionUI.setup();
    }

    void ActionSelectionState::handleEvent(BattleSystem* owner, sf::Event event)
    {
        if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Left)
            {
                selectedOption = (selectedOption - 1 + 4) % 4; // 4 is the number of options

            }
            else if (keyPressed->code == sf::Keyboard::Key::Right)
            {
                selectedOption = (selectedOption + 1) % 4; // 4 is the number of options
            }
            else if (keyPressed->code == sf::Keyboard::Key::Z)
            {
                switch (selectedOption)
                {
                    case 0: // Luchar
                        std::cout << "Player selected: Luchar" << std::endl;
                        owner->setChosenAction(ActionType::Fight);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                    case 1: // Especial
                        std::cout << "Player selected: Especial" << std::endl;
                        owner->setChosenAction(ActionType::Special);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                    case 2: // En Guardia
                        std::cout << "Player selected: En Guardia" << std::endl;
                        owner->setChosenAction(ActionType::Guard);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                    case 3: // Escapar
                        std::cout << "Player selected: Escapar" << std::endl;
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
        std::cout << "Exiting ActionSelectionState" << std::endl;
    }
} // namespace Battle

