#include "Button.h"
#include <iostream>

Button::Button(std::shared_ptr<sf::RenderWindow>window, sf::Vector2f position,bool arrow = false, bool left = false)
{
    this->window = window;
    
   

    texture = std::make_unique<sf::Texture>();

    if (arrow)
    {
        if (!texture->loadFromFile(left ? "assets/arrow_l.png" : "assets/arrow_r.png"))
            std::cerr << "Failed to load file!";
    }
    else
    {
        //*texture = std::move();
    }
    m_buttonSprite.setTexture(*texture);
    m_buttonSprite.setPosition(position);

    m_isActive = true;
    m_isHovered = false;
}

bool Button::isActive() const
{
    return m_isActive;
}

void Button::setActive(bool active)
{
    m_isActive = active;
}

void Button::draw()
{
    window->draw(m_buttonSprite);
}

void Button::setSize(sf::Vector2f size)
{
    m_buttonSprite.setScale(size.x / m_buttonSprite.getLocalBounds().width,
        size.y / m_buttonSprite.getLocalBounds().height);
}

bool Button::isClicked()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isHovered())
        return true;
    else
        return false;

}

bool Button::isHovered()
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));

    if (m_buttonSprite.getGlobalBounds().contains(mousePos)) {
        m_isHovered = true;
        m_buttonSprite.setColor(sf::Color(255, 0, 0)); // ustaw kolor na czerwony
    }
    else {
        m_isHovered = false;
        m_buttonSprite.setColor(sf::Color(0, 255, 0)); // ustaw kolor na zielony
    }

    return m_isHovered;
}
