#ifndef BATTLE_RUNTURNSTATE_H
#define BATTLE_RUNTURNSTATE_H

#include "../../Util/StateMachine/IState.h"
#include "../BattleSystem.h"

namespace Battle
{
    /**
     * @brief State for executing player and enemy actions in a single turn.
     */
    class RunTurnState : public IState<BattleSystem>
    {
    public:
        RunTurnState();
        ~RunTurnState();

        void enter(BattleSystem* owner) override;
        void handleEvent(BattleSystem* owner, sf::Event event) override;
        void update(BattleSystem* owner) override;
        void draw(sf::RenderWindow& window) override; // Corrected signature
        void exit() override;
        const char* getName() const override { return "RunTurnState"; }
    };
} // namespace Battle

#endif // BATTLE_RUNTURNSTATE_H
