#ifndef BATTLE_RUNTURNSTATE_H
#define BATTLE_RUNTURNSTATE_H

#include "../../Util/StateMachine/IState.h"
#include "../../GameController.h"
#include "../../GameStates/GameMenuState.h"
#include "../BattleSystem.h"
#include "ActionSelectionState.h"
#include <iostream>
#include <queue>
#include <cstdlib>

// Declaracion forward para evitar dependencias circulares
class BattleSystem;

using namespace std;
using namespace sf;

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /* Enum para representar el resultado de la batalla */
    enum class BattleResult
    {
        Victory,
        Defeat,
        Escape
    };
    
    /* Clase que representa el estado de ejecucion de un turno */
    class RunTurnState : public IState<BattleSystem>
    {
    private:
        /* Enum para representar los pasos del turno */
        enum class TurnStep
        {
            START,                  // Inicio del turno
            POST_INTRO_MESSAGE,     // Mensaje de introduccion
            PLAYER_ACTION,          // Accion del jugador
            INVALID_ACTION,         // Accion invalida
            ENEMY_CHECK,            // Verificacion del enemigo
            ENEMY_ACTION,           // Accion del enemigo
            PLAYER_CHECK,           // Verificacion del jugador
            FINISH_TURN,            // Fin del turno
            SHOW_EXP_RESULTS,       // Muestra los resultados de experiencia
            SHOW_LEVEL_UP_RESULTS,  // Muestra los resultados de subida de nivel
            FINALIZE_BATTLE         // Finaliza la batalla
        };
        
        /* Paso actual del turno */
        TurnStep currentStep;
        /* Puntero al sistema de batalla */
        BattleSystem* battleSystemOwner = nullptr;
        /* Resultado de la batalla */
        BattleResult result;
        /* Indica si el mensaje de experiencia esta en cola */
        bool expMessageQueued;

        /* Indica si el jugador ha subido de nivel */
        bool levelUpOccurred;
            
    public:
        /* Constructor */
        RunTurnState();

        /* Metodos de estado */
        void enter(BattleSystem* owner) override;
        void handleEvent(BattleSystem* owner, Event event) override;
        void update(BattleSystem* owner) override;
        void draw(RenderWindow& window) override;
        void exit() override;
    };
} // namespace Battle

#endif // BATTLE_RUNTURNSTATE_H
