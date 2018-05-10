#ifndef TEEKO_MAINMENU_H
#define TEEKO_MAINMENU_H

#include <SFML/Graphics.hpp>

class MainMenu {
private:
    sf::RenderWindow main_window_;
    const int kBorderX = 750;
    const int kBorderY = 750;
public:
    MainMenu();
    void Render();
    void DrawButtons();
};


#endif //TEEKO_MAINMENU_H
