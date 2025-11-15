#include "Dialog.h"

/* Constructor que recibe la cola de dialogo */
Dialog::Dialog(const queue<string>& dialogLines) : lines(dialogLines)
{
}

/* Getter de la cola de dialogo, CONST significa que no se modificara */
const queue<string>& Dialog::getLines() const
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