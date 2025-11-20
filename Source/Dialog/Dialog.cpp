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

void Dialog::popLine()
{
    if (!lines.empty())
    {
        lines.pop();
    }
}