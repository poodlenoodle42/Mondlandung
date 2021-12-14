#include "Lander.hpp"
Lander::Lander()
    : fuel(0)
    , hight(0)
    , speed(0)
    , thrust(0)
    , gravitation(0) {
}

Lander::Lander(double fuel, double hight, double speed, double thrust, double gravitation)
    : fuel(fuel)
    , hight(hight)
    , speed(speed)
    , thrust(thrust)
    , gravitation(gravitation) {
}

bool Lander::setup_sprite() {
    bool success = lander_texture.loadFromFile("assets/lander_texture.png");
    if (success) {
        lander_sprite.setTexture(lander_texture, true);
    }
    auto size = lander_sprite.getLocalBounds();
    lander_sprite.scale(sf::Vector2f(1 / size.height, 1 / size.height));
    size = lander_sprite.getGlobalBounds();
    lander_sprite.setOrigin(sf::Vector2f(size.width / 2, size.height / 2));
    lander_sprite.setPosition(sf::Vector2f(0.f, hight));

    bool fire_success = fire_texture.loadFromFile("assets/fire_texture.png");
    if (fire_success) {
        fire_sprite.setTexture(fire_texture);
    }
    size = fire_sprite.getLocalBounds();
    fire_sprite.scale(sf::Vector2f(1 / size.height, 1 / size.height));
    size = fire_sprite.getGlobalBounds();
    fire_sprite.setOrigin(sf::Vector2f(size.width / 2, size.height / 2));
    return success && fire_success;
}

void Lander::draw(sf::RenderWindow& window) {
    if (fire) {
        fire_sprite.setPosition(lander_sprite.getPosition() + sf::Vector2f(0.4f, 0.65f));
        window.draw(fire_sprite);
    }
    window.draw(lander_sprite);
}

void Lander::step(double deltaTime, bool fire) {
    this->fire = fire;
    speed += gravitation * deltaTime;
    if (fire) {
        speed -= thrust * deltaTime;
        fuel -= thrust * deltaTime;
    }
    hight -= speed * deltaTime;

    lander_sprite.move(sf::Vector2f(0.f, -speed));
}