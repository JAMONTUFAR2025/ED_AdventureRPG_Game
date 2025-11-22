#include "GameMenuUI.h"
/**
 * Constructor de la UI del Menu del Juego
 * Inicializa los punteros a null
 */
GameMenuUI::GameMenuUI() : 
        playerChar(nullptr), 
        playerNameText(nullptr), 
        playerLevelText(nullptr), 
        playerHealthText(nullptr), 
        playerPpBarBack(nullptr), 
        playerPpBarFront(nullptr),
        playerPpText(nullptr), 
        expNextLevel(nullptr), 
        playerPointsText(nullptr), 
        dialogControlText(nullptr)
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

    delete playerNameText;
    delete playerLevelText;
    delete playerHealthText;
    delete playerPpBarBack;
    delete playerPpBarFront;
    delete playerPpText;
    delete expNextLevel;
    delete playerPointsText;
    delete dialogControlText;
}

/* Configuracion inicial de la UI del Menu del Juego */
void GameMenuUI::setup(GameController* owner, Player* player)
{
    // Asigna el jugador a la variable miembro
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

    // Configura la caja de titulo
    titleBox.setup(700.0f, 100.0f, (GlobalSettings::SCREEN_WIDTH - 700) / 2, 20, Color::Red, 2);
    // Establece el texto del titulo
    titleBox.setText("Menu de Acciones");

    // HUD DEL JUGADOR EN EL LADO DERECHO
    float hudX = GlobalSettings::SCREEN_WIDTH - 250;

    // Verificamos si los elementos ya existen y los eliminamos para evitar fugas de memoria
    // TEXTO NOMBRE JUGADOR
    if (playerNameText) delete playerNameText;
    playerNameText = new Text(font, playerChar->getCharacter().getBaseCharacter().getName(), GlobalSettings::FONT_SIZE);
    playerNameText->setFillColor(Color::White);
    playerNameText->setPosition({hudX, 140});
    // TEXTO NIVEL JUGADOR
    if (playerLevelText) delete playerLevelText;
    playerLevelText = new Text(font, "Nv " + to_string(playerChar->getCharacter().getLevel()), GlobalSettings::FONT_SIZE);
    playerLevelText->setFillColor(Color::White);
    playerLevelText->setPosition({hudX + 150, 140});
    // BARRA DE VIDA DELANTERA
    playerHealthBarFront.setFillColor(Color::White); // White health
    playerHealthBarFront.setPosition({hudX, 185});
    // BARRA DE VIDA TRASERA
    playerHealthBarBack.setSize({200, 20});
    playerHealthBarBack.setFillColor(Color::Black);
    playerHealthBarBack.setOutlineColor(Color::White);
    playerHealthBarBack.setOutlineThickness(2);
    playerHealthBarBack.setPosition({hudX, 185});
    // TEXTO DE VIDA
    if (playerHealthText) delete playerHealthText;
    playerHealthText = new Text(font, "", GlobalSettings::FONT_SIZE);
    playerHealthText->setFillColor(Color::White);
    playerHealthText->setPosition({hudX + 5, 220});

    /* PUNTOS ULTIMOS DEL JUGADOR (PD) */
    // BARRA PD TRASERA
    playerPpBarBack = new RectangleShape({200, 10});
    playerPpBarBack->setFillColor(Color::Black);
    playerPpBarBack->setOutlineColor(Color::White);
    playerPpBarBack->setOutlineThickness(2);
    playerPpBarBack->setPosition({hudX, 205});
    // BARRA PP DELANTERA
    playerPpBarFront = new RectangleShape({0, 10});
    playerPpBarFront->setFillColor(Color::Cyan);
    playerPpBarFront->setPosition({hudX, 205});

    // TEXTO PUNTOS DEFINITIVA
    if (playerPpText) delete playerPpText;
    playerPpText = new Text(font, "PD: 0/10", GlobalSettings::FONT_SIZE);
    playerPpText->setFillColor(Color::Cyan);
    playerPpText->setPosition({hudX + 115, 220});

    // TEXTO EXP PARA SIGUIENTE NIVEL
    if (expNextLevel) delete expNextLevel;
    expNextLevel = new Text(font, "", GlobalSettings::FONT_SIZE);
    expNextLevel->setFillColor(Color::White);
    expNextLevel->setPosition({hudX, 250});
    // TEXTO PUNTOS DEL JUGADOR
    if (playerPointsText) delete playerPointsText;
    playerPointsText = new Text(font, "", GlobalSettings::FONT_SIZE);
    playerPointsText->setFillColor(Color::White);
    playerPointsText->setPosition({hudX, 280});

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

    // Vector de controles
    vector<string> controls = {
        "W / S - Cambiar opcion.",
        "E - Seleccionar opcion."
    };

    // Variables para posicionar los controles
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

    // Texto de control de dialogo
    dialogControlText = new Text(font, "E - Siguiente dialogo", GlobalSettings::FONT_SIZE);
    // Color blanco por defecto
    dialogControlText->setFillColor(Color::White);
    // Posicionamos el texto centrado debajo del menu
    dialogControlText->setPosition({startX + spacing / 2, startY});

    // Configura la caja de descripcion
    descriptionBox.setup(700.0f, 150.0f, 50, 380);
}

