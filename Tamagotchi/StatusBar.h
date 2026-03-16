#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class StatusBar
{
    std::shared_ptr<sf::RenderWindow> window;
    sf::RectangleShape rect;
    sf::RectangleShape fillRect;
    sf::Sprite icon;
    float fillRatio;


public:
    enum class ICON { hunger, health, energy, happiness };

    StatusBar(){}

    StatusBar(std::shared_ptr<sf::RenderWindow>&window,std::unique_ptr<sf::Texture>& texture, const ICON& i,const sf::Vector2f& pos = sf::Vector2f(100, 100))
    {

        this->window = window;

        texture = std::make_unique<sf::Texture>();

        if (!texture->loadFromFile(i == ICON::energy ? "assets/power.png" :
            (i == ICON::hunger ? "assets/hunger.png" :
                (i == ICON::health ? "assets/health.png" : "assets/happiness.png"))))
        {
            std::cerr << "File failed to load!";
            return;
        }


        texture->setSmooth(true);



        icon = sf::Sprite(*texture);
        /**
        icon.setScale(i == ICON::energy ? sf::Vector2f(0.07, 0.07) : 
            (i == ICON::hunger ? sf::Vector2f(0.07, 0.07) : 
                (i==ICON::happiness ? sf::Vector2f(0.07, 0.07) : sf::Vector2f(1, 1))));
        /**/
        

        rect.setSize(sf::Vector2f(50, 50));
        rect.setPosition(pos);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(3);
        rect.setOutlineColor(sf::Color::Black);

        fillRect.setFillColor(sf::Color::Green);

        set_fillRatio(0.5);

        float iconX = rect.getPosition().x + rect.getSize().x / 2 - icon.getGlobalBounds().width / 2;
        float iconY = rect.getPosition().y + rect.getSize().y / 2 - icon.getGlobalBounds().height / 2;

        icon.setPosition(iconX, iconY);


    }

    void set_fillRatio(float fillRatio = 0.5)
    {
        fillRatio = std::max(0.0f, std::min(fillRatio, 1.0f)); //zabezpiecz przed wartoœciami spoza zakresu [0,1]
        this->fillRatio = fillRatio;
        fillRect.setSize(sf::Vector2f(rect.getSize().x, rect.getSize().y * fillRatio));
        fillRect.setPosition(rect.getPosition().x, rect.getPosition().y + rect.getSize().y * (1 - fillRatio));
    }

    void draw()
    {

        window->draw(rect);
        window->draw(fillRect);
        window->draw(icon);
    }
};
