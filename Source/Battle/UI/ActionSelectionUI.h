#ifndef BATTLE_ACTIONSELECTIONUI_H
#define BATTLE_ACTIONSELECTIONUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../../UI/DialogBox.h" // Assuming DialogBox is in the main UI directory

namespace Battle
{
    class ActionSelectionUI
    {
    private:
        /* Rectangulo que representa la caja de acciones */
        DialogBox actionBox;
        sf::Font font;
        std::vector<sf::Text*> optionTexts;
        std::vector<std::string> optionDescriptions;
        DialogBox dialogBox;
        
        public:
        ActionSelectionUI();
        ~ActionSelectionUI();
        
        void setup();
        void draw(sf::RenderWindow& window, int selectedOption);
        void updateDialogBoxDescription(int selectedOption);
    };
} // namespace Battle

#endif // BATTLE_ACTIONSELECTIONUI_H
