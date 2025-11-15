#include "DialogManager.h"

/**
 * Constructor del DialogManager
 * Inicializa el puntero en null, la linea actual y caracter actual en 0, por defecto el dialogo no esta activo
 * Configura la caja de dialogo
 */
DialogManager::DialogManager() : currentDialog(nullptr), currentLine(0), currentCharacter(0), isDialogActive(false)
{
    dialogBox.setup();
}

/**
 * Destructor del DialogManager
 * Libera la memoria de los dialogos en la cola y del dialogo actual
 */
DialogManager::~DialogManager()
{
    // Borrar el dialogo actual si existe
    if (currentDialog)
    {
        delete currentDialog;
        currentDialog = nullptr;
    }

    // Borrar todos los dialogos en la cola
    while (!dialogQueue.empty())
    {
        delete dialogQueue.front();
        dialogQueue.pop();
    }
}

/* Inicia un dialogo */
void DialogManager::startDialog(Dialog* dialog)
{
    // Agrega el dialogo a la cola
    dialogQueue.push(dialog);
    // Si no hay dialogo activo, procesa el siguiente dialogo
    if(!isDialogActive)
    {
        processNextDialog();
    }
}

/* Procesa el siguiente dialogo de la cola */
void DialogManager::processNextDialog()
{
    // Si hay dialogos en la cola, inicia el siguiente
    if(!dialogQueue.empty())
    {
        // Obtiene el siguiente dialogo de la cola en una variable temporal
        currentDialog = dialogQueue.front();
        // y se elimina el dialogo de la cola original
        dialogQueue.pop();

        // Reinicia los contadores
        currentCharacter = 0;
        // Marca el dialogo como activo
        isDialogActive = true;
        // Reinicia el reloj
        clock.restart();

        // Muestra la primera linea del dialogo si hay uno
        if(currentDialog && !currentDialog->getLines().empty())
        {
            dialogBox.setText(currentDialog->getLines().front().substr(0, currentCharacter));
        }
        // Si no, limpia la caja de dialogo
        else
        {
            dialogBox.setText("");
        }
    }
    // Si no hay mas dialogos en la cola
    else
    {
        // Marca el dialogo como inactivo, el puntero en null
        currentDialog = nullptr;
        // El dialogo ya no esta activo
        isDialogActive = false;
        // Limpia la caja de dialogo
        dialogBox.setText("");
    }
}

/* Actualiza el estado del dialogo */
void DialogManager::update()
{
    // Si no hay dialogo, no hacemos nada
    if(!isDialogActive || !currentDialog || currentDialog->getLines().empty())
    {
        return;
    }

    // Avanza el texto del dialogo segun el tiempo transcurrido
    if(clock.getElapsedTime().asSeconds() > 0.03f)
    {
        // Obtiene la linea actual del dialogo
        const string& currentLineText = currentDialog->getLines().front();
        // Si no hemos terminado de escribir la linea actual
        if(currentCharacter < currentLineText.length())
        {
            // Avanza un caracter en la linea actual
            currentCharacter++;
            // Actualiza el texto en la caja de dialogo
            dialogBox.setText(currentLineText.substr(0, currentCharacter));
            // Marca que la escritura no ha terminado
            typingFinished = false;
        }
        else
        {
            // Marca que la escritura ha terminado
            typingFinished = true;
        }
        // Reinicia el reloj
        clock.restart();
    }
}

/* Dibuja la caja de dialogo en la ventana */
void DialogManager::draw(RenderWindow& window)
{
    // Si hay un dialogo activo, dibuja la caja de dialogo
    if(isDialogActive)
    {
        dialogBox.draw(window);
    }
}

/* Indica si un dialogo esta activo */
bool DialogManager::isActive()
{
    return isDialogActive;
}

/* Avanza a la siguiente linea del dialogo */
void DialogManager::nextLine()
{
    // Si no hay dialogo, no hacemos nada
    if(!isDialogActive || !currentDialog)
    {
        return;
    }

    // Si la linea actual no esta completamente escrita, termina de escribirla y ahi llega
    if(!currentDialog->getLines().empty() && currentCharacter < currentDialog->getLines().front().length())
    {
        // Termina de escribir la linea actual
        currentCharacter = currentDialog->getLines().front().length();
        // Actualiza el texto en la caja de dialogo
        dialogBox.setText(currentDialog->getLines().front());
        return;
    }

    // Si la linea actual esta completamente escrita, avanza a la siguiente linea o dialogo
    if(!currentDialog->getLines().empty())
    {
        // Elimina la linea actual del dialogo
        currentDialog->popLine();

        // Si hay mas lineas en el dialogo actual
        if(!currentDialog->getLines().empty())
        {
            // Reinicia para la siguiente linea en el dialogo actual
            currentCharacter = 0;
            // Actualiza el texto en la caja de dialogo
            dialogBox.setText(currentDialog->getLines().front().substr(0, currentCharacter));
            // Reinicia el reloj para la nueva linea
            clock.restart();
        }
        // Si no hay mas lineas en el dialogo actual
        else
        {
            // Borra el dialogo actual ya que ya no tiene lineas
            delete currentDialog;
            currentDialog = nullptr;
            // Procesa el siguiente dialogo en la cola
            processNextDialog();
        }
    }
    // Si no hay lineas en el dialogo actual
    else
    {
        // Borra el dialogo actual ya que ya no tiene lineas
        delete currentDialog;
        currentDialog = nullptr;
        // Procesa el siguiente dialogo en la cola, esto no deberia ejecutarse porque significaria un dialogo NULL
        processNextDialog();
    }
}

