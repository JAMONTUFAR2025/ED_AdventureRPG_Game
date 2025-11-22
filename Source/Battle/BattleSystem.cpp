#include "BattleSystem.h"
#include "../GameController.h"
#include "States/ActionSelectionState.h"
#include "States/RunTurnState.h"

/* Namespace Battle, para mejor organizacion */
namespace Battle
{
    /**
     * Constructor
     * Inicializa el sistema de batalla con el propietario, el jugador y el enemigo
     */
    BattleSystem::BattleSystem(GameController* owner, Player* playerCharacter, Character& enemyCharacter)
        : owner(owner), stateMachine(this), player(playerCharacter), enemy(enemyCharacter), battleUI(), chosenAction(ActionType::None), battleIsOver(false), isPlayerGuarding(false), hasHealthBarUpdated(false), hasPlayerLeveledUp(false), hasUltimatePointsUpdated(false)
    {
    }

    /* Metodo que inicia la batalla */
    void BattleSystem::startBattle()
    {
        // Configura la UI de la batalla
        battleUI.setup(player->getCharacter(), enemy);
        // Actualiza las barras de vida y puntos de definitiva
        battleUI.updateHealthBars(player->getCharacter(), enemy);
        battleUI.updatePlayerUltimatePoints(player->getUltimatePoints());
        // Coloca el estado inicial de RunTurnState
        stateMachine.changeState(new RunTurnState());
    }

    /* Metodo que maneja los eventos de la batalla */
    void BattleSystem::handleEvent(sf::Event event)
    {
        // Si se presiono una tecla
        if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            // Avanzar dialogo si se presiona E
            if (keyPressed->code == sf::Keyboard::Key::E)
            {
                if (dialogManager.isActive())
                {
                    dialogManager.nextLine();
                    return;
                }
            }
        }
        // Delegar el manejo de eventos a la maquina de estados
        stateMachine.handleEvent(event);
    }

    /* Metodo que actualiza el sistema de batalla */
    void BattleSystem::update()
    {
        // Actualizar el gestor de dialogos y la maquina de estados
        dialogManager.update();
        stateMachine.update();

        // Actualizar las barras de vida si es necesario
        if(hasHealthBarUpdated)
        {
            battleUI.updateHealthBars(player->getCharacter(), enemy);
            hasHealthBarUpdated = false;
        }
        
        // Cambiar el texto de subida de nivel
        if(hasPlayerLeveledUp)
        {
            battleUI.updatePlayerLevelText(player->getCharacter().getLevel());
            hasPlayerLeveledUp = false;
        }

        // Actualizar puntos de definitiva
        if(hasUltimatePointsUpdated)
        {
            battleUI.updatePlayerUltimatePoints(player->getUltimatePoints());
            hasUltimatePointsUpdated = false;
        }
    }

    /* Metodo que dibuja la batalla */
    void BattleSystem::draw(sf::RenderWindow& window, bool isDialogActive)
    {
        // Dibujar la maquina de estados, el gestor de dialogos y la UI de la batalla
        stateMachine.draw(window);
        dialogManager.draw(window);
        battleUI.draw(window, static_cast<int>(chosenAction), dialogManager.isActive());
    }

    /* Getter y Setters */
    Player* BattleSystem::getPlayer() { return player; }
    Character& BattleSystem::getEnemy() { return enemy; }
    BattleUI& BattleSystem::getBattleUI() { return battleUI; }
    DialogManager& BattleSystem::getDialogManager() { return dialogManager; }

    ActionType BattleSystem::getChosenAction() { return chosenAction; }
    void BattleSystem::setChosenAction(ActionType action) { chosenAction = action; }

    StateMachine<BattleSystem>& BattleSystem::getStateMachine() { return stateMachine; }

    bool BattleSystem::isBattleOver() { return battleIsOver; }
    void BattleSystem::endBattle() { battleIsOver = true; }

    bool BattleSystem::getPlayerGuarding() { return isPlayerGuarding; }
    void BattleSystem::setPlayerGuarding(bool guarding) { isPlayerGuarding = guarding; }

    bool BattleSystem::getHasHealthBarUpdated() { return hasHealthBarUpdated; }
    void BattleSystem::setHasHealthBarUpdated(bool updated) { hasHealthBarUpdated = updated; }

    bool BattleSystem::getHasPlayerLeveledUp() { return hasPlayerLeveledUp; }
    void BattleSystem::setHasPlayerLeveledUp(bool leveledUp) { hasPlayerLeveledUp = leveledUp; }

    bool BattleSystem::getHasUltimatePointsUpdated() { return hasUltimatePointsUpdated; }
    void BattleSystem::setHasUltimatePointsUpdated(bool updated) { hasUltimatePointsUpdated = updated; }
} // namespace Battle
