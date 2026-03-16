#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>

enum class Kind { stitch, dog };

class Zwierzak
{
    
    std::shared_ptr<sf::RenderWindow>window;
    sf::Sprite s;
    std::unique_ptr<sf::Texture> texture_normal;
    std::unique_ptr<sf::Texture> texture_sad;
    std::unique_ptr<sf::Texture> texture_sleep;

    sf::Text imie;

    
    short szczescie;
    short sytosc;
    short czystosc;
    short zdrowie;
    int pieniadze;
    bool sen;
    Kind rodzaj;

public:

    
    enum class Mood { sad,normal,sleep };

    Zwierzak();
    Zwierzak(std::shared_ptr<sf::RenderWindow>&window,const Kind & rodzaj, std::string imie)
    {
        this->window = window;
        this->rodzaj = rodzaj;
        
        texture_normal = std::make_unique<sf::Texture>();
        texture_sad = std::make_unique<sf::Texture>();
        texture_sleep = std::make_unique<sf::Texture>();

        loadFromFile(rodzaj);
        
        s.setTexture(*texture_normal);


        szczescie = 80;
        sytosc = 80;
        czystosc = 80;
        zdrowie = 80;
        pieniadze = 0;
        sen = 80;



    }
    //virtual ~Zwierzak() = default;
    void setFont(const sf::Font& f)
    {
        imie.setFont(f);
    }
    void setScale(sf::Vector2f&& size)
    {
        s.setScale(size);
    } 
    void setPosition(sf::Vector2f&& size)
    {
        s.setPosition(size);
    }

    void loadFromFile(Kind k)
    {
        if (k == Kind::stitch)
        {
            texture_normal->loadFromFile("assets/stitch.png");
            texture_sad->loadFromFile("assets/stitch.png");
            texture_sleep->loadFromFile("assets/stitch.png");
        }
    }
    void nakarm();
    void wyczysc();
    void zagraj();
    void poglaskaj();
    void wlacz_wylacz_swiatlo();

    

    void draw(Mood k)
    {
        s.setTexture(k == Mood::normal ? *texture_normal : (k == Mood::sad ? *texture_sad : *texture_sleep));

        window->draw(s);
        //window->draw(imie);
    }
};





