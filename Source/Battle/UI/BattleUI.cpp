#include "BattleUI.h"
#include "../../Gameplay/GlobalSettings.h" // For screen dimensions
#include <iostream>

namespace Battle
{
    BattleUI::BattleUI()
        : player_nameText(nullptr), player_healthText(nullptr), enemy_nameText(nullptr), enemy_healthText(nullptr) // Initialize Text* members to nullptr
    {
        optionDescriptions.push_back("Ataca al enemigo con tu arma.");
        optionDescriptions.push_back("Usa una de tus habilidades especiales.");
        optionDescriptions.push_back("Reduce el dano recibido en el proximo turno.");
        optionDescriptions.push_back("Intenta huir de la batalla.");
    }

    BattleUI::~BattleUI()
    {
        for (sf::Text* text : optionTexts)
        {
            delete text;
        }
        optionTexts.clear();

        delete player_nameText;
        delete player_healthText;
        delete enemy_nameText;
        delete enemy_healthText;
    }

    void BattleUI::setup(const Character& playerChar, const Character& enemyChar)
    {
        if (!font.openFromFile("Assets/fonts/font.otf"))
        {
            std::cerr << "Error al cargar Assets/fonts/font.otf" << std::endl;
            if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
            {
                std::cerr << "Error al cargar font C:/Windows/Fonts/arial.ttf" << std::endl;
                return;
            }
        }

        // --- Action Selection UI ---
        std::vector<std::string> options = {"Luchar", "Especial", "En Guardia", "Escapar"};

        float startX = GlobalSettings::SCREEN_WIDTH * 0.7f; // Right side of the screen
        float startY = GlobalSettings::SCREEN_HEIGHT * 0.7f; // Bottom part of the screen
        float spacing = 30.0f;

        for (size_t i = 0; i < options.size(); ++i)
        {
            sf::Text* optionText = new sf::Text(font, options[i], 24);
            optionText->setFillColor(sf::Color::White);
            optionText->setPosition(sf::Vector2f(startX, startY + i * spacing));
            optionTexts.push_back(optionText);
        }

        // --- Player UI ---
        player_nameText = new sf::Text(font, playerChar.getBaseCharacter().getName(), 20);
        player_nameText->setFillColor(sf::Color::White);
        player_nameText->setPosition(sf::Vector2f(50, 40)); // Top-left for player
        
        player_healthBarBack.setSize(sf::Vector2f(200, 20));
        player_healthBarBack.setFillColor(sf::Color(50, 50, 50)); // Dark gray background
        player_healthBarBack.setPosition(sf::Vector2f(50, 70));

        player_healthBarFront.setSize(sf::Vector2f(200, 20));
        player_healthBarFront.setFillColor(sf::Color::Green); // Green health
        player_healthBarFront.setPosition(sf::Vector2f(50, 70));

        player_healthText = new sf::Text(font, "", 16);
        player_healthText->setFillColor(sf::Color::White);
        player_healthText->setPosition(sf::Vector2f(55, 70));


        // --- Enemy UI ---
        enemy_nameText = new sf::Text(font, enemyChar.getBaseCharacter().getName(), 20);
        enemy_nameText->setFillColor(sf::Color::White);
        enemy_nameText->setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH - 250, 40)); // Top-right for enemy
        
        enemy_healthBarBack.setSize(sf::Vector2f(200, 20));
        enemy_healthBarBack.setFillColor(sf::Color(50, 50, 50)); // Dark gray background
        enemy_healthBarBack.setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH - 250, 70));

        enemy_healthBarFront.setSize(sf::Vector2f(200, 20));
        enemy_healthBarFront.setFillColor(sf::Color::Red); // Red health
        enemy_healthBarFront.setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH - 250, 70));

        enemy_healthText = new sf::Text(font, "", 16);
        enemy_healthText->setFillColor(sf::Color::White);
        enemy_healthText->setPosition(sf::Vector2f(GlobalSettings::SCREEN_WIDTH - 245, 70));

        // Initial update of dynamic UI elements
        updateHealthBars(playerChar, enemyChar);
    }

    void BattleUI::draw(sf::RenderWindow& window, int selectedOption)
    {
        // Draw action selection options
        for (size_t i = 0; i < optionTexts.size(); ++i)
        {
            if (static_cast<int>(i) == selectedOption)
            {
                optionTexts[i]->setFillColor(sf::Color::Yellow);
            }
            else
            {
                optionTexts[i]->setFillColor(sf::Color::White);
            }
            window.draw(*optionTexts[i]);
        }

        // Draw Player UI
        if (player_nameText) window.draw(*player_nameText);
        window.draw(player_healthBarBack);
        window.draw(player_healthBarFront);
        if (player_healthText) window.draw(*player_healthText);

        // Draw Enemy UI
        if (enemy_nameText) window.draw(*enemy_nameText);
        window.draw(enemy_healthBarBack);
        window.draw(enemy_healthBarFront);
        if (enemy_healthText) window.draw(*enemy_healthText);
    }

    void BattleUI::updateHealthBars(const Character& playerChar, const Character& enemyChar)
    {
        // Update player health bar
        float playerHealthRatio = static_cast<float>(playerChar.getCurrentHealth()) / playerChar.getMaxHealth();
        player_healthBarFront.setSize(sf::Vector2f(200 * playerHealthRatio, 20));
        if (player_healthText) player_healthText->setString(std::to_string(playerChar.getCurrentHealth()) + "/" + std::to_string(playerChar.getMaxHealth()));

        // Update enemy health bar
        float enemyHealthRatio = static_cast<float>(enemyChar.getCurrentHealth()) / enemyChar.getMaxHealth();
        enemy_healthBarFront.setSize(sf::Vector2f(200 * enemyHealthRatio, 20));
        if (enemy_healthText) enemy_healthText->setString(std::to_string(enemyChar.getCurrentHealth()) + "/" + std::to_string(enemyChar.getMaxHealth()));
    }

    // void BattleUI::displayBattleMessage(const std::string& message)
    // {
    //     // This is now handled by DialogManager
    // }
} // namespace Battle
