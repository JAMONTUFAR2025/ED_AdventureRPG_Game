#include "DialogManager.h"

DialogManager::DialogManager() : currentDialog(nullptr), currentLine(0), currentCharacter(0), isDialogActive(false)
{
    dialogBox.setup();
}

void DialogManager::startDialog(Dialog* dialog)
{
    currentDialog = dialog;
    currentLine = 0;
    currentCharacter = 0;
    isDialogActive = true;
    clock.restart();
}

void DialogManager::update()
{
    if (!isDialogActive || !currentDialog)
    {
        return;
    }

    if (clock.getElapsedTime().asSeconds() > 0.05f) // Adjust speed here
    {
        const std::vector<std::string>& lines = currentDialog->getLines();
        if (currentLine < lines.size())
        {
            if (currentCharacter < lines[currentLine].length())
            {
                currentCharacter++;
                dialogBox.setText(lines[currentLine].substr(0, currentCharacter));
            }
        }
        clock.restart();
    }
}

void DialogManager::draw(sf::RenderWindow& window)
{
    if (isDialogActive)
    {
        dialogBox.draw(window);
    }
}

bool DialogManager::isActive()
{
    return isDialogActive;
}

void DialogManager::nextLine()
{
    if (!isDialogActive || !currentDialog)
    {
        return;
    }

    const std::vector<std::string>& lines = currentDialog->getLines();
    if (currentLine < lines.size() - 1)
    {
        currentLine++;
        currentCharacter = 0;
    }
    else
    {
        isDialogActive = false;
    }
}
