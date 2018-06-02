#ifndef TEEKO_GAMERENDERER_H
#define TEEKO_GAMERENDERER_H

#include <SFML/Graphics.hpp>
#include "../model/Game.h"

class GameRenderer{
private:
    Game* game_;
    sf::RenderWindow* main_window_;
    const int kBorderX = 750;
    const int kBorderY = 750;
public:
    explicit GameRenderer(Game *game, sf::RenderWindow *window);
    void Render();
    void DrawBoard();
    void DrawSpaces();
    void DrawMarkers();
    void DrawTurnLabel();
    void DrawBackground();
    void DrawWinnerMessage();
    int GetCoordX(int space_id);
    int GetCoordY(int space_id);
    void ClickController(int mouse_x, int mouse_y);
    int GetClickedSpaceID(int x, int y);
};


#endif //TEEKO_GAMERENDERER_H
