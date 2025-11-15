#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

/**
 * Clase para manejar el cuadro de dialogo en pantalla
 */
class DialogBox
{
private:
    /* Rectangulo que representa la caja de dialogo */
    RectangleShape box;
    /* Texto que se muestra dentro de la caja de dialogo, es un puntero */
    Text* text;
    /* Fuente utilizada para el texto */
    Font font;

public:
    /* Constructor de la caja de dialogo */
    DialogBox();
    /* Destructor de la caja de dialogo */
    ~DialogBox();
    /* Inicializa la caja de dialogo */
    void setup();
    /* Setter para el texto */
    void setText(const string& str);
    /* Dibuja la caja de dialogo en la ventana */
    void draw(RenderWindow& window);
};

#endif // DIALOGBOX_H
