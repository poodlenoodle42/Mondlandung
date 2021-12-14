#include "UI.hpp"
#include <iostream>
UI::UI(sf::View view) {
    ui_view = view;
    if (!font.loadFromFile("assets/sagan.ttf")) {
        std::cout << "Failed loading font\n";
    }
}

void UI::add_static_text(const sf::Text& text) {
    sf::Text t = text;
    t.setFont(font);
    static_text.push_back(std::move(t));
}

void UI::add_updating_text(const std::pair<sf::Text, Update_Text>& text) {
    sf::Text t = text.first;
    t.setFont(font);
    self_updating_texts.push_back(std::pair(t, text.second));
}

void UI::draw(sf::RenderWindow& window) {
    sf::View current_view = window.getView();
    window.setView(ui_view);
    for (const auto& s_text : static_text) {
        window.draw(s_text);
    }
    for (auto& u_text : self_updating_texts) {
        u_text.first.setString(u_text.second.get_text());
        window.draw(u_text.first);
    }
    window.setView(current_view);
}