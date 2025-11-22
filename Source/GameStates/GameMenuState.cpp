#include "GameMenuState.h"

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
    // Guardamos el propietario en un atributo puntero
    this->owner = owner;
    // Guardamos el jugador actual
    Player* player = owner->getPlayer();
    if(player)
    {
        // Configuramos la UI
        gameMenuUI.setup(owner, player);
    }
}

/* Actualiza el estado del menu del juego */
void GameMenuState::update(GameController* owner)
{
    // Si hay un dialogo activo, regresar y desactivar actualizacion de descripcion
    if(owner->getDialogManager()->isActive())
    {
        return;
    }
    // Actualiza la descripcion del menu segun la opcion seleccionada
    gameMenuUI.updateDescriptionBox(selectedOption);
}

/* Manejo de eventos del menu del juego */
void GameMenuState::handleEvent(GameController* owner, Event event)
{
    // Verificamos si el evento es de tipo KeyPressed
    if(const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>()){
        // Si hay un dialogo activo, se avanza el dialogo
        if(owner->getDialogManager()->isActive())
        {
            // Avanza el dialogo si se presiona E
            if(keyPressed->code == Keyboard::Key::E)
            {
                owner->getDialogManager()->nextLine();
            }
            // Esto evita cambiar de opcion si hay un dialogo activo
            return;
        }

        // Navegacion por las opciones del menu
        // Subir entre 4 opciones
        if(keyPressed->code == Keyboard::Key::W)
        {
            selectedOption = (selectedOption - 1 + 4) % 4;
        }
        // Bajar entre 4 opciones
        else if(keyPressed->code == Keyboard::Key::S)
        {
            selectedOption = (selectedOption + 1) % 4;
        }
        // Seleccion de opcion
        else if(keyPressed->code == Keyboard::Key::E)
        {
            // Obtener el jugador actual
            Player* player = owner->getPlayer();
            if(!player)
            {
                return;
            }

            switch (selectedOption)
            {
                case 0: // Explorar
                {
                    // Iniciamos un combate contra un enemigo aleatorio
                    CharacterDB characterDB;
                    BaseCharacter enemyBase = characterDB.getRandomBaseCharacter();
                    Character enemyChar(enemyBase, player->getCharacter().getLevel());

                    owner->getStateMachine().changeState(new BattleState(*owner, player, enemyChar));
                    break;
                }
                case 1: // Comprar pocion de curacion (10 puntos)
                {
                    // Cola de dialogos a mostrar
                    queue<string> dialogQueue;
                    // Evitar comprar si ya tiene la salud al maximo
                    if(player->getCharacter().getCurrentHealth() == player->getCharacter().getMaxHealth())
                    {
                        dialogQueue.push("Tus PS estan al maximo!");
                        owner->getDialogManager()->startDialog(new Dialog(dialogQueue));
                    }
                    // Comprar pocion de curacion si hay puntos suficientes
                    else if(player->getPoints() >= 10)
                    {
                        player->gainPoints(-10);
                        player->getCharacter().setCurrentHealth(player->getCharacter().getMaxHealth());
                        dialogQueue.push("PS restaurados al maximo!");
                        owner->getDialogManager()->startDialog(new Dialog(dialogQueue));
                    }
                    // No hay puntos suficientes
                    else
                    {
                        dialogQueue.push("Puntos insuficientes!");
                        owner->getDialogManager()->startDialog(new Dialog(dialogQueue));
                    }
                    break;
                }
                case 2: // Comprar trofeo (200 puntos)
                {
                    // Cola de dialogos a mostrar
                    queue<string> dialogQueue;
                    // Comprar trofeo si hay puntos suficientes
                    if(player->getPoints() >= 200)
                    {
                        player->gainPoints(-200);
                        // False significa que el juego no se perdio
                        owner->getStateMachine().changeState(new GameOverState(false));
                    }
                    // No hay puntos suficientes
                    else
                    {
                        dialogQueue.push("Puntos insuficientes!");
                        owner->getDialogManager()->startDialog(new Dialog(dialogQueue));
                    }
                    break;
                }
                case 3: // Salir
                    // Regresar al menu principal y destruir al jugador
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
