#ifndef ISTATE_H
#define ISTATE_H

#include <SFML/Graphics.hpp>

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
    /**
     * Destructor virtual
     */
    virtual ~IState() = default;

    /**
     * Se ejecuta una vez al entrar en el estado
     */
    virtual void enter(T* owner) = 0;

    /**
     * Se ejecuta en cada frame mientras se este en el estado
     */
    virtual void execute(T* owner, sf::Event event) = 0;

    /**
     * Se ejecuta en cada frame para dibujar los elementos del estado
     */
    virtual void draw(sf::RenderWindow& window) = 0;

    /**
     * Se ejecuta una vez al salir del estado
     */
    virtual void exit() = 0;

    /**
     * Obtiene el nombre del estado
     */
    virtual const char* getName() const = 0;
};

#endif // ISTATE_H