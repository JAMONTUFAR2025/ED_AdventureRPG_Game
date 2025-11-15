#include "ActionSelectionUI.h"
#include "../../Gameplay/GlobalSettings.h" // For screen dimensions
#include <iostream>

namespace Battle
{
    ActionSelectionUI::ActionSelectionUI()
    {
        optionDescriptions.push_back("Ataca al enemigo con tu arma.");
        optionDescriptions.push_back("Usa una de tus habilidades especiales.");
        optionDescriptions.push_back("Reduce el dano recibido en el proximo turno.");
        optionDescriptions.push_back("Intenta huir de la batalla.");
    }

    ActionSelectionUI::~ActionSelectionUI()
    {
        for (sf::Text* text : optionTexts)
        {
            delete text;
        }
        optionTexts.clear();
    }

    void ActionSelectionUI::setup()
    {
        if (!font.openFromFile("Assets/fonts/font.otf"))
        {
            std::cerr << "Error al cargar Assets/fonts/font.otf" << std::endl;
            if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
            {
                std::cerr << "Error al cargar font C:/Windows/Fonts/arial.ttf" << std::endl;
                return;
            }
        }

        std::vector<std::string> options = {"Luchar", "Especial", "En Guardia", "Escapar"};

        float startX = GlobalSettings::SCREEN_WIDTH * 0.7f; // Right side of the screen
        float startY = GlobalSettings::SCREEN_HEIGHT * 0.7f; // Bottom part of the screen
        float spacing = 30.0f;

        for (size_t i = 0; i < options.size(); ++i)
        {
            sf::Text* optionText = new sf::Text(font, options[i], 24);
            optionText->setFillColor(sf::Color::White);
            optionText->setPosition(sf::Vector2f(startX, startY + i * spacing));
            optionTexts.push_back(optionText);
        }

        dialogBox.setup();
        // Position the dialog box appropriately for battle UI
        // Assuming it needs to be higher up than in the main menu
        // Need to adjust DialogBox position, current setup is fixed
        // For now, it will use its default position.
    }

    void ActionSelectionUI::draw(sf::RenderWindow& window, int selectedOption)
    {
        for (size_t i = 0; i < optionTexts.size(); ++i)
        {
            if (static_cast<int>(i) == selectedOption)
            {
                optionTexts[i]->setFillColor(sf::Color::Yellow);
            }
            else
            {
                optionTexts[i]->setFillColor(sf::Color::White);
            }
            window.draw(*optionTexts[i]);
        }
        dialogBox.draw(window);
    }

    void ActionSelectionUI::updateDialogBoxDescription(int selectedOption)
    {
        if (selectedOption >= 0 && selectedOption < optionDescriptions.size())
        {
            dialogBox.setText(optionDescriptions[selectedOption]);
        }
    }
} // namespace Battle
