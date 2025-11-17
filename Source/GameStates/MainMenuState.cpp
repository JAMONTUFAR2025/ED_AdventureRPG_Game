#include "MainMenuState.h"
#include "../GameController.h"
#include <iostream>
#include <queue>
#include <string>
#include "GameMenuState.h"

/**
 * Constructor del Menu Principal
 * Inicializa la opcion seleccionada en 0
 */
MainMenuState::MainMenuState() : selectedOption(0)
{
}

/* Al entrar al menu, dibujamos e inicializamos la UI */
void MainMenuState::enter(GameController* owner)
{
    cout<<"Entering MainMenuState"<<endl;
    // Inicializa la UI del menu principal
    mainMenuUI.setup(owner);
}

/* Actualiza el estado del menu principal */
void MainMenuState::update(GameController* owner)
{
    // Actualiza la descripcion del menu segun la opcion seleccionada
    mainMenuUI.updateDescriptionBox(selectedOption);
}

void MainMenuState::handleEvent(GameController* owner, Event event)
{   
    // Verificamos si el evento es de tipo KeyPressed
    if (const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
    {
        // Navegacion por las opciones del menu
        if (keyPressed->code == Keyboard::Key::Up || keyPressed->code == Keyboard::Key::Down)
        {
            selectedOption = selectedOption == 0 ? 1 : 0;
        }
        else if (keyPressed->code == Keyboard::Key::Z)
        {
            if (selectedOption == 0)
            {
                cout<<"Selected: Jugar"<<endl;
                owner->stateMachine.changeState(new GameMenuState());
            }
            else if (selectedOption == 1)
            {
                cout<<"Selected: Salir"<<endl;
                owner->window.close();
            }
        }
    }
}

/* Dibuja la ventana del menu principal */
void MainMenuState::draw(RenderWindow& window)
{
    // Dibuja la UI del menu principal
    mainMenuUI.draw(window, selectedOption);
}

/* Al salir del menu, realizamos las acciones necesarias */
void MainMenuState::exit()
{
    cout<<"Exiting MainMenuState"<<endl;
    // MainMenuState no posee el dialogo, DialogManager gestiona su ciclo de vida
}

/* Getter para el nombre de este estado */
const char* MainMenuState::getName() const
{
    return "MainMenuState";
}
