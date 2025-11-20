#ifndef GAMEOVERUI_H
#define GAMEOVERUI_H
#include <SFML/Graphics.hpp>
#include "DialogBox.h"
#include <vector>

/* Namespaces para acortar */
using namespace std;
using namespace sf;

/**
 * Clase para manejar la UI de Game Over
 */
class GameOverUI
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

    /* Cuadro de dialogo para descripciones */
    DialogBox descriptionBox;
public:
    /* Constructor */
    GameOverUI();
    /* Destructor */
    ~GameOverUI();
    /* Configura la UI del menu de Game Over */
    void setup(bool isGameLost);
    /* Dibuja la UI en la ventana */
    void draw(RenderWindow& window, int selectedOption);
    /* Actualiza la descripcion en el Box segun la opcion seleccionada */
    void updateDescriptionBox(int selectedOption);
};

#endif // GAMEOVERUI_H
