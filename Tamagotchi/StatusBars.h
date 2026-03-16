#pragma once
#include "StatusBar.h"

class StatusBars
{
    std::shared_ptr<sf::RenderWindow>window;

    StatusBar healthBar;
    StatusBar energyBar;
    StatusBar hungerBar;
    StatusBar happinessBar;


    std::unique_ptr<sf::Texture> health_icon;
    std::unique_ptr<sf::Texture> energy_icon;
    std::unique_ptr<sf::Texture> hunger_icon;
    std::unique_ptr<sf::Texture> happiness_icon;

public:
    StatusBars() {};
    StatusBars(std::shared_ptr<sf::RenderWindow>& window)
    {
        this->window = window;

        healthBar = StatusBar(window, health_icon, StatusBar::ICON::health, sf::Vector2f(175, 25));
        energyBar = StatusBar(window, energy_icon, StatusBar::ICON::energy, sf::Vector2f(275, 25));
        hungerBar = StatusBar(window, hunger_icon, StatusBar::ICON::hunger, sf::Vector2f(375, 25));
        happinessBar = StatusBar(window, happiness_icon, StatusBar::ICON::happiness, sf::Vector2f(475, 25));
    }

    void draw()
    {
        healthBar.draw();
        energyBar.draw();
        hungerBar.draw();
        happinessBar.draw();
    }


};

