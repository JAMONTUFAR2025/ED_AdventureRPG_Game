#ifndef BATTLESTATE_H
#define BATTLESTATE_H

#include "../Util/StateMachine/IState.h"
#include <SFML/Graphics.hpp>
#include "../Battle/BattleSystem.h"
#include "../Dialog/DialogManager.h"

// Declaracion forward para evitar dependencias circulares
class GameController;

class BattleState : public IState<GameController>
{
private:
    GameController* owner;
    Battle::BattleSystem* battleSystem;
    
    Player* player;
    Character enemyCharacter;
    DialogManager* dialogManager;

public:
    BattleState(GameController& owner, Player* player, Character enemy);
    ~BattleState();

    void enter(GameController* owner) override;
    void handleEvent(GameController* owner, Event event) override;
    void update(GameController* owner) override;
    void draw(RenderWindow& window) override;
    void exit() override;
};

#endif // BATTLESTATE_H
