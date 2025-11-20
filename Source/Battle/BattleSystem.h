#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "../Util/StateMachine/StateMachine.h"
#include "../Character/Player.h"
#include <SFML/Graphics.hpp>
#include "UI/BattleUI.h" // Include BattleUI
#include "../Dialog/DialogManager.h" // Include DialogManager

// Declaracion forward
class GameController;

namespace Battle
{
    enum class ActionType
    {
        None,
        Fight,
        Special,
        Guard,
        Escape
    };

    class BattleSystem
    {
    private:
        bool battleIsOver;
        bool isPlayerGuarding;
    public:
        GameController* owner;
        StateMachine<BattleSystem> stateMachine;

        Player player;
        Character enemy;
        BattleUI battleUI; // UI for the battle
        DialogManager dialogManager;

        ActionType chosenAction; // Stores the player's chosen action

        BattleSystem(GameController* owner, const Player& playerCharacter, const Character& enemyCharacter);

        void startBattle();
        void handleEvent(sf::Event event);
        void update();
        void draw(sf::RenderWindow& window);

        Player& getPlayer() { return player; }
        Character& getEnemy() { return enemy; }
        BattleUI& getBattleUI() { return battleUI; }
        DialogManager& getDialogManager() { return dialogManager; }
        
        ActionType getChosenAction() const { return chosenAction; }
        void setChosenAction(ActionType action) { chosenAction = action; }
        
        StateMachine<BattleSystem>& getStateMachine() { return stateMachine; }

        bool isBattleOver() const;
        void endBattle();

        bool getPlayerGuarding() const { return isPlayerGuarding; }
        void setPlayerGuarding(bool guarding) { isPlayerGuarding = guarding; }

    };
} // namespace Battle

#endif // BATTLESYSTEM_H
