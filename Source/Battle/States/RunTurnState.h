#ifndef BATTLE_RUNTURNSTATE_H
#define BATTLE_RUNTURNSTATE_H

#include "../../Util/StateMachine/IState.h"
#include "../BattleSystem.h"

namespace Battle
{
    enum class BattleResult
    {
        Victory,
        Defeat,
        Escape
    };
    
    /**
     * @brief State for executing player and enemy actions in a single turn.
     */
    class RunTurnState : public IState<BattleSystem>
    {
    private:
        enum class TurnStep
        {
            START,
            PLAYER_ACTION,
            ENEMY_CHECK,
            ENEMY_ACTION,
            PLAYER_CHECK,
            FINISH_TURN,
            BATTLE_END
        };
        
        TurnStep currentStep;
        BattleSystem* battleSystemOwner = nullptr;
        BattleResult result;
        bool finalMessageQueued;
            
    public:
        RunTurnState();

        void enter(BattleSystem* owner) override;
        void handleEvent(BattleSystem* owner, sf::Event event) override;
        void update(BattleSystem* owner) override;
        void draw(sf::RenderWindow& window) override; // Corrected signature
        void exit() override;
        const char* getName() const override { return "RunTurnState"; }
    };
} // namespace Battle

#endif // BATTLE_RUNTURNSTATE_H
