#include <SFML/Graphics.hpp>

class Lander {
    private:
        sf::Sprite lander_sprite;
        sf::Texture lander_texture;
        double fuel;
        double hight;
        double speed;
        double thrust;
        double gravitation;
    public:
        Lander();
        Lander(double fuel, double hight, double speed, double thrust,double gravitation);
        inline double get_fuel() const {return fuel;}
        inline double get_hight() const {return hight;}
        inline double get_speed() const {return speed;}
        inline double get_thrust() const {return thrust;}
        inline double get_gravitation() const {return gravitation;}
        inline sf::Vector2f get_sprite_pos() const {return lander_sprite.getPosition();}
        void step(double deltaTime, bool fire);
        bool setup_sprite();
        void draw(sf::RenderWindow& window) const;
};