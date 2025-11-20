#include "GameMenuUI.h"
#include "../GameController.h" // Assuming GameController is needed for window size
#include "../Gameplay/GlobalSettings.h" // For global settings like font size
#include "../Character/Player.h" // Include Player for direct access
#include <iostream>

/**
 * Constructor de la UI del Menu del Juego
 * Inicializa los punteros a null
 */
GameMenuUI::GameMenuUI() : playerChar(nullptr), player_nameText(nullptr), player_levelText(nullptr), player_healthText(nullptr), player_ppBarBack(nullptr), player_ppBarFront(nullptr), player_ppText(nullptr), expNextLevel(nullptr), playerPointsText(nullptr), dialogControlText(nullptr)
{
    // Inicializar descripciones
    optionDescriptions.push_back("Inicias un combate contra enemigos salvajes. \nEstos siempre estan igualados a tu nivel. \nGana experiencia y puntos de jugador.");
    optionDescriptions.push_back("Medicina en forma de spray que cura heridas. \nRestaura todos tus puntos de salud.\nCosto: 10 puntos de jugador.");
    optionDescriptions.push_back("Compra un trofeo para ganar el juego. \nTermina la partida actual.\nCosto: 200 puntos de jugador.");
    optionDescriptions.push_back("Regresar al menu principal. \nTermina la partida actual. \nADVERTENCIA: Esta accion no se puede deshacer.");
}

/**
 * Destructor de la UI del Menu del Juego
 * Libera la memoria asignada a los textos
 */
GameMenuUI::~GameMenuUI()
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

    delete player_nameText;
    delete player_levelText;
    delete player_healthText;
    delete player_ppBarBack;
    delete player_ppBarFront;
    delete player_ppText;
    delete expNextLevel;
    delete playerPointsText;
    delete dialogControlText;
}

