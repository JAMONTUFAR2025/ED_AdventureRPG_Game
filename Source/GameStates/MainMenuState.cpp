#include "MainMenuState.h"
#include "../GameController.h"
#include <iostream>
#include <queue>
#include <string>

/**
 * Constructor del Menu Principal
 * Inicializa la opcion seleccionada en 0
 * Inicializa el puntero del dialogo de prueba en null
 * Inicializa la bandera de dialogo terminado en false
 */
MainMenuState::MainMenuState() : selectedOption(0), dialogJustEnded(false)
{
}

/* Al entrar al menu, dibujamos e inicializamos la UI */
void MainMenuState::enter(GameController* owner)
{
    cout<<"Entering MainMenuState"<<endl;
    // Inicializa la UI del menu principal
    mainMenuUI.setup(owner);

    // El banderin pasa a false para indicar que no ha terminado ningun dialogo aun
    dialogJustEnded = false;
}

/* Actualiza el estado del menu principal */
void MainMenuState::update(GameController* owner)
{
    // Almacenamos si el dialogo estaba activo antes de la actualizacion
    bool wasDialogActive = dialogManager.isActive();

    // Actualizamos el dialogo si esta activo
    if(dialogManager.isActive())
    {
        dialogManager.update();
    }

    // Verificamos si el dialogo acaba de volverse inactivo despues de esta actualizacion
    if(wasDialogActive && !dialogManager.isActive())
    {
        // Establece la bandera para consumir la siguiente pulsacion de la tecla Z
        dialogJustEnded = true;
    }
}

void MainMenuState::handleEvent(GameController* owner, Event event)
{
    // Este if evita que el dialogo se reabra inmediatamente despues de cerrarse
    if(dialogJustEnded)
    {
        // Verificamos si se pulso una tecla
        if(const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
        {
            // Al pulsar la Z, reseteamos la bandera y consumimos el evento
            if(keyPressed->code == Keyboard::Key::Z)
            {
                dialogJustEnded = false;
                return;
            }
        }
    }

    // Si el dialogo esta activo, manejamos la entrada del dialogo
    if(dialogManager.isActive())
    {
        // Verificamos si se pulso una tecla
        if(const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
        {
            // Al pulsar la Z y el texto haya terminado, avanzamos a la siguiente linea del dialogo
            if(keyPressed->code == Keyboard::Key::Z && dialogManager.typingFinished)
            {
                dialogManager.nextLine();
            }
        }

        return;
    }
    
    // Si no hay dialogo activo, manejamos la entrada del menu principal
    mainMenuUI.handleInput(event, owner, selectedOption);
    // Al pulsar una tecla
    if(const Event::KeyPressed* keyPressed = event.getIf<Event::KeyPressed>())
    {
        // Si se pulsa la Z
        if(keyPressed->code == Keyboard::Key::Z)
        {
            // Jugar
            if(selectedOption == 0)
            {
                // Creamos dialogos de prueba
                vector<string> tempDialogLines = {"Hola, aventurero!", "Bienvenido a Adventure RPG.", "Espero que disfrutes tu estancia."};
                queue<string> newDialogLines;
                for(const string& line : tempDialogLines) {
                    newDialogLines.push(line);
                }
                dialogManager.startDialog(new Dialog(newDialogLines));
            }
        }
    }
}

/* Dibuja la ventana del menu principal */
void MainMenuState::draw(RenderWindow& window)
{
    // Dibuja la UI del menu principal
    mainMenuUI.draw(window, selectedOption);
    // Si hay un dialogo activo, dibuja la caja de dialogo
    if(dialogManager.isActive())
    {
        dialogManager.draw(window);
    }
}

/* Al salir del menu, realizamos las acciones necesarias */
void MainMenuState::exit()
{
    cout<<"Exiting MainMenuState"<<endl;
    // MainMenuState no posee el dialogo, DialogManager gestiona su ciclo de vida
}

/* Getter para el nombre de este estado */
const char* MainMenuState::getName() const
{
    return "MainMenuState";
}
