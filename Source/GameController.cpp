#include "GameController.h"
#include "GameStates/MainMenuState.h"
#include <iostream>

/**
 * Controlador principal del juego.
 * Hereda de SFML RenderWindow para manejar la ventana del juego
 * y utiliza una maquina de estados para gestionar los diferentes
 * estados del juego (menu principal, juego, pausa, etc).
 */
GameController::GameController() : window(sf::VideoMode({800, 600}), "Adventure RPG"), stateMachine(this)
{
    /* Inicializa el estado del menu principal */
    stateMachine.push(new MainMenuState());
}

/* Inicia el bucle del juego */
void GameController::runGameLoop()
{
    // Bucle principal del juego, mientras la ventana este abierta
    while(window.isOpen())
    {
        // Procesa los eventos, ejecuta la logica del estado actual y renderiza
        processEvents();
        stateMachine.update();
        render();
    }
}

/* Procesa los eventos de la ventana */
void GameController::processEvents()
{
    // Variable para almacenar los eventos
    while (const auto event = window.pollEvent())
    {
        // Si se recibe un evento de cierre, cierra la ventana
        if(event->is<sf::Event::Closed>())
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
    window.display();
}
