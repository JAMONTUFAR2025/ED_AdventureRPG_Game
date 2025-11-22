#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include <SFML/Graphics.hpp>
#include "../Util/StateMachine/StateMachine.h"
#include "../GameController.h"
#include "../Character/Player.h"
#include "UI/BattleUI.h"
#include "../Dialog/DialogManager.h"
#include "States/ActionSelectionState.h"
#include "States/RunTurnState.h"

using namespace std;
using namespace sf;

// Declaracion forward para evitar dependencias circulares
class GameController;

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /* Clase enum para representar los tipos de acciones en batalla */
    enum class ActionType
    {
        None,
        Fight,
        Special,
        Guard,
        Escape
    };

    /* Clase que representa el sistema de batalla */
    class BattleSystem
    {
    private:
        /* Banderines */
        /* La batalla ha iniciado */
        bool battleStarted;
        /* La batalla ha terminado */
        bool battleIsOver;
        /* El jugador esta en guardia */
        bool isPlayerGuarding;

        /* Indicadores de actualizacion */
        bool hasHealthBarUpdated;
        bool hasPlayerLeveledUp;
        bool hasUltimatePointsUpdated;
    public:
        /* Puntero al controlador del juego que posee este sistema de batalla */
        GameController* owner;
        /* Maquina de subestados para gestionar los estados de la batalla */
        StateMachine<BattleSystem> stateMachine;

        /* Personaje jugador */
        Player* player;
        /* Personaje enemigo */
        Character enemy;
        /* Interfaz de usuario de la batalla */
        BattleUI battleUI;
        /* Gestor de dialogos */
        DialogManager dialogManager;

        /* Accion elegida por el jugador */
        ActionType chosenAction;

        /* Constructor */
        BattleSystem(GameController* owner, Player* playerCharacter, Character& enemyCharacter);

        /* Metodos para controlar la batalla */
        void startBattle();
        void handleEvent(Event event);
        void update();
        void draw(RenderWindow& window, bool isDialogActive);

        /* Getters y Setters */
        Player* getPlayer();
        Character& getEnemy();
        BattleUI& getBattleUI();
        DialogManager& getDialogManager();
        
        ActionType getChosenAction();
        void setChosenAction(ActionType action);
        
        StateMachine<BattleSystem>& getStateMachine();

        bool getBattleStarted();
        void setBattleStarted(bool started);

        bool isBattleOver();
        void endBattle();

        bool getPlayerGuarding();
        void setPlayerGuarding(bool guarding);

        bool getHasHealthBarUpdated();
        void setHasHealthBarUpdated(bool updated);

        bool getHasPlayerLeveledUp();
        void setHasPlayerLeveledUp(bool leveledUp);

        bool getHasUltimatePointsUpdated();
        void setHasUltimatePointsUpdated(bool updated);
    };
} // namespace Battle

#endif // BATTLESYSTEM_H