/* Dibuja la UI del Menu del Juego en la ventana */
void GameMenuUI::draw(RenderWindow& window, int selectedOption, bool isDialogActive)
{
    // Si hay un dialogo activo
    if (isDialogActive)
    {
        // Dibuja el texto de control para avanzar el dialogo
        if (dialogControlText) window.draw(*dialogControlText);
    }
    // Si no hay dialogo activo
    else
    {
        // Dibuja los controles para seleccionar una opcion
        for (Text* control : controlsTexts)
        {
            window.draw(*control);
        }
        
        // Dibuja la caja de dialogo
        descriptionBox.draw(window);
    }
    
    // Dibuja la caja de titulo
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

    // Dibuja el HUD del jugador
    if (playerChar)
    {
        updatePlayerHUD();
        window.draw(*playerNameText);
        window.draw(*playerLevelText);
        window.draw(playerHealthBarBack);
        window.draw(playerHealthBarFront);
        window.draw(*playerHealthText);
        window.draw(*playerPpBarBack);
        window.draw(*playerPpBarFront);
        window.draw(*playerPpText);
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

/* ACTUALIZA EL HUD DEL JUGADOR */
void GameMenuUI::updatePlayerHUD()
{
    // Si no hay jugador, salir
    if (!playerChar) return;

    // Actualizar barra de vida
    float playerHealthRatio = static_cast<float>(playerChar->getCharacter().getCurrentHealth()) / playerChar->getCharacter().getMaxHealth();
    playerHealthBarFront.setSize(Vector2f(200 * playerHealthRatio, 20));
    playerHealthText->setString("PS: " + to_string(playerChar->getCharacter().getCurrentHealth()) + "/" + to_string(playerChar->getCharacter().getMaxHealth()));

    // Actualizar puntos de definitiva
    float ppRatio = static_cast<float>(playerChar->getUltimatePoints()) / 10.0f;
    playerPpBarFront->setSize(Vector2f(200 * ppRatio, 10));
    playerPpText->setString("PD: " + to_string(playerChar->getUltimatePoints()) + "/10");

    // Actualizar nivel
    playerLevelText->setString("Nv " + to_string(playerChar->getCharacter().getLevel()));

    // Actualizar exp siguiente nivel
    expNextLevel->setString("Siguiente nivel: " + to_string(playerChar->getNextLevelExp() - playerChar->getCurrentExp()));

    // Actualizar puntos del jugador
    playerPointsText->setString("Puntos de jugador: " + to_string(playerChar->getPoints()));
}
