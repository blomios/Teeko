#include "GameRenderer.h"


GameRenderer::GameRenderer(Game *game) {
    this->game_ = game;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // TODO(Piryus) : Check whether this is auto-detectable, avoid weird graphics
    main_window_.create(sf::VideoMode(1200, 800), "Teeko", sf::Style::Default, settings);
}

void GameRenderer::Render() {
    sf::Event event;
    while (main_window_.isOpen()) {
        // TODO(Piryus) Events function
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
                case sf::Event::MouseButtonReleased: {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        ClickController(sf::Mouse::getPosition(main_window_).x, sf::Mouse::getPosition(main_window_).y);
                    }
                    break;
                }
            }
        }

        this->DrawBackground();
        this->DrawBoard();
        this->DrawSpaces();
        this->DrawMarkers();
        this->DrawTurnLabel();

        // Display window
        main_window_.display();
    }
}

void GameRenderer::DrawBoard() {
    sf::RectangleShape border(sf::Vector2f(kBorderX, kBorderY));
    int border_position_x = (main_window_.getSize().x - kBorderX) / 2;
    int border_position_y = (main_window_.getSize().y - kBorderY) / 2;
    border.setPosition(border_position_x, border_position_y);
    border.setFillColor(sf::Color(210, 105, 30));
    border.setOutlineThickness(10);
    border.setOutlineColor(sf::Color(0, 0, 0));
    main_window_.draw(border);

}

