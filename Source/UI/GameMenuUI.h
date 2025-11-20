#ifndef GAMEMENUUI_H
#define GAMEMENUUI_H

#include <SFML/Graphics.hpp>
#include "DialogBox.h"
#include "../GameController.h"
#include "../Gameplay/GlobalSettings.h"
#include "../Character/Player.h"
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

// Declaracion forward de GameController para evitar dependencias circulares
class GameController;

/**
 * Clase para manejar la UI del Menu del Juego
 */
class GameMenuUI
{
private:
    /* Fuente */
    Font font;
    /* Caja de titulo */
    DialogBox titleBox;

    /* Texto de las opciones del menu */
    vector<Text*> optionTexts;
    /* Descripciones de las opciones */
    vector<string> optionDescriptions;
    /* Vector de textos para los controles */
    vector<Text*> controlsTexts;

    /* Cuadro de dialogo para descripciones */
    DialogBox descriptionBox;

    /* Variables para el HUD del jugador */
    Player* playerChar;
    Text* playerNameText;
    Text* playerLevelText;
    RectangleShape playerHealthBarBack;
    RectangleShape playerHealthBarFront;
    Text* playerHealthText;
    RectangleShape* playerPpBarBack;
    RectangleShape* playerPpBarFront;
    Text* playerPpText;
    Text* expNextLevel;
    Text* playerPointsText;

    /* Texto para mostrar el control para pasar al siguiente dialogo */
    Text* dialogControlText;

    /* Actualiza el HUD del jugador */
    void updatePlayerHUD();
    
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
};

#endif // GAMEMENUUI_H
