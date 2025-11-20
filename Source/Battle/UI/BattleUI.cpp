#include "BattleUI.h"
#include "../../Gameplay/GlobalSettings.h" // For screen dimensions
#include <iostream>

namespace Battle
{
    BattleUI::BattleUI()
        : player_nameText(nullptr), player_levelText(nullptr),  player_healthText(nullptr),
        enemy_nameText(nullptr), enemy_levelText(nullptr), enemy_healthText(nullptr),
        vsText(nullptr), player_ppBarBack(nullptr), player_ppBarFront(nullptr), player_ppText(nullptr)
    {
    }

    BattleUI::~BattleUI()
    {
        // optionTexts are now cleaned up in setup()
        delete player_nameText;
        delete player_levelText;
        delete player_healthText;
        delete enemy_nameText;
        delete enemy_levelText;
        delete enemy_healthText;
        delete vsText;
        delete player_ppBarBack;
        delete player_ppBarFront;
        delete player_ppText;
    }

    void BattleUI::setup(const Character& playerChar, const Character& enemyChar)
    {
        if (!font.openFromFile(GlobalSettings::FONT_PATH))
        {
            std::cerr << "Error al cargar " << GlobalSettings::FONT_PATH << std::endl;
            if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
            {
                std::cerr << "Error al cargar font C:/Windows/Fonts/arial.ttf" << std::endl;
                return;
            }
        }

        // --- Title UI ---
        titleBox.setup(700.0f, 100.0f, (GlobalSettings::SCREEN_WIDTH - 700) / 2, 20, Color::Red, 2);
        titleBox.setText("Batalla!");

        // --- Player UI ---
        // TEXTO NOMBRE JUGADOR
        if (player_nameText) delete player_nameText;
        player_nameText = new sf::Text(font, playerChar.getBaseCharacter().getName(), GlobalSettings::FONT_SIZE);
        player_nameText->setFillColor(sf::Color::White);
        player_nameText->setPosition(sf::Vector2f(50, 140)); // Top-left for player
        // TEXTO NIVEL JUGADOR
        if (player_levelText) delete player_levelText;
        player_levelText = new sf::Text(font, "Nv " + std::to_string(playerChar.getLevel()), GlobalSettings::FONT_SIZE);
        player_levelText->setFillColor(sf::Color::White);
        player_levelText->setPosition(sf::Vector2f(200, 140));
        // BARRA DE VIDA DELANTERA
        player_healthBarFront.setFillColor(sf::Color::White); // White health
        player_healthBarFront.setPosition(sf::Vector2f(50, 185));
        // BARRA DE VIDA TRASERA
        player_healthBarBack.setSize(sf::Vector2f(200, 20));
        player_healthBarBack.setFillColor(sf::Color::Black);
        player_healthBarBack.setOutlineColor(sf::Color::White);
        player_healthBarBack.setOutlineThickness(2);
        player_healthBarBack.setPosition(sf::Vector2f(50, 185));
        // TEXTO DE VIDA
        if (player_healthText) delete player_healthText;
        player_healthText = new sf::Text(font, "", GlobalSettings::FONT_SIZE);
        player_healthText->setFillColor(sf::Color::White);
        player_healthText->setPosition(sf::Vector2f(55, 220));

        // --- Player Ultimate Points (PP) UI ---
        // BARRA PP TRASERA
        player_ppBarBack = new sf::RectangleShape(sf::Vector2f(200, 10));
        player_ppBarBack->setFillColor(sf::Color::Black);
        player_ppBarBack->setOutlineColor(sf::Color::White);
        player_ppBarBack->setOutlineThickness(2);
        player_ppBarBack->setPosition(sf::Vector2f(50, 205)); // Below health bar

        // BARRA PP DELANTERA
        player_ppBarFront = new sf::RectangleShape(sf::Vector2f(0, 10)); // Starts empty
        player_ppBarFront->setFillColor(sf::Color::Cyan);
        player_ppBarFront->setPosition(sf::Vector2f(50, 205));

        // TEXTO PP
        if (player_ppText) delete player_ppText;
        player_ppText = new sf::Text(font, "PP: 0/10", GlobalSettings::FONT_SIZE);
        player_ppText->setFillColor(sf::Color::Cyan);
        player_ppText->setPosition(sf::Vector2f(165, 220));


        // --- Enemy UI ---
        // TEXTO NOMBRE ENEMIGO
        if (enemy_nameText) delete enemy_nameText;
        enemy_nameText = new sf::Text(font, enemyChar.getBaseCharacter().getName(), GlobalSettings::FONT_SIZE);
        enemy_nameText->setFillColor(sf::Color::White);
        enemy_nameText->setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH - 250, 140)); // Top-right for enemy
        // TEXTO NIVEL ENEMIGO
        if (enemy_levelText) delete enemy_levelText;
        enemy_levelText = new sf::Text(font, "Nv " + std::to_string(enemyChar.getLevel()), GlobalSettings::FONT_SIZE);
        enemy_levelText->setFillColor(sf::Color::White);
        enemy_levelText->setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH - 100, 140));
        // BARRA DE VIDA DELANTERA
        enemy_healthBarFront.setFillColor(sf::Color::White); // White health
        enemy_healthBarFront.setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH - 250, 185));
        // BARRA DE VIDA TRASERA
        enemy_healthBarBack.setSize(sf::Vector2f(200, 30));
        enemy_healthBarBack.setFillColor(sf::Color::Black);
        enemy_healthBarBack.setOutlineColor(sf::Color::White);
        enemy_healthBarBack.setOutlineThickness(2);
        enemy_healthBarBack.setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH - 250, 185));
        // TEXTO DE VIDA
        if (enemy_healthText) delete enemy_healthText;
        enemy_healthText = new sf::Text(font, "", GlobalSettings::FONT_SIZE);
        enemy_healthText->setFillColor(sf::Color::White);
        enemy_healthText->setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH - 245, 220));

        // TEXTO VS
        if (vsText) delete vsText;
        vsText = new sf::Text(font, "VS", GlobalSettings::FONT_SIZE * 2);
        vsText->setFillColor(sf::Color::White);
        vsText->setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH / 2 - 40, 140));

        // Initial update of dynamic UI elements
        updateHealthBars(playerChar, enemyChar);
    }

    void BattleUI::draw(sf::RenderWindow& window, int selectedOption)
    {
        // Draw Title UI
        titleBox.draw(window);

        // Draw Player UI
        if (player_nameText) window.draw(*player_nameText);
        if (player_levelText) window.draw(*player_levelText);
        window.draw(player_healthBarBack);
        window.draw(player_healthBarFront);
        if (player_healthText) window.draw(*player_healthText);

        // Draw Player Ultimate Points (PP) UI
        if (player_ppBarBack) window.draw(*player_ppBarBack);
        if (player_ppBarFront) window.draw(*player_ppBarFront);
        if (player_ppText) window.draw(*player_ppText);

        // Draw Enemy UI
        if (enemy_nameText) window.draw(*enemy_nameText);
        if(enemy_levelText) window.draw(*enemy_levelText);
        window.draw(enemy_healthBarBack);
        window.draw(enemy_healthBarFront);
        if (enemy_healthText) window.draw(*enemy_healthText);

        // Draw VS Text
        if (vsText) window.draw(*vsText);
    }

    void BattleUI::updateHealthBars(const Character& playerChar, const Character& enemyChar)
    {
        // Update player health bar
        float playerHealthRatio = static_cast<float>(playerChar.getCurrentHealth()) / playerChar.getMaxHealth();
        player_healthBarFront.setSize(sf::Vector2f(200 * playerHealthRatio, 20));
        if (player_healthText) player_healthText->setString("PS: " + std::to_string(playerChar.getCurrentHealth()) + "/" + std::to_string(playerChar.getMaxHealth()));

        // Update enemy health bar
        float enemyHealthRatio = static_cast<float>(enemyChar.getCurrentHealth()) / enemyChar.getMaxHealth();
        enemy_healthBarFront.setSize(sf::Vector2f(200 * enemyHealthRatio, 30));
        if (enemy_healthText) enemy_healthText->setString("PS: " + std::to_string(enemyChar.getCurrentHealth()) + "/" + std::to_string(enemyChar.getMaxHealth()));
    }

    void BattleUI::updatePlayerLevelText(int newLevel)
    {
        if (player_levelText) player_levelText->setString("Nv " + std::to_string(newLevel));
    }

    void BattleUI::updatePlayerUltimatePoints(int currentPP)
    {
        if (player_ppBarFront)
        {
            float ppRatio = static_cast<float>(currentPP) / 10.0f; // Max PP is 10
            player_ppBarFront->setSize(sf::Vector2f(200 * ppRatio, 10));
        }
        if (player_ppText)
        {
            player_ppText->setString("PP: " + std::to_string(currentPP) + "/10");
        }
    }
} // namespace Battle
