#ifndef TEEKO_SPECTATORMENU_H
#define TEEKO_SPECTATORMENU_H


#include "AIMenu.h"

class SpectatorMenu : public AIMenu {
public:
    // Constructor for the AIMenu, takes in parameter the window in which it will be displayed
    explicit SpectatorMenu(sf::RenderWindow* window);
    // Manages every events triggered by a mouse click
    void ClickController(int mouse_x, int mouse_y) override;
};


#endif //TEEKO_SPECTATORMENU_H
