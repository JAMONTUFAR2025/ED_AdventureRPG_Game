#include "../Source/GameController.h"



/** Punto de entrada de la aplicacion */
int main()
{
    /* Creamos el controlador del juego */
    GameController gameController;
    /* Iniciar bucle del juego */
    gameController.runGameLoop();

    return 0;
}