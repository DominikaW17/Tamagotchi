#include <iostream>
#include <memory>
#include "MainGame.h"


//class 


int main()
{

    //std::unique_ptr<MainGame> game(new MainGame());
   

    //game->skyJump();

    //game->home();

    sf::RenderWindow window(sf::VideoMode(700, 800), "SFML works!");
   
   

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
       
        window.display();
    }


}
