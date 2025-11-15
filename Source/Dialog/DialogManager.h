#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include "Dialog.h"
#include "../UI/DialogBox.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class DialogManager
{
private:
    DialogBox dialogBox;
    Dialog* currentDialog;
    int currentLine;
    int currentCharacter;
    sf::Clock clock;
    bool isDialogActive;

public:
    DialogManager();
    void startDialog(Dialog* dialog);
    void update();
    void draw(sf::RenderWindow& window);
    bool isActive();
    void nextLine();
};

#endif // DIALOGMANAGER_H
