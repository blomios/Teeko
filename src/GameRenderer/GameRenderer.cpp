#include "GameRenderer.h"

/**
 * Basic constructor for a GameRenderer
 * @param game, the game to render
 * @param window, the window in which the game will be rendered
 */
GameRenderer::GameRenderer(Game *game, sf::RenderWindow *window) {
    this->game_ = game;
    this->main_window_ = window;
}

/**
 * Renders every game elements
 * Contains the main graphic loop managing events including clicks
 */
void GameRenderer::Render() {
    sf::Event event{};
    bool exit_game(false);
    // Loop managing events
    while (main_window_->isOpen() && !exit_game) {
        while (main_window_->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {  // Close button
                    main_window_->close();
                    break;
                }
                case sf::Event::Resized: {  // Occurs when window is resized
                    main_window_->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    break;
                }
                case sf::Event::MouseButtonReleased: { // On clicks
                    // Checks if it it a left click
                    // If there is a winner, blocks every clicks, we don't want players to be playing when a game is already won !
                    if (event.mouseButton.button == sf::Mouse::Left && game_->GetWinner() == nullptr &&
                        !game_->IsSpectatorGame()) {
                        // Passes the mouse position (relative to window) to the click controller
                        ClickController(sf::Mouse::getPosition(*main_window_).x,
                                        sf::Mouse::getPosition(*main_window_).y);
                    }
                    break;
                }
                case sf::Event::KeyPressed: { // On "Esc" pressed
                    if (event.key.code == sf::Keyboard::Escape) {
                        exit_game = true;
                    }
                }
            }
        }

        // Draws game elements
        this->DrawBackground();
        this->DrawBoard();
        this->DrawSpaces();
        this->DrawMarkers();
        this->DrawTurnLabel();
        if (game_->GetWinner() != nullptr)
            this->DrawWinnerMessage();

        // Displays the window with the game elements
        main_window_->display();
    }
}

/**
 * Renders the board, which is only a brownish square with an outline
 */
void GameRenderer::DrawBoard() {
    // Creates the square used as a board
    sf::RectangleShape board(sf::Vector2f(kBoardX, kBoardY));
    // Centers it in the window
    int board_position_x = (main_window_->getSize().x - kBoardX) / 2;
    int board_position_y = (main_window_->getSize().y - kBoardY) / 2;
    board.setPosition(board_position_x, board_position_y);
    // Brownish fill color
    board.setFillColor(sf::Color(210, 105, 30));
    board.setOutlineColor(sf::Color::Black);
    board.setOutlineThickness(10);
    main_window_->draw(board);

}

/**
 * Renders the spaces on the board and the links between them
 */
void GameRenderer::DrawSpaces() {
    // The 25 spaces of the board, organized in a 5*5 array
    sf::CircleShape spaces[5][5];
    // The first space is positioned 25px away from the border of the board
    int space_position_x = (main_window_->getSize().x - kBoardX) / 2 + 25;
    // Spaces are rendered one by one, column by column
    for (int i = 0; i < 5; i++) {
        int space_position_y = (main_window_->getSize().y - kBoardY) / 2 + 25;
        for (int j = 0; j < 5; j++) {
            spaces[i][j].setRadius(50);
            spaces[i][j].setFillColor(sf::Color(255, 178, 71)); // Light orange
            spaces[i][j].setOutlineThickness(4);
            spaces[i][j].setOutlineColor(sf::Color::Black);
            // Set spaces position
            spaces[i][j].setPosition(space_position_x, space_position_y);
            main_window_->draw(spaces[i][j]);
            if (i < 4) { // Render the link between this space and the next one
                sf::RectangleShape link(sf::Vector2f(50, 5));
                link.setPosition(space_position_x + 100, space_position_y + 50);
                link.setFillColor(sf::Color::Black);
                main_window_->draw(link);
            }
            if (j < 4) { // Render the link between this space and the one below it
                sf::RectangleShape link(sf::Vector2f(50, 5));
                link.setFillColor(sf::Color::Black);
                link.setPosition(space_position_x + 50, space_position_y + 100);
                link.rotate(90);
                main_window_->draw(link);
            }
            if (i < 4 && j < 4) { // Render the link between this space and the one on the right diagonal
                int link_position_x = space_position_x + 50 + 35;
                int link_position_y = space_position_y + 50 + 35;
                sf::RectangleShape link(sf::Vector2f(110, 5));
                link.setFillColor(sf::Color::Black);
                link.setPosition(link_position_x, link_position_y);
                link.rotate(45);
                main_window_->draw(link);
            }
            if (i > 0 && j < 4) { // Render the link between this space and the one on the left diagonal
                int link_position_x = space_position_x + 50 - 35;
                int link_position_y = space_position_y + 50 + 35;
                sf::RectangleShape link(sf::Vector2f(110, 5));
                link.setFillColor(sf::Color::Black);
                link.setPosition(link_position_x, link_position_y);
                link.rotate(135);
                main_window_->draw(link);
            }
            space_position_y += 150;
        }
        space_position_x += 150;
    }
}

