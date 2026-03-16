#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Button.h"
#include "Zwierzak.h"
#include "StatusBar.h"
#include "Platform.h"
#include "House.h"
#include "StatusBars.h"

class MainGame
{
	std::shared_ptr<sf::RenderWindow> window;

    sf::Clock clock;
    
    std::unique_ptr<sf::Font> font;

    Button arrow_button_right;
    Button arrow_button_left;

    StatusBars bars;
    House house;
    Zwierzak zwierzak;

    

    int score;

    

    bool load_asseets()
    {

        

        font = std::make_unique<sf::Font>();

        if (!font->loadFromFile("assets/arial.ttf"))  return false; 

        house.set_font(*font);
        zwierzak.setFont(*font);

        choice_pet();

        zwierzak.setPosition(sf::Vector2f(250,300));
        
       
        return true;
    }

    void choice_pet()
    {
        //TO DO
        //std::string imie;
        //zrobic okno odpowiadajace za  wybor zwierzaka
        //
        
        //animal.loadFromFile("");
        //placeholder do wpisywania nazwy zwierzaka

        //zwierzak = Zwierzak(window, imie);

       

        zwierzak = Zwierzak(window,Kind::stitch, "Stitch");

    }

public:

	MainGame()
	{
        
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(700, 800), "Tamagotchi");
		window->setFramerateLimit(70);
		
        house = House(window);
        bars = StatusBars(window);
        arrow_button_left = Button(window, sf::Vector2f(10, 20), true, true);
        arrow_button_right = Button(window, sf::Vector2f(590, 20), true, false);


        if (!load_asseets())
        {
            std::cerr << "File failed to load!";
            return;
        }

        
        house.set_living_room();
                
        score = 0;
	}


    void home()
    {
        window->clear();

        while (window->isOpen())
        {
            sf::Event e{};

            while (window->pollEvent(e))
                if(e.type == sf::Event::Closed)
                    window->close();

            if (arrow_button_right.isClicked())
            {
                if (house.get_current_room() == Room::LivingRoom)
                {
                    house.set_sleeping_room();
                    
                }
                else if (house.get_current_room() == Room::SleepingRoom)
                {
                    house.set_kitchen();
                }

            }
            if (arrow_button_left.isClicked())
            {
                house.set_gaming_room();
                zwierzak.setPosition(sf::Vector2f(300, 220));
            }



            sf::Time elapsed = clock.getElapsedTime(); 
            //std::cout << "Czas gry: " << elapsed.asSeconds() << " sekund" << std::endl;

            house.draw();
            
            bars.draw();
            zwierzak.draw(Zwierzak::Mood::normal);
            arrow_button_left.draw();
            arrow_button_right.draw();
            window->display();
            

        }
    }
    
	void skyJump()
	{
        sf::Texture t1, t2, t3, t4;

        t1.loadFromFile("assets/pink.png");
        t2.loadFromFile("assets/platform.png");
        t3.loadFromFile("assets/stitch.png");
        t4.loadFromFile("assets/arrow_l.png");

        sf::Sprite sBackground(t1);
        sf::Text score_text;
        sf::Font font;
        font.loadFromFile("assets/arial.ttf");

        score_text.setFont(font);
        score_text.setPosition(250, 10);
        score_text.setCharacterSize(50);
        score_text.setFillColor(sf::Color::Black);




        zwierzak.setScale(sf::Vector2f(0.3, 0.3));


        const short nPlat = 5;

        std::vector<Platform> plat = Platform::generuj(100, 733, nPlat);

        const int jump = -13;

        int x = 100, y = 100, h = 200;
        float dx = 0, dy = 0;
        //int score = 0;
        bool gameOver = false;

        window->clear();
        while (window->isOpen())
        {
            sf::Event e;
            while (window->pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                    window->close();

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x += 6;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x -= 6;

           


            dy += 0.2;
            y += dy;


            if (y > 700)
            {

                sf::Text text;
                text.setFont(font);
                text.setString("Game Over!");
                text.setCharacterSize(60);
                text.setPosition(150, 300);

                window->draw(text);
                window->display();

                // zaczekaj kilka sekund

                sf::sleep(sf::seconds(2));
                return;

            }


            if (y < h)
                for (int i = 0; i < nPlat; i++)
                {
                    y = h;
                    plat[i].setY(plat[i].getY() - dy);
                    //znikanie platform i pojawianie siê nowych
                    if (plat[i].getY() > 733)
                    {
                        std::random_device dev;
                        std::mt19937 rng(dev());
                        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 400);
                        plat[i].setY(0);
                        plat[i].setX(dist6(rng));
                        score++;

                    }
                }

            //wykrywanie kolizji
            for (int i = 0; i < nPlat; i++)
                if ((x + 50 > plat[i].getX()) && (x + 20 < plat[i].getX() + 68)
                    && (y + 70 > plat[i].getY()) && (y + 70 < plat[i].getY() + 14) && (dy > 0))
                {
                    dy = jump;


                    score_text.setString("Score: " + std::to_string(score));
                }

            zwierzak.setPosition(sf::Vector2f(x, y));
            
          


            window->draw(sBackground);
            window->draw(score_text);
            zwierzak.draw(Zwierzak::Mood::sad);

            sf::Sprite s(t2);
            for (int i = 0; i < nPlat; i++)
            {

                s.setPosition(plat[i].getX(), plat[i].getY());
                window->draw(s);
            }

            window->display();

            
        }
        
        
        
	}

    
};

