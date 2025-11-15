#include "StateMachine.h"

// SE USA UN ARCHIVO .TPP PARA LAS IMPLEMENTACIONES DE PLANTILLAS

/**
 * Constructor de la maquina de estados
 */
template <typename T>
StateMachine<T>::StateMachine(T* owner) : owner(owner) { }

/**
 * Destructor de la maquina de estados
 */
template <typename T>
StateMachine<T>::~StateMachine()
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
template <typename T>
void StateMachine<T>::handleEvent(sf::Event event)
{
    // Si la pila no esta vacia, ejecutamos el estado superior
    if(!stateStack.empty())
    {
        stateStack.top()->handleEvent(owner, event);
    }
}

template <typename T>
void StateMachine<T>::update()
{
    // Si la pila no esta vacia, actualizamos el estado superior
    if(!stateStack.empty())
    {
        stateStack.top()->update(owner);
    }
}

/**
 * Dibuja el estado actual
 */
template <typename T>
void StateMachine<T>::draw(sf::RenderWindow& window)
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
template <typename T>
void StateMachine<T>::push(IState<T>* newState)
{
    stateStack.push(newState);
    stateStack.top()->enter(owner);
}

/**
 * Elimina el estado superior de la pila
 */
template <typename T>
void StateMachine<T>::pop()
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
template <typename T>
void StateMachine<T>::changeState(IState<T>* newState)
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

/**
 * Obtiene el estado actual sin eliminarlo de la pila
 */
template <typename T>
IState<T>* StateMachine<T>::getCurrentState()
{
    // Si la pila esta vacia, devolvemos nullptr, si no, el estado superior
    return stateStack.empty() ? nullptr : stateStack.top();
}

/**
 * Obtiene una copia de la pila de estados
 */
template <typename T>
vector<IState<T>*> StateMachine<T>::getStack()
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
