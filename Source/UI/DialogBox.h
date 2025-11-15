#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class DialogBox
{
private:
    sf::RectangleShape box;
    sf::Text* text;
    sf::Font font;

public:
    DialogBox();
    ~DialogBox();
    void setup();
    void setText(const std::string& str);
    void draw(sf::RenderWindow& window);
};

#endif // DIALOGBOX_H
