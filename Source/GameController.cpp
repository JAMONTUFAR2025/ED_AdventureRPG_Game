#include "GameController.h"

/**
 * Constructor del controlador principal del juego
 * Inicializa la ventana, la maquina de estados y el manejador de dialogos
 */
GameController::GameController() : 
        window(VideoMode({GlobalSettings::SCREEN_WIDTH, GlobalSettings::SCREEN_HEIGHT}), 
        "Adventure RPG", 
        Style::Close | Style::Titlebar), 
        stateMachine(this), 
        dialogManager()
{
    // Oculta el cursor del mouse
    window.setMouseCursorVisible(false);
    // Inicia la maquina de estados con el estado del menu principal
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
        // Actualiza el manejador de dialogos
        dialogManager.update();
        // Actualiza la maquina de estados
        stateMachine.update();
        // Renderiza la ventana
        render();
    }
}

/* Procesa los eventos de la ventana */
void GameController::processEvents()
{
    // Variable para almacenar los eventos
    while (optional<Event> event = window.pollEvent())
    {
        // Si se recibe un evento de cierre, cierra la ventana
        if(event->is<Event::Closed>())
        {
            window.close();
        }
        
        // Pasa el evento a la maquina de estados
        stateMachine.handleEvent(*event);
    }
}

/* Renderiza la ventana */
void GameController::render()
{
    // Limpiamos la ventana
    window.clear();
    // Dibujamos el estado actual de la maquina de estados
    stateMachine.draw(window);
    // Dibujamos el manejador de dialogos
    dialogManager.draw(window);
    // Mostramos el contenido de la ventana
    window.display();
}

/**
 * Ventana principal
 */
/* Getter de la ventana principal */
RenderWindow& GameController::getWindow()
{
    return window;
}

/**
 * Jugador
 */
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
/* Getter de la instancia del jugador */
Player* GameController::getPlayer()
{
    return player;
}

/**
 * Maquina de estados
 */
/* Getter para la maquina de estados */
StateMachine<GameController>& GameController::getStateMachine()
{
    return stateMachine;
}
/* Setter para la maquina de estados */
void GameController::setStateMachine(StateMachine<GameController>& stateMachine)
{
    this->stateMachine = stateMachine;
}

/**
 * Manejador de dialogos
 */
/* Getter del manejador de dialogos */
DialogManager* GameController::getDialogManager()
{
    return &dialogManager;
}
/* Setter para el manejador de dialogos */
void GameController::setDialogManager(DialogManager& dialogManager)
{
    this->dialogManager = dialogManager;
}
