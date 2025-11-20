#ifndef MAINMENUUI_H
#define MAINMENUUI_H

#include <SFML/Graphics.hpp>
#include "DialogBox.h"
#include <vector>

/* Namespaces para acortar */
using namespace sf;
using namespace std;

// Declaracion forward de GameController para evitar dependencias circulares
class GameController;

/**
 * Clase para manejar la UI del Menu Principal
 */
class MainMenuUI
{
private:
    /* Fuente */
    Font font;
    /* Caja de titulo */
    DialogBox titleBox;

    /* Texto de las opciones del menu */
    vector<Text*> optionTexts;
    /* Texto para las descripciones del menu */
    vector<string> optionDescriptions;
    /* Texto para los controles del menu */
    vector<Text*> controlsTexts;

    /* Cuadro de dialogo para descripciones */
    DialogBox descriptionBox;

public:
    /* Constructor */
    MainMenuUI();
    /* Destructor */
    ~MainMenuUI();

    /* Configura la UI del menu principal */
    void setup(GameController* owner);
    /* Dibuja la UI en la ventana */
    void draw(RenderWindow& window, int selectedOption);
    /* Actualiza la descripcion en el Box segun la opcion seleccionada */
    void updateDescriptionBox(int selectedOption);
};

#endif // MAINMENUUI_H
