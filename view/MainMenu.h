#ifndef TEEKO_MAINMENU_H
#define TEEKO_MAINMENU_H

#include <SFML/Graphics.hpp>

class MainMenu {
private:
    sf::RenderWindow main_window_;
    const int kBorderX = 750;
    const int kBorderY = 750;
    sf::RectangleShape play_two_button;
    sf::RectangleShape play_ai_button;
    sf::RectangleShape exit_button;

public:
    MainMenu();
    void Render();
    void DrawButtons();
    void HighlightButtonsController(int mouse_x, int mouse_y);
    void ClickController(int mouse_x, int mouse_y);
};


#endif //TEEKO_MAINMENU_H
