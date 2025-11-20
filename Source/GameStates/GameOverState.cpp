#include "GameOverState.h"
#include "../GameController.h"
#include "../GameStates/MainMenuState.h" // Assuming we transition back to main menu or similar

/**
 * Constructor del Game Over
 * Inicializa la opcion seleccionada en 0
 */
GameOverState::GameOverState(bool isGameLost_) : selectedOption(0), isGameLost(isGameLost_)
{
    
}

/* Al entrar al Game Over, dibujamos e inicializamos la UI */
void GameOverState::enter(GameController* owner)
{
    cout << "Entering GameOverState" << endl;
    gameOverUI.setup(isGameLost);
}

/* Actualiza el estado del Game Over */
void GameOverState::update(GameController* owner)
{
    gameOverUI.updateDescriptionBox(selectedOption);
}

/* Manejo de eventos del Game Over */
void GameOverState::handleEvent(GameController* owner, Event event)
{
    // Verificamos si el evento es de tipo KeyPressed
    if (const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
    {
        if (keyPressed->code == Keyboard::Key::Z)
        {
            cout<<"Seleccionado opcion: " << selectedOption << endl;
            owner->stateMachine.changeState(new MainMenuState());
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
    cout << "Exiting GameOverState" << endl;
}

/* Getter para el nombre de este estado */
const char* GameOverState::getName() const
{
    return "GameMenuState";
}
