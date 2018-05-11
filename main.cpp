#include <SFML/Graphics.hpp>
#include "model/Game.h"
#include "view/GameRenderer.h"

int main()
{
    Game game(true);
    game.Start();
    GameRenderer game_renderer(&game);
    game_renderer.Render();
    return 0;
}