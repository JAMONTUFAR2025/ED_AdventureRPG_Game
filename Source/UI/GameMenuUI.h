#ifndef GAMEMENUUI_H
#define GAMEMENUUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "DialogBox.h"
#include "../Character/Player.h" // Incluir la definición completa de Player

using namespace sf;
using namespace std;

// Forward declaration to avoid circular dependencies
class GameController;

/**
 * Clase para manejar la UI del Menu del Juego
 */
class GameMenuUI
{
private:
    /* Fuente */
    Font font;
    
    DialogBox titleBox;

    /* Texto de las opciones del menu */
    vector<Text*> optionTexts;
    /* Descripciones de las opciones */
    vector<string> optionDescriptions;
    /* Vector de textos para los controles */
    vector<Text*> controlsTexts;

    /* Cuadro de dialogo para descripciones */
    DialogBox descriptionBox;

    // --- Player HUD ---
    Player* playerChar;
    sf::Text* player_nameText;
    sf::Text* player_levelText;
    sf::RectangleShape player_healthBarBack;
    sf::RectangleShape player_healthBarFront;
    sf::Text* player_healthText;
    sf::RectangleShape* player_ppBarBack;
    sf::RectangleShape* player_ppBarFront;
    sf::Text* player_ppText;

    sf::Text* expNextLevel;
    sf::Text* playerPointsText;

    sf::Text* dialogControlText; // New member for dialog control text


public:
    /* Constructor */
    GameMenuUI();
    /* Destructor */
    ~GameMenuUI();

    /* Configura la UI del menu del juego */
    void setup(GameController* owner, Player* player);
    /* Dibuja la UI en la ventana */
    void draw(RenderWindow& window, int selectedOption, bool isDialogActive);
    /* Actualiza la descripcion en el DialogBox segun la opcion seleccionada */
    void updateDescriptionBox(int selectedOption);

private:
    void updatePlayerHUD();
};

#endif // GAMEMENUUI_H
