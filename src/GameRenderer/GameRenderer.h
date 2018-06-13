#ifndef TEEKO_GAMERENDERER_H
#define TEEKO_GAMERENDERER_H

#include <SFML/Graphics.hpp>
#include "../Core/Game.h"

/**
 * @brief Renders the game itself and manages clicks
 */
class GameRenderer {
private:
    // The game displayed by the renderer
    Game *game_;
    // The window in which the game is rendered
    sf::RenderWindow *main_window_;
    // The board's size
    const int kBoardX = 750;
    const int kBoardY = 750;
public:
    // Constructor using the game to render and the window iun which it should render the game
    explicit GameRenderer(Game *game, sf::RenderWindow *window);

    // Renders every elements of the game by calling appropriate functions
    void Render();

    // Renders the game board
    void DrawBoard();

    // Renders the spaces and the link between them
    void DrawSpaces();

    // Renders the markers, if any
    void DrawMarkers();

    // Renders the turn indicator in the top left corner
    void DrawTurnLabel();

    // Renders the wooden background
    void DrawBackground();

    // Renders a message if there is a winner
    void DrawWinnerMessage();

    // Returns the X position based on a space ID (between 1 and 25)
    int GetCoordX(int space_id);

    // Returns the Y position based on a space ID (between 1 and 25)
    int GetCoordY(int space_id);

    // Manages every events triggered by a mouse click
    void ClickController(int mouse_x, int mouse_y);

    // Returns the space ID clicked on by the player based on mouse coordinates
    int GetClickedSpaceID(int x, int y);
};


#endif //TEEKO_GAMERENDERER_H
