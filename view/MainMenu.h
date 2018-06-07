#ifndef TEEKO_MAINMENU_H
#define TEEKO_MAINMENU_H

#include "AIMenu.h"

/**
 * @brief Class for creating and rendering a main menu
 */
class MainMenu : public Menu {
private:
    // The "Play (2 Players)" button of the main menu
    sf::RectangleShape play_two_button_;
    // The "Play against A.I." button
    sf::RectangleShape play_ai_button_;
    // The "Exit Game" button
    sf::RectangleShape exit_button_;
public:
    // Default constructor
    MainMenu();
    // Calls the functions necessary to draw the background, the logo and the buttons, also wait for events (clicks)
    void Render() override;
    // Draws the 3 buttons of the main menu
    void DrawButtons() override;
    // On mouseover, changes the color of a button
    void ButtonsColorController(int mouse_x, int mouse_y) override;
    // Manages every events triggered by a mouse click
    void ClickController(int mouse_x, int mouse_y) override;
    // Draws the big "Teeko" logo
    void DrawTitle();
};


#endif //TEEKO_MAINMENU_H
