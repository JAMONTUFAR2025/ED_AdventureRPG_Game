#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include "Util/StateMachine/StateMachine.h"
#include "Character/Player.h"
#include "Dialog/DialogManager.h"
#include "Gameplay/GlobalSettings.h"
#include "GameStates/MainMenuState.h"

using namespace std;
using namespace sf;

/**
 * Clase encargada del controlador principal del juego.
 * Actua como el T, propietario de la maquina de estados.
 */
class GameController
{
private:
    /* Ventana principal del juego */
    RenderWindow window;

    /* Personaje del jugador */
    Player* player;
    /* Maquina de estados principal del juego */
    StateMachine<GameController> stateMachine;
    /* Manejador de dialogos */
    DialogManager dialogManager;

    /* Para manejar las entradas */
    void processEvents();
    /* Para dibujar en la ventana */
    void render();
    
public:
    /* Constructor */
    GameController();

    /* Metodo para iniciar el bucle del juego */
    void runGameLoop();

    /* Getter para la ventana principal */
    RenderWindow& getWindow();

    /* Crea a el jugador */
    void createPlayer();
    /* Destruye el jugador */
    void destroyPlayer();
    /* Obtiene el jugador */
    Player* getPlayer();

    /* Getter para la maquina de estados */
    StateMachine<GameController>& getStateMachine();
    /* Setter para la maquina de estados */
    void setStateMachine(StateMachine<GameController>& stateMachine);

    /* Getter para el manejador de dialogos */
    DialogManager* getDialogManager();
    /* Setter para el manejador de dialogos */
    void setDialogManager(DialogManager& dialogManager);
};

#endif // GAMECONTROLLER_H
