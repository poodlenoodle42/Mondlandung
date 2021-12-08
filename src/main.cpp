#include <SFML/Graphics.hpp>
#include "Moon.hpp"
#include "Lander.hpp"
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    Moon moon{1000,1000};
    Lander lander{1000,1000,100,10,1.5};
    if(!(moon.setup_sprite() && lander.setup_sprite())) {
        std::cout << "Error loading textures and setting up sprites\n";
        return 1;
    }
    sf::View player_view(sf::Vector2f(200.f,200.f),lander.get_sprite_pos());
    player_view = window.getDefaultView();
    //window.setView(player_view);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed){
                if(event.KeyPressed == sf::Keyboard::Space) {
                    player_view.zoom(1.5f);
                }
            }
        }

        window.clear();
        moon.draw(window);
        lander.draw(window);
        window.display();
        
        window.setView(player_view);
    }

    return 0;
}