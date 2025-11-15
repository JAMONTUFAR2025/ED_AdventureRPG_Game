#include "GameMenuState.h"
#include "../GameController.h"
#include "../GameStates/MainMenuState.h" // Assuming we transition back to main menu or similar

/**
 * Constructor del Menu del Juego
 * Inicializa la opcion seleccionada en 0
 */
GameMenuState::GameMenuState() : selectedOption(0)
{
}

/* Al entrar al menu, dibujamos e inicializamos la UI */
void GameMenuState::enter(GameController* owner)
{
    cout << "Entering GameMenuState" << endl;
    gameMenuUI.setup(owner);
    gameMenuUI.updateDialogBoxDescription(selectedOption); // Set initial description
}

/* Actualiza el estado del menu del juego */
void GameMenuState::update(GameController* owner)
{
    // No hay logica de actualizacion compleja en este menu, solo se actualiza la UI
}

/* Manejo de eventos del menu del juego */
void GameMenuState::handleEvent(GameController* owner, Event event)
{
    // Verificamos si el evento es de tipo KeyPressed
    if (const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
    {
        // Navegacion por las opciones del menu
        if (keyPressed->code == Keyboard::Key::Up)
        {
            selectedOption = (selectedOption - 1 + 4) % 4; // 4 is the number of options
            gameMenuUI.updateDialogBoxDescription(selectedOption);
        }
        else if (keyPressed->code == Keyboard::Key::Down)
        {
            selectedOption = (selectedOption + 1) % 4; // 4 is the number of options
            gameMenuUI.updateDialogBoxDescription(selectedOption);
        }
        else if (keyPressed->code == Keyboard::Key::Z)
        {
            switch (selectedOption)
            {
                case 0: // Explorar
                    cout << "Seleccionado: Explorar" << endl;
                    // TODO: Implement actual exploration logic or state change
                    break;
                case 1: // Comprar pocion de curacion (10 puntos)
                    cout << "Seleccionado: Comprar pocion de curacion (10 puntos)" << endl;
                    // TODO: Implement potion purchase logic
                    break;
                case 2: // Comprar trofeo (1000 puntos)
                    cout << "Seleccionado: Comprar trofeo (1000 puntos)" << endl;
                    // TODO: Implement trophy purchase logic
                    break;
                case 3: // Salir
                    cout << "Seleccionado: Salir. Cerrando juego." << endl;
                    owner->window.close(); // Close the game window
                    break;
            }
        }
    }
}

/* Dibuja el menu del juego en la ventana */
void GameMenuState::draw(RenderWindow& window)
{
    gameMenuUI.draw(window, selectedOption);
}

/* Al salir del menu, realizamos las acciones necesarias */
void GameMenuState::exit()
{
    cout << "Exiting GameMenuState" << endl;
}

/* Getter para el nombre de este estado */
const char* GameMenuState::getName() const
{
    return "GameMenuState";
}
