#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include "Util/StateMachine/StateMachine.h"

using namespace std;
using namespace sf;

/**
 * Clase encargada del controlador principal del juego.
 * Actua como el T, propietario de la maquina de estados.
 */
class GameController
{
private:
    /* Para manejar las entradas */
    void processEvents();
    /* Para dibujar en la ventana */
    void render();
    
public:
    /* Ventana principal del juego */
    RenderWindow window;
    /* Maquina de estados del juego */
    StateMachine<GameController> stateMachine;

    /* Constructor */
    GameController();

    /* Metodo para iniciar el bucle del juego */
    void runGameLoop();
};

#endif // GAMECONTROLLER_H
