#include "MainMenu.h"
#include "../model/Game.h"
#include "GameRenderer.h"

MainMenu::MainMenu() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    main_window_.create(sf::VideoMode(1200, 800), "Teeko", sf::Style::Default, settings);
    sf::Image icon;
    icon.loadFromFile("..\\resources\\images\\icon.png");
    main_window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void MainMenu::Render() {
    sf::Event event;
    while (main_window_.isOpen()) {
        while (main_window_.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {  // Close button
                    main_window_.close();
                    break;
                }
                case sf::Event::Resized: {  // Occur when window is resized
                    main_window_.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    break;
                }
                case sf::Event::MouseButtonReleased: { // On player's click
                    ClickController(sf::Mouse::getPosition(main_window_).x,
                                    sf::Mouse::getPosition(main_window_).y);
                    break;
                }
            }
        }

        this->DrawButtons();
        // Display window
        main_window_.display();
    }
}

void MainMenu::DrawButtons() { //TODO(Piryus) Refactor this (soon)
    // Buttons size
    int button_size_x = 400;
    int button_size_y = 50;

    // Create "2 players" button
    play_two_button = sf::RectangleShape(sf::Vector2f(button_size_x, button_size_y));
    int button_play_two_x = (main_window_.getSize().x - button_size_x) / 2;
    int button_play_two_y = (main_window_.getSize().y - button_size_y) / 2;
    play_two_button.setPosition(button_play_two_x, button_play_two_y);
    play_two_button.setFillColor(sf::Color(230, 126, 34));
    play_two_button.setOutlineThickness(10);
    play_two_button.setOutlineColor(sf::Color(211, 84, 0));
    main_window_.draw(play_two_button);

    // Create "Play against AI" button
    play_ai_button = sf::RectangleShape(sf::Vector2f(button_size_x, button_size_y));
    int button_ai_x = (main_window_.getSize().x - button_size_x) / 2;
    int button_ai_y = (main_window_.getSize().y - button_size_y) / 2 + button_size_y + 50;
    play_ai_button.setPosition(button_ai_x, button_ai_y);
    play_ai_button.setFillColor(sf::Color(230, 126, 34));
    play_ai_button.setOutlineThickness(10);
    play_ai_button.setOutlineColor(sf::Color(211, 84, 0));
    main_window_.draw(play_ai_button);

    // Create "Exit" button
    exit_button = sf::RectangleShape(sf::Vector2f(button_size_x, button_size_y));
    int exit_button_x = (main_window_.getSize().x - button_size_x) / 2;
    int exit_button_y = (main_window_.getSize().y - button_size_y) / 2 + button_size_y * 2 + 50 * 2;
    exit_button.setPosition(exit_button_x, exit_button_y);
    exit_button.setFillColor(sf::Color(230, 126, 34));
    exit_button.setOutlineThickness(10);
    exit_button.setOutlineColor(sf::Color(211, 84, 0));
    main_window_.draw(exit_button);

    // If mouse is on a button, change its color
    HighlightButtonsController(sf::Mouse::getPosition(main_window_).x,
                               sf::Mouse::getPosition(main_window_).y);

    // Load font for button text
    sf::Font theboldfont;
    theboldfont.loadFromFile("..\\resources\\fonts\\theboldfont.ttf");

    // Draw text for the 2 players button
    sf::Text play_2_text("Play (2 players)", theboldfont);
    play_2_text.setCharacterSize(40);
    play_2_text.setOrigin(play_2_text.getGlobalBounds().width / 2, play_2_text.getGlobalBounds().height / 2);
    play_2_text.setPosition(play_two_button.getPosition().x + button_size_x / 2,
                            play_two_button.getPosition().y + button_size_y / 2 - 10);
    main_window_.draw(play_2_text);

    // Draw text for the AI button
    sf::Text play_ai_text("Play against A.I.", theboldfont);
    play_ai_text.setCharacterSize(40);
    play_ai_text.setOrigin(play_ai_text.getGlobalBounds().width / 2, play_ai_text.getGlobalBounds().height / 2);
    play_ai_text.setPosition(play_ai_button.getPosition().x + button_size_x / 2,
                             play_ai_button.getPosition().y + button_size_y / 2 - 10);
    main_window_.draw(play_ai_text);

    // Draw text for the exit button
    sf::Text exit_text("Exit game", theboldfont);
    exit_text.setCharacterSize(40);
    exit_text.setOrigin(exit_text.getGlobalBounds().width / 2, exit_text.getGlobalBounds().height / 2);
    exit_text.setPosition(exit_button.getPosition().x + button_size_x / 2,
                          exit_button.getPosition().y + button_size_y / 2 - 10);
    main_window_.draw(exit_text);
}

void MainMenu::HighlightButtonsController(int mouse_x, int mouse_y) {
    std::vector<sf::RectangleShape> buttons_vec{play_two_button, play_ai_button, exit_button};
    for (sf::RectangleShape button : buttons_vec) {
        if (mouse_x >= button.getPosition().x &&
            mouse_x <= (button.getPosition().x + button.getSize().x) &&
            mouse_y >= button.getPosition().y &&
            mouse_y <= (button.getPosition().y + button.getSize().y)) {
            button.setFillColor(sf::Color(39, 174, 96));
            main_window_.draw(button);
        }
    }
}

void MainMenu::ClickController(int mouse_x, int mouse_y) {
    std::vector<sf::RectangleShape> buttons_vec{play_two_button, play_ai_button, exit_button};
    for (int i = 0; i < 3; i++) {
        if (mouse_x >= buttons_vec.at(i).getPosition().x &&
            mouse_x <= (buttons_vec.at(i).getPosition().x + buttons_vec.at(i).getSize().x) &&
            mouse_y >= buttons_vec.at(i).getPosition().y &&
            mouse_y <= (buttons_vec.at(i).getPosition().y + buttons_vec.at(i).getSize().y)) {
            switch (i) {
                case 0 : { // Two players button
                    main_window_.close();
                    Game game;
                    game.Start();
                    GameRenderer game_renderer(&game);
                    game_renderer.Render();
                    break;
                }
                case 1 : { // AI button
                    break;
                }
                case 2 : { // Exit
                    main_window_.close();
                    break;
                }
            }
        }
    }
}
