#ifndef TEEKO_AIMENU_H
#define TEEKO_AIMENU_H

#include "Menu.h"

/**
 * @brief Class for creating and rendering the AI menu with the difficulty choice
 */
class AIMenu : public Menu {
public:
    // Constructor for the AIMenu, takes in parameter the window in which it will be displayed
    explicit AIMenu(sf::RenderWindow* window);
    // Calls the functions necessary to draw the background and the buttons, also wait for events (clicks)
    void Render() override;
    // Draw the difficulty buttons
    void DrawButtons() override;
    // Changes the color of the button on mouseover
    void ButtonsColorController(int mouse_x, int mouse_y) override;
    // Manages every events triggered by a mouse click
    void ClickController(int mouse_x, int mouse_y) override;
    // Renders the little text inviting the user to choose a difficulty
    void DrawText();
protected:
    // The "Easy" difficulty button
    sf::RectangleShape easy_button_;
    // The "Normal" difficulty button
    sf::RectangleShape normal_button_;
    // The "Hard" difficulty button
    sf::RectangleShape hard_button_;
};


#endif //TEEKO_AIMENU_H
