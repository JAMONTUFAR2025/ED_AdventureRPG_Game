#include "DialogBox.h"
#include <iostream>

/**
 * Constructor de la caja de dialogo
 * Inicializa los punteros a null
 */
DialogBox::DialogBox() : text(nullptr)
{
}

/**
 * Destructor de la caja de dialogo
 * Libera la memoria del texto
 */
DialogBox::~DialogBox()
{
    delete text;
}

/* Inicializa la caja de dialogo */
void DialogBox::setup()
{
    // Intenta cargar la fuente desde el archivo, si falla, intenta cargar una fuente por defecto del sistema
    if (!font.openFromFile("Assets/fonts/font.otf"))
    {
        cout<<"Error loading font Assets/fonts/font.otf"<<endl;
        if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            cout<<"Error loading fallback font C:/Windows/Fonts/arial.ttf"<<endl;
            return;
        }
    }

    // Configura el tamanio del rectangulo
    box.setSize(Vector2f(700, 150));
    // Establece el relleno en color negro con un poco de transparencia
    box.setFillColor(Color(0, 0, 0, 150));
    // Establece el color del borde en blanco
    box.setOutlineColor(Color::White);
    // Establece el grosor del borde en 6 pixeles
    box.setOutlineThickness(6);
    // Establece la posicion del rectangulo
    box.setPosition({50, 380});

    // Configura el texto dentro de la caja de dialogo
    text = new Text(font, "", 32);
    text->setCharacterSize(32);
    text->setFillColor(Color::White);
    text->setPosition({70, 420});
}

/* Setter para el texto */
void DialogBox::setText(const string& str)
{
    if(text)
        text->setString(str);
}

/* Dibuja la caja de dialogo en la ventana */
void DialogBox::draw(RenderWindow& window)
{
    window.draw(box);
    if(text)
        window.draw(*text);
}