/* Configuracion inicial de la UI del Menu del Juego */
void GameMenuUI::setup(GameController* owner, Player* player)
{
    this->playerChar = player;
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
    titleBox.setText("Menu de Acciones");

    // --- Player HUD (lado derecho) ---
    float hudX = GlobalSettings::SCREEN_WIDTH - 250;
    // TEXTO NOMBRE JUGADOR
    if (player_nameText) delete player_nameText;
    player_nameText = new sf::Text(font, playerChar->getCharacter().getBaseCharacter().getName(), GlobalSettings::FONT_SIZE);
    player_nameText->setFillColor(sf::Color::White);
    player_nameText->setPosition(sf::Vector2f(hudX, 140));
    // TEXTO NIVEL JUGADOR
    if (player_levelText) delete player_levelText;
    player_levelText = new sf::Text(font, "Nv " + std::to_string(playerChar->getCharacter().getLevel()), GlobalSettings::FONT_SIZE);
    player_levelText->setFillColor(sf::Color::White);
    player_levelText->setPosition(sf::Vector2f(hudX + 150, 140));
    // BARRA DE VIDA DELANTERA
    player_healthBarFront.setFillColor(sf::Color::White); // White health
    player_healthBarFront.setPosition(sf::Vector2f(hudX, 185));
    // BARRA DE VIDA TRASERA
    player_healthBarBack.setSize(sf::Vector2f(200, 20));
    player_healthBarBack.setFillColor(sf::Color::Black);
    player_healthBarBack.setOutlineColor(sf::Color::White);
    player_healthBarBack.setOutlineThickness(2);
    player_healthBarBack.setPosition(sf::Vector2f(hudX, 185));
    // TEXTO DE VIDA
    if (player_healthText) delete player_healthText;
    player_healthText = new sf::Text(font, "", GlobalSettings::FONT_SIZE);
    player_healthText->setFillColor(sf::Color::White);
    player_healthText->setPosition(sf::Vector2f(hudX + 5, 220));

    // --- Player Ultimate Points (PP) UI ---
    // BARRA PP TRASERA
    player_ppBarBack = new sf::RectangleShape(sf::Vector2f(200, 10));
    player_ppBarBack->setFillColor(sf::Color::Black);
    player_ppBarBack->setOutlineColor(sf::Color::White);
    player_ppBarBack->setOutlineThickness(2);
    player_ppBarBack->setPosition(sf::Vector2f(hudX, 205)); // Below health bar

    // BARRA PP DELANTERA
    player_ppBarFront = new sf::RectangleShape(sf::Vector2f(0, 10)); // Starts empty
    player_ppBarFront->setFillColor(sf::Color::Cyan);
    player_ppBarFront->setPosition(sf::Vector2f(hudX, 205));

    // TEXTO PP
    if (player_ppText) delete player_ppText;
    player_ppText = new sf::Text(font, "PP: 0/10", GlobalSettings::FONT_SIZE);
    player_ppText->setFillColor(sf::Color::Cyan);
    player_ppText->setPosition(sf::Vector2f(hudX + 115, 220));

    // TEXTO EXP PARA SIGUIENTE NIVEL
    if (expNextLevel) delete expNextLevel;
    expNextLevel = new sf::Text(font, "", GlobalSettings::FONT_SIZE);
    expNextLevel->setFillColor(sf::Color::White);
    expNextLevel->setPosition(sf::Vector2f(hudX, 250));
    // TEXTO PUNTOS DEL JUGADOR
    if (playerPointsText) delete playerPointsText;
    playerPointsText = new sf::Text(font, "", GlobalSettings::FONT_SIZE);
    playerPointsText->setFillColor(sf::Color::White);
    playerPointsText->setPosition(sf::Vector2f(hudX, 280));

    // Lista de opciones
    vector<string> options = {
        "Explorar el mundo.",
        "Comprar pocion.",
        "Comprar trofeo.",
        "Salir y terminar partida."
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

    // Lista de controles
    vector<string> controls = {
        "W / S - Cambiar opcion.",
        "E - Seleccionar opcion."
    };

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

    // Texto de control de dialogo
    if (dialogControlText) delete dialogControlText;
    dialogControlText = new sf::Text(font, "E - Siguiente dialogo", GlobalSettings::FONT_SIZE);
    dialogControlText->setFillColor(sf::Color::White);
    dialogControlText->setPosition({startX + spacing / 2, startY});

    descriptionBox.setup(700.0f, 150.0f, 50, 380);
}

/* Dibuja la UI del Menu del Juego en la ventana */
void GameMenuUI::draw(RenderWindow& window, int selectedOption, bool isDialogActive)
{
    if (isDialogActive)
    {
        if (dialogControlText) window.draw(*dialogControlText);
    }
    else // Si no hay dialogo activo, dibuja todos los elementos del menu
    {
        
        // Dibuja los controles
        for (Text* control : controlsTexts)
        {
            window.draw(*control);
        }
        
        // Dibuja la caja de dialogo
        descriptionBox.draw(window);
    }
    
    titleBox.draw(window);

    // Dibuja las opciones
    for (int i = 0; i < optionTexts.size(); i++)
    {
        // Guardamos la cadena original
        String originalString = optionTexts[i]->getString();

        // Resalta la opcion seleccionada en amarillo
        if (i == selectedOption)
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

    // Dibuja el HUD del jugador (siempre visible)
    if (playerChar)
    {
        updatePlayerHUD();
        window.draw(*player_nameText);
        window.draw(*player_levelText);
        window.draw(player_healthBarBack);
        window.draw(player_healthBarFront);
        window.draw(*player_healthText);
        window.draw(*player_ppBarBack);
        window.draw(*player_ppBarFront);
        window.draw(*player_ppText);
        window.draw(*expNextLevel);
        window.draw(*playerPointsText);
    }
}

/* Actualiza la descripcion en el Box segun la opcion seleccionada */
void GameMenuUI::updateDescriptionBox(int selectedOption)
{
    if (selectedOption >= 0 && selectedOption < optionDescriptions.size())
    {
        descriptionBox.setText(optionDescriptions[selectedOption]);
    }
}

void GameMenuUI::updatePlayerHUD()
{
    if (!playerChar) return;

    // Actualizar barra de vida
    float playerHealthRatio = static_cast<float>(playerChar->getCharacter().getCurrentHealth()) / playerChar->getCharacter().getMaxHealth();
    player_healthBarFront.setSize(sf::Vector2f(200 * playerHealthRatio, 20));
    player_healthText->setString("PS: " + std::to_string(playerChar->getCharacter().getCurrentHealth()) + "/" + std::to_string(playerChar->getCharacter().getMaxHealth()));

    // Actualizar puntos de ultimate
    float ppRatio = static_cast<float>(playerChar->getUltimatePoints()) / 10.0f; // Max PP is 10
    player_ppBarFront->setSize(sf::Vector2f(200 * ppRatio, 10));
    player_ppText->setString("PD: " + std::to_string(playerChar->getUltimatePoints()) + "/10");

    // Actualizar nivel
    player_levelText->setString("Nv " + std::to_string(playerChar->getCharacter().getLevel()));

    // Actualizar exp siguiente nivel
    expNextLevel->setString("Siguiente nivel: " + std::to_string(playerChar->getNextLevelExp() - playerChar->getCurrentExp()));

    // Actualizar puntos del jugador
    playerPointsText->setString("Puntos de jugador: " + std::to_string(playerChar->getPoints()));
}
