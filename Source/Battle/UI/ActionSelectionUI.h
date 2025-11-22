#ifndef BATTLE_ACTIONSELECTIONUI_H
#define BATTLE_ACTIONSELECTIONUI_H

#include <SFML/Graphics.hpp>
#include "../../UI/DialogBox.h"
#include "../../Gameplay/GlobalSettings.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /* Clase para la interfaz de seleccion de accion */
    class ActionSelectionUI
    {
    private:
        /* Caja de dialogo para las acciones */
        DialogBox actionBox;
        /* Fuente para los textos */
        Font font;
        /* Textos de las opciones */
        vector<Text*> optionTexts;
        /* Descripciones de las opciones */
        vector<string> optionDescriptions;
        
        /* Textos de los controles */
        vector<Text*> controlsTexts;
        /* Caja de dialogo para las descripciones */
        DialogBox dialogBox;
        
        public:
        /* Constructor */
        ActionSelectionUI();
        /* Destructor */
        ~ActionSelectionUI();
        
        /* Metodos para la interfaz */
        void setup();
        void draw(RenderWindow& window, int selectedOption);
        void updateDialogBoxDescription(int selectedOption);
    };
} // namespace Battle

#endif // BATTLE_ACTIONSELECTIONUI_H
