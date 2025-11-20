#ifndef BATTLE_BATTLEUI_H
#define BATTLE_BATTLEUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../../UI/DialogBox.h" // Assuming DialogBox is in the main UI directory
#include "../../Character/Character.h" // To get character info
#include "ActionSelectionUI.h" // For ActionSelectionUI

namespace Battle
{
    class BattleUI
    {
    private:
        sf::Font font;
        
        DialogBox titleBox;

        sf::Text* player_nameText;
        sf::Text* player_levelText;
        sf::RectangleShape player_healthBarBack;
        sf::RectangleShape player_healthBarFront;
        sf::Text* player_healthText;

        // Ultimate Points (PP) UI elements
        sf::RectangleShape* player_ppBarBack;
        sf::RectangleShape* player_ppBarFront;
        sf::Text* player_ppText;

        sf::Text* enemy_nameText;
        sf::Text* enemy_levelText;
        sf::RectangleShape enemy_healthBarBack;
        sf::RectangleShape enemy_healthBarFront;
        sf::Text* enemy_healthText;

        sf::Text* vsText;

        sf::Text* dialogControlText; // New member for dialog control text
    public:
        BattleUI();
        ~BattleUI();

        void setup(Character& playerChar, Character& enemyChar);
        void draw(sf::RenderWindow& window, int selectedOption, bool isDialogActive);
        
        void updateHealthBars(Character& playerChar, Character& enemyChar);
        void updatePlayerLevelText(int newLevel);
        void updatePlayerUltimatePoints(int currentPP);

        sf::Text& getPlayerNameText() { return *player_nameText; }
        sf::Text& getEnemyNameText() { return *enemy_nameText; }
    };
} // namespace Battle

#endif // BATTLE_BATTLEUI_H
