#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include "../Character/BaseCharacter.h"
#include <string>
using namespace std;

/* Configuracion global del juego */
class GlobalSettings
{
    public:
        /* Resolucion de grosor y altura */
        static const unsigned int SCREEN_WIDTH;
        static const unsigned int SCREEN_HEIGHT;

        /* Tamanio de fuente */
        static const int FONT_SIZE;
        /* Direccion de fuente */
        static const string FONT_PATH;
};

#endif // GLOBAL_SETTINGS_H
    