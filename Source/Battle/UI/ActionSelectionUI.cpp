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
        // - - CAJA - -
        // Configura el tamanio del rectangulo
        box.setSize(Vector2f(700, 50));
        // Establece el relleno en color negro con un poco de transparencia
        box.setFillColor(Color(0, 0, 0, 150));
        // Establece el color del borde en blanco
        box.setOutlineColor(Color::White);
        // Establece el grosor del borde en 6 pixeles
        box.setOutlineThickness(6);
        // Establece la posicion del rectangulo
        box.setPosition({50, 300});

        // --- Action Selection UI ---
        std::vector<std::string> options = {"A luchar!", "Definitiva!", "En guardia!", "A escapar!"};

        float startX = 70;
        float startY = 300;
        float spacing = 165.0f;

        for (size_t i = 0; i < options.size(); ++i)
        {
            sf::Text* optionText = new sf::Text(font, options[i], GlobalSettings::FONT_SIZE);
            optionText->setFillColor(sf::Color::White);
            optionText->setPosition(sf::Vector2f(startX + i * spacing, startY));
            optionTexts.push_back(optionText);
        }

        dialogBox.setup();
    }

    void ActionSelectionUI::draw(sf::RenderWindow& window, int selectedOption)
    {
        window.draw(box);

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
