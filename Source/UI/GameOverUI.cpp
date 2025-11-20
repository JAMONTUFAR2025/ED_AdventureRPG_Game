#include "GameOverUI.h"
#include "../Gameplay/GlobalSettings.h" // For screen dimensions
#include <iostream>
/**
 * Constructor de la UI del Menu de Game Over
 * Inicializa los punteros a null y la opcion seleccionada en 0
 */
GameOverUI::GameOverUI()
{
    // Inicializar descripciones
    optionDescriptions.push_back("Reintentar el combate desde el principio.");
    optionDescriptions.push_back("Volver al menu principal.");
}

/**
 * Destructor de la UI del Menu de Game Over
 * Libera la memoria asignada a los textos
 */
GameOverUI::~GameOverUI()
{
    // Para cada opcion
    for(Text* option : optionTexts)
    {
        // Libera la memoria asignada de cada opcion
        delete option;
    }
    // Limpia el vector de opciones
    optionTexts.clear();
}
/* Configuracion inicial de la UI del Menu de Game Over */
void GameOverUI::setup(bool isGameLost)
{
    // Intenta cargar la fuente desde el archivo, si falla, intenta cargar una fuente por defecto del sistema
    if (!font.openFromFile(GlobalSettings::FONT_PATH))
    {
        cerr<<"Error al cargar " << GlobalSettings::FONT_PATH << endl;
        // Intentamos cargar una fuente por defecto del sistema, si falla salimos de la funcion
        if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            cerr<<"Error al cargar font C:/Windows/Fonts/arial.ttf"<<endl;
            return;
        }
    }

    // TITULO
    titleBox.setup(700.0f, 100.0f, (GlobalSettings::SCREEN_WIDTH - 700) / 2, 20, Color::Red, 2);
    titleBox.setText(isGameLost ? "Has Perdido!" : "Has Ganado!");

    // Lista de opciones
    vector<string> options = {"Volver al menu principal"};

    // Creamos los textos para cada opcion
    for (int i = 0; i < options.size(); i++)
    {
        // Creamos un nuevo texto para la opcion en puntero
        Text* option = new Text(font, options[i], GlobalSettings::FONT_SIZE);
        // Color blanco por defecto
        option->setFillColor(Color::White);
        // Posicionamos las opciones centradas horizontalmente y con espacio vertical entre ellas
        float posX = (GlobalSettings::SCREEN_WIDTH - option->getLocalBounds().position.x) / 2;
        float posY = 200.0f + i * 100.0f;
        option->setPosition(Vector2f(posX, posY));
        // Agregamos la opcion al vector de textos
        optionTexts.push_back(option);
    }

    // Configuramos la caja de descripcion
    descriptionBox.setup(700.0f, 150.0f, (GlobalSettings::SCREEN_WIDTH - 700) / 2, 400);
}

/* Dibuja la UI del Menu de Game Over en la ventana */
void GameOverUI::draw(RenderWindow& window, int currentSelectedOption)
{
    titleBox.draw(window);

    // Dibuja las opciones
    for (size_t i = 0; i < optionTexts.size(); ++i)
    {
        string originalString = optionTexts[i]->getString();

        if (static_cast<int>(i) == currentSelectedOption)
        {
            optionTexts[i]->setString("> " + originalString);
            optionTexts[i]->setFillColor(Color::Yellow);
        }
        else
        {
            // Remueve el "> " si estaba presente
            if (originalString.rfind("> ", 0) == 0)
            {
                optionTexts[i]->setString(originalString.substr(2));
            }
            optionTexts[i]->setFillColor(Color::White);
        }

        window.draw(*optionTexts[i]);
    }

    // Actualiza y dibuja la descripcion de la opcion seleccionada
    if (currentSelectedOption >= 0 && currentSelectedOption < optionDescriptions.size())
    {
        descriptionBox.setText(optionDescriptions[currentSelectedOption]);
    }
    descriptionBox.draw(window);
}

/* Actualiza la descripcion en el Box segun la opcion seleccionada */
void GameOverUI::updateDescriptionBox(int selectedOption)
{
    if (selectedOption >= 0 && selectedOption < optionDescriptions.size())
    {
        descriptionBox.setText(optionDescriptions[selectedOption]);
    }
}