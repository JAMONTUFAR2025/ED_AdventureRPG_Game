#include "RunTurnState.h"

/* Namespace Battle, para mejor organizacion */
namespace Battle
{

    /**
     * Constructor
     * Establece el paso inicial del turno en START y los banderines en false
     */
    RunTurnState::RunTurnState() : currentStep(TurnStep::START), expMessageQueued(false), levelUpOccurred(false)
    {
    }

    /* Se ejecuta al entrar al estado */
    void RunTurnState::enter(BattleSystem* owner)
    {
        // Obtenemos el puntero al sistema de batalla
        this->battleSystemOwner = owner;
        // Inicializamos el paso actual del turno en START
        currentStep = TurnStep::START;
        // El jugador no esta en guardia al iniciar el turno
        owner->setPlayerGuarding(false);
        // Reiniciamos el multiplicador de defensa del jugador
        owner->getPlayer()->setDefenseMultiplier(1.0f);
    }

    /* Maneja los eventos del estado */
    void RunTurnState::handleEvent(BattleSystem* owner, Event event)
    {
        // No se manejan eventos en este estado
    }

    /* Actualiza el estado */
    void RunTurnState::update(BattleSystem* owner)
    {
        // Si el dialogo esta activo, no hacer nada
        if(owner->getDialogManager().isActive())
        {
            return;
        }
        
        // Cola de mensajes
        queue<string> messages;
        // Indica si el ataque es critico
        bool isCritical = false;

        switch (currentStep)
        {
            // Inicio del turno
            case TurnStep::START:
                // Si la batalla no ha comenzado, mostrar mensaje de inicio
                if(!owner->getBattleStarted())
                {
                    // Mensaje de introduccion en la cola
                    messages.push("Te has encontrado con un/una " + owner->getEnemy().getBaseCharacter().getName() + " salvaje!");
                    // Iniciar el dialogo con el mensaje de introduccion
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    // Marcar la batalla como iniciada
                    owner->setBattleStarted(true);
                    // Pasar al siguiente paso
                    currentStep = TurnStep::POST_INTRO_MESSAGE;
                }
                else
                {
                    // Pasar al paso de accion del jugador
                    currentStep = TurnStep::PLAYER_ACTION;
                }
                break;
            
            // Despues del mensaje de introduccion
            case TurnStep::POST_INTRO_MESSAGE:
                // Si el dialogo no esta activo, cambiar al estado de seleccion de accion
                if(!owner->getDialogManager().isActive())
                {
                    owner->getStateMachine().changeState(new ActionSelectionState());
                }
                break;

            // Accion del jugador
            case TurnStep::PLAYER_ACTION:
            {
                // Calcular si el ataque es critico
                isCritical = false;
                if(rand() % 100 < 20) isCritical = true;

                int playerDamage = 0;
                bool validAction = true;
                // Ejecutar la accion seleccionada
                switch (owner->getChosenAction())
                {
                    // Luchar
                    case ActionType::Fight:
                        // Ganar 1 punto de definitiva
                        owner->getPlayer()->gainUltimatePoints(1);
                        // Calcular el danio infligido al enemigo
                        playerDamage = owner->getEnemy().takeDamage(owner->getPlayer()->getCharacter(), owner->getEnemy().getDefense(), 50, isCritical);
                        // Mensaje de ataque en la cola
                        messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " ha usado un ataque basico! \nDanio infligido: " + to_string(playerDamage) + "\n+1 punto de definitiva!");
                        // Mostrar mensaje de golpe critico si es necesario
                        if(isCritical) messages.push("Un golpe critico!");
                        break;
                    // Ataque especial
                    case ActionType::Special:
                        // Comprobar si tiene suficientes puntos de definitiva
                        if(owner->getPlayer()->getUltimatePoints() >= 5)
                        {
                            // Usar 5 puntos de definitiva
                            owner->getPlayer()->useUltimate(5);
                            // Calcular el danio infligido al enemigo
                            playerDamage = owner->getEnemy().takeDamage(owner->getPlayer()->getCharacter(), owner->getEnemy().getDefense(),  150, isCritical);
                            // Mensaje de ataque especial en la cola
                            messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " ha usado un poderoso ataque definitivo! \nDanio infligido: " + to_string(playerDamage) + "\n-5 puntos de definitiva!");
                            // Mostrar mensaje de golpe critico si es necesario
                            if(isCritical) messages.push("Un golpe critico devastador!");
                        }
                        // Si no tiene suficientes puntos, mostrar mensaje de que la accion es invalida
                        else
                        {
                            messages.push("No tienes suficientes puntos de definitiva!");
                            validAction = false;
                        }
                        break;
                    // En guardia
                    case ActionType::Guard:
                        // Ganar 2 puntos de definitiva
                        owner->getPlayer()->gainUltimatePoints(2);
                        // Mensaje de guardia en la cola
                        messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " ha fortalecido su cuerpo!\nDefensa duplicada este turno!\n+2 puntos de definitiva!");
                        // Poner al jugador en guardia
                        owner->setPlayerGuarding(true);
                        // Duplicar el multiplicador de defensa del jugador
                        owner->getPlayer()->setDefenseMultiplier(2.0f);
                        break;
                    // Escapar
                    case ActionType::Escape:
                        // Mensaje de escape en la cola
                        messages.push("Escapaste sin problemas!");
                        // Iniciar dialogo con el mensaje de escape
                        owner->getDialogManager().startDialog(new Dialog(messages));
                        // Establecer el resultado de la batalla como escape
                        result = BattleResult::Escape;
                        // Pasar al paso de mostrar resultados de experiencia
                        currentStep = TurnStep::SHOW_EXP_RESULTS;
                        return;
                    // Ninguna accion
                    case ActionType::None:
                        validAction = false;
                        break;
                }
                // Iniciar dialogo con los mensajes generados
                if(!messages.empty()) owner->getDialogManager().startDialog(new Dialog(messages));
                
