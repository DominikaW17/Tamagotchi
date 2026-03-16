#pragma once
#include <SFML/Graphics.hpp>

enum class Room { LivingRoom, SleepingRoom, Kitchen, GamingRoom };

class House
{
    std::shared_ptr<sf::RenderWindow>window;

    std::unique_ptr<sf::Texture> gaming_room;
    std::unique_ptr<sf::Texture> kitchen;
    std::unique_ptr<sf::Texture> sleeping_room;
    std::unique_ptr<sf::Texture> living_room;

    std::unique_ptr<sf::Text> room_name;


    sf::Sprite current_room;


    Room currentRoom;

public:
    House() {};

    House(std::shared_ptr<sf::RenderWindow>&window)
    {
        gaming_room = std::make_unique<sf::Texture>();
        kitchen = std::make_unique<sf::Texture>();
        sleeping_room = std::make_unique<sf::Texture>();
        living_room = std::make_unique<sf::Texture>();

        room_name = std::make_unique<sf::Text>();

        room_name->setOutlineThickness(4);

        room_name->setPosition(270, 100);


        if (!gaming_room->loadFromFile("assets/game_room.png"));
        if (!kitchen->loadFromFile("assets/kitchen.png"));
        if (!sleeping_room->loadFromFile("assets/sypialnia.png"));
        if (!living_room->loadFromFile("assets/room.png"));

        this->window = window;
    }



    void set_gaming_room()
    {
        current_room.setTexture(*gaming_room);
        currentRoom = Room::GamingRoom;
        room_name->setString("Gaming Room");
    }
    void set_living_room()
    {
        current_room.setTexture(*living_room);
        currentRoom = Room::LivingRoom;
        room_name->setString("Living Room");

        
       
    }
    void set_sleeping_room()
    {
        current_room.setTexture(*sleeping_room);
        currentRoom = Room::SleepingRoom;
        room_name->setString("Sleeping Room");
       
    }
    void set_kitchen()
    {
        current_room.setTexture(*kitchen);
        currentRoom = Room::Kitchen;
        room_name->setString("Kitchen");
        
    }

    Room get_current_room()
    {
		return currentRoom;
	}

    void set_font(const sf::Font& f)
    {
		room_name->setFont(f);
	}

    void draw()
    {
        window->draw(current_room);
        window->draw(*room_name);
    }

};

