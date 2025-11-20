#ifndef BATTLE_ACTIONSELECTIONSTATE_H
#define BATTLE_ACTIONSELECTIONSTATE_H

#include "../../Util/StateMachine/IState.h"
#include "../BattleSystem.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Battle
{
    class ActionSelectionState : public IState<BattleSystem>
    {
    private:
        int selectedOption;
        BattleSystem* battleSystemOwner;
        ActionSelectionUI actionSelectionUI;

    public:
        ActionSelectionState();

        void enter(BattleSystem* owner) override;
        void handleEvent(BattleSystem* owner, sf::Event event) override;
        void update(BattleSystem* owner) override;
        void draw(sf::RenderWindow& window) override;
        void exit() override;
    };
} // namespace Battle

#endif // BATTLE_ACTIONSELECTIONSTATE_H