                // Si la accion es valida, pasar al siguiente paso
                if(validAction) 
                {
                    currentStep = TurnStep::ENEMY_CHECK;
                }
                // Si la accion no es valida, volver al paso de accion del jugador
                else
                {
                    currentStep = TurnStep::INVALID_ACTION;
                }
            }
            break;

            // Accion invalida
            case TurnStep::INVALID_ACTION:
                // Si el dialogo no esta activo, volver al estado de seleccion de accion
                if(!owner->getDialogManager().isActive())
                {
                    owner->getStateMachine().changeState(new ActionSelectionState());
                }
                break;

            // Verificacion del enemigo
            case TurnStep::ENEMY_CHECK:
                // Actualizar la barra de vida del enemigo
                owner->setHasHealthBarUpdated(true);
                // Actualizar los puntos de definitiva del jugador
                owner->setHasUltimatePointsUpdated(true);
                // Si el enemigo ha sido derrotado, mostrar mensaje de victoria
                if(owner->getEnemy().getCurrentHealth() <= 0)
                {
                    // Mostrar mensaje de victoria
                    messages.push(owner->getEnemy().getBaseCharacter().getName() + " ha sido derrotado!");
                    // Desencolar el dialogo con el mensaje de victoria
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    // Establecer el resultado de la batalla como victoria
                    result = BattleResult::Victory;
                    // Pasar al paso de mostrar resultados de experiencia
                    currentStep = TurnStep::SHOW_EXP_RESULTS;
                    return;
                }
                // Si el enemigo no ha sido derrotado, pasar al paso de accion del enemigo
                currentStep = TurnStep::ENEMY_ACTION;
                break;

            // Accion del enemigo
            case TurnStep::ENEMY_ACTION:
            {
                // Lo mismo que el jugador pero con un ataque basico simple
                isCritical = false;
                if(rand() % 100 < 20) isCritical = true;
                int enemyDamage = owner->getPlayer()->getCharacter().takeDamage(owner->getEnemy(), owner->getPlayer()->getDefense(), 50, isCritical);
                messages.push(owner->getEnemy().getBaseCharacter().getName() + " lanzo un ataque! \nDanio infligido: " + to_string(enemyDamage));
                if(isCritical) messages.push("Un golpe critico!");
                owner->getDialogManager().startDialog(new Dialog(messages));
                currentStep = TurnStep::PLAYER_CHECK;
                break;
            }

            // Verificacion del jugador
            case TurnStep::PLAYER_CHECK:
                // Lo mismo que con el enemigo
                owner->setHasHealthBarUpdated(true);
                if(owner->getPlayer()->getCharacter().getCurrentHealth() <= 0)
                {
                    messages.push(owner->getPlayer()->getCharacter().getBaseCharacter().getName() + " ha sido derrotado...");
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    result = BattleResult::Defeat;
                    currentStep = TurnStep::SHOW_EXP_RESULTS;
                    return;
                }
                // Si el jugador no ha sido derrotado, pasar al paso de fin del turno
                currentStep = TurnStep::FINISH_TURN;
                break;
            
            // Fin del turno
            case TurnStep::FINISH_TURN:
                // Reiniciar el multiplicador de defensa del jugador y quitar la guardia
                owner->getPlayer()->setDefenseMultiplier(1.0f);
                owner->setPlayerGuarding(false);
                // Volver al estado de seleccion de accion
                owner->getStateMachine().changeState(new ActionSelectionState());
                break;
            
            // Muestra los resultados de experiencia
            case TurnStep::SHOW_EXP_RESULTS:
                // Esperar a que el dialogo termine
                if(owner->getDialogManager().isActive()) break;

                // Si no hay mensaje de experiencia en cola
                if(!expMessageQueued)
                {
                    switch(result)
                    {
                        // Victoria
                        case BattleResult::Victory:
                        {
                            // Encolar mensajes de victoria, experiencia ganada y puntos ganados
                            messages.push("Victoria!");
                            // Calcular experiencia ganada
                            int expGained = owner->getEnemy().getBaseCharacter().getExpYield() * (1 + owner->getEnemy().getLevel() / 5);
                            messages.push("Has ganado " + to_string(expGained) + " puntos de experiencia!");

                            // Calcular puntos de jugador ganados
                            int enemyPoints = owner->getEnemy().getBaseCharacter().getPointsYield() * (1 + owner->getEnemy().getLevel() / 5);
                            owner->getPlayer()->gainPoints(enemyPoints);
                            messages.push("Tambien has ganado " + to_string(enemyPoints) + " puntos de jugador!");

                            // Comprobar si ha subido de nivel
                            int oldLevel = owner->getPlayer()->getCharacter().getLevel();
                            owner->getPlayer()->gainExperience(expGained);
                            int newLevel = owner->getPlayer()->getCharacter().getLevel();

                            if(newLevel > oldLevel) levelUpOccurred = true;
                        }
                        
                        break;
                        // Derrota
                        case BattleResult::Defeat:
                            break;
                        // Escapar
                        case BattleResult::Escape:
                            break;
                    }
                    // Desencolar el dialogo con los mensajes de experiencia
                    if(!messages.empty()) owner->getDialogManager().startDialog(new Dialog(messages));
                    expMessageQueued = true;
                }
                // Caso contrario
                else
                {
                    // Ir al siguiente paso de mostrar resultados de subida de nivel
                    currentStep = TurnStep::SHOW_LEVEL_UP_RESULTS;
                }
                break;

            // Muestra los resultados de subida de nivel
            case TurnStep::SHOW_LEVEL_UP_RESULTS:
                // Esperar a que el dialogo termine
                if(owner->getDialogManager().isActive()) break;
                // Si ha subido de nivel, mostrar mensaje
                if(levelUpOccurred)
                {
                    // Encolar mensaje de subida de nivel
                    messages.push("Has subido al nivel " + to_string(owner->getPlayer()->getCharacter().getLevel()) + "!");
                    // Desencolar el dialogo con el mensaje de subida de nivel
                    owner->getDialogManager().startDialog(new Dialog(messages));
                    // Actualizar la UI
                    owner->setHasHealthBarUpdated(true);
                    owner->setHasPlayerLeveledUp(true);
                }
                // Pasar al paso de finalizar la batalla
                currentStep = TurnStep::FINALIZE_BATTLE;
                break;
            
            // Finaliza la batalla
            case TurnStep::FINALIZE_BATTLE:
                // Esperar a que el dialogo termine
                if(owner->getDialogManager().isActive()) break;
                // Terminar la batalla
                owner->endBattle();
                
                break;
        }
    }

    /* Dibuja en el estado */
    void RunTurnState::draw(RenderWindow& window)
    {
        // Todo se hace en BattleUI
    }

    /* Al salir del estado */
    void RunTurnState::exit()
    {
        // Nada por aqui, todo se hace en los destructores
    }
} // namespace Battle
