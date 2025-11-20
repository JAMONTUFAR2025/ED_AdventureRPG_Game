#include "GameMenuState.h"
#include "../GameController.h"
#include "../GameStates/BattleState.h"
#include "../GameStates/GameOverState.h"
#include "../GameStates/MainMenuState.h"
#include "../Character/Character.h"
#include "../Character/Player.h"
#include "../Character/BaseCharacter.h"
#include "../Character/CharacterDB.h"

/**
 * Constructor del Menu del Juego
 * Inicializa la opcion seleccionada en 0
 */
GameMenuState::GameMenuState() : selectedOption(0), owner(nullptr)
{
}

/* Al entrar al menu, dibujamos e inicializamos la UI */
void GameMenuState::enter(GameController* owner)
{
    this->owner = owner;
    Player* player = owner->getPlayer();
    if (player)
    {
        gameMenuUI.setup(owner, player);
    }
}

/* Actualiza el estado del menu del juego */
void GameMenuState::update(GameController* owner)
{
    if (owner->getDialogManager()->isActive())
    {
        return;
    }
    gameMenuUI.updateDescriptionBox(selectedOption);
}

/* Manejo de eventos del menu del juego */
void GameMenuState::handleEvent(GameController* owner, Event event)
{
    // Verificamos si el evento es de tipo KeyPressed
    if (const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>()){
        // Si hay un dialogo activo, se avanza el dialogo
        if (owner->getDialogManager()->isActive())
        {
            if (keyPressed->code == Keyboard::Key::E) // Changed from Z to E
            {
                owner->getDialogManager()->nextLine();
            }
            return;
        }

        // Navegacion por las opciones del menu
        if (keyPressed->code == Keyboard::Key::W)
        {
            selectedOption = (selectedOption - 1 + 4) % 4;
        
        }
        else if (keyPressed->code == Keyboard::Key::S)
        {
            selectedOption = (selectedOption + 1) % 4;
        
        }
        else if (keyPressed->code == Keyboard::Key::E)
        {
            Player* player = owner->getPlayer();
            if (!player)
            {
                return;
            }

            switch (selectedOption)
            {
                case 0: // Explorar
                {
                    // Create placeholder enemy character
                    CharacterDB characterDB;
                    BaseCharacter enemyBase = characterDB.getRandomBaseCharacter(); // Get a random enemy
                    Character enemyChar(enemyBase, player->getCharacter().getLevel()); // BaseCharacter, mismo nivel que el jugador

                    owner->getStateMachine().changeState(new BattleState(*owner, player, enemyChar));
                    break;
                }
                case 1: // Comprar pocion de curacion (10 puntos)
                {
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
                    std::queue<std::string> dialogQueue;
                    if(player->getPoints() >= 200)
                    {
                        player->gainPoints(-200);
                        owner->getStateMachine().changeState(new GameOverState(false)); // False significa que el juego no se perdio
                    }
                    else
                    {
                        dialogQueue.push("Puntos insuficientes!");
                        owner->getDialogManager()->startDialog(new Dialog(dialogQueue));
                    }
                    break;
                }
                case 3: // Salir
                    owner->destroyPlayer();
                    owner->getStateMachine().changeState(new MainMenuState());
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
}
