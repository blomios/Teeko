#include "MainMenu.h"

MainMenu::MainMenu() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    main_window_.create(sf::VideoMode(1200, 800), "Teeko", sf::Style::Default, settings);
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
            }
        }

        this->DrawButtons();
        // Display window
        main_window_.display();
    }
}

void MainMenu::DrawButtons() {
    int button_size_x = 400;
    int button_size_y = 50;
    sf::RectangleShape play_two_button(sf::Vector2f(button_size_x,button_size_y));
    int button_play_two_x = (main_window_.getSize().x-button_size_x)/2;
    int button_play_two_y = (main_window_.getSize().y-button_size_y)/2;
    play_two_button.setPosition(button_play_two_x, button_play_two_y);
    play_two_button.setFillColor(sf::Color(26, 188, 156));
    play_two_button.setOutlineThickness(10);
    play_two_button.setOutlineColor(sf::Color(22, 160, 133));
    main_window_.draw(play_two_button);

    sf::Font theboldfont;
    theboldfont.loadFromFile("..\\resources\\fonts\\theboldfont.ttf");
    sf::Text play_2_text("Play (2 players)", theboldfont);
    play_2_text.setCharacterSize(40);
    play_2_text.setOrigin(play_2_text.getGlobalBounds().width/2,play_2_text.getGlobalBounds().height/2);
    play_2_text.setPosition(play_two_button.getPosition().x+button_size_x/2,play_two_button.getPosition().y+button_size_y/2-10);
    main_window_.draw(play_2_text);
}