#include "Platform.h"


Platform::Platform(int x, int y) : x(x), y(y){}



std::vector<Platform> Platform::generuj(int minY, int maxY, int ilePlatform)
{
    std::vector<Platform> platformy;

    int roznicaY = (maxY - minY) / (ilePlatform - 1);

    for (int i = 0; i < ilePlatform; i++)
    {
        int y = minY + i * roznicaY;
        int x = 400;
        Platform platforma(x, y);
        platformy.push_back(platforma);
    }

    return platformy;
}
