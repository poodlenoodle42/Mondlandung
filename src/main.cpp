#include <SFML/Graphics.hpp>
#include "Moon.hpp"
#include "Lander.hpp"
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

    Moon moon{10000,1000};
    Lander lander{1000,100000,100,10,1.5};
    if(!(moon.setup_sprite() && lander.setup_sprite())) {
        std::cout << "Error loading textures and setting up sprites\n";
        return 1;
    }
    sf::View player_view(sf::Vector2f(200.f,200.f),lander.get_sprite_pos());
    player_view = window.getDefaultView();
    

    player_view.setCenter(lander.get_sprite_pos() + lander.get_sprite().getOrigin());
    player_view.setSize(sf::Vector2f(2,2));
    window.setView(player_view);
    //window.setView(player_view);
    window.setFramerateLimit(60);
    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        bool boost = false;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Space) {
                    boost = true;
                }
            }
        }

        player_view.setCenter(lander.get_sprite_pos() + lander.get_sprite().getOrigin());
        window.setView(player_view);
        window.clear();
        moon.draw(window);
        lander.draw(window);
        window.display();

        lander.step(deltaTime,boost);
        std::cout << lander.get_fuel() << " " << lander.get_hight() << "\n";
    }

    return 0;
}