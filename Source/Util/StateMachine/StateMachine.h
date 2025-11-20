#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "IState.h"
#include<stack>

using namespace std;
using namespace sf;

/**
 * Maquina de estados generica con pilas
 * Se usa vector para el metodo getPreviousState()
 * Es generica y puede tener cualquier propietario T
 */
template <typename T>
class StateMachine
{
    private:
        /* Pila de estados con propietario generico, es un puntero */
        stack<IState<T>*> stateStack;

        /* Objeto propietario, puntero para evitar copias */
        T* owner;
    
    public:
        /* Constructor de la maquina de estados */
        StateMachine(T* owner);

        /* Destructor de la maquina de estados */
        ~StateMachine();

        /* Se ejecuta en cada frame y maneja eventos del estado actual */
        void handleEvent(Event event);

        /* Se ejecuta en cada frame y actualiza el estado actual sin contar eventos */
        void update();

        /* Dibuja el estado actual */
        void draw(RenderWindow& window);

        /* Coloca un nuevo estado en la pila */
        void push(IState<T>* newState);

        /* Elimina el estado superior de la pila */
        void pop();

        /* Cambia el estado actual por uno nuevo de la pila */
        void changeState(IState<T>* newState);

        /* Obtiene el estado actual sin eliminarlo de la pila */
        IState<T>* getCurrentState();

        /* Obtiene una copia de la pila de estados */
        vector<IState<T>*> getStack();
};
#include "StateMachine.tpp" // PARA EVITAR ERRORES DE ENLAZADO CON PLANTILLAS
#endif // STATEMACHINE_H
