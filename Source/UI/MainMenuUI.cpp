#include "MainMenuUI.h"
#include "../../GameController.h" // Assuming GameController is needed for window size
#include <iostream>

/**
 * Constructor de la UI del Menu Principal
 * Inicializa los punteros a null y la opcion seleccionada en 0
 */
MainMenuUI::MainMenuUI() : titleText(nullptr), selectedOption(0)
{
}

/**
 * Destructor de la UI del Menu Principal
 * Libera la memoria asignada a los textos
 */
MainMenuUI::~MainMenuUI()
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

/* Configuracion inicial de la UI del Menu Principal */
void MainMenuUI::setup(GameController* owner)
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
    titleText = new Text(titleFont, "Adventure RPG", 64);
    // El texto del titulo es color rojo
    titleText->setFillColor(Color::Red);
    
    // Creamos un rectangulo que tendra el tamanio del texto del titulo
    FloatRect titleRect = titleText->getLocalBounds();
    // El origen es el centro del rectangulo
    titleText->setOrigin({titleRect.position.x + titleRect.size.x / 2.0f, titleRect.position.y + titleRect.size.y / 2.0f});
    // Colocamos el titulo en la parte superior de la ventana y centrado
    titleText->setPosition(Vector2f(owner->window.getSize().x / 2.0f, owner->window.getSize().y / 4.0f));

    // Lista de opciones
    vector<string> options = {"Jugar", "Salir"};

    // Creamos los textos para cada opcion
    for (int i = 0; i < options.size(); i++)
    {
        // Creamos un nuevo texto para la opcion en puntero
        Text* option = new Text(optionsFont, options[i], 32);
        // Color blanco por defecto
        option->setFillColor(Color::White);
        // Centramos el origen del texto
        FloatRect optionRect = option->getLocalBounds();
        // El origen es el centro del rectangulo
        option->setOrigin({optionRect.position.x + optionRect.size.x / 2.0f, optionRect.position.y + optionRect.size.y / 2.0f});
        // Posicionamos la opcion debajo del titulo, con un espacio de 50 pixeles entre cada una
        option->setPosition(Vector2f(owner->window.getSize().x / 2.0f, owner->window.getSize().y / 2.0f + i * 50));
        // Agregamos la opcion al vector de opciones
        optionTexts.push_back(option);
    }
}

/* Manejo de entrada del usuario */
void MainMenuUI::handleInput(Event event, GameController* owner, int& currentSelectedOption)
{
    // Verificamos si el evento es de tipo KeyPressed
    if (const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
    {
        // Navegacion por las opciones del menu
        if (keyPressed->code == Keyboard::Key::Up)
        {
            if (currentSelectedOption > 0)
            {
                currentSelectedOption--;
            }
        }
        else if (keyPressed->code == Keyboard::Key::Down)
        {
            if (currentSelectedOption < optionTexts.size() - 1)
            {
                currentSelectedOption++;
            }
        }
        // Seleccion de la opcion
        else if (keyPressed->code == Keyboard::Key::Z)
        {
            if (currentSelectedOption == 0)
            {
                cout<<"Selected: Jugar"<<endl;
            }
            else if (currentSelectedOption == 1)
            {
                cout<<"Selected: Salir"<<endl;
                owner->window.close();
            }
        }
    }
}

/* Dibuja la UI del Menu Principal en la ventana */
void MainMenuUI::draw(RenderWindow& window, int currentSelectedOption)
{
    // Dibuja el titulo
    if(titleText)
        window.draw(*titleText);

    // Dibuja las opciones
    for (int i = 0; i < optionTexts.size(); i++)
    {
        // Resalta la opcion seleccionada en amarillo
        if (i == currentSelectedOption)
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
}