void GameRenderer::DrawSpaces() {
    sf::CircleShape spaces[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            spaces[i][j].setRadius(50);
            spaces[i][j].setFillColor(sf::Color(255, 178, 71));
            spaces[i][j].setOutlineThickness(4);
            spaces[i][j].setOutlineColor(sf::Color::Black);
            // Define spaces position
            int space_position_x = (main_window_.getSize().x - kBorderX) / 2 + i * 150 + 25;
            int space_position_y = (main_window_.getSize().y - kBorderY) / 2 + j * 150 + 25;
            // Set spaces position
            spaces[i][j].setPosition(space_position_x, space_position_y);
            main_window_.draw(spaces[i][j]);
            if (i < 4) { // Render the link between this space and the next one
                sf::RectangleShape link(sf::Vector2f(50, 5));
                link.setPosition(space_position_x + 100, space_position_y + 50);
                link.setFillColor(sf::Color::Black);
                main_window_.draw(link);
            }
            if (j < 4) { // Render the link between this space and the one below it
                sf::RectangleShape link(sf::Vector2f(50, 5));
                link.setFillColor(sf::Color::Black);
                link.setPosition(space_position_x + 50, space_position_y + 100);
                link.rotate(90);
                main_window_.draw(link);
            }
            if (i < 4 && j < 4) { // Render the link between this space and the one on the right diagonal
                int link_position_x = space_position_x + 50 + 35;
                int link_position_y = space_position_y + 50 + 35;
                sf::RectangleShape link(sf::Vector2f(110, 5));
                link.setFillColor(sf::Color::Black);
                link.setPosition(link_position_x, link_position_y);
                link.rotate(45);
                main_window_.draw(link);
            }
            if (i > 0 && j < 4) { // Render the link between this space and the one on the left diagonal
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
}

void GameRenderer::DrawMarkers() {
    // TODO(Piryus) Draw markers from the board
    for (auto &player : *game_->getPlayers()) {
        vector<Space *> *player_spaces = player.getSpaces();
        for (int j = 0; j < player_spaces->size(); j++) {
            sf::CircleShape marker(43);
            if (player.getSpaces()->at(j)->getMarker()->IsSelected()) {
                marker.setOutlineThickness(-10);
                marker.setOutlineColor(sf::Color(0, 100, 255));
            }
            if (player.getColor() == "Red")
                marker.setFillColor(sf::Color(216, 0, 0));
            else if (player.getColor() == "Black")
                marker.setFillColor(sf::Color::Black);
            marker.setPosition(GetCoordX(player_spaces->at(j)->getSpace_id()) + (50 - marker.getRadius()),
                               GetCoordY(player_spaces->at(j)->getSpace_id()) + (50 - marker.getRadius()));
            main_window_.draw(marker);
        }
    }

    // TODO Draw selected marker (if there is one)
}

void GameRenderer::DrawTurnLabel() {
    sf::Font junegull;
    junegull.loadFromFile("..\\resources\\fonts\\junegull.ttf");

    // Display turn number
    sf::Text turn_text("Turn : " + std::to_string(game_->GetTurnNumber()), junegull);
    turn_text.setCharacterSize(40);
    turn_text.setPosition(20, 10);
    main_window_.draw(turn_text);

    // Display player color
    string player_turn;
    if (game_->GetPlayerTurn() == 0)
        player_turn = "BLACK";
    else player_turn = "RED";
    sf::Text player_turn_text(player_turn, junegull);
    if (game_->GetPlayerTurn() == 0)
        player_turn_text.setFillColor(sf::Color::Black);
    else player_turn_text.setFillColor(sf::Color::Red);
    player_turn_text.setCharacterSize(40);
    player_turn_text.setPosition(20, 50);
    main_window_.draw(player_turn_text);
}

void GameRenderer::DrawBackground() {
    sf::Texture wood_texture;
    if (!wood_texture.loadFromFile("..\\resources\\images\\wood.jpg")) {
        printf("Error while loading wood texture.\n");
    } else {
        wood_texture.setRepeated(true);
        sf::Sprite background_sprite;
        background_sprite.setTexture(wood_texture);
        background_sprite.setTextureRect(sf::IntRect(0, 0, main_window_.getSize().x, main_window_.getSize().y));
        main_window_.draw(background_sprite);
    }
}

int GameRenderer::GetCoordX(int space_id) {
    int x = space_id % 5;
    if (x == 0) {
        x = 4;
    } else
        x--;
    return (main_window_.getSize().x - 750) / 2 + x * 150 + 25;
}

int GameRenderer::GetCoordY(int space_id) {
    int y = space_id / 5;
    if (space_id % 5 == 0) {
        y = space_id / 5 - 1;
    }
    return (main_window_.getSize().y - 750) / 2 + y * 150 + 25;
}

void GameRenderer::ClickController(int mouse_x, int mouse_y) {
    vector<Space> *spaces = game_->GetSpaces();
    int turn_number = game_->GetTurnNumber();
    int player_turn = game_->GetPlayerTurn();
    Space *selected_space = nullptr;
    int clicked_space_id = GetClickedSpaceID(mouse_x, mouse_y);

    for (int j = 0; j < spaces->size(); j++) {
        if (spaces->at(j).getMarker() != nullptr && spaces->at(j).getMarker()->IsSelected())
            selected_space = &spaces->at(j);
    }

    if (selected_space == nullptr && clicked_space_id != -1) { // If the player clicks on a space and if no space is selected
        // If the player clicks on a marker
        if (spaces->at(clicked_space_id-1).getMarker() != nullptr)
            spaces->at(clicked_space_id-1).getMarker()->Select();
        // If he clicks on an empty space
        else game_->placeMarker(spaces->at(clicked_space_id-1), player_turn);
    } else if (selected_space != nullptr && clicked_space_id == -1) { // If the player clicks out of a space and if a space is selected
        // Unselect the space
        selected_space->getMarker()->Unselect();
        selected_space = nullptr;
    } else if (selected_space != nullptr && clicked_space_id != -1) { // If the player clicks on a valid space and if there is a selected marker
        // Unselect the selected space
        selected_space->getMarker()->Unselect();
        selected_space = nullptr;
        // If the player clicked on a marker
        if (spaces->at(clicked_space_id-1).getMarker() != nullptr)
            spaces->at(clicked_space_id-1).getMarker()->Select();
        else {
            game_->moveMarker(spaces->at(selected_space->getSpace_id()-1), spaces->at(clicked_space_id-1), player_turn);
        }
    }
}

int GameRenderer::GetClickedSpaceID(int x, int y) {
    int space_id = -1;
    for (int i = 0; i < 25; i++) {
        if ((x >= GetCoordX(i + 1) && x <= GetCoordX(i + 1) + 100) &&
            (y >= GetCoordY(i + 1) && y <= GetCoordY(i + 1) + 100)) {
            space_id = i+1;
        }
    }
    return space_id;
}