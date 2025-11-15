#include "DialogBox.h"
#include <iostream>

DialogBox::DialogBox() : text(nullptr)
{
}

DialogBox::~DialogBox()
{
    delete text;
}

void DialogBox::setup()
{
    if (!font.openFromFile("Assets/fonts/font.otf"))
    {
        std::cerr << "Error loading font Assets/fonts/font.otf" << std::endl;
        if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            std::cerr << "Error loading fallback font C:/Windows/Fonts/arial.ttf" << std::endl;
            return;
        }
    }

    box.setSize(sf::Vector2f(700, 150));
    box.setFillColor(sf::Color(0, 0, 0, 150));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.setPosition({50, 400});

    text = new sf::Text(font, "", 24);
    text->setCharacterSize(24);
    text->setFillColor(sf::Color::White);
    text->setPosition({70, 420});
}

void DialogBox::setText(const std::string& str)
{
    if(text)
        text->setString(str);
}

void DialogBox::draw(sf::RenderWindow& window)
{
    window.draw(box);
    if(text)
        window.draw(*text);
}
