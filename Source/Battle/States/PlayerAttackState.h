#ifndef BATTLE_PLAYERATTACKSTATE_H
#define BATTLE_PLAYERATTACKSTATE_H

#include "../../Util/StateMachine/IState.h"
#include "../BattleSystem.h"

namespace Battle
{
    /**
     * @brief State for when the player's "Luchar" action is executed.
     */
    class PlayerAttackState : public IState<BattleSystem>
    {
    public:
        PlayerAttackState();
        ~PlayerAttackState();

        void enter(BattleSystem* owner) override;
        void handleEvent(BattleSystem* owner, sf::Event event) override;
        void update(BattleSystem* owner) override;
        void draw(sf::RenderWindow& window) override;
        void exit() override;
        const char* getName() const override { return "PlayerAttackState"; }
    };
} // namespace Battle

#endif // BATTLE_PLAYERATTACKSTATE_H
