#include "MainMenuState.h"
#include "../GameController.h"
#include <iostream>
#include <vector>
#include <string>

/* Constructor, inicializa los punteros a nullptr */
MainMenuState::MainMenuState() : font(nullptr), text(nullptr), stackText(nullptr)
{
}

/* Se ejecuta al entrar en el estado */
void MainMenuState::enter(GameController* owner)
{
    cout << "Entering MainMenuState" << endl;

    // Creamos la fuente dinamicamente
    font = new Font();

    // Cargamos la fuente para el texto de depuracion
    if(font->openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        // Si la fuente se carga correctamente, creamos los textos
        text = new Text(*font, "Estado: MainMenu (DEBUG)", 12);
        text->setFillColor(Color::White);
        text->setPosition({10.f, 10.f});

        stackText = new Text(*font, "", 12);
        stackText->setFillColor(Color::White);
        stackText->setPosition({10.f, 30.f});
    }
    else
    {
        cerr<<"Error: No se pudo cargar la fuente 'arial.ttf'. Asegurate de que el archivo existe en C:/Windows/Fonts/"<<endl;
    }
}

void MainMenuState::execute(GameController* owner)
{
    // Actualizamos el texto de la pila de estados
    if(stackText)
    {
        string stackString = "STATE STACK:\n";
        vector<IState<GameController>*> stack = owner->stateMachine.getStack();
        for(IState<GameController>*& state : stack)
        {
            stackString += " - " + string(state->getName()) + "\n";
        }
        stackText->setString(stackString);
    }
}

void MainMenuState::draw(sf::RenderWindow& window)
{
    // Dibujamos los textos de depuracion si no son nulos
    if(text)
    {
        window.draw(*text);
    }
    if(stackText)
    {
        window.draw(*stackText);
    }
}

void MainMenuState::exit()
{
    cout<<"Exiting MainMenuState"<<endl;

    // Liberamos la memoria de la fuente y los textos
    delete text;
    delete stackText;
    delete font;
}

const char* MainMenuState::getName() const
{
    return "MainMenuState";
}

