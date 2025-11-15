#ifndef GAMEMENUSTATE_H
#define GAMEMENUSTATE_H

#include "../Util/StateMachine/IState.h"
#include <SFML/Graphics.hpp>
#include "../UI/GameMenuUI.h"
#include <iostream>

using namespace sf;
using namespace std;

// Forward declaration
class GameController;

/**
 * Estado del Menu del Juego
 * Permite navegar por las opciones del menu de acciones
 */
class GameMenuState : public IState<GameController>
{
private:
    /* UI del menu del juego */
    GameMenuUI gameMenuUI;
    /* Opcion seleccionada */
    int selectedOption;

public:
    /* Constructor del Menu del Juego */
    GameMenuState();
    /* Al entrar al menu, dibujamos e inicializamos la UI */
    void enter(GameController* owner) override;
    /* Ejecuta la logica del menu del juego, se manejan las entradas */
    void handleEvent(GameController* owner, Event event) override;
    void update(GameController* owner) override;
    /* Dibuja el menu del juego */
    void draw(RenderWindow& window) override;
    /* Al salir del menu, realizamos las acciones necesarias */
    void exit() override;
    /* Obtiene el nombre del estado, para depuracion */
    const char* getName() const override;
};

#endif // GAMEMENUSTATE_H
