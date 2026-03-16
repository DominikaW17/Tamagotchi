#pragma once

#include <SFML/Graphics.hpp>

class Button
{
    std::shared_ptr<sf::RenderWindow>window;
    sf::Sprite m_buttonSprite;
    std::unique_ptr<sf::Texture> texture;

    bool m_isActive;
    bool m_isHovered;

public:
    Button(){}
    Button(std::shared_ptr<sf::RenderWindow> window, sf::Vector2f position, bool arrow, bool left);


    bool isActive() const;

    void setActive(bool active);

    void draw();

    bool isHovered();

    void setPosition(sf::Vector2f pos)
    {
        m_buttonSprite.setPosition(pos);
    }

    void setSize(sf::Vector2f size);

    bool isClicked();

};
