#include <exception>
#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    Game game;
    try
    {
        game.Init();
        game.Update();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
    return 0;
}