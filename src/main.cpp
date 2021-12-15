#include "Lander.hpp"
#include "Moon.hpp"
#include "UI.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>


template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

void setup_ui(const Lander& l, double radius, UI& ui, unsigned int font_size) {
    sf::Text t;
    t.setCharacterSize(font_size);
    t.setFillColor(sf::Color::White);
    ui.add_updating_text(std::pair(t,Update_Text([&](){
        return string_format("Height %.2f",l.get_hight());
    })));
    t.move(0,font_size);
    ui.add_updating_text(std::pair(t,Update_Text([&](){
        return string_format("Speed %.2f",l.get_speed());
    })));
    t.move(0,font_size);
    ui.add_updating_text(std::pair(t,Update_Text([&](){
        return string_format("Fuel %.2f",l.get_fuel());
    })));


}

int main() {

    sf::RenderWindow window(sf::VideoMode(600, 600), "Mondlandung");

    Moon moon(1000, 1000);
    Lander lander(100, 500, 10, 5, 1.5);
    UI ui(window.getDefaultView());

    setup_ui(lander,moon.get_radius(),ui,24);

    if (!(moon.setup_sprite() && lander.setup_sprite())) {
        std::cout << "Error loading textures and setting up sprites\n";
        return 1;
    }
    // player_view(sf::Vector2f(200.f, 200.f), lander.get_sprite_pos());
    sf::View player_view = window.getDefaultView();

    player_view.setCenter(lander.get_sprite_pos() + lander.get_sprite().getOrigin());
    player_view.setSize(sf::Vector2f(10, 10));
    window.setView(player_view);
    // window.setView(player_view);
    window.setFramerateLimit(60);
    sf::Clock clock;
    bool end = false;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        bool boost = false;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            boost = true;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player_view.zoom(1 - deltaTime);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player_view.zoom(1 + deltaTime);
        }

        player_view.setCenter(lander.get_sprite_pos() + lander.get_sprite().getOrigin());
        window.setView(player_view);
        window.clear();
        moon.draw(window);
        lander.draw(window);
        ui.draw(window);
        window.display();

        lander.step(deltaTime, boost);

        if(lander.get_hight() == 0 && !end){
            end = true;
            if(lander.get_speed() > 5){
                sf::Text t;
                t.setCharacterSize(50);
                t.setFillColor(sf::Color::Red);
                t.setString("Crashed");
                t.setPosition((static_cast<float>(window.getSize().x) / 2) - 50 * 3.f,static_cast<float>(window.getSize().y) / 2);
                ui.add_static_text(t);

            } else {
                sf::Text t;
                t.setCharacterSize(50);
                t.setFillColor(sf::Color::Green);
                t.setString("Success");
                t.setPosition((static_cast<float>(window.getSize().x) / 2) - 50 * 3.f,static_cast<float>(window.getSize().y) / 2);
                ui.add_static_text(t);
            }
        }
        //std::cout << lander.get_fuel() << " " << lander.get_hight() << " "
        //          << lander.get_speed() << "\n";
    }

    return 0;
}