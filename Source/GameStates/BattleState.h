#ifndef BATTLESTATE_H
#define BATTLESTATE_H

#include <SFML/Graphics.hpp>
#include "../Util/StateMachine/IState.h"
#include "../GameController.h"
#include "../Battle/BattleSystem.h"
#include "../GameStates/GameMenuState.h"
#include "../GameStates/GameOverState.h"
#include "../Dialog/DialogManager.h"
#include <iostream>

using namespace std;
using namespace sf;

// Declaracion forward para evitar dependencias circulares
class GameController;

/**
 * Estado de Batalla
 * Maneja la logica de las batallas entre el jugador y los enemigos
 */
class BattleState : public IState<GameController>
{
private:
    /* Poseedor de GameController */
    GameController* owner;
    /* Sistema de batalla, usa namespace Battle*/
    Battle::BattleSystem* battleSystem;
    /* Jugador actual */
    Player* player;
    /* Personaje enemigo */
    Character enemyCharacter;
    /* Manejador de dialogos */
    DialogManager* dialogManager;

public:
    /* Constructor */
    BattleState(GameController& owner, Player* player, Character enemy);
    /* Destructor */
    ~BattleState();

    /* Se ejecuta al entrar al estado */
    void enter(GameController* owner) override;
    /* Maneja los eventos del estado */
    void handleEvent(GameController* owner, Event event) override;
    /* Actualiza la logica del estado */
    void update(GameController* owner) override;
    /* Dibuja el estado en la ventana */
    void draw(RenderWindow& window) override;
    /* Se ejecuta al salir del estado */
    void exit() override;
};

#endif // BATTLESTATE_H