/**
 * Renders markers on the board
 */
void GameRenderer::DrawMarkers() {
    // This loop scans each player's spaces vector
    for (auto &player : *game_->GetPlayers()) {
        for (Space *space : *player->GetSpaces()) {
            sf::CircleShape marker(43);
            // If marker is selected, it adds a blue outline
            if (space->GetMarker()->IsSelected()) {
                marker.setOutlineThickness(-10);
                marker.setOutlineColor(sf::Color(0, 100, 255)); // Blueish
            }
            if (player->GetColor() == "Red")
                marker.setFillColor(sf::Color(216, 0, 0)); // Red
            else if (player->GetColor() == "Black")
                marker.setFillColor(sf::Color::Black);
            // Center the marker in its space
            marker.setPosition(GetCoordX(space->GetSpaceId()) + (50 - marker.getRadius()),
                               GetCoordY(space->GetSpaceId()) + (50 - marker.getRadius()));
            main_window_->draw(marker);
        }
    }
}

/**
 * Renders the turn indicator in the top left corner of the window
 * It also renders the color of the player whose turn it is
 */
void GameRenderer::DrawTurnLabel() {
    // Loads the font
    sf::Font junegull;
    junegull.loadFromFile(R"(..\resources\fonts\junegull.ttf)");

    // Displays turn number
    sf::Text turn_text("Turn : " + std::to_string(game_->GetTurnNumber()), junegull);
    turn_text.setCharacterSize(40);
    turn_text.setPosition(20, 10);
    main_window_->draw(turn_text);

    // Displays player color
    string player_turn;
    if (game_->GetPlayerTurn() == 0)
        player_turn = "RED";
    else player_turn = "BLACK";
    sf::Text player_turn_text(player_turn, junegull);
    if (game_->GetPlayerTurn() == 0)
        player_turn_text.setFillColor(sf::Color::Red);
    else player_turn_text.setFillColor(sf::Color::Black);
    player_turn_text.setCharacterSize(40);
    player_turn_text.setPosition(20, 50);
    main_window_->draw(player_turn_text);
}

/**
 * Displays the menu's background
 */
