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
        bool battleStarted;
        bool battleIsOver;
        bool isPlayerGuarding;

        bool hasHealthBarUpdated;
        bool hasPlayerLeveledUp;
        bool hasUltimatePointsUpdated;
    public:
        GameController* owner;
        StateMachine<BattleSystem> stateMachine;

        Player* player;
        Character enemy;
        BattleUI battleUI; // UI for the battle
        DialogManager dialogManager;

        ActionType chosenAction; // Stores the player's chosen action

        BattleSystem(GameController* owner, Player* playerCharacter, const Character& enemyCharacter);

        void startBattle();
        void handleEvent(sf::Event event);
        void update();
        void draw(sf::RenderWindow& window);

        Player* getPlayer() { return player; }
        Character& getEnemy() { return enemy; }
        BattleUI& getBattleUI() { return battleUI; }
        DialogManager& getDialogManager() { return dialogManager; }
        
        ActionType getChosenAction() const { return chosenAction; }
        void setChosenAction(ActionType action) { chosenAction = action; }
        
        StateMachine<BattleSystem>& getStateMachine() { return stateMachine; }

        bool getBattleStarted() const;
        void setBattleStarted(bool started);

        bool isBattleOver() const;
        void endBattle();

        bool getPlayerGuarding() const;
        void setPlayerGuarding(bool guarding);

        bool getHasHealthBarUpdated() const;
        void setHasHealthBarUpdated(bool updated);

        bool getHasPlayerLeveledUp() const;
        void setHasPlayerLeveledUp(bool leveledUp);

        bool getHasUltimatePointsUpdated() const;
        void setHasUltimatePointsUpdated(bool updated);
    };
} // namespace Battle

#endif // BATTLESYSTEM_H
