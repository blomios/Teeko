#ifndef TEEKO_MENU_H
#define TEEKO_MENU_H

#include "GameRenderer.h"

class Menu {
public:
    Menu();
    Menu(sf::RenderWindow *main_window_);
    sf::RectangleShape CreateButton(int x, int y, sf::Color color, sf::Color outline_color);
    sf::Text CreateButtonText(sf::RectangleShape* button, std::string text);
    void DrawBackground();
    virtual void Render()= 0;
    virtual void DrawButtons()= 0;
    virtual void HighlightButtonsController(int mouse_x, int mouse_y)= 0;
    virtual void ClickController(int mouse_x, int mouse_y)= 0;
protected:
    sf::RenderWindow* main_window_;
    // Buttons size
    int kButtonWidth = 400;
    int kButtonHeight= 50;
    sf::Font theboldfont;
};


#endif //TEEKO_MENU_H
