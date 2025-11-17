#ifndef BATTLE_ACTIONSELECTIONSTATE_H
#define BATTLE_ACTIONSELECTIONSTATE_H

#include "../../Util/StateMachine/IState.h"
#include "../BattleSystem.h" // Owner of this state
#include <SFML/Graphics.hpp>
#include <vector>

namespace Battle
{
    /**
     * @brief State for player to select an action (Fight, Special, Guard, Escape).
     */
    class ActionSelectionState : public IState<BattleSystem>
    {
    private:
        int selectedOption;
        BattleSystem* battleSystemOwner; // Pointer to the owning BattleSystem
        ActionSelectionUI actionSelectionUI;

    public:
        ActionSelectionState();
        ~ActionSelectionState();

        void enter(BattleSystem* owner) override;
        void handleEvent(BattleSystem* owner, sf::Event event) override;
        void update(BattleSystem* owner) override;
        void draw(sf::RenderWindow& window) override; // Corrected signature
        void exit() override;
        const char* getName() const override { return "ActionSelectionState"; }
    };
} // namespace Battle

#endif // BATTLE_ACTIONSELECTIONSTATE_H
