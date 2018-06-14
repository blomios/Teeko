#include "SpectatorMenu.h"

SpectatorMenu::SpectatorMenu(sf::RenderWindow *window) : AIMenu(window) {}

void SpectatorMenu::ClickController(int mouse_x, int mouse_y) {
    std::vector<sf::RectangleShape> buttons_vec{easy_button_, normal_button_, hard_button_};
    for (int i = 0; i < 3; i++) {
        if (mouse_x >= buttons_vec.at(i).getPosition().x &&
            mouse_x <= (buttons_vec.at(i).getPosition().x + buttons_vec.at(i).getSize().x) &&
            mouse_y >= buttons_vec.at(i).getPosition().y &&
            mouse_y <= (buttons_vec.at(i).getPosition().y + buttons_vec.at(i).getSize().y)) {
            switch (i) {
                case 0 : { // Easy mode
                    Game game(true, 0, true);
                    std::thread spectator(&Game::SpectatorLoop, &game);
                    GameRenderer game_renderer(&game, main_window_);
                    game_renderer.Render();
                    spectator.join();
                    break;
                }
                case 1 : { // Normal mode
                    Game game(true, 1, true);
                    std::thread spectator(&Game::SpectatorLoop, &game);
                    GameRenderer game_renderer(&game, main_window_);
                    game_renderer.Render();
                    spectator.join();
                    break;
                }
                case 2 : { // Hard mode
                    Game game(true, 2, true);
                    std::thread spectator(&Game::SpectatorLoop, &game);
                    GameRenderer game_renderer(&game, main_window_);
                    game_renderer.Render();
                    spectator.join();
                    break;
                }
            }
        }
    }
}
