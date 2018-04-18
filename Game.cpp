#include "Game.h"

void Game::Start() {
    main_window_.create(sf::VideoMode(1200, 800), "Teeko");
    Loop();
}

void Game::Loop() {
    sf::Event event;
    while (main_window_.isOpen())
    {
        while (main_window_.pollEvent(event))
        {
            // Close button
            if (event.type == sf::Event::Closed)
                main_window_.close();
            // Resizing, prevent bad scaling
            else if(event.type == sf::Event::Resized)
                main_window_.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }

        main_window_.clear(sf::Color(238,192,106)); // Set the background color

        // Draw the game board border
        int border_x = 750, border_y = 750;
        sf::RectangleShape border(sf::Vector2f(border_x,border_y));
        int border_position_x = (main_window_.getSize().x-border_x)/2;
        int border_position_y = (main_window_.getSize().y-border_y)/2;
        border.setPosition(border_position_x,border_position_y);
        border.setFillColor(sf::Color(0,0,0,0));
        border.setOutlineThickness(10);
        border.setOutlineColor(sf::Color(0,0,0));
        main_window_.draw(border);

        // Draw the spaces
        sf::CircleShape spaces[5][5];
        int x,y;
        for(int i = 0; i<5; i++) {
            for(int j = 0; j<5; j++) {
                spaces[i][j].setRadius(50);
                spaces[i][j].setFillColor(sf::Color::Transparent);
                spaces[i][j].setOutlineThickness(3);
                spaces[i][j].setOutlineColor(sf::Color(25, 25, 25));
                // Define spaces position
                int space_position_x = border_position_x + i * 150 + 25;
                int space_position_y = border_position_y + j * 150 + 25;
                // Set spaces position
                spaces[i][j].setPosition(space_position_x, space_position_y);
                main_window_.draw(spaces[i][j]);
                if (i < 4) {
                    // Render the link between this space and the next one
                    sf::RectangleShape link(sf::Vector2f(50, 5));
                    link.setPosition(space_position_x + 100, space_position_y + 50);
                    link.setFillColor(sf::Color::Black);
                    main_window_.draw(link);
                }
                if (j < 4) {
                    // Render the link between this space and the one below it
                    sf::RectangleShape link(sf::Vector2f(50, 5));
                    link.setFillColor(sf::Color::Black);
                    link.setPosition(space_position_x + 50, space_position_y + 100);
                    link.rotate(90);
                    main_window_.draw(link);
                }
                // Render the link between this space and the two diagonally
                if(i < 4 && j < 4) {
                    int link_position_x = space_position_x + 50 + 35;
                    int link_position_y = space_position_y + 50 + 35;
                    sf::RectangleShape link(sf::Vector2f(110, 5));
                    link.setFillColor(sf::Color::Black);
                    link.setPosition(link_position_x, link_position_y);
                    link.rotate(45);
                    main_window_.draw(link);
                }
                if(i > 0 && j < 4) {
                    int link_position_x = space_position_x + 50 - 35;
                    int link_position_y = space_position_y + 50 + 35;
                    sf::RectangleShape link(sf::Vector2f(110, 5));
                    link.setFillColor(sf::Color::Black);
                    link.setPosition(link_position_x, link_position_y);
                    link.rotate(135);
                    main_window_.draw(link);
                }
            }
        }

        // Render two markers
        // TODO(Piryus) Remove when not needed anymore
        sf::CircleShape red_marker(50);
        sf::CircleShape black_marker(50);
        red_marker.setFillColor(sf::Color::Red);
        black_marker.setFillColor(sf::Color::Black);
        red_marker.setPosition(border_position_x + 4 * 150 + 25, border_position_y + 3 * 150 + 25);
        black_marker.setPosition(border_position_x + 2 * 150 + 25, border_position_y + 0 * 150 + 25);
        main_window_.draw(red_marker);
        main_window_.draw(black_marker);
        main_window_.display();
    }
}