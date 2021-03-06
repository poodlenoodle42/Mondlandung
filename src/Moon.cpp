#include "Moon.hpp"

Moon::Moon(double radius, int num_points) {
    moon_shape = sf::CircleShape(radius, num_points);
    moon_shape.setOrigin(radius, radius);
    moon_shape.setPosition(0.f, radius);
}
bool Moon::setup_sprite() {
    bool success = moon_texture.loadFromFile("assets/moon_texture.jpg");
    if (success) {
        moon_shape.setTexture(&moon_texture);
    }
    return success;
}

void Moon::draw(sf::RenderWindow& window) const {
    window.draw(moon_shape);
}