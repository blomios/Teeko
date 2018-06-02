#include "Menu.h"

/**
 * Constructor for a menu in an existing window
 * @param window, the existing window in which the menu will appear
 */
Menu::Menu(sf::RenderWindow *window) : main_window_(window) {
    // Load font for button text
    theboldfont.loadFromFile(R"(..\resources\fonts\theboldfont.ttf)");
}

/**
 * Default constructor
 * Creates a new window
 */
Menu::Menu() {
    main_window_ = new sf::RenderWindow;
    // Load font for button text
    theboldfont.loadFromFile(R"(..\resources\fonts\theboldfont.ttf)");
}

/**
 * Displays the menu's background
 */
void Menu::DrawBackground() {
    // This part loads the wood texture used in the background
    sf::Texture wood_texture;
    if (!wood_texture.loadFromFile(R"(..\resources\images\wood.jpg)")) {
        printf("Error while loading wood texture.\n");
    } else { // If the texture was loaded without error
        // Allow the texture to repeat itself
        wood_texture.setRepeated(true);
        // Creates a sprite of the size of the window and sets its texture to the previously wooden defined one
        sf::Sprite background_sprite;
        background_sprite.setTexture(wood_texture);
        background_sprite.setTextureRect(sf::IntRect(0, 0, main_window_->getSize().x, main_window_->getSize().y));
        main_window_->draw(background_sprite);
    }
}

/**
 * Creates a menu button
 * The button is then returned and is NOT displayed by this function
 * @param x, position on the x axis
 * @param y, position on the y axis
 * @param color, button's color
 * @param outline_color,
 * @return the button
 */
sf::RectangleShape Menu::CreateButton(int x, int y, sf::Color color, sf::Color outline_color) {
    // Creates a rectangle of the size defined by the class constants
    sf::RectangleShape button = sf::RectangleShape(sf::Vector2f(kButtonWidth, kButtonHeight));
    button.setPosition(x, y);
    button.setFillColor(color);
    button.setOutlineThickness(10);
    button.setOutlineColor(outline_color);
    return button;
}

/**
 * Creates the text for a button
 * The passed button is used to get its coordinates for the text
 * A little trick is used to place the text exactly at the middle of the button :
 * Once the text is created, it is in fact a rectangle
 * We then set the axis' origin to the center of that rectangle so it is easier to place at the middle of the button
 * @param button, the button
 * @param text, a string containing the button text
 * @return the button text, a sf::Text
 */
sf::Text Menu::CreateButtonText(sf::RectangleShape *button, std::string text) {
    sf::Text button_text(text, theboldfont);
    button_text.setCharacterSize(40);
    // Sets the axis' origin to the middle of the text rectangle
    button_text.setOrigin(button_text.getGlobalBounds().width / 2, button_text.getGlobalBounds().height / 2);
    // Places the text at the middle of the button, -10 on the y axis is used to correct a little shift caused by the font
    button_text.setPosition(button->getPosition().x + kButtonWidth / 2,
                     button->getPosition().y + kButtonHeight / 2 - 10);
    return button_text;
}
