#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include "Dialog.h"
#include "../UI/DialogBox.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <queue>

using namespace std;
using namespace sf;

/**
 * Clase para manejar los dialogos en el juego
 */
class DialogManager
{
private:
    /* Caja de dialogo para mostrar texto */
    DialogBox dialogBox;
    /* Dialogo actual que se esta mostrando, es un puntero */
    Dialog* currentDialog;
    /* Cola para almacenar los dialogos pendientes, almacena punteros */
    queue<Dialog*> dialogQueue;
    /* Linea actual del dialogo */
    int currentLine;
    /* Caracter actual en la linea del dialogo */
    int currentCharacter;
    /* Reloj para controlar el tiempo entre caracteres */
    Clock clock;
    /* Indica si un dialogo esta activo */
    bool isDialogActive;

    /* Procesa el siguiente dialogo en la cola */
    void processNextDialog();
public:
    /* Constructor */
    DialogManager();
    /* Inicia un dialogo */
    void startDialog(Dialog* dialog);
    /* Actualiza el estado del dialogo */
    void update();
    /* Dibuja la caja de dialogo en la ventana */
    void draw(RenderWindow& window);
    /* Indica si un dialogo esta activo */
    bool isActive();
    /* Avanza a la siguiente linea del dialogo */
    void nextLine();
};

#endif // DIALOGMANAGER_H
