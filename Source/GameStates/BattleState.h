#ifndef BATTLESTATE_H
#define BATTLESTATE_H

#include "../Util/StateMachine/IState.h"
#include <SFML/Graphics.hpp>
#include "../Battle/BattleSystem.h" // Include the BattleSystem

// Forward declaration
class GameController;

/**
 * @brief Represents the main game state when a battle is taking place.
 * This state owns and manages a BattleSystem instance.
 */
class BattleState : public IState<GameController>
{
private:
    Battle::BattleSystem* battleSystem; // The battle system instance
    // Player and Enemy characters (can be passed to BattleSystem from GameController)
    Character playerCharacter;
    Character enemyCharacter;

public:
    /**
     * @brief Constructor for BattleState.
     * @param player The player's Character object.
     * @param enemy The enemy's Character object.
     */
    BattleState(const Character& player, const Character& enemy);
    ~BattleState();

    void enter(GameController* owner) override;
    void handleEvent(GameController* owner, sf::Event event) override;
    void update(GameController* owner) override;
    void draw(sf::RenderWindow& window) override;
    void exit() override;
    const char* getName() const override { return "BattleState"; }
};

#endif // BATTLESTATE_H
