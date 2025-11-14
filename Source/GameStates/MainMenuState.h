#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../Util/StateMachine/IState.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// Forward declaration of GameController to avoid circular dependencies
class GameController;

class MainMenuState : public IState<GameController>
{
private:
    sf::Font titleFont;
    sf::Text* titleText;

    sf::Font optionsFont;
    std::vector<sf::Text*> optionTexts;
    int selectedOption;

public:
    MainMenuState();
    void enter(GameController* owner) override;
    void execute(GameController* owner, sf::Event event) override;
    void draw(sf::RenderWindow& window) override;
    void exit() override;
    const char* getName() const override;
};

#endif // MAINMENUSTATE_H
