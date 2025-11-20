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
        if (!font.openFromFile(GlobalSettings::FONT_PATH))
        {
            std::cerr << "Error al cargar " << GlobalSettings::FONT_PATH << std::endl;
            if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
            {
                std::cerr << "Error al cargar font C:/Windows/Fonts/arial.ttf" << std::endl;
                return;
            }
        }

        float startX = 70;
        float startY = 300;
        float spacing = 165.0f;

        // - - CAJA - -
        actionBox.setup(700.0f, 50.0f, 50, startY);

        // --- Action Selection UI ---
        std::vector<std::string> options = {"Luchar!", "Definitiva!", "Recargar!", "Escapar!"};


        for (size_t i = 0; i < options.size(); ++i)
        {
            sf::Text* optionText = new sf::Text(font, options[i], GlobalSettings::FONT_SIZE);
            optionText->setFillColor(sf::Color::White);
            optionText->setPosition(sf::Vector2f(startX + i * spacing, startY));
            optionTexts.push_back(optionText);
        }

        dialogBox.setup(700.0f, 150.0f, 50, 380);
    }

    void ActionSelectionUI::draw(sf::RenderWindow& window, int selectedOption)
    {
        actionBox.draw(window);

        // Draw action selection options
        for (size_t i = 0; i < optionTexts.size(); ++i)
        {
            string originalString = optionTexts[i]->getString();

            if (static_cast<int>(i) == selectedOption)
            {
                optionTexts[i]->setString("> " + originalString);
                optionTexts[i]->setFillColor(sf::Color::Yellow);
            }
            else
            {
                optionTexts[i]->setString("  " + originalString);
                optionTexts[i]->setFillColor(sf::Color::White);
            }
            window.draw(*optionTexts[i]);

            optionTexts[i]->setString(originalString);
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
