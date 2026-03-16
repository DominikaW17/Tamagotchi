#include "function.h"

void game_sky_jump(sf::RenderWindow& window)
{

    window.setFramerateLimit(60);

    sf::Texture t1, t2, t3, t4;

    t1.loadFromFile("assets/pink.png");
    t2.loadFromFile("assets/platform.png");
    t3.loadFromFile("assets/stitch.png");
    t4.loadFromFile("assets/arrow_l.png");

    sf::Sprite sBackground(t1), sPlat(t2), sPers(t3);
    sf::Text score_text;
    sf::Font font;
    font.loadFromFile("assets/arial.ttf");

    score_text.setFont(font);
    score_text.setPosition(250, 10);
    //ustawienie rozmiaru
    score_text.setCharacterSize(50);
    //ustawienie koloru
    score_text.setFillColor(sf::Color::Black);



    Button back(sf::Vector2f(10, 100), t4);

    sPers.setScale(0.3, 0.3);


    const short nPlat = 5;

    std::vector<Platforma> plat = Platforma::generuj(t4, 100, 733, nPlat);

    const int jump = -13;

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;
    int score = 0;
    bool gameOver = false;

    window.clear();
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x += 6;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x -= 6;

        //to do
        if (back.isClicked(window))
        {
            return;
        }


        dy += 0.2;
        y += dy;


        if (y > 700)
        {

            sf::Text text;
            text.setFont(font);
            text.setString("Game Over!");
            text.setCharacterSize(60);
            text.setPosition(150, 300);

            window.draw(text);
            window.display();

            // zaczekaj kilka sekund

            sf::sleep(sf::seconds(2));
            return;

        }


        if (y < h)
            for (int i = 0; i < nPlat; i++)
            {
                y = h;
                plat[i].y = plat[i].y - dy;
                //znikanie platform i pojawianie siê nowych
                if (plat[i].y > 733)
                {
                    std::random_device dev;
                    std::mt19937 rng(dev());
                    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 400);
                    plat[i].y = 0; plat[i].x = dist6(rng);
                    score++;

                }
            }

        //wykrywanie kolizji
        for (int i = 0; i < nPlat; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))
            {
                dy = jump;


                score_text.setString("Score: " + std::to_string(score));
            }

        sPers.setPosition(x, y);



        window.draw(sBackground);
        window.draw(score_text);
        back.draw(window);
        window.draw(sPers);

        for (int i = 0; i < nPlat; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);
            window.draw(sPlat);
        }

        window.display();
    }
}

void start_game()
{
    sf::RenderWindow game(sf::VideoMode(700, 800), "Game!");
    sf::Texture room, arrow_l, arrow_r;

    if (!room.loadFromFile("assets/room.png"))
    {
        std::cerr << "File open error\n";
        return;
    }
    if (!arrow_l.loadFromFile("assets/arrow_l.png"))
    {
        std::cerr << "File open error\n";
        return;
    }
    if (!arrow_r.loadFromFile("assets/arrow_r.png"))
    {
        std::cerr << "File open error\n";
        return;
    }

    enum Room { LivingRoom, SleepingRoom, Kitchen };
    Room currentRoom = LivingRoom;

    sf::Sprite r(room);

    Button arrow_button_right(sf::Vector2f(590, 10), arrow_r);
    Button arrow_button_left(sf::Vector2f(10, 10), arrow_l);

    //arrow_button_right.setSize(sf::Vector2f(100, 100));
    //arrow_button_left.setSize(sf::Vector2f(100, 100));

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        std::cerr << "File open error\n";
        return;
    }

    text.setFont(font);
    text.setString("Pokoj");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(300, 10);


    //animal z klasy

    sf::Texture animal;

    animal.loadFromFile("assets/stitch.png");

    sf::Sprite stitch(animal);



    stitch.setPosition(200, 200);

    while (game.isOpen())
    {
        sf::Event e;
        while (game.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                game.close();

            //obs³uga strza³ek
            if (arrow_button_right.isClicked(game))
            {
                if (currentRoom == LivingRoom) {
                    room.loadFromFile("assets/sypialnia.png");
                    currentRoom = SleepingRoom;
                    text.setString("Sypialnia");
                }
                else if (currentRoom == SleepingRoom) {
                    room.loadFromFile("assets/kitchen2.png");
                    currentRoom = Kitchen;
                    text.setString("Kuchnia");
                }
                else if (currentRoom == Kitchen) {
                    //room.loadFromFile("assets/room.png");
                    //currentRoom = LivingRoom;
                    //text.setString("Pokoj");

                    game_sky_jump(game);
                    //game2(game);
                }
            }
            else if (arrow_button_left.isClicked(game))
            {
                if (currentRoom == LivingRoom) {
                    room.loadFromFile("assets/kitchen2.png");
                    currentRoom = Kitchen;
                    text.setString("Kuchnia");
                }
                else if (currentRoom == SleepingRoom) {
                    room.loadFromFile("assets/room.png");
                    currentRoom = LivingRoom;
                    text.setString("Pokoj");
                }
                else if (currentRoom == Kitchen) {
                    room.loadFromFile("assets/sypialnia.png");
                    currentRoom = SleepingRoom;
                    text.setString("Sypialnia");
                }
            }



        }


        game.clear();

        game.draw(r);
        game.draw(stitch);
        game.draw(text);
        arrow_button_left.draw(game);
        arrow_button_right.draw(game);
        game.display();
    }



}


