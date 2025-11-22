#ifndef ISTATE_H
#define ISTATE_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/**
 * Definicion forward de la clase StateMachine para evitar referencias circulares
 * Es generica y puede tener cualquier propietario T
 */
template <typename T> class StateMachine;

/**
 * Interfaz para los estados de la maquina de estados
 * Es generica para los estados que creemos
 */
template <typename T> class IState
{
public:
    /* Destructor virtual */
    virtual ~IState() = default;

    /* Se ejecuta una vez al entrar en el estado */
    virtual void enter(T* owner) = 0;

    /* Se ejecuta en cada frame mientras se este en el estado */
    // Para manejar eventos
    virtual void handleEvent(T* owner, Event event) = 0;
    // Para actualizar la logica sin contar eventos
    virtual void update(T* owner) = 0;

    /* Se ejecuta en cada frame para dibujar los elementos del estado */
    virtual void draw(RenderWindow& window) = 0;

    /* Se ejecuta una vez al salir del estado */
    virtual void exit() = 0;
};

#endif // ISTATE_H