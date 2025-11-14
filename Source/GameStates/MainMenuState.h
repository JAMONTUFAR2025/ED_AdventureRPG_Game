#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../Util/StateMachine/IState.h"
#include <SFML/Graphics.hpp>

/* Namespaces para acortar */
using namespace sf;
using namespace std;

// Declaracion forward
class GameController;

#include "../UI/MainMenuUI.h"

/**
 * Estado del Menu Principal
 * Permite navegar por las opciones del menu principal
 */
class MainMenuState : public IState<GameController>
{
private:
    /* UI del menu principal */
    MainMenuUI mainMenuUI;
    /* Opcion seleccionada */
    int selectedOption;

public:
    /* Constructor del Menu Principal */
    MainMenuState();
    /* Al entrar al menu, dibujamos e inicializamos la UI */
    void enter(GameController* owner) override;
    /* Ejecuta la logica del menu principal, se manejan las entradas */
    void execute(GameController* owner, Event event) override;
    /* Dibuja el menu principal */
    void draw(RenderWindow& window) override;
    /* Al salir del menu, realizamos las acciones necesarias */
    void exit() override;
    /* Obtiene el nombre del estado, para depuracion */
    const char* getName() const override;
};

#endif // MAINMENUSTATE_H
