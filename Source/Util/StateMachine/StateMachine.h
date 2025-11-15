#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "IState.h"
#include<stack>
//#include<vector>

using namespace std;

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
        /**
         * Constructor de la maquina de estados
         */
        StateMachine(T* owner);

        /**
         * Destructor de la maquina de estados
         */
        ~StateMachine();

        /**
         * Ejecuta el metodo execute del estado actual
         */
        void handleEvent(sf::Event event);
        void update();

        /**
         * Dibuja el estado actual
         */
        void draw(sf::RenderWindow& window);

        /**
         * Coloca un nuevo estado en la pila
         */
        void push(IState<T>* newState);

        /**
         * Elimina el estado superior de la pila
         */
        void pop();

        /**
         * Cambia el estado actual por uno nuevo de la pila
         */
        void changeState(IState<T>* newState);

        /**
         * Obtiene el estado actual sin eliminarlo de la pila
         */
        IState<T>* getCurrentState();

        /**
         * Obtiene una copia de la pila de estados
         */
        vector<IState<T>*> getStack();
};

#include "StateMachine.tpp"

#endif // STATEMACHINE_H
