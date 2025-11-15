#ifndef BATTLE_BATTLEENDSTATE_H
#define BATTLE_BATTLEENDSTATE_H

#include "../../Util/StateMachine/IState.h"
#include "../BattleSystem.h"
#include <SFML/Graphics.hpp>

namespace Battle
{
    enum class BattleResult
    {
        Victory,
        Defeat,
        Escape
    };

    /**
     * @brief State for when the battle has ended. Displays result and transitions out.
     */
    class BattleEndState : public IState<BattleSystem>
    {
    private:
        BattleResult result;
        sf::Text* messageText; // Changed to pointer
        sf::Font font;
        bool isMessageDisplayed;

    public:
        BattleEndState(BattleResult result);
        ~BattleEndState();

        void enter(BattleSystem* owner) override;
        void handleEvent(BattleSystem* owner, sf::Event event) override;
        void update(BattleSystem* owner) override;
        void draw(sf::RenderWindow& window) override; // Corrected signature
        void exit() override;
        const char* getName() const override { return "BattleEndState"; }
    };
} // namespace Battle

#endif // BATTLE_BATTLEENDSTATE_H
