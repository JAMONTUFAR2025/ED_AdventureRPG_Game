#include "MainMenuState.h"

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
    // Inicializa la UI del menu principal
    mainMenuUI.setup(owner);
}

/* Actualiza el estado del menu principal */
void MainMenuState::update(GameController* owner)
{
    // Actualiza la descripcion del menu segun la opcion seleccionada
    mainMenuUI.updateDescriptionBox(selectedOption);
}

/* Manejo de eventos del menu principal */
void MainMenuState::handleEvent(GameController* owner, Event event)
{   
    // Verificamos si el evento es de tipo KeyPressed
    if(const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
    {
        // Navegacion por las opciones del menu principal
        if(keyPressed->code == Keyboard::Key::W || keyPressed->code == Keyboard::Key::S)
        {
            selectedOption = selectedOption == 0 ? 1 : 0;
        }
        // Seleccion de opcion
        else if(keyPressed->code == Keyboard::Key::E)
        {
            // Jugar
            if(selectedOption == 0)
            {
                // Creamos al jugador y cambiamos al estado del menu del juego
                owner->createPlayer();
                owner->getStateMachine().changeState(new GameMenuState());
            }
            // Salir
            else if(selectedOption == 1)
            {
                owner->getWindow().close();
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
    // Actualmente no hay acciones necesarias al salir del menu principal, ya que se maneja en el destructor de las clases correspondientes
}
