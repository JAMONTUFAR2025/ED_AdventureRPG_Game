#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "../Util/StateMachine/IState.h"
#include <SFML/Graphics.hpp>
#include "../UI/GameOverUI.h"
#include <iostream>

using namespace sf;
using namespace std;

// Declaracion forward para evitar dependencias circulares
class GameController;

/**
 * Estado del Game Over
 * Permite navegar por las opciones del Game Over
 */
class GameOverState : public IState<GameController>
{
private:
    /* UI del Game Over */
    GameOverUI gameOverUI;
    /* Opcion seleccionada */
    int selectedOption;
    /* Bandera para indicar si el juego se perdio */
    bool isGameLost;

public:
    /* Constructor del Game Over */
    GameOverState(bool isGameLost);
    /* Al entrar al Game Over, dibujamos e inicializamos la UI */
    void enter(GameController* owner) override;
    /* Ejecuta la logica del GameOver, se manejan las entradas */
    void handleEvent(GameController* owner, Event event) override;
    void update(GameController* owner) override;
    /* Dibuja el GameOver del juego */
    void draw(RenderWindow& window) override;
    /* Al salir del GameOver, realizamos las acciones necesarias */
    void exit() override;
};

#endif // GAMEMENUSTATE_H
