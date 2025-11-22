#include "ActionSelectionState.h"

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /**  
     * Constructor
     * Inicializa la opcion seleccionada en 0 y el puntero del sistema de batalla en nullptr
     */
    ActionSelectionState::ActionSelectionState() : selectedOption(0), battleSystemOwner(nullptr)
    {
    }

    /* Al entrar al estado */
    void ActionSelectionState::enter(BattleSystem* owner)
    {
        // Obtenemos el puntero al sistema de batalla
        this->battleSystemOwner = owner;
        // Configuramos la UI de la batalla
        this->battleSystemOwner->getBattleUI().setup(this->battleSystemOwner->getPlayer()->getCharacter(), this->battleSystemOwner->getEnemy());
        // Actualizamos los puntos de definitiva del jugador en la UI
        this->battleSystemOwner->getBattleUI().updatePlayerUltimatePoints(this->battleSystemOwner->getPlayer()->getUltimatePoints());
        // Configuramos la UI de seleccion de accion
        actionSelectionUI.setup();
    }

    /* Maneja los eventos del estado */
    void ActionSelectionState::handleEvent(BattleSystem* owner, Event event)
    {
        // Si se presiona una tecla
        if(const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
        {
            // Moverse a la izquierda
            if(keyPressed->code == Keyboard::Key::A)
            {
                selectedOption = (selectedOption - 1 + 4) % 4; // 4 opciones totales

            }
            // Moverse a la derecha
            else if(keyPressed->code == Keyboard::Key::D)
            {
                selectedOption = (selectedOption + 1) % 4; // 4 opciones totales
            }
            // Seleccionar opcion
            else if(keyPressed->code == Keyboard::Key::E)
            {
                switch (selectedOption)
                {
                    case 0: // Luchar
                        owner->setChosenAction(ActionType::Fight);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                    case 1: // Especial
                        owner->setChosenAction(ActionType::Special);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                    case 2: // En Guardia
                        owner->setChosenAction(ActionType::Guard);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                    case 3: // Escapar
                        owner->setChosenAction(ActionType::Escape);
                        owner->getStateMachine().changeState(new RunTurnState());
                        break;
                }
            }
        }
    }

    /* Actualiza el estado */
    void ActionSelectionState::update(BattleSystem* owner)
    {
        // Actualiza la descripcion en la caja de dialogo segun la opcion seleccionada
        actionSelectionUI.updateDialogBoxDescription(selectedOption);
    }

    /* Dibuja el estado */
    void ActionSelectionState::draw(RenderWindow& window)
    {
        // Dibuja la interfaz de seleccion de accion
        actionSelectionUI.draw(window, selectedOption);
    }

    /* Se ejecuta al salir del estado */
    void ActionSelectionState::exit()
    {
        // Nada que limpiar por ahora, se hace en el destructor
    }
} // namespace Battle

