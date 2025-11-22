#ifndef GAMEMENUSTATE_H
#define GAMEMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "../Util/StateMachine/IState.h"
#include "../GameController.h"
#include "../GameStates/BattleState.h"
#include "../GameStates/GameOverState.h"
#include "../GameStates/MainMenuState.h"
#include "../UI/GameMenuUI.h"
#include "../Character/BaseCharacter.h"
#include "../Character/Character.h"
#include "../Character/CharacterDB.h"
#include "../Character/Player.h"
#include <iostream>

using namespace sf;
using namespace std;

// Declaracion forward para evitar dependencias circulares
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
    /* Poseedor del controlador del juego */
    GameController* owner;
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
};

#endif // GAMEMENUSTATE_H
