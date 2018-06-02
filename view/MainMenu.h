#ifndef TEEKO_MAINMENU_H
#define TEEKO_MAINMENU_H

#include "AIMenu.h"

class MainMenu : public Menu {
private:
    const int kBorderX = 750;
    const int kBorderY = 750;
    sf::RectangleShape play_two_button_;
    sf::RectangleShape play_ai_button_;
    sf::RectangleShape exit_button_;
public:
    MainMenu();
    void Render() override;
    void DrawButtons() override;
    void HighlightButtonsController(int mouse_x, int mouse_y) override;
    void ClickController(int mouse_x, int mouse_y) override;
    void DrawTitle();
};


#endif //TEEKO_MAINMENU_H
