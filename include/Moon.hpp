#include <SFML/Graphics.hpp>

class Moon {
private:
    sf::CircleShape moon_shape;
    sf::Texture moon_texture;

public:
    Moon(double radius, int num_points);
    bool setup_sprite();
    inline float get_radius() const { return moon_shape.getRadius(); }
    inline const sf::CircleShape& get_shape() const { return moon_shape; }
    void draw(sf::RenderWindow& window) const;
};