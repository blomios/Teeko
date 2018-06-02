#include "MainMenu.h"

MainMenu::MainMenu() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    main_window_->create(sf::VideoMode(1200, 800), "Teeko", sf::Style::Default, settings);
    sf::Image icon;
    icon.loadFromFile("..\\resources\\images\\icon.png");
    main_window_->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void MainMenu::Render() {
    sf::Event event;
    while (main_window_->isOpen()) {
        while (main_window_->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {  // Close button
                    main_window_->close();
                    break;
                }
                case sf::Event::Resized: {  // Occur when window is resized
                    main_window_->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    break;
                }
                case sf::Event::MouseButtonReleased: { // On player's click
                    ClickController(sf::Mouse::getPosition(*main_window_).x,
                                    sf::Mouse::getPosition(*main_window_).y);
                    break;
                }
            }
        }

        this->DrawBackground();
        this->DrawTitle();
        this->DrawButtons();
        // Display window
        main_window_->display();
    }
}

void MainMenu::DrawTitle() {
    sf::Texture teeko_img;
    teeko_img.loadFromFile("..\\resources\\images\\teeko.png");
    sf::Sprite teeko;
    teeko.setTexture(teeko_img);
    teeko.setPosition((main_window_->getSize().x-teeko.getLocalBounds().width)/2,(main_window_->getSize().y-teeko.getLocalBounds().height)/12);
    main_window_->draw(teeko);
}

void MainMenu::DrawButtons() { //TODO(Piryus) Refactor this (soon)
    // Buttons position
    int button_x = (main_window_->getSize().x - kButtonWidth) / 2;
    int button_y = (main_window_->getSize().y - kButtonHeight) / 2;

    // Create play button
    play_two_button_ = CreateButton(button_x,button_y,sf::Color(230, 126, 34),sf::Color(211, 84, 0));
    main_window_->draw(play_two_button_);

    // Create "Play against AI" button
    button_y = (main_window_->getSize().y - kButtonHeight) / 2 + kButtonHeight + 50;
    play_ai_button_ = CreateButton(button_x,button_y,sf::Color(230, 126, 34),sf::Color(211, 84, 0));
    main_window_->draw(play_ai_button_);

    // Create "Exit" button
    button_y = (main_window_->getSize().y - kButtonHeight) / 2 + kButtonHeight * 2 + 50 * 2;
    exit_button_ = CreateButton(button_x,button_y,sf::Color(230, 126, 34),sf::Color(211, 84, 0));
    main_window_->draw(exit_button_);

    // If mouse is on a button, change its color
    HighlightButtonsController(sf::Mouse::getPosition(*main_window_).x,
                               sf::Mouse::getPosition(*main_window_).y);

    // Draw button texts
    main_window_->draw(CreateButtonText(&play_two_button_, "Play (2 players)"));
    main_window_->draw(CreateButtonText(&play_ai_button_, "Play against A.I."));
    main_window_->draw(CreateButtonText(&exit_button_, "Exit game"));
}

void MainMenu::HighlightButtonsController(int mouse_x, int mouse_y) {
    std::vector<sf::RectangleShape> buttons_vec{play_two_button_, play_ai_button_, exit_button_};
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

void MainMenu::ClickController(int mouse_x, int mouse_y) {
    std::vector<sf::RectangleShape> buttons_vec{play_two_button_, play_ai_button_, exit_button_};
    for (int i = 0; i < 3; i++) {
        if (mouse_x >= buttons_vec.at(i).getPosition().x &&
            mouse_x <= (buttons_vec.at(i).getPosition().x + buttons_vec.at(i).getSize().x) &&
            mouse_y >= buttons_vec.at(i).getPosition().y &&
            mouse_y <= (buttons_vec.at(i).getPosition().y + buttons_vec.at(i).getSize().y)) {
            switch (i) {
                case 0 : { // Two players button
                    Game game(false);
                    GameRenderer game_renderer(&game, main_window_);
                    game_renderer.Render();
                    break;
                }
                case 1 : { // AI button
                    AIMenu ai_menu(main_window_);
                    break;
                }
                case 2 : { // Exit
                    main_window_->close();
                    break;
                }
            }
        }
    }
}
