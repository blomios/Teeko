#include <SFML/Graphics.hpp>
#include "model/Game.h"
#include "view/GameRenderer.h"
#include "view/MainMenu.h"

int main()
{
    MainMenu mainMenu;
    mainMenu.Render();
    //GameRenderer game_renderer(&game);
    //game_renderer.Render();
    return 0;
}