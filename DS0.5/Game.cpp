#include "Game.h"
#include <SFML/Graphics.hpp>

void Game::Init()
{
	m_window.create(sf::VideoMode(1500.f, 750.f), "SFML works!");
    m_map.Init();
}

void Game::Update()
{
    while (m_window.isOpen())
    {
        Events();
        Draw();
    }
}

void Game::Draw()
{
    m_window.clear();
    m_map.Draw(m_window);
    //m_window.draw();
    m_window.display();
}

void Game::Events()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}
