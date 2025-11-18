#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include "../Character/BaseCharacter.h"

/* Configuracion global del juego */
class GlobalSettings
{
    public:
        /* Resolucion de grosor y altura */
        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 600;

        /* Tamanio de fuente */
        static const int FONT_SIZE = 32;

        /* Puntos del jugador */
        static int playerPoints;
        /* Puntos de definitiva del juegador */
        static int playerDefinitivePoints;
};

#endif // GLOBAL_SETTINGS_H
    