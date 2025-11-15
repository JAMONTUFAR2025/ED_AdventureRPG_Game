#ifndef GAMEMENUUI_H
#define GAMEMENUUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "DialogBox.h"

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
    /* Fuente del titulo */
    Font titleFont;
    /* Texto del titulo en pantalla */
    Text* titleText;

    /* Fuente para las opciones del menu */
    Font optionsFont;
    /* Texto de las opciones del menu */
    vector<Text*> optionTexts;
    /* Descripciones de las opciones */
    vector<string> optionDescriptions;

    /* Cuadro de dialogo para descripciones */
    DialogBox dialogBox;

public:
    /* Constructor */
    GameMenuUI();
    /* Destructor */
    ~GameMenuUI();

    /* Configura la UI del menu del juego */
    void setup(GameController* owner);
    /* Dibuja la UI en la ventana */
    void draw(RenderWindow& window, int selectedOption);
    /* Actualiza la descripcion en el DialogBox segun la opcion seleccionada */
    void updateDialogBoxDescription(int selectedOption);
};

#endif // GAMEMENUUI_H
