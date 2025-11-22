#include "ActionSelectionUI.h"

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /**
     * Constructor
     * Inicializa las descripciones de las opciones
     */
    ActionSelectionUI::ActionSelectionUI()
    {
        // Descripciones de las opciones
        optionDescriptions.push_back("Ejecuta un ataque basico.\nPotencia: 50 \nRecargas 1 punto de definitiva.");
        optionDescriptions.push_back("Ejecuta un potente ataque especial. \nPotencia: 150 \nCosto: 5 puntos de definitiva." );
        optionDescriptions.push_back("Fortaleces tu cuerpo y concentras energia. \nEfecto: Duplicas tu defensa este turno. \nRecargas 2 puntos de definitiva.");
        optionDescriptions.push_back("Por si las cosas se complican. \nEfecto: Escapas y terminas el combate. \nNo ganaras experiencia ni puntos.");
    }

    /**
     * Destructor
     * Libera la memoria de los textos
     */
    ActionSelectionUI::~ActionSelectionUI()
    {
        // Liberamos la memoria de los textos
        for(Text* text : optionTexts)
        {
            delete text;
        }

        for(Text* text : controlsTexts)
        {
            delete text;
        }
        // Limpiamos los vectores
        optionTexts.clear();
        controlsTexts.clear();
    }

    /* Configura la interfaz de seleccion de accion */
    void ActionSelectionUI::setup()
    {
        // Cargamos la fuente
        if(!font.openFromFile(GlobalSettings::FONT_PATH))
        {
            cout<<"Error al cargar "<<GlobalSettings::FONT_PATH<<endl;
            // Si no se puede cargar la fuente, intentamos cargar una fuente de sistema
            if(!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
            {
                cout<<"Error al cargar font C:/Windows/Fonts/arial.ttf"<<endl;
                return;
            }
        }

        // Posicion inicial de los textos
        float startX = 70;
        float startY = 300;
        float spacing = 165.0f;

        // Configuramos la caja de acciones
        actionBox.setup(700.0f, 50.0f, 50, startY);

        // Opciones de accion
        vector<string> options = {"Luchar!", "Definitiva!", "En guardia!", "Escapar!"};

        // Creamos los textos para cada opcion
        for(int i = 0; i < options.size(); i++)
        {
            // Creamos un nuevo texto para la opcion de tamanio definido en GlobalSettings
            Text* optionText = new Text(font, options[i], GlobalSettings::FONT_SIZE);
            // Color blanco por defecto
            optionText->setFillColor(Color::White);
            // Posicionamos la opcion con un espaciado definido
            optionText->setPosition(Vector2f(startX + i * spacing, startY));
            // Agregamos la opcion al vector de opciones
            optionTexts.push_back(optionText);
        }

        // Controles
        vector<string> controls = {
            "A / D - Cambiar opcion.",
            "E - Seleccionar opcion."
        };

        // Creamos los textos para cada control
        for(int i = 0; i < controls.size(); i++)
        {
            Text* controlText = new Text(font, controls[i], GlobalSettings::FONT_SIZE);
            controlText->setFillColor(Color::White);
            // Spacing = 330 para que queden separados
            // Para llegar a Y = 550
            controlText->setPosition(Vector2f(startX + i * (spacing + 165.0f), startY + 250.0f));
            controlsTexts.push_back(controlText);
        }

        // Configuramos la caja de dialogo
        dialogBox.setup(700.0f, 150.0f, 50, 380);
    }

    /* Dibuja la interfaz de seleccion de accion */
    void ActionSelectionUI::draw(RenderWindow& window, int selectedOption)
    {
        // Dibujamos la caja de acciones
        actionBox.draw(window);

        // Dibujamos los textos de las opciones
        for(int i = 0; i < optionTexts.size(); i++)
        {
            // Guardamos el texto original
            string originalString = optionTexts[i]->getString();

            // Resaltamos la opcion seleccionada
            if(i == selectedOption)
            {
                optionTexts[i]->setString("> " + originalString);
                optionTexts[i]->setFillColor(Color::Yellow);
            }
            else
            {
                optionTexts[i]->setString("  " + originalString);
                optionTexts[i]->setFillColor(Color::White);
            }
            // Dibujamos el texto
            window.draw(*optionTexts[i]);

            // Restauramos el texto original
            optionTexts[i]->setString(originalString);
        }
        
        // Dibujamos los textos de los controles
        for(Text* controlText : controlsTexts)
        {
            window.draw(*controlText);
        }

        // Dibujamos la caja de dialogo
        dialogBox.draw(window);
    }

    /* Actualiza la descripcion en la caja de dialogo */
    void ActionSelectionUI::updateDialogBoxDescription(int selectedOption)
    {
        // Actualizamos el texto de la caja de dialogo con la descripcion de la opcion seleccionada
        if(selectedOption >= 0 && selectedOption < optionDescriptions.size())
        {
            dialogBox.setText(optionDescriptions[selectedOption]);
        }
    }
} // namespace Battle
