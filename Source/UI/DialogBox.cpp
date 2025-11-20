#include "DialogBox.h"
#include "../Gameplay/GlobalSettings.h" // For global settings like font size
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
void DialogBox::setup(float width, float height, int posX, int posY, Color textColor, int characterSize)
{
    // Intenta cargar la fuente desde el archivo, si falla, intenta cargar una fuente por defecto del sistema
    if (!font.openFromFile(GlobalSettings::FONT_PATH))
    {
        cout<<"Error loading font " << GlobalSettings::FONT_PATH << endl;
        if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            cout<<"Error loading fallback font C:/Windows/Fonts/arial.ttf"<<endl;
            return;
        }
    }

    // Configura el tamanio del rectangulo
    box.setSize({width, height});
    // Establece el relleno en color negro con un poco de transparencia
    box.setFillColor(Color(0, 0, 0, height));
    // Establece el color del borde en blanco
    box.setOutlineColor(Color::White);
    // Establece el grosor del borde en 6 pixeles
    box.setOutlineThickness(6);
    // Establece la posicion del rectangulo
    box.setPosition({float(posX), float(posY)});

    // Configura el texto dentro de la caja de dialogo
    text = new Text(font, "", GlobalSettings::FONT_SIZE);
    text->setCharacterSize(GlobalSettings::FONT_SIZE * characterSize);
    text->setFillColor(textColor);
    text->setPosition({float(posX) + 20.0f, float(posY)});
}

void DialogBox::setup(float width, float height, int posX, int posY)
{
    setup(width, height, posX, posY, Color::White, 1);
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
