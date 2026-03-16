#include "Platforma.h"

Platforma::Platforma(sf::Texture& texture, int x, int y) : x(x), y(y)
{
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Platforma::setPosition(sf::Vector2f v)
{
    x = v.x;
    y = v.y;
}

void Platforma::rysuj(sf::RenderWindow& window)
{
    window.draw(sprite);
}

std::vector<Platforma> Platforma::generuj(sf::Texture& texture, int minY, int maxY, int ilePlatform)
{
    std::vector<Platforma> platformy;

    int roznicaY = (maxY - minY) / (ilePlatform - 1);

    for (int i = 0; i < ilePlatform; i++)
    {
        int y = minY + i * roznicaY;
        int x = 400;
        Platforma platforma(texture, x, y);
        platformy.push_back(platforma);
    }

    return platformy;
}
