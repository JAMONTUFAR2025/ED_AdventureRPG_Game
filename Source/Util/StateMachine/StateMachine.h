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
        StateMachine(T* owner) : owner(owner) { }

        /**
         * Destructor de la maquina de estados
         */
        ~StateMachine()
        {
            // Limpiamos la pila de estados
            while(!stateStack.empty())
            {
                IState<T>* stateToDelete = stateStack.top();
                stateStack.pop();
                delete stateToDelete;
            }
        }

        /**
         * Ejecuta el metodo execute del estado actual
         */
        void execute()
        {
            // Si la pila no esta vacia, ejecutamos el estado superior
            if(!stateStack.empty())
            {
                stateStack.top()->execute(owner);
            }
        }

        /**
         * Dibuja el estado actual
         */
        void draw(sf::RenderWindow& window)
        {
            // Si la pila no esta vacia, dibujamos el estado superior
            if(!stateStack.empty())
            {
                stateStack.top()->draw(window);
            }
        }

        /**
         * Coloca un nuevo estado en la pila
         */
        void push(IState<T>* newState)
        {
            stateStack.push(newState);
            stateStack.top()->enter(owner);
        }

        /**
         * Elimina el estado superior de la pila
         */
        void pop()
        {
            // Si la pila esta vacia, no hacemos nada
            if(stateStack.empty())
            {
                return;
            }

            // Salimos del estado superior y lo borramos
            stateStack.top()->exit();
            delete stateStack.top();
            stateStack.pop();
        }

        /**
         * Cambia el estado actual por uno nuevo de la pila
         */
        void changeState(IState<T>* newState)
        {
            // Si la pila no esta vacia, salimos del estado actual y lo borramos
            if(!stateStack.empty())
            {
                stateStack.top()->exit();
                delete stateStack.top();
                stateStack.pop();
            }

            // Colocamos el nuevo estado en la pila y entramos en el
            stateStack.push(newState);
            stateStack.top()->enter(owner);
        }

        /* ESTO NO SE USARA */
        /**
         * Obtiene el estado anterior al actual sin eliminarlo de la pila
         */
        // IState<T>* getPreviousState()
        // {
        //     // Si hay al menos dos estados en la pila, devolvemos el anterior al actual
        //     if(stateStack.size() > 1)
        //     {
        //         std::vector<IState<T>*> tempStates = std::vector<IState<T>*>();
        //         // Hacemos una copia de la pila de estados
        //         std::stack<IState<T>*> copy = stateStack;
        //         while(!copy.empty())
        //         {
        //             tempStates.push_back(copy.top());
        //             copy.pop();
        //         }
        //         return tempStates[tempStates.size() - 2];
        //     }
        //     return nullptr;
        // }

        /**
         * Obtiene el estado actual sin eliminarlo de la pila
         */
        IState<T>* getCurrentState()
        {
            // Si la pila esta vacia, devolvemos nullptr, si no, el estado superior
            return stateStack.empty() ? nullptr : stateStack.top();
        }

        /**
         * Obtiene una copia de la pila de estados
         */
        vector<IState<T>*> getStack()
        {
            vector<IState<T>*> stackCopy;
            stack<IState<T>*> tempStack = stateStack;
            while (!tempStack.empty())
            {
                stackCopy.push_back(tempStack.top());
                tempStack.pop();
            }
            return stackCopy;
        }
};

#endif // STATEMACHINE_H
