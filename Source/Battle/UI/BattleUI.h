#ifndef BATTLE_BATTLEUI_H
#define BATTLE_BATTLEUI_H

#include <SFML/Graphics.hpp>
#include "../../Character/Character.h"
#include "../../Gameplay/GlobalSettings.h"
#include "../../UI/DialogBox.h"
#include "ActionSelectionUI.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /* Clase que representa la interfaz de usuario de la batalla */
    class BattleUI
    {
    private:
        /* Fuente para los textos de la UI */
        Font font;
        /* Cuadro de dialogo para el titulo */
        DialogBox titleBox;

        /* Textos y barra de vida del jugador */
        Text* player_nameText;
        Text* player_levelText;
        RectangleShape player_healthBarBack;
        RectangleShape player_healthBarFront;
        Text* player_healthText;

        /* Textos y barra de puntos de definitiva del jugador */
        RectangleShape player_ppBarBack;
        RectangleShape player_ppBarFront;
        Text* player_ppText;

        /* Textos y barra de vida del enemigo */
        Text* enemy_nameText;
        Text* enemy_levelText;
        RectangleShape enemy_healthBarBack;
        RectangleShape enemy_healthBarFront;
        Text* enemy_healthText;

        /* Texto de VS */
        Text* vsText;
        /* Texto para mostrar el control para pasar al siguiente dialogo */
        Text* dialogControlText;
    public:
        /* Constructor y destructor */
        BattleUI();
        ~BattleUI();

        /* Metodos para configurar, dibujar y actualizar la UI */
        void setup(Character& playerChar, Character& enemyChar);
        void draw(RenderWindow& window, int selectedOption, bool isDialogActive);
        void updateHealthBars(Character& playerChar, Character& enemyChar);
        void updatePlayerLevelText(int newLevel);
        void updatePlayerUltimatePoints(int currentPP);

        /* Getters */
        Text& getPlayerNameText();
        Text& getEnemyNameText();
    };
} // namespace Battle

#endif // BATTLE_BATTLEUI_H
