#include "MainMenuState.h"
#include "../GameController.h"
#include <iostream>
#include <vector>
#include <string>

MainMenuState::MainMenuState() : titleText(nullptr), selectedOption(0)
{
}

void MainMenuState::enter(GameController* owner)
{
    std::cout << "Entering MainMenuState" << std::endl;

    if (!titleFont.openFromFile("Assets/fonts/font.otf"))
    {
        std::cerr << "Error loading font Assets/fonts/font.otf" << std::endl;
        // Fallback to a default font
        if (!titleFont.openFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            std::cerr << "Error loading fallback font C:/Windows/Fonts/arial.ttf" << std::endl;
            return;
        }
    }
    optionsFont = titleFont;

    titleText = new sf::Text(titleFont, "Adventure RPG", 64);
    titleText->setFillColor(sf::Color::White);
    sf::FloatRect titleRect = titleText->getLocalBounds();
    titleText->setOrigin({titleRect.position.x + titleRect.size.x / 2.0f, titleRect.position.y + titleRect.size.y / 2.0f});
    titleText->setPosition(sf::Vector2f(owner->window.getSize().x / 2.0f, owner->window.getSize().y / 4.0f));

    std::vector<std::string> options = {"Jugar", "Salir"};
    for (int i = 0; i < options.size(); ++i)
    {
        sf::Text* option = new sf::Text(optionsFont, options[i], 32);
        option->setFillColor(sf::Color::White);
        sf::FloatRect optionRect = option->getLocalBounds();
        option->setOrigin({optionRect.position.x + optionRect.size.x / 2.0f, optionRect.position.y + optionRect.size.y / 2.0f});
        option->setPosition(sf::Vector2f(owner->window.getSize().x / 2.0f, owner->window.getSize().y / 2.0f + i * 50));
        optionTexts.push_back(option);
    }
}

void MainMenuState::execute(GameController* owner, sf::Event event)
{
    if (const auto keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Up)
        {
            if (selectedOption > 0)
            {
                selectedOption--;
            }
        }
        else if (keyPressed->code == sf::Keyboard::Key::Down)
        {
            if (selectedOption < optionTexts.size() - 1)
            {
                selectedOption++;
            }
        }
        else if (keyPressed->code == sf::Keyboard::Key::Z)
        {
            if (selectedOption == 0)
            {
                std::cout << "Selected: Jugar" << std::endl;
            }
            else if (selectedOption == 1)
            {
                std::cout << "Selected: Salir" << std::endl;
                owner->window.close();
            }
        }
    }
}

void MainMenuState::draw(sf::RenderWindow& window)
{
    if(titleText)
        window.draw(*titleText);

    for (int i = 0; i < optionTexts.size(); ++i)
    {
        if (i == selectedOption)
        {
            optionTexts[i]->setFillColor(sf::Color::Yellow);
        }
        else
        {
            optionTexts[i]->setFillColor(sf::Color::White);
        }
        window.draw(*optionTexts[i]);
    }
}

void MainMenuState::exit()
{
    std::cout << "Exiting MainMenuState" << std::endl;
    delete titleText;
    for(auto& option : optionTexts)
    {
        delete option;
    }
    optionTexts.clear();
}

const char* MainMenuState::getName() const
{
    return "MainMenuState";
}
