#include "AIMenu.h"

/**
 * Constructor for the AI Menu
 * Calls Render()
 * @param window, the window in which the menu will be rendered
 */
AIMenu::AIMenu(sf::RenderWindow *window) : Menu(window) {
    this->Render();
}

/**
 * Renders the elements of the menu : background, buttons, text, ...
 * Also contains the main loop managing the events
 */
void AIMenu::Render() {
    sf::Event event{};
    bool loop(true);
    while (main_window_->isOpen() && loop) {
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
                case sf::Event::MouseButtonReleased: { // On player's click
                    ClickController(sf::Mouse::getPosition(*main_window_).x,
                                    sf::Mouse::getPosition(*main_window_).y);
                    break;
                }
                case sf::Event::KeyPressed: {
                    if (event.key.code == sf::Keyboard::Escape) {
                        loop = false;
                    }
                }
            }
        }
        this->DrawBackground();
        this->DrawText();
        this->DrawButtons();
        main_window_->display();
    }
}

void AIMenu::DrawButtons() {
    int button_x = (main_window_->getSize().x - kButtonWidth) / 2;
    int button_y = (main_window_->getSize().y - kButtonHeight) / 2;

    // Create "Easy" button
    easy_button_ = CreateButton(button_x,button_y,sf::Color(230, 126, 34),sf::Color(211, 84, 0));
    main_window_->draw(easy_button_);

    // Create "Normal" button
    button_y = (main_window_->getSize().y - kButtonHeight) / 2 + kButtonHeight + 50;
    normal_button_ = CreateButton(button_x,button_y,sf::Color(230, 126, 34),sf::Color(211, 84, 0));
    main_window_->draw(normal_button_);

    // Create "Hard" button
    button_y = (main_window_->getSize().y - kButtonHeight) / 2 + kButtonHeight * 2 + 50 * 2;
    hard_button_ = CreateButton(button_x,button_y,sf::Color(230, 126, 34),sf::Color(211, 84, 0));
    main_window_->draw(hard_button_);

    // If mouse is on a button, change its color
    HighlightButtonsController(sf::Mouse::getPosition(*main_window_).x,
                               sf::Mouse::getPosition(*main_window_).y);

    // Draw button texts
    main_window_->draw(CreateButtonText(&easy_button_, "Easy"));
    main_window_->draw(CreateButtonText(&normal_button_, "Normal"));
    main_window_->draw(CreateButtonText(&hard_button_, "Hard"));
}

void AIMenu::HighlightButtonsController(int mouse_x, int mouse_y) {
    std::vector<sf::RectangleShape> buttons_vec{easy_button_, normal_button_, hard_button_};
    for (sf::RectangleShape button : buttons_vec) {
        if (mouse_x >= button.getPosition().x &&
            mouse_x <= (button.getPosition().x + button.getSize().x) &&
            mouse_y >= button.getPosition().y &&
            mouse_y <= (button.getPosition().y + button.getSize().y)) {
            button.setFillColor(sf::Color(39, 174, 96));
            main_window_->draw(button);
        }
    }
}

void AIMenu::ClickController(int mouse_x, int mouse_y) {
    std::vector<sf::RectangleShape> buttons_vec{easy_button_, normal_button_, hard_button_};
    for (int i = 0; i < 3; i++) {
        if (mouse_x >= buttons_vec.at(i).getPosition().x &&
            mouse_x <= (buttons_vec.at(i).getPosition().x + buttons_vec.at(i).getSize().x) &&
            mouse_y >= buttons_vec.at(i).getPosition().y &&
            mouse_y <= (buttons_vec.at(i).getPosition().y + buttons_vec.at(i).getSize().y)) {
            switch (i) {
                case 0 : { // Easy mode
                    Game game(true, 0);
                    GameRenderer game_renderer(&game, main_window_);
                    game_renderer.Render();
                    break;
                }
                case 1 : { // Normal mode
                    Game game(true, 1);
                    GameRenderer game_renderer(&game, main_window_);
                    game_renderer.Render();
                    break;
                }
                case 2 : { // Hard mode
                    Game game(true, 2);
                    GameRenderer game_renderer(&game, main_window_);
                    game_renderer.Render();
                    break;
                }
            }
        }
    }
}

void AIMenu::DrawText() {
    sf::Text difficulty_text("Select difficulty :", theboldfont);
    difficulty_text.setCharacterSize(100);
    difficulty_text.setOrigin(difficulty_text.getGlobalBounds().width / 2, difficulty_text.getGlobalBounds().height / 2);
    difficulty_text.setPosition(main_window_->getSize().x / 2, (main_window_->getSize().y-difficulty_text.getLocalBounds().height) / 5);
    main_window_->draw(difficulty_text);
}
