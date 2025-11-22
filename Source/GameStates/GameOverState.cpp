#include "GameOverState.h"

/**
 * Constructor del Game Over
 * Inicializa la opcion seleccionada en 0 y la bandera de perdida de juego
 */
GameOverState::GameOverState(bool isGameLost_) : selectedOption(0), isGameLost(isGameLost_)
{
}

/* Al entrar al Game Over, dibujamos e inicializamos la UI */
void GameOverState::enter(GameController* owner)
{
    gameOverUI.setup(isGameLost);
}

/* Actualiza el estado del Game Over */
void GameOverState::update(GameController* owner)
{
    gameOverUI.updateDescriptionBox();
}

/* Manejo de eventos del Game Over */
void GameOverState::handleEvent(GameController* owner, Event event)
{
    // Verificamos si se pulso una tecla
    if(const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
    {
        // Seleccion de opcion
        if(keyPressed->code == Keyboard::Key::E)
        {
            owner->destroyPlayer(); // Destruye el jugador actual
            owner->getStateMachine().changeState(new MainMenuState());
        }
    }
}

/* Dibuja el menu del juego en la ventana */
void GameOverState::draw(RenderWindow& window)
{
    gameOverUI.draw(window, selectedOption);
}

/* Al salir del menu, realizamos las acciones necesarias */
void GameOverState::exit()
{
    // Actualmente no hay acciones necesarias al salir del menu principal, ya que se maneja en el destructor de las clases correspondientes
}