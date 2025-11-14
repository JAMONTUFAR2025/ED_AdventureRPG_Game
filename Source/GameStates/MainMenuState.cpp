#include "MainMenuState.h"
#include "../GameController.h"
#include <iostream>
#include <vector>

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
    mainMenuUI.setup(owner);
}

/* Ejecuta la logica del menu principal, se manejan las entradas */
void MainMenuState::execute(GameController* owner, Event event)
{
    mainMenuUI.handleInput(event, owner, selectedOption);
}

/* Dibuja el menu principal */
void MainMenuState::draw(RenderWindow& window)
{
    mainMenuUI.draw(window, selectedOption);
}

/* Al salir del menu, realizamos las acciones necesarias */
void MainMenuState::exit()
{
    cout<<"Exiting MainMenuState"<<endl;
}

/* Obtiene el nombre del estado, para depuracion */
const char* MainMenuState::getName() const
{
    return "MainMenuState";
}