void GameRenderer::DrawBackground() {
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
 * Gets X coordinate of a space
 * Useful to place markers for example
 * Example :
 * Here is our board :
 * |_|_|_|_|_|
 * |_|_|_|_|_|
 * |_|_|_|X|_|
 * |_|_|_|_|_|
 * |_|_|_|_|_|
 * 14 is X's id
 * GetCoord(X) returns 600 if the window's width is 1000px
 * @param space_id
 * @return Space position on X axis (int)
 */
int GameRenderer::GetCoordX(int space_id) {
    int x = (space_id - 1) % 5;
    return (main_window_->getSize().x - kBoardX) / 2 + 25 + x * 150;
}

/**
 * Gets Y coordinate of a space
 * Useful to place markers for example
 * Example :
 * Here is our board :
 * |_|_|_|_|_|
 * |_|_|_|_|_|
 * |_|_|_|X|_|
 * |_|_|_|_|_|
 * |_|_|_|_|_|
 * 14 is X's id
 * GetCoord(X) returns 600 if the window's width is 1000px
 * @param space_id
 * @return Space position on Y axis (int)
 */
int GameRenderer::GetCoordY(int space_id) {
    int y = (space_id - 1) / 5;
    return (main_window_->getSize().y - kBoardY) / 2 + y * 150 + 25;
}

/**
 * Manages clicks in the game
 * The function allows the player to place a marker, select one and move it
 * One important thing to remember when trying to understand how this function works is that the player can click on
 * a space or on the marker of the space. Here, it doesn't really make a difference and instead of checking if he clicked
 * on a marker, we check if the space he clicked on has a marker on it. It leads to the possibility of selecting a marker
 * when clicking between the space's border and the marker (about 10px).
 * @param mouse_x, mouse position on the X axis
 * @param mouse_y, mouse position on the Y axis
 */
void GameRenderer::ClickController(int mouse_x, int mouse_y) {
    // Gets the space vector of the game
    vector<Space> *spaces = game_->GetSpaces();
    // Gets the player whose turn it is
    int player_turn = game_->GetPlayerTurn();

    // Space with the marker selected by player, for now : none
    Space *selected_space = nullptr;
    // If there is already a selected space, retrieves it
    for (Space &space : *spaces) {
        if (space.GetMarker() != nullptr && space.GetMarker()->IsSelected())
            selected_space = &space;
    }

    // If the player clicked on a space, gets its ID else clicked_space_id = -1
    int clicked_space_id = GetClickedSpaceID(mouse_x, mouse_y);

    // If no space is selected and if the player clicked on a space and if it's not an AI game or if it's Black's turn
    if (selected_space == nullptr &&
        clicked_space_id != -1 && (!game_->IsAIGame() || player_turn == 1)) {

        // If the player clicked on a space with marker and if this marker's color is the same as the player's
        if (spaces->at(clicked_space_id - 1).GetMarker() != nullptr &&
            (spaces->at(clicked_space_id - 1).GetMarker()->GetColor() ==
             game_->GetPlayers()->at(player_turn)->GetColor())) {
            // Selects the marker the player clicked on (or the marker of the space the player clicked on)
            spaces->at(clicked_space_id - 1).GetMarker()->Select();
        }
            // If he clicked on an empty space, then try to place a marker on this space. PlaceMarker will whether the player is
            // authorized to place a marker or not (e.g. if he already has 4 markers placed on the board)
        else game_->PlaceMarker(spaces->at(clicked_space_id - 1), player_turn);

    } else if (selected_space != nullptr &&
               clicked_space_id == -1) { // If the player clicked out of a space and if a space is selected
        // Unselects the space
        selected_space->GetMarker()->Unselect();

    }
    // If the player clicked on a valid space and if there is already a selected marker
    else if (selected_space != nullptr && clicked_space_id != -1) {
        // If the player clicked on one of his marker
        if (spaces->at(clicked_space_id - 1).GetMarker() != nullptr &&
            (spaces->at(clicked_space_id - 1).GetMarker()->GetColor() ==
             game_->GetPlayers()->at(game_->GetPlayerTurn())->GetColor())) {
            // Unselects the selected marker
            selected_space->GetMarker()->Unselect();
            // Selects the other marker
            spaces->at(clicked_space_id - 1).GetMarker()->Select();
        } else { // If there is a selected marker and he clicked on an empty space, try to move the marker on this space
            selected_space->GetMarker()->Unselect();
            game_->MoveMarker(spaces->at(selected_space->GetSpaceId() - 1), spaces->at(clicked_space_id - 1),
                              player_turn);
        }
    }
}

/**
 * Returns the space ID based on coordinates
 * If there is no space at these coordinates, returns -1
 * @param x, X-coordinate of the mouse
 * @param y, Y-coordinate of the mouse
 * @return the clicked space's ID, if none, returns -1
 */
int GameRenderer::GetClickedSpaceID(int x, int y) {
    // We assume there is no space at these coordinates
    int space_id = -1;
    // Checks whether the coordinates match a space position or not
    for (int i = 0; i < 25; i++) {
        if ((x >= GetCoordX(i + 1) && x <= GetCoordX(i + 1) + 100) &&
            (y >= GetCoordY(i + 1) && y <= GetCoordY(i + 1) + 100)) {
            // Spaces' IDs range is 1->25
            space_id = i + 1;
        }
    }
    return space_id;
}

/**
 * Renders the winner message
 */
void GameRenderer::DrawWinnerMessage() {
    // Plays victory music
    game_->GetSoundManager()->PlayVictoryMusic();

    // Hides the game with black mask
    sf::RectangleShape black_mask(sf::Vector2f(main_window_->getSize().x, main_window_->getSize().y));
    black_mask.setFillColor(sf::Color(0, 0, 0, 150)); // Transparent black
    main_window_->draw(black_mask);

    // Loads the font
    sf::Font junegull;
    junegull.loadFromFile(R"(..\resources\fonts\junegull.ttf)");

    // Displays the winner
    sf::Text winner(game_->GetWinner()->GetColor() + " wins!", junegull);
    winner.setCharacterSize(70);
    winner.setOrigin(winner.getGlobalBounds().width / 2, winner.getGlobalBounds().height / 2);
    winner.setPosition(main_window_->getSize().x / 2,
                       main_window_->getSize().y / 2);
    main_window_->draw(winner);
}
