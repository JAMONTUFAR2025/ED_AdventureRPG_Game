#include "MainMenuState.h"
#include "../GameController.h"
#include <iostream>
#include <vector>
#include <string>

MainMenuState::MainMenuState() : selectedOption(0), testDialog(nullptr), dialogJustEnded(false)
{
}

void MainMenuState::enter(GameController* owner)
{
    std::cout << "Entering MainMenuState" << std::endl;
    mainMenuUI.setup(owner);
    std::vector<std::string> dialogLines = {"Hola, aventurero!", "Bienvenido a Adventure RPG.", "Espero que disfrutes tu estancia."};
    testDialog = new Dialog(dialogLines);
    dialogJustEnded = false; // Ensure flag is reset on entering state
}

void MainMenuState::update(GameController* owner)
{
    bool wasDialogActive = dialogManager.isActive(); // Store dialog state before update

    if (dialogManager.isActive())
    {
        dialogManager.update();
    }

    // Check if dialog just became inactive after this update
    if (wasDialogActive && !dialogManager.isActive())
    {
        dialogJustEnded = true; // Set flag to consume next Z key press
    }
}

void MainMenuState::handleEvent(GameController* owner, sf::Event event)
{
    // If a dialog just ended, consume the 'Z' key press that might have ended it
    // and prevent it from being processed by the menu for this frame.
    if (dialogJustEnded)
    {
        if (const auto keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Z)
            {
                dialogJustEnded = false; // Reset the flag
                return; // Consume the event
            }
        }
    }

    if (dialogManager.isActive())
    {
        if (const auto keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Z)
            {
                dialogManager.nextLine();
            }
        }
    }
    else // Dialog is not active, handle menu input
    {
        mainMenuUI.handleInput(event, owner, selectedOption);
        if (const auto keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Z)
            {
                if (selectedOption == 0) // Jugar
                {
                    dialogManager.startDialog(testDialog);
                }
            }
        }
    }
}

void MainMenuState::draw(sf::RenderWindow& window)
{
    mainMenuUI.draw(window, selectedOption);
    if (dialogManager.isActive())
    {
        dialogManager.draw(window);
    }
}

void MainMenuState::exit()
{
    std::cout << "Exiting MainMenuState" << std::endl;
    delete testDialog;
}

const char* MainMenuState::getName() const
{
    return "MainMenuState";
}
