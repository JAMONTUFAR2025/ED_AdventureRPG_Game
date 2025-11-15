#include "GameMenuUI.h"
#include "../GameController.h" // Assuming GameController is needed for window size
#include <iostream>

/**
 * Constructor de la UI del Menu del Juego
 * Inicializa los punteros a null
 */
GameMenuUI::GameMenuUI() : titleText(nullptr)
{
    // Inicializar descripciones
    optionDescriptions.push_back("Inicias un combate contra enemigos salvajes.");
    optionDescriptions.push_back("Restaura todos tus puntos de salud.");
    optionDescriptions.push_back("Compra esto para ganar el juego.");
    optionDescriptions.push_back("Cerrar el juego.");
}

/**
 * Destructor de la UI del Menu del Juego
 * Libera la memoria asignada a los textos
 */
GameMenuUI::~GameMenuUI()
{
    // Libera la memoria asignada del titulo
    delete titleText;
    // Para cada opcion
    for(Text* option : optionTexts)
    {
        // Libera la memoria asignada de cada opcion
        delete option;
    }
    // Limpia el vector de opciones
    optionTexts.clear();
}

/* Configuracion inicial de la UI del Menu del Juego */
void GameMenuUI::setup(GameController* owner)
{
    // Intenta cargar la fuente desde el archivo, si falla, intenta cargar una fuente por defecto del sistema
    if (!titleFont.openFromFile("Assets/fonts/font.otf"))
    {
        cerr<<"Error al cargar Assets/fonts/font.otf"<<endl;
        // Intentamos cargar una fuente por defecto del sistema, si falla salimos de la funcion
        if (!titleFont.openFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            cerr<<"Error al cargar font C:/Windows/Fonts/arial.ttf"<<endl;
            return;
        }
    }

    // Carga las fuentes, no se manejan errores por simplicidad
    optionsFont = titleFont;

    // Configura el texto del titulo como un objeto nuevo
    titleText = new Text(titleFont, "Menu de Acciones", 48);
    // El texto del titulo es color rojo
    titleText->setFillColor(Color::Red);
    // Posicionamos el titulo en la esquina superior izquierda
    titleText->setPosition(Vector2f(20, 20));

    // Lista de opciones
    vector<string> options = {
        "Explorar",
        "Comprar pocion de curacion (10 puntos)",
        "Comprar trofeo (1000 puntos)",
        "Salir"
    };

    // Creamos los textos para cada opcion
    for (int i = 0; i < options.size(); i++)
    {
        // Creamos un nuevo texto para la opcion en puntero
        Text* option = new Text(optionsFont, options[i], 32);
        // Color blanco por defecto
        option->setFillColor(Color::White);
        // Posicionamos la opcion debajo del titulo, con un espacio de 40 pixeles entre cada una
        option->setPosition(Vector2f(50, 100 + i * 40));
        // Agregamos la opcion al vector de opciones
        optionTexts.push_back(option);
    }

    // Setup del DialogBox
    dialogBox.setup();
}

/* Dibuja la UI del Menu del Juego en la ventana */
void GameMenuUI::draw(RenderWindow& window, int selectedOption)
{
    // Dibuja el titulo
    if(titleText)
        window.draw(*titleText);

    // Dibuja las opciones
    for (int i = 0; i < optionTexts.size(); i++)
    {
        // Resalta la opcion seleccionada en amarillo
        if (i == selectedOption)
        {
            optionTexts[i]->setFillColor(Color::Yellow);
        }
        // Opcion no seleccionada en blanco
        else
        {
            optionTexts[i]->setFillColor(Color::White);
        }
        // Dibuja la opcion
        window.draw(*optionTexts[i]);
    }

    // Dibuja la caja de dialogo
    dialogBox.draw(window);
}

/* Actualiza la descripcion en el DialogBox segun la opcion seleccionada */
void GameMenuUI::updateDialogBoxDescription(int selectedOption)
{
    if (selectedOption >= 0 && selectedOption < optionDescriptions.size())
    {
        dialogBox.setText(optionDescriptions[selectedOption]);
    }
}
