#pragma once
#include <SFML/Graphics.hpp>
class Platforma
{
public:
    sf::Sprite sprite;
    int x, y;

public:
    Platforma(sf::Texture& texture, int x, int y);

    void setPosition(sf::Vector2f v);
    void rysuj(sf::RenderWindow& window);
    static std::vector<Platforma> generuj(sf::Texture& texture, int minY, int maxY, int ilePlatform);
    int getX() { return x; }
    int getY() { return y; }

};
