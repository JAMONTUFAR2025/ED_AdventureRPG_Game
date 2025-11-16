#include "DialogBox.h"
#include <iostream>

DialogBox::DialogBox() : text(nullptr), currentCharIndex(0), isMessageComplete(false)
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
        cout << "Error loading font Assets/fonts/font.otf" << endl;
        if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            cout << "Error loading fallback font C:/Windows/Fonts/arial.ttf" << endl;
            return;
        }
    }

    box.setSize(Vector2f(700, 150));
    box.setFillColor(Color(0, 0, 0, 150));
    box.setOutlineColor(Color::White);
    box.setOutlineThickness(6);
    box.setPosition({50, 380});

    text = new Text(font, "", 32);
    text->setCharacterSize(32);
    text->setFillColor(Color::White);
    text->setPosition({70, 420});

    if (!messageQueue.empty())
    {
        nextMessage();
    }
}

void DialogBox::setText(const string& str)
{
    // Clear queue and display immediately
    while (!messageQueue.empty())
    {
        messageQueue.pop();
    }
    currentMessage = str;
    displayedText = str;
    currentCharIndex = str.length();
    isMessageComplete = true;
    if (text)
    {
        text->setString(displayedText);
    }
}

void DialogBox::addMessage(const string& message)
{
    messageQueue.push(message);
    if (!isBusy())
    {
        nextMessage();
    }
}

void DialogBox::nextMessage()
{
    if (!messageQueue.empty())
    {
        currentMessage = messageQueue.front();
        messageQueue.pop();
        displayedText = "";
        currentCharIndex = 0;
        isMessageComplete = false;
        clock.restart();
    }
    else
    {
        currentMessage = "";
        isMessageComplete = true;
    }
}

void DialogBox::update(Time dt)
{
    if (!isMessageComplete && isBusy())
    {
        if (clock.getElapsedTime() > timePerChar)
        {
            if (currentCharIndex < currentMessage.length())
            {
                displayedText += currentMessage[currentCharIndex];
                if (text)
                {
                    text->setString(displayedText);
                }
                currentCharIndex++;
                clock.restart();
            }
            else
            {
                isMessageComplete = true;
            }
        }
    }
}

bool DialogBox::isBusy() const
{
    return !currentMessage.empty() || !messageQueue.empty();
}

void DialogBox::handleInput()
{
    if (isBusy())
    {
        if (!isMessageComplete)
        {
            // Skip typewriter effect
            isMessageComplete = true;
            displayedText = currentMessage;
            if (text)
            {
                text->setString(displayedText);
            }
        }
        else
        {
            // Move to next message
            nextMessage();
        }
    }
}

void DialogBox::draw(RenderWindow& window)
{
    if (isBusy())
    {
        window.draw(box);
        if (text)
        {
            window.draw(*text);
        }
    }
}
