#ifndef TEEKO_MENU_H
#define TEEKO_MENU_H

#include "GameRenderer.h"

/**
 * @brief Generic class for menus
 */
class Menu {
public:
    // Default constructor
    Menu();
    // Constructor for a menu in an existing window
    explicit Menu(sf::RenderWindow *window);
    // Creates a menu button
    sf::RectangleShape CreateButton(int x, int y, sf::Color color, sf::Color outline_color);
    // Creates the text for a menu button
    sf::Text CreateButtonText(sf::RectangleShape* button, std::string text);
    // Displays the menu's background
    void DrawBackground();
    // Calls every functions necessary to draw the menu
    virtual void Render()= 0;
    // Displays the menu buttons
    virtual void DrawButtons()= 0;
    // Changes button's color on mouseover
    virtual void HighlightButtonsController(int mouse_x, int mouse_y)= 0;
    // Manages every click on the window and calls the appropriate functions
    virtual void ClickController(int mouse_x, int mouse_y)= 0;
protected:
    // The window in which the menu is displayed
    sf::RenderWindow* main_window_;
    // Buttons' width
    int kButtonWidth = 400;
    // Buttons' height
    int kButtonHeight = 50;
    // The font used for the buttons
    sf::Font theboldfont;
};


#endif //TEEKO_MENU_H
