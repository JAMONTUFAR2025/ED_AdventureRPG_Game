#include "Dialog.h"

/* Constructor que recibe la cola de dialogo */
Dialog::Dialog(queue<string>& dialogLines) : lines(dialogLines)
{
}

/* Getter de la cola de dialogo, significa que no se modificara */
queue<string>& Dialog::getLines() 
{
    return lines;
}

/* Elimina la linea actual del dialogo */
void Dialog::popLine()
{
    // Elimina la linea actual si no esta vacia
    if(!lines.empty())
    {
        lines.pop();
    }
}