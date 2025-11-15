#ifndef BATTLE_BATTLEUI_H
#define BATTLE_BATTLEUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../../UI/DialogBox.h" // Assuming DialogBox is in the main UI directory
#include "../../Character/Character.h" // To get character info

namespace Battle
{
    /**
     * @brief UI for action selection and general battle display.
     */
    class BattleUI
    {
    private:
        sf::Font font;

        // Action selection elements
        std::vector<sf::Text*> optionTexts;
        std::vector<std::string> optionDescriptions;
        DialogBox dialogBox;

        // Player UI elements
        sf::Text* player_nameText;
        sf::RectangleShape player_healthBarBack;
        sf::RectangleShape player_healthBarFront;
        sf::Text* player_healthText;

        // Enemy UI elements
        sf::Text* enemy_nameText;
        sf::RectangleShape enemy_healthBarBack;
        sf::RectangleShape enemy_healthBarFront;
        sf::Text* enemy_healthText;


    public:
        BattleUI();
        ~BattleUI();

        void setup(const Character& playerChar, const Character& enemyChar);
        void draw(sf::RenderWindow& window, int selectedOption, const Character& playerChar, const Character& enemyChar);
        void updateDialogBoxDescription(int selectedOption);
        void updateHealthBars(const Character& playerChar, const Character& enemyChar);
        void displayBattleMessage(const std::string& message);

        // Getters for Text elements
        const sf::Text& getPlayerNameText() const { return *player_nameText; }
        const sf::Text& getEnemyNameText() const { return *enemy_nameText; }
    };
} // namespace Battle

#endif // BATTLE_BATTLEUI_H
