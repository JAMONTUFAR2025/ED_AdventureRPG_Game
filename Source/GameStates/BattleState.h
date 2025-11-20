#ifndef BATTLESTATE_H
#define BATTLESTATE_H

#include "../Util/StateMachine/IState.h"
#include <SFML/Graphics.hpp>
#include "../Battle/BattleSystem.h" // Include the BattleSystem
#include "../Dialog/DialogManager.h" // Include DialogManager

// Forward declaration
class GameController;

/**
 * @brief Represents the main game state when a battle is taking place.
 * This state owns and manages a BattleSystem instance.
 */
class BattleState : public IState<GameController>
{
private:
    GameController* owner; // Pointer to the GameController
    Battle::BattleSystem* battleSystem; // The battle system instance
    // Player and Enemy characters (can be passed to BattleSystem from GameController)
    Player* player;
    Character enemyCharacter;
    DialogManager* dialogManager; // Pointer to the DialogManager

public:
    /**
     * @brief Constructor for BattleState.
     * @param player The player's Character object.
     * @param enemy The enemy's Character object.
     */
    BattleState(GameController& owner, Player* player, Character enemy);
    ~BattleState();

    void enter(GameController* owner) override;
    void handleEvent(GameController* owner, Event event) override;
    void update(GameController* owner) override;
    void draw(RenderWindow& window) override;
    void exit() override;
};

#endif // BATTLESTATE_H
