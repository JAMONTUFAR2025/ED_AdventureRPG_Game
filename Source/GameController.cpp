#include "GameController.h"
#include "Gameplay/GlobalSettings.h"
#include "GameStates/MainMenuState.h"
#include <iostream>

/**
 * Controlador principal del juego.
 * Hereda de SFML RenderWindow para manejar la ventana del juego
 * y utiliza una maquina de estados para gestionar los diferentes
 * estados del juego (menu principal, juego, pausa, etc).
 */
GameController::GameController() : window(VideoMode({GlobalSettings::SCREEN_WIDTH, GlobalSettings::SCREEN_HEIGHT}), "Adventure RPG", Style::Close | Style::Titlebar), stateMachine(this), dialogManager()
{
    // Oculta el cursor del mouse
    window.setMouseCursorVisible(false);
    /* Inicializa el estado del menu principal */
    stateMachine.push(new MainMenuState());
    // Inicializa el puntero del jugador
    player = nullptr;
}

/* Inicia el bucle del juego */
void GameController::runGameLoop()
{
    // Bucle principal del juego, mientras la ventana este abierta
    while(window.isOpen())
    {
        // Procesa los eventos, ejecuta la logica del estado actual y renderiza
        processEvents();
        dialogManager.update(); // Update the dialog manager before updating the state machine
        stateMachine.update();
        render();
    }
}

/* Procesa los eventos de la ventana */
void GameController::processEvents()
{
    // Variable para almacenar los eventos
    while (const optional<Event> event = window.pollEvent())
    {
        // Si se recibe un evento de cierre, cierra la ventana
        if(event->is<Event::Closed>())
        {
            window.close();
        }
        
        stateMachine.handleEvent(*event);
    }
}

/* Renderiza la ventana */
void GameController::render()
{
    window.clear();
    // Dibujamos el estado actual de la maquina de estados
    stateMachine.draw(window);
    dialogManager.draw(window); // Draw the dialog manager
    window.display();
}

/* Crea una instancia del jugador */
void GameController::createPlayer()
{
    if (!player)
    {
        player = new Player();
    }
}

/* Destruye la instancia del jugador */
void GameController::destroyPlayer()
{
    if (player)
    {
        delete player;
        player = nullptr;
    }
}

/* Obtiene la instancia del jugador */
Player* GameController::getPlayer()
{
    return player;
}

/* Obtiene el manejador de dialogos */
DialogManager* GameController::getDialogManager()
{
    return &dialogManager;
}
