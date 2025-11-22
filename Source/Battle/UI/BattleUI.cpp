#include "BattleUI.h"

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /**
     * Constructor
     * Inicializa los punteros en nullptr
     */
    BattleUI::BattleUI()
        : player_nameText(nullptr), player_levelText(nullptr),  player_healthText(nullptr),
        enemy_nameText(nullptr), enemy_levelText(nullptr), enemy_healthText(nullptr),
        vsText(nullptr), player_ppText(nullptr), dialogControlText(nullptr)
    {
    }

    /**
     * Destructor
     * Libera la memoria de los punteros
     */
    BattleUI::~BattleUI()
    {
        delete player_nameText;
        delete player_levelText;
        delete player_healthText;
        delete enemy_nameText;
        delete enemy_levelText;
        delete enemy_healthText;
        delete vsText;
        delete player_ppText;
        delete dialogControlText;
    }

    /* Configura la interfaz de usuario de la batalla */
    void BattleUI::setup(Character& playerChar, Character& enemyChar)
    {
        // Cargar la fuente con la ruta definida en GlobalSettings
        if(!font.openFromFile(GlobalSettings::FONT_PATH))
        {
            // Error al cargar la fuente, intentar cargar una fuente por defecto del sistema
            cout<<"Error al cargar "<<GlobalSettings::FONT_PATH<<endl;
            if(!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
            {
                cout<<"Error al cargar font C:/Windows/Fonts/arial.ttf"<<endl;
                return;
            }
        }

        // --- Titulo UI ---
        titleBox.setup(700.0f, 100.0f, (GlobalSettings::SCREEN_WIDTH - 700) / 2, 20, Color::Red, 2);
        titleBox.setText("Batalla!");

        // --- Jugador UI ---
        // TEXTO NOMBRE JUGADOR
        if(player_nameText) delete player_nameText;
        player_nameText = new Text(font, playerChar.getBaseCharacter().getName(), GlobalSettings::FONT_SIZE);
        player_nameText->setFillColor(Color::White);
        player_nameText->setPosition(Vector2f(50, 140));
        // TEXTO NIVEL JUGADOR
        if(player_levelText) delete player_levelText;
        player_levelText = new Text(font, "Nv " + to_string(playerChar.getLevel()), GlobalSettings::FONT_SIZE);
        player_levelText->setFillColor(Color::White);
        player_levelText->setPosition(Vector2f(200, 140));
        // BARRA DE VIDA DELANTERA
        player_healthBarFront.setFillColor(Color::White);
        player_healthBarFront.setPosition(Vector2f(50, 185));
        // BARRA DE VIDA TRASERA
        player_healthBarBack.setSize(Vector2f(200, 20));
        player_healthBarBack.setFillColor(Color::Black);
        player_healthBarBack.setOutlineColor(Color::White);
        player_healthBarBack.setOutlineThickness(2);
        player_healthBarBack.setPosition(Vector2f(50, 185));
        // TEXTO DE VIDA
        if(player_healthText) delete player_healthText;
        player_healthText = new Text(font, "", GlobalSettings::FONT_SIZE);
        player_healthText->setFillColor(Color::White);
        player_healthText->setPosition(Vector2f(55, 220));

        // --- Jugador puntos de definitiva (PD) UI ---
        // BARRA PP TRASERA
        player_ppBarBack.setSize(Vector2f(200, 10));
        player_ppBarBack.setFillColor(Color::Black);
        player_ppBarBack.setOutlineColor(Color::White);
        player_ppBarBack.setOutlineThickness(2);
        player_ppBarBack.setPosition(Vector2f(50, 205));
        // BARRA PP DELANTERA
        player_ppBarFront.setSize(Vector2f(0, 10));
        player_ppBarFront.setFillColor(Color::Cyan);
        player_ppBarFront.setPosition(Vector2f(50, 205));
        // TEXTO PD
        if(player_ppText) delete player_ppText;
        player_ppText = new Text(font, "PD: 0/10", GlobalSettings::FONT_SIZE);
        player_ppText->setFillColor(Color::Cyan);
        player_ppText->setPosition(Vector2f(165, 220));

        // --- Enemigo UI ---
        // TEXTO NOMBRE ENEMIGO
        if(enemy_nameText) delete enemy_nameText;
        enemy_nameText = new Text(font, enemyChar.getBaseCharacter().getName(), GlobalSettings::FONT_SIZE);
        enemy_nameText->setFillColor(Color::White);
        enemy_nameText->setPosition(Vector2f(GlobalSettings::SCREEN_WIDTH - 250, 140));
        // TEXTO NIVEL ENEMIGO
        if(enemy_levelText) delete enemy_levelText;
        enemy_levelText = new Text(font, "Nv " + to_string(enemyChar.getLevel()), GlobalSettings::FONT_SIZE);
        enemy_levelText->setFillColor(Color::White);
        enemy_levelText->setPosition(Vector2f(GlobalSettings::SCREEN_WIDTH - 100, 140));
        // BARRA DE VIDA DELANTERA
        enemy_healthBarFront.setFillColor(Color::White); // White health
        enemy_healthBarFront.setPosition(Vector2f(GlobalSettings::SCREEN_WIDTH - 250, 185));
        // BARRA DE VIDA TRASERA
        enemy_healthBarBack.setSize(Vector2f(200, 30));
        enemy_healthBarBack.setFillColor(Color::Black);
        enemy_healthBarBack.setOutlineColor(Color::White);
        enemy_healthBarBack.setOutlineThickness(2);
        enemy_healthBarBack.setPosition(Vector2f(GlobalSettings::SCREEN_WIDTH - 250, 185));
        // TEXTO DE VIDA
        if(enemy_healthText) delete enemy_healthText;
        enemy_healthText = new Text(font, "", GlobalSettings::FONT_SIZE);
        enemy_healthText->setFillColor(Color::White);
        enemy_healthText->setPosition(Vector2f(GlobalSettings::SCREEN_WIDTH - 245, 220));

        // --- TEXTO VS ---
        if(vsText) delete vsText;
        vsText = new Text(font, "VS", GlobalSettings::FONT_SIZE * 2);
        vsText->setFillColor(Color::White);
        vsText->setPosition(Vector2f(GlobalSettings::SCREEN_WIDTH / 2 - 40, 140));

        // --- TEXTO CONTROL DIALOGO ---
        if(dialogControlText) delete dialogControlText;
        dialogControlText = new Text(font, "E - Siguiente dialogo", GlobalSettings::FONT_SIZE);
        dialogControlText->setFillColor(Color::White);
        dialogControlText->setPosition({70.0f + 330.0f / 2, 550.0f});

        // Actualizacion inicial de elementos dinamicos de la interfaz
        updateHealthBars(playerChar, enemyChar);
    }

    /* Dibuja la interfaz de batalla */
    void BattleUI::draw(RenderWindow& window, int selectedOption, bool isDialogActive)
    {
        // Dibuja el cuadro de dialogo del titulo
        titleBox.draw(window);

        // Si existen, dibuja lo siguiente
        // --- Jugador UI ---
        // Textos de nombre y nivel
        if(player_nameText) window.draw(*player_nameText);
        if(player_levelText) window.draw(*player_levelText);
        // Barras de vida
        window.draw(player_healthBarBack);
        window.draw(player_healthBarFront);
        // Texto de vida
        if(player_healthText) window.draw(*player_healthText);
        // Barras y texto de puntos de definitiva
        window.draw(player_ppBarBack);
        window.draw(player_ppBarFront);
        if(player_ppText) window.draw(*player_ppText);

        // --- Enemigo UI ---
        // Textos de nombre y nivel
        if(enemy_nameText) window.draw(*enemy_nameText);
        if(enemy_levelText) window.draw(*enemy_levelText);
        // Barras de vida
        window.draw(enemy_healthBarBack);
        window.draw(enemy_healthBarFront);
        // Texto de vida
        if(enemy_healthText) window.draw(*enemy_healthText);

        /* --- Texto VS --- */
        if(vsText) window.draw(*vsText);
        /* --- Texto control dialogo --- */
        if(isDialogActive && dialogControlText) window.draw(*dialogControlText);
    }

    /* Metodo que mantiene las barras de vida actualizadas */
    void BattleUI::updateHealthBars(Character& playerChar, Character& enemyChar)
    {
        // Convierte la salud actual a un ratio para la barra de vida
        float playerHealthRatio = static_cast<float>(playerChar.getCurrentHealth()) / playerChar.getMaxHealth();
        // Actualiza el tamanio de la barra de vida del jugador
        player_healthBarFront.setSize(Vector2f(200 * playerHealthRatio, 20));
        // Actualiza el texto de vida del jugador
        if(player_healthText) player_healthText->setString("PS: " + to_string(playerChar.getCurrentHealth()) + "/" + to_string(playerChar.getMaxHealth()));
        // Hace lo mismo para el enemigo
        float enemyHealthRatio = static_cast<float>(enemyChar.getCurrentHealth()) / enemyChar.getMaxHealth();
        enemy_healthBarFront.setSize(Vector2f(200 * enemyHealthRatio, 30));
        if(enemy_healthText) enemy_healthText->setString("PS: " + to_string(enemyChar.getCurrentHealth()) + "/" + to_string(enemyChar.getMaxHealth()));
    }

    /* Metodo que actualiza el texto del nivel del jugador */
    void BattleUI::updatePlayerLevelText(int newLevel)
    {
        if(player_levelText) player_levelText->setString("Nv " + to_string(newLevel));
    }

    /* Metodo que actualiza los puntos de definitiva del jugador */
    void BattleUI::updatePlayerUltimatePoints(int currentPP)
    {
        // Maximo de puntos de definitiva es 10
        float ppRatio = static_cast<float>(currentPP) / 10.0f;
        // Actualiza el tamanio de la barra de puntos de definitiva
        player_ppBarFront.setSize(Vector2f(200 * ppRatio, 10));
        // Actualiza el texto de puntos de definitiva
        if(player_ppText)
        {
            player_ppText->setString("PD: " + to_string(currentPP) + "/10");
        }
    }

    /* Getters */
    Text& BattleUI::getPlayerNameText() { return *player_nameText; }
    Text& BattleUI::getEnemyNameText() { return *enemy_nameText; }
} // namespace Battle
