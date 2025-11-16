#include "BattleSystem.h"
#include "../GameController.h" // For GameController functions if needed
#include "States/ActionSelectionState.h" // Initial state for battle
#include <iostream>

namespace Battle
{
    /**
     * @brief Constructor for BattleSystem.
     * @param owner A pointer to the main GameController.
     * @param playerCharacter The player's Character object.
     * @param enemyCharacter The enemy's Character object.
     */
    BattleSystem::BattleSystem(GameController* owner, const Character& playerCharacter, const Character& enemyCharacter)
        : owner(owner), stateMachine(this), player(playerCharacter), enemy(enemyCharacter), battleUI(), chosenAction(ActionType::None)
    {
    }

    /**
     * @brief Destructor for BattleSystem.
     */
    BattleSystem::~BattleSystem()
    {
    }

    /**
     * @brief Initializes the battle system and sets the initial state.
     */
    void BattleSystem::startBattle()
    {
        std::cout << "Battle started! Player: " << player.getBaseCharacter().getName()
                  << " vs Enemy: " << enemy.getBaseCharacter().getName() << std::endl;
        
        battleUI.setup(player, enemy); // Setup the battle UI
        battleUI.updateHealthBars(player, enemy); // Initial health bar update

        // Set the initial state for the battle (e.g., player selects action)
        stateMachine.changeState(new ActionSelectionState());
    }

    /**
     * @brief Handles SFML events for the battle system.
     * @param event The SFML event to process.
     */
    void BattleSystem::handleEvent(sf::Event event)
    {
        if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Z)
            {
                if (dialogManager.isActive())
                {
                    dialogManager.nextLine();
                    return; // Don't pass to state machine if UI handled it
                }
            }
        }
        stateMachine.handleEvent(event);
    }

    /**
     * @brief Updates the current battle state.
     */
    void BattleSystem::update()
    {
        dialogManager.update();
        stateMachine.update();
        battleUI.updateHealthBars(player, enemy); // Keep health bars updated
    }

    /**
     * @brief Draws the current battle state to the window.
     * @param window The SFML RenderWindow to draw to.
     */
    void BattleSystem::draw(sf::RenderWindow& window)
    {
        stateMachine.draw(window);
        dialogManager.draw(window);
    }
} // namespace Battle
