#include "GameOverUI.h"
/**
 * Constructor de la UI del Menu de Game Over
 * Inicializa los punteros a null
 */
GameOverUI::GameOverUI() : optionText(nullptr), controlsText(nullptr)
{
    // Inicializar descripciones
    optionDescription = "Regresar al menu principal.";
}

/**
 * Destructor de la UI del Menu de Game Over
 * Libera la memoria asignada a los textos como punteros y los pone a null como buena practica
 */
GameOverUI::~GameOverUI()
{
    delete optionText;
    optionText = nullptr;
    delete controlsText;
    controlsText = nullptr;
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

    // Configuramos la caja de titulo
    titleBox.setup(700.0f, 100.0f, (GlobalSettings::SCREEN_WIDTH - 700) / 2, 20, Color::Red, 2);
    // Establecemos un texto segun si el juego se perdio o se gano
    titleBox.setText(isGameLost ? "Uy, has perdido!" : "Felicidades, has ganado! ");

    /* Configuramos la opcion */
    // Eliminamos el texto anterior si existe
    if (optionText) delete optionText;
    // Creamos un nuevo texto para la opcion en puntero
    optionText = new Text(font, "Salir.", GlobalSettings::FONT_SIZE);
    // Color blanco por defecto
    optionText->setFillColor(Color::White);
    // Posicionamos la opcion debajo del titulo
    optionText->setPosition({50, 140});

    /* Configuramos el control */
    // Eliminamos el texto anterior si existe
    if (controlsText) delete controlsText;
    // Creamos el texto para el control en puntero
    controlsText = new Text(font, "E - Seleccionar opcion.", GlobalSettings::FONT_SIZE);
    // Color blanco por defecto
    controlsText->setFillColor(Color::White);
    // Posicionamos el control en la parte inferior
    controlsText->setPosition({70.0f, 550.0f});

    // Configuramos la caja de descripcion
    descriptionBox.setup(700.0f, 150.0f, 50, 380);
    // Establecemos la descripcion inicial
    descriptionBox.setText(optionDescription);
}

/* Dibuja la UI del Menu de Game Over en la ventana */
void GameOverUI::draw(RenderWindow& window, int currentSelectedOption)
{
    // Dibuja la caja de titulo
    titleBox.draw(window);

    // Dibuja la unica opcion
    if (optionText)
    {
        // Guardamos la cadena original para restaurarla despues
        string originalString = optionText->getString();
        
        // Resalta la opcion seleccionada en amarillo
        if (currentSelectedOption == 0)
        {
            optionText->setString("> " + originalString);
            optionText->setFillColor(Color::Yellow);
        }
        // Opcion no seleccionada en blanco
        else
        {
            optionText->setString("  " + originalString);
            optionText->setFillColor(Color::White);
        }
        
        // Dibuja la opcion
        window.draw(*optionText);
        
        // Restauramos la cadena original para evitar modificaciones permanentes
        optionText->setString(originalString);
    }

    // Dibuja el control
    if (controlsText)
    {
        window.draw(*controlsText);
    }

    // Dibuja la caja de descripcion
    descriptionBox.draw(window);
}

/* Actualiza la descripcion en el Box segun la opcion seleccionada */
void GameOverUI::updateDescriptionBox()
{
    // En el menu de Game Over solo hay una opcion, asi que siempre sera la misma descripcion
    descriptionBox.setText(optionDescription);
}