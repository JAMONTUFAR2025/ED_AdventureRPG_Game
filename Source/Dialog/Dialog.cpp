#include "Dialog.h"

/* Constructor que recibe las lineas de dialogo */
Dialog::Dialog(const vector<string>& dialogLines) : lines(dialogLines)
{
}

/* Getter de las lineas de dialogo, CONST significa que no se modificara */
const vector<string>& Dialog::getLines() const
{
    return lines;
}