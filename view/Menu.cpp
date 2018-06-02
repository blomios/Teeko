#include "Menu.h"

Menu::Menu(sf::RenderWindow *main_window_) : main_window_(main_window_) {
    // Load font for button text
    theboldfont.loadFromFile("..\\resources\\fonts\\theboldfont.ttf");
}

Menu::Menu() {
    main_window_ = new sf::RenderWindow;
    // Load font for button text
    theboldfont.loadFromFile("..\\resources\\fonts\\theboldfont.ttf");
}

void Menu::DrawBackground() {
    sf::Texture wood_texture;
    if (!wood_texture.loadFromFile("..\\resources\\images\\wood.jpg")) {
        printf("Error while loading wood texture.\n");
    } else {
        wood_texture.setRepeated(true);
        sf::Sprite background_sprite;
        background_sprite.setTexture(wood_texture);
        background_sprite.setTextureRect(sf::IntRect(0, 0, main_window_->getSize().x, main_window_->getSize().y));
        main_window_->draw(background_sprite);
    }
}

sf::RectangleShape Menu::CreateButton(int x, int y, sf::Color color, sf::Color outline_color) {
    // Create button
    sf::RectangleShape button = sf::RectangleShape(sf::Vector2f(kButtonWidth, kButtonHeight));
    button.setPosition(x, y);
    button.setFillColor(color);
    button.setOutlineThickness(10);
    button.setOutlineColor(outline_color);

    return button;
}

sf::Text Menu::CreateButtonText(sf::RectangleShape *button, std::string text) {
    // Draw the button text
    sf::Text button_text(text, theboldfont);
    button_text.setCharacterSize(40);
    button_text.setOrigin(button_text.getGlobalBounds().width / 2, button_text.getGlobalBounds().height / 2);
    button_text.setPosition(button->getPosition().x + kButtonWidth / 2,
                     button->getPosition().y + kButtonHeight / 2 - 10);

    return button_text;
}
