#include "ActionSelectionUI.h"
#include "../../Gameplay/GlobalSettings.h" // For screen dimensions
#include <iostream>

namespace Battle
{
    ActionSelectionUI::ActionSelectionUI()
    {
        optionDescriptions.push_back("Ejecuta un ataque basico.\nPotencia: 50 \nRecargas 1 punto de definitiva.");
        optionDescriptions.push_back("Ejecuta un potente ataque especial. \nPotencia: 150 \nCosto: 5 puntos de definitiva." );
        optionDescriptions.push_back("Fortaleces tu cuerpo y concentras energia. \nEfecto: Duplicas tu defensa este turno. \nRecargas 2 puntos de definitiva.");
        optionDescriptions.push_back("Por si las cosas se complican. \nEfecto: Escapas y terminas el combate. \nNo ganaras experiencia ni puntos.");
    }

    ActionSelectionUI::~ActionSelectionUI()
    {
        for (sf::Text* text : optionTexts)
        {
            delete text;
        }

        for (sf::Text* text : controlsTexts)
        {
            delete text;
        }

        optionTexts.clear();
        controlsTexts.clear();
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
        std::vector<std::string> options = {"Luchar!", "Definitiva!", "En guardia!", "Escapar!"};


        for (int i = 0; i < options.size(); i++)
        {
            sf::Text* optionText = new sf::Text(font, options[i], GlobalSettings::FONT_SIZE);
            optionText->setFillColor(sf::Color::White);
            optionText->setPosition(sf::Vector2f(startX + i * spacing, startY));
            optionTexts.push_back(optionText);
        }

        // Lista de controles
        std::vector<std::string> controls = {
            "A / D - Cambiar opcion.",
            "E - Seleccionar opcion."
        };

        // Creamos los textos para cada control
        for (int i = 0; i < controls.size(); i++)
        {
            sf::Text* controlText = new sf::Text(font, controls[i], GlobalSettings::FONT_SIZE);
            controlText->setFillColor(sf::Color::White);
            // Spacing = 330 para que queden separados
            // Para llegar a Y = 550
            controlText->setPosition(sf::Vector2f(startX + i * (spacing + 165.0f), startY + 250.0f));
            controlsTexts.push_back(controlText);
        }

        dialogBox.setup(700.0f, 150.0f, 50, 380);
    }

    void ActionSelectionUI::draw(sf::RenderWindow& window, int selectedOption)
    {
        actionBox.draw(window);

        // Draw action selection options
        for (int i = 0; i < optionTexts.size(); i++)
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
        
        // Draw controls
        for (sf::Text* controlText : controlsTexts)
        {
            window.draw(*controlText);
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
