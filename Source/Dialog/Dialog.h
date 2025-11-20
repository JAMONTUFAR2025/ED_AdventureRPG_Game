#ifndef DIALOG_H
#define DIALOG_H

#include<string>
#include<queue>

using namespace std;

/**
 * Clase para manejar dialogos en el juego
 */
class Dialog
{
    private:
        /* Cola de dialogo */
        queue<string> lines;

    public:
        /* Constructor que recibe la cola de dialogo */
        Dialog(queue<string>& dialogLines);
        /* Getter de la cola de dialogo, significa que no se modificara */
        queue<string>& getLines();
        /* Elimina la linea actual del dialogo */
        void popLine();
};

#endif // DIALOG_H