#include "Lander.hpp"
Lander::Lander() : fuel(0), hight(0), speed(0), thrust(0), gravitation(0) {}

Lander::Lander(double fuel, double hight, double speed, double thrust,double gravitation) :
fuel(fuel), hight(hight), speed(speed), thrust(thrust), gravitation(gravitation) {}

bool Lander::setup_sprite() {
    bool success = lander_texture.loadFromFile("assets/lander_texture.png");
    if(success) {
        lander_sprite.setTexture(lander_texture,true);
    }
    auto size = lander_sprite.getLocalBounds();
    lander_sprite.scale(sf::Vector2f(1/size.height,1/size.height));
    size = lander_sprite.getGlobalBounds();
    lander_sprite.setOrigin(sf::Vector2f(size.width/2,size.height/2));
    lander_sprite.setPosition(sf::Vector2f(0.f,hight));
    return success;
}

void Lander::draw(sf::RenderWindow& window) const {
    window.draw(lander_sprite);
}

void Lander::step(double deltaTime, bool fire) {
    speed += gravitation * deltaTime;
    if(fire){
        speed -= thrust * deltaTime;
        fuel -= thrust * deltaTime;
    }
    hight -= speed * deltaTime;
    
    lander_sprite.move(sf::Vector2f(0.f,-speed));

}