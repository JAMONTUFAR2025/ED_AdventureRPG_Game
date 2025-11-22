#ifndef BATTLE_ACTIONSELECTIONSTATE_H
#define BATTLE_ACTIONSELECTIONSTATE_H

#include "../../Util/StateMachine/IState.h"
#include <SFML/Graphics.hpp>
#include "../BattleSystem.h"
#include "../UI/ActionSelectionUI.h"
#include "../UI/ActionSelectionUI.h"
#include "RunTurnState.h"
#include <vector>
#include <iostream>

// Declaracion forward para evitar dependencias circulares
class BattleSystem;

using namespace std;
using namespace sf;

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /* Clase que representa el estado de seleccion de accion */
    class ActionSelectionState : public IState<BattleSystem>
    {
    private:
        /* Opcion seleccionada */
        int selectedOption;
        /* Puntero al sistema de batalla */
        BattleSystem* battleSystemOwner;
        /* Interfaz de seleccion de accion */
        ActionSelectionUI actionSelectionUI;

    public:
        /* Constructor */
        ActionSelectionState();

        /* Metodos de estado */
        void enter(BattleSystem* owner) override;
        void handleEvent(BattleSystem* owner, Event event) override;
        void update(BattleSystem* owner) override;
        void draw(RenderWindow& window) override;
        void exit() override;
    };
} // namespace Battle

#endif // BATTLE_ACTIONSELECTIONSTATE_H
