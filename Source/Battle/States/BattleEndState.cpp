#include "BattleEndState.h"
#include "../../GameController.h" // For GameController to change main states
#include "../../GameStates/GameMenuState.h" // Assuming we transition back to game menu
#include "../../Gameplay/GlobalSettings.h"
#include <iostream>

namespace Battle
{
    BattleEndState::BattleEndState(BattleResult result)
        : result(result), isMessageDisplayed(false), messageText(nullptr) // Initialize messageText to nullptr
    {
    }

    BattleEndState::~BattleEndState()
    {
        delete messageText;
    }

    void BattleEndState::enter(BattleSystem* owner)
    {
        std::cout << "Entering BattleEndState. Result: ";
        std::string message;

        if (!font.openFromFile("Assets/fonts/font.otf"))
        {
            std::cerr << "Error al cargar Assets/fonts/font.otf" << std::endl;
        }

        switch (result)
        {
            case BattleResult::Victory:
            {
                int expGained = owner->getEnemy().getBaseCharacter().getExpYield();
                owner->getPlayer().gainExperience(expGained);
                message = "Victory!\n\nPlayer gained " + std::to_string(expGained) + " EXP!";
                std::cout << "Victory! Player gained " << expGained << " EXP!" << std::endl;
                break;
            }
            case BattleResult::Defeat:
                message = "Defeat!";
                std::cout << "Defeat!" << std::endl;
                break;
            case BattleResult::Escape:
                message = "Escaped!";
                std::cout << "Escaped!" << std::endl;
                break;
        }

        messageText = new sf::Text(font, message + "\n\nPress Z to continue...", 50); // New the messageText
        messageText->setFont(font);
        messageText->setCharacterSize(50);
        messageText->setFillColor(sf::Color::White);
        messageText->setString(message + "\n\nPress Z to continue...");
        
        // Center the text
        sf::FloatRect textRect = messageText->getLocalBounds();
        messageText->setOrigin(sf::Vector2f(textRect.position.x + textRect.position.x / 2.0f, textRect.position.y + textRect.position.y / 2.0f));
        messageText->setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH / 2.0f, GlobalSettings::SCREEN_HEIGHT / 2.0f));

        isMessageDisplayed = true;
    }

    void BattleEndState::handleEvent(BattleSystem* owner, sf::Event event)
    {
        if (isMessageDisplayed)
        {
            if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Z)
                {
                    std::cout << "Transitioning out of BattleSystem..." << std::endl;
                    owner->owner->stateMachine.changeState(new GameMenuState());
                }
            }
        }
    }

    void BattleEndState::update(BattleSystem* owner)
    {
        // No update logic needed
    }

    void BattleEndState::draw(sf::RenderWindow& window)
    {
        if (isMessageDisplayed && messageText)
        {
            window.draw(*messageText);
        }
    }

    void BattleEndState::exit()
    {
        std::cout << "Exiting BattleEndState" << std::endl;
    }
} // namespace Battle
