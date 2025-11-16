#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "../Util/StateMachine/StateMachine.h"
#include "../Character/Character.h"
#include <SFML/Graphics.hpp>
#include "UI/BattleUI.h" // Include BattleUI

// Forward declarations
class GameController;

namespace Battle
{
    // Enum to represent the player's chosen action
    enum class ActionType
    {
        None,
        Fight,
        Special,
        Guard,
        Escape
    };

    /**
     * @brief The BattleSystem class manages the state and flow of a single battle.
     * It contains a state machine to handle different phases of the battle (e.g., player turn, enemy turn).
     */
    class BattleSystem
    {
    public: // Changed from private to public
        GameController* owner; // Reference to the main game controller
        StateMachine<BattleSystem> stateMachine; // Sub-state machine for battle phases

        Character player;
        Character enemy;
        BattleUI battleUI; // UI for the battle

        ActionType chosenAction; // Stores the player's chosen action

    public:
        /**
         * @brief Constructor for BattleSystem.
         * @param owner A pointer to the main GameController.
         * @param playerCharacter The player's Character object.
         * @param enemyCharacter The enemy's Character object.
         */
        BattleSystem(GameController* owner, const Character& playerCharacter, const Character& enemyCharacter);

        /**
         * @brief Destructor for BattleSystem.
         */
        ~BattleSystem();

        /**
         * @brief Initializes the battle system and sets the initial state.
         */
        void startBattle();

        /**
         * @brief Handles SFML events for the battle system.
         * @param event The SFML event to process.
         */
        void handleEvent(sf::Event event);

        /**
         * @brief Updates the current battle state.
         */
        void update();

        /**
         * @brief Draws the current battle state to the window.
         * @param window The SFML RenderWindow to draw to.
         */
        void draw(sf::RenderWindow& window);

        // Getters for player and enemy characters
        Character& getPlayer() { return player; }
        Character& getEnemy() { return enemy; }

        // Getter for the sub-state machine
        StateMachine<BattleSystem>& getStateMachine() { return stateMachine; }

        // Setter for the chosen action
        void setChosenAction(ActionType action) { chosenAction = action; }
        // Getter for the chosen action
        ActionType getChosenAction() const { return chosenAction; }

        // Getter for BattleUI
        BattleUI& getBattleUI() { return battleUI; }

    private:
        sf::Clock m_clock;
    };
} // namespace Battle

#endif // BATTLESYSTEM_H
