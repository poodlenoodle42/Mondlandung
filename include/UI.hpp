#include "Update_Text.hpp"
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
class UI {
private:
    sf::Font font;
    std::vector<std::pair<sf::Text, Update_Text>> self_updating_texts;
    std::vector<sf::Text> static_text;
    sf::View ui_view;

public:
    UI(sf::View view);
    void add_static_text(const sf::Text& text);
    void add_updating_text(const std::pair<sf::Text, Update_Text>& text);
    void draw(sf::RenderWindow& window);
};