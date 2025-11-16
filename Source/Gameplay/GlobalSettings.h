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

        /* Jugador */
        inline static const BaseCharacter playerBaseCharacter = BaseCharacter("Hero", 20, 30, 40, 0);

        /* Puntos del jugador */
        static int playerPoints;
        /* Puntos de definitiva del juegador */
        static int playerDefinitivePoints;
};

#endif // GLOBAL_SETTINGS_H
    