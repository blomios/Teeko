#ifndef TEEKO_GAMERENDERER_H
#define TEEKO_GAMERENDERER_H


#include <SFML/Graphics.hpp>
#include "../model/Game.h"

class Game; // Forward declaration to implement circular dependency

class GameRenderer{
private:
    Game* game_;
    sf::RenderWindow main_window_;
    const int kBorderX = 750;
    const int kBorderY = 750;
public:
    explicit GameRenderer(Game *game);
    void Render();
    void DrawBoard();
    void DrawSpaces();
    void DrawMarkers();
    void DrawTurnLabel();
    void DrawBackground();
    int GetCoordX(int space_id);
    int GetCoordY(int space_id);
    void ClickController(int mouse_x, int mouse_y);
    int GetClickedSpaceID(int x, int y);
};


#endif //TEEKO_GAMERENDERER_H
