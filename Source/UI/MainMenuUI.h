#ifndef MAINMENUUI_H
#define MAINMENUUI_H

#include <SFML/Graphics.hpp>
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
    /* Fuente del titulo */
    Font titleFont;
    /* Texto en pantalla */
    Text* titleText;

    /* Fuente para las opciones del menu */
    Font optionsFont;
    /* Texto de las opciones del menu */
    vector<Text*> optionTexts;
    /* Opcion seleccionada */
    int selectedOption;

public:
    /* Constructor */
    MainMenuUI();
    /* Destructor */
    ~MainMenuUI();

    /* Configura la UI del menu principal */
    void setup(GameController* owner);
    /* Maneja la entrada del usuario */
    void handleInput(Event event, GameController* owner, int& selectedOption);
    /* Dibuja la UI en la ventana */
    void draw(RenderWindow& window, int selectedOption);
};

#endif // MAINMENUUI_H
