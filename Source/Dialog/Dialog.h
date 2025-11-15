#ifndef DIALOG_H
#define DIALOG_H

#include<string>
#include<vector>

using namespace std;

/**
 * Clase para manejar dialogos en el juego
 */
class Dialog
{
    private:
        /* Lineas de dialogo */
        vector<string> lines;

    public:
        /* Constructor que recibe las lineas de dialogo */
        Dialog(const vector<string>& dialogLines);
        /* Getter de las lineas de dialogo, CONST significa que no se modificara */
        const vector<string>& getLines() const;
};

#endif // DIALOG_H