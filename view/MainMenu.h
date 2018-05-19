#ifndef TEEKO_MAINMENU_H
#define TEEKO_MAINMENU_H

#include <SFML/Graphics.hpp>
#include "../model/Game.h"
#include "GameRenderer.h"

class MainMenu {
private:
    sf::RenderWindow main_window_;
    const int kBorderX = 750;
    const int kBorderY = 750;
    sf::RectangleShape play_two_button_;
    sf::RectangleShape play_ai_button_;
    sf::RectangleShape exit_button_;

public:
    MainMenu();
    void Render();
    void DrawButtons();
    void HighlightButtonsController(int mouse_x, int mouse_y);
    void ClickController(int mouse_x, int mouse_y);
    void DrawTitle();
    void DrawBackground();
};


#endif //TEEKO_MAINMENU_H
