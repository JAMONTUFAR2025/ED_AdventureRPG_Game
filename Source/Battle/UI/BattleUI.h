#ifndef BATTLE_BATTLEUI_H
#define BATTLE_BATTLEUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../../UI/DialogBox.h"
#include "../../Character/Character.h"
#include "ActionSelectionUI.h"

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /* Clase que representa la interfaz de usuario de la batalla */
    class BattleUI
    {
    private:
        /* Fuente para los textos de la UI */
        sf::Font font;
        /* Cuadro de dialogo para el titulo */
        DialogBox titleBox;

        /* Textos y barra de vida del jugador */
        sf::Text* player_nameText;
        sf::Text* player_levelText;
        sf::RectangleShape player_healthBarBack;
        sf::RectangleShape player_healthBarFront;
        sf::Text* player_healthText;

        /* Textos y barra de puntos de definitiva del jugador */
        sf::RectangleShape player_ppBarBack;
        sf::RectangleShape player_ppBarFront;
        sf::Text* player_ppText;

        /* Textos y barra de vida del enemigo */
        sf::Text* enemy_nameText;
        sf::Text* enemy_levelText;
        sf::RectangleShape enemy_healthBarBack;
        sf::RectangleShape enemy_healthBarFront;
        sf::Text* enemy_healthText;

        /* Texto de VS */
        sf::Text* vsText;
        /* Texto para mostrar el control para pasar al siguiente dialogo */
        sf::Text* dialogControlText;
    public:
        /* Constructor y destructor */
        BattleUI();
        ~BattleUI();

        /* Metodos para configurar, dibujar y actualizar la UI */
        void setup(Character& playerChar, Character& enemyChar);
        void draw(sf::RenderWindow& window, int selectedOption, bool isDialogActive);
        void updateHealthBars(Character& playerChar, Character& enemyChar);
        void updatePlayerLevelText(int newLevel);
        void updatePlayerUltimatePoints(int currentPP);

        /* Getters */
        sf::Text& getPlayerNameText();
        sf::Text& getEnemyNameText();
    };
} // namespace Battle

#endif // BATTLE_BATTLEUI_H
