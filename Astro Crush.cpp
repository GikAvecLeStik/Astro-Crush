// Astro Crush.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <SFML/Graphics.hpp>
#include "Player.hpp"

int main()
{
    

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    window.setView(sf::View(sf::FloatRect(0, 0, 320, 180)));
    Player player;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player.dt();
        window.clear();
        player.draw(window);
        player.update();
        window.display();
    }

    return 0;
}

