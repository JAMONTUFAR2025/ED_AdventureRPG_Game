#include "MainMenuUI.h"
#include "../GameController.h" // Assuming GameController is needed for window size
#include "../Gameplay/GlobalSettings.h" // For global settings like font size
#include <iostream>

/**
 * Constructor de la UI del Menu Principal
 * Inicializa los punteros a null y la opcion seleccionada en 0
 */
MainMenuUI::MainMenuUI()
{
    // Inicializar descripciones
    optionDescriptions.push_back("Inicia una nueva aventura.\n\nCreado por: Josue Alejandro Montufar Zuniga");
    optionDescriptions.push_back("Cierra el juego.\n\nCreado por: Josue Alejandro Montufar Zuniga");
}

/**
 * Destructor de la UI del Menu Principal
 * Libera la memoria asignada a los textos
 */
MainMenuUI::~MainMenuUI()
{
    // Para cada opcion
    for(Text* option : optionTexts)
    {
        // Libera la memoria asignada de cada opcion
        delete option;
    }
    // Para cada control
    for(Text* control : controlsTexts)
    {
        // Libera la memoria asignada de cada control
        delete control;
    }
    // Limpia el vector de opciones
    optionTexts.clear();
    // Limpia el vector de controles
    controlsTexts.clear();
}

/* Configuracion inicial de la UI del Menu Principal */
void MainMenuUI::setup(GameController* owner)
{
    // Intenta cargar la fuente desde el archivo, si falla, intenta cargar una fuente por defecto del sistema
    if (!font.openFromFile(GlobalSettings::FONT_PATH))
    {
        cerr<<"Error al cargar <<" << GlobalSettings::FONT_PATH << endl;
        // Intentamos cargar una fuente por defecto del sistema, si falla salimos de la funcion
        if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            cerr<<"Error al cargar font C:/Windows/Fonts/arial.ttf"<<endl;
            return;
        }
    }

    // TITULO
    titleBox.setup(700.0f, 100.0f, (GlobalSettings::SCREEN_WIDTH - 700) / 2, 20, Color::Red, 2);
    titleBox.setText("Proyecto Final: Adventure RPG");

    // Lista de opciones
    vector<string> options = {"Nueva partida", "Salir"};

    // Lista de controles
    vector<string> controls = {
        "W / S - Cambiar opcion.",
        "E - Seleccionar opcion."
    };

    // Creamos los textos para cada opcion
    for (int i = 0; i < options.size(); i++)
    {
        // Creamos un nuevo texto para la opcion en puntero
        Text* option = new Text(font, options[i], GlobalSettings::FONT_SIZE);
        // Color blanco por defecto
        option->setFillColor(Color::White);
        // Posicionamos la opcion debajo del titulo, con un espacio de 40 pixeles entre cada una
        option->setPosition(Vector2f(50, 140 + i * 40));
        // Agregamos la opcion al vector de opciones
        optionTexts.push_back(option);
    }

    float startX = 70.0f;
    float startY = 550.0f;
    float spacing = 330.0f;

    // Creamos los textos para cada control
    for (int i = 0; i < controls.size(); i++)
    {
        // Creamos un nuevo texto para el control en puntero
        Text* control = new Text(font, controls[i], GlobalSettings::FONT_SIZE);
        // Color blanco por defecto
        control->setFillColor(Color::White);

        control->setPosition(Vector2f(startX + i * spacing, startY));
        // Agregamos el control al vector de controles
        controlsTexts.push_back(control);
    }

    descriptionBox.setup(700.0f, 150.0f, 50, 380);
}

/* Dibuja la UI del Menu Principal en la ventana */
void MainMenuUI::draw(RenderWindow& window, int currentSelectedOption)
{
    titleBox.draw(window);
    
    // Dibuja las opciones
    for (int i = 0; i < optionTexts.size(); i++)
    {
        // Guardamos la cadena original
        String originalString = optionTexts[i]->getString();
        
        // Resalta la opcion seleccionada en amarillo
        if (i == currentSelectedOption)
        {
            optionTexts[i]->setString("> " + originalString);
            optionTexts[i]->setFillColor(Color::Yellow);
        }
        // Opcion no seleccionada en blanco
        else
        {
            optionTexts[i]->setString("  " + originalString);
            optionTexts[i]->setFillColor(Color::White);
        }
        
        // Dibuja la opcion
        window.draw(*optionTexts[i]);
        
        // Restauramos la cadena original para evitar modificaciones permanentes
        optionTexts[i]->setString(originalString);
    }

    // Dibuja los controles
    for (Text* control : controlsTexts)
    {
        window.draw(*control);
    }

    // Dibuja la caja de descripcion
    descriptionBox.draw(window);
}

/* Actualiza la descripcion en el Box segun la opcion seleccionada */
void MainMenuUI::updateDescriptionBox(int selectedOption)
{
    if (selectedOption >= 0 && selectedOption < optionDescriptions.size())
    {
        descriptionBox.setText(optionDescriptions[selectedOption]);
    }
}
