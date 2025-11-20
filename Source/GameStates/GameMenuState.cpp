#include "GameMenuState.h"
#include "../GameController.h"
#include "../GameStates/BattleState.h" // Assuming we transition to battle state
#include "../GameStates/GameOverState.h" // For transitioning to GameOverState
#include "../GameStates/MainMenuState.h" // Assuming we transition back to main menu or similar
#include "../Character/Character.h" // Include Character for creating instances
#include "../Character/Player.h" // Include Player for creating instances
#include "../Character/BaseCharacter.h" // Include BaseCharacter for creating instances
#include "../Character/CharacterDB.h" // Include CharacterDB for accessing base characters

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
    this->owner = owner;
    cout << "Entering GameMenuState" << endl;
    Player* player = owner->getPlayer();
    if (player)
    {
        gameMenuUI.setup(owner, player);
    }
    else
    {
        // This should not happen if the game logic is correct
        cout << "CRITICAL ERROR: Player is null when entering GameMenuState." << endl;
    }
}

/* Actualiza el estado del menu del juego */
void GameMenuState::update(GameController* owner)
{
    if (owner->getDialogManager()->isActive())
    {
        return; // Wait for messages to finish displaying
    }
    gameMenuUI.updateDescriptionBox(selectedOption);
}

/* Manejo de eventos del menu del juego */
void GameMenuState::handleEvent(GameController* owner, Event event)
{
    // Verificamos si el evento es de tipo KeyPressed
    if (const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
    {
        // Si hay un dialogo activo, se avanza el dialogo
        if (owner->getDialogManager()->isActive())
        {
            if (keyPressed->code == Keyboard::Key::E)
            {
                owner->getDialogManager()->nextLine();
            }
            return;
        }

        // Navegacion por las opciones del menu
        if (keyPressed->code == Keyboard::Key::W)
        {
            selectedOption = (selectedOption - 1 + 4) % 4; // 4 is the number of options
        
        }
        else if (keyPressed->code == Keyboard::Key::S)
        {
            selectedOption = (selectedOption + 1) % 4; // 4 is the number of options
        
        }
        else if (keyPressed->code == Keyboard::Key::E)
        {
            Player* player = owner->getPlayer();
            if (!player)
            {
                cout << "Error: Player not found!" << endl;
                return;
            }

            switch (selectedOption)
            {
                case 0: // Explorar
                {
                    cout << "Seleccionado: Explorar" << endl;
                    
                    // Create placeholder enemy character
                    CharacterDB characterDB;
                    BaseCharacter enemyBase = characterDB.getRandomBaseCharacter(); // Get a random enemy
                    Character enemyChar(enemyBase, player->getCharacter().getLevel()); // BaseCharacter, mismo nivel que el jugador

                    owner->stateMachine.changeState(new BattleState(*owner, player, enemyChar));
                    break;
                }
                case 1: // Comprar pocion de curacion (10 puntos)
                {
                    cout << "Seleccionado: Comprar pocion." << endl;
                    std::queue<std::string> dialogQueue;
                    if (player->getCharacter().getCurrentHealth() == player->getCharacter().getMaxHealth())
                    {
                        dialogQueue.push("Tus PS estan al maximo!");
                        owner->getDialogManager()->startDialog(new Dialog(dialogQueue));
                    }
                    else if(player->getPoints() >= 10)
                    {
                        player->gainPoints(-10);
                        player->getCharacter().setCurrentHealth(player->getCharacter().getMaxHealth());
                        dialogQueue.push("PS restaurados al maximo!");
                        owner->getDialogManager()->startDialog(new Dialog(dialogQueue));
                    }
                    else
                    {
                        dialogQueue.push("Puntos insuficientes!");
                        owner->getDialogManager()->startDialog(new Dialog(dialogQueue));
                    }
                    break;
                }
                case 2: // Comprar trofeo (1000 puntos)
                {
                    cout << "Seleccionado: Comprar trofeo." << endl;
                    std::queue<std::string> dialogQueue;
                    if(player->getPoints() >= 200)
                    {
                        player->gainPoints(-200);
                        owner->stateMachine.changeState(new GameOverState(false)); // false indicates the game is won
                    }
                    else
                    {
                        dialogQueue.push("Puntos insuficientes!");
                        owner->getDialogManager()->startDialog(new Dialog(dialogQueue));
                    }
                    break;
                }
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
    gameMenuUI.draw(window, selectedOption, owner->getDialogManager()->isActive());
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
