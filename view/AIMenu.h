#ifndef TEEKO_AIMENU_H
#define TEEKO_AIMENU_H

#include "Menu.h"

class AIMenu : public Menu {
public:
    AIMenu(sf::RenderWindow* window);
    void Render() override;
    void DrawButtons() override;
    void HighlightButtonsController(int mouse_x, int mouse_y) override;
    void ClickController(int mouse_x, int mouse_y);
    void DrawText();
private:
    sf::RectangleShape easy_button_;
    sf::RectangleShape normal_button_;
    sf::RectangleShape hard_button_;
};


#endif //TEEKO_AIMENU_H
