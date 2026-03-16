#pragma once
#include <SFML/Graphics.hpp>

class Platform
{
public:
   
    int x;
    int y;

public:
    Platform(int x, int y);

    static std::vector<Platform> generuj(int minY, int maxY, int ilePlatform);
    int getX() { return x; }
    int getY() { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

};
