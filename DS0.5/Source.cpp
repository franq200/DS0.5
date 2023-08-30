#include <SFML/Graphics.hpp>
#include <exception>
#include "Game.h"

int main()
{
    Game game;
    try
    {
        game.Init();
    }
    catch (std::exception e)
    {
        std::cout << e.what();
    }
    game.Update();
    return 0;
}