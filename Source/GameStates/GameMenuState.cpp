#include "GameMenuState.h"
#include "../GameController.h"
#include "../GameStates/MainMenuState.h" // Assuming we transition back to main menu or similar
#include "../GameStates/BattleState.h" // Assuming we transition to battle state
#include "../Character/Character.h" // Include Character for creating instances
#include "../Character/Player.h" // Include Player for creating instances
#include "../Character/BaseCharacter.h" // Include BaseCharacter for creating instances

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
}

/* Actualiza el estado del menu del juego */
void GameMenuState::update(GameController* owner)
{
    gameMenuUI.updateDescriptionBox(selectedOption);
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
        
        }
        else if (keyPressed->code == Keyboard::Key::Down)
        {
            selectedOption = (selectedOption + 1) % 4; // 4 is the number of options
        
        }
        else if (keyPressed->code == Keyboard::Key::Z)
        {
            switch (selectedOption)
            {
                case 0: // Explorar
                {
                    cout << "Seleccionado: Explorar" << endl;
                    Player* player = owner->getPlayer();
                    if (!player)
                    {
                        cout << "Error: Player not found!" << endl;
                        break;
                    }
                    
                    // Create placeholder enemy character
                    BaseCharacter enemyBase("Enemigo", 50, 8, 2, 20); // Name, MaxHealth, Attack, Defense, ExpYield
                    Character enemyChar(enemyBase, 1); // BaseCharacter, initialLevel

                    owner->stateMachine.changeState(new BattleState(*owner, player, enemyChar));
                    break;
                }
                case 1: // Comprar pocion de curacion (10 puntos)
                    cout << "Seleccionado: Comprar pocion de curacion (10 puntos)" << endl;
                    // TODO: Implement potion purchase logic
                    break;
                case 2: // Comprar trofeo (1000 puntos)
                    cout << "Seleccionado: Comprar trofeo (1000 puntos)" << endl;
                    // TODO: Implement trophy purchase logic
                    break;
                case 3: // Salir
                    cout << "Seleccionado: Salir. Volviendo al menu principal." << endl;
                    owner->destroyPlayer();
                    owner->stateMachine.changeState(new MainMenuState());
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
