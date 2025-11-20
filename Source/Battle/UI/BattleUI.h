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
    public:
        BattleUI();
        ~BattleUI();

        void setup(const Character& playerChar, const Character& enemyChar);
        void draw(sf::RenderWindow& window, int selectedOption);
        
        void updateHealthBars(const Character& playerChar, const Character& enemyChar);
        void updatePlayerLevelText(int newLevel);
        void updatePlayerUltimatePoints(int currentPP);

        const sf::Text& getPlayerNameText() const { return *player_nameText; }
        const sf::Text& getEnemyNameText() const { return *enemy_nameText; }
    };
} // namespace Battle

#endif // BATTLE_BATTLEUI_H
