#include "BattleState.h"
#include "../GameController.h"
#include "../GameStates/GameMenuState.h"
#include "../GameStates/GameOverState.h"
#include <iostream>

/**
 * Constructor
 * Inicializa los atributos con los parametros recibidos
 */
BattleState::BattleState(GameController& owner, Player* player, Character enemy)
    : player(player), enemyCharacter(enemy), battleSystem(nullptr)
{
}

/**
 * Destructor
 * Libera la memoria del sistema de batalla
 */
BattleState::~BattleState()
{
    delete battleSystem;
}

/* Se ejecuta al entrar al estado */
void BattleState::enter(GameController* owner)
{
    // Guarda el propietario en un atributo puntero
    this->owner = owner;
    // Inicializa el sistema de batalla
    battleSystem = new Battle::BattleSystem(owner, player, enemyCharacter);
    battleSystem->startBattle();
}

/* Maneja los eventos del estado */
void BattleState::handleEvent(GameController* owner, sf::Event event)
{
    // Pasa el evento al sistema de batalla
    if (battleSystem)
    {
        battleSystem->handleEvent(event);
    }
}

/* Actualiza la logica del estado */
void BattleState::update(GameController* owner)
{
    // Si hay un sistema de batalla, actualiza su logica
    if (battleSystem)
    {
        // Actualiza el sistema de batalla
        battleSystem->update();
        // Si la batalla ha terminado, regresar al menu del juego o al game over
        if (battleSystem->isBattleOver())
        {
            // Verifica si el jugador perdio
            if(battleSystem->getPlayer()->getCharacter().getCurrentHealth() <= 0)
            {
                owner->getStateMachine().changeState(new GameOverState(true)); // True significa que el juego se perdio
                return; 
            }
            
            // Regresar al menu del juego si el jugador gano
            owner->getStateMachine().changeState(new GameMenuState());
            return; 
        }
    }
}

/* Dibuja el estado en la ventana */
void BattleState::draw(sf::RenderWindow& window)
{
    // Si hay un sistema de batalla, dibuja sus elementos
    if (battleSystem)
    {
        // Dibuja el sistema de batalla
        battleSystem->draw(window, owner->getDialogManager()->isActive());
    }
}

/* Se ejecuta al salir del estado */
void BattleState::exit()
{
    // Actualmente no hay acciones necesarias al salir del estado de batalla, ya que se maneja en el destructor de las clases correspondientes
}
