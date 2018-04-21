#ifndef TEEKO_GAMERENDERER_H
#define TEEKO_GAMERENDERER_H


#include <SFML/Graphics.hpp>
#include "../model/Game.h"

class Game; // Forward declaration to implement circular dependency

class GameRenderer{
private:
    Game* game_;
    sf::RenderWindow main_window_;
public:
    GameRenderer(Game *game);
    void Render();
    int getCoordX(int space_id);
    int getCoordY(int space_id);
};


#endif //TEEKO_GAMERENDERER_H
