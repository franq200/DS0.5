#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Helper.h"
#include <iostream>

void Game::Init()
{
	m_window.create(sf::VideoMode(1500, 750), "SFML works!");
    LoadTextures();
    m_map.Init(m_character);
}

void Game::Update()
{
    while (m_window.isOpen())
    {
        Events();
        TryMoveCharacter();
        Draw();
    }
}

void Game::Draw()
{
    m_window.clear();
    m_map.Draw(m_window);
    m_window.draw(m_character);
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

void Game::LoadTextures()
{
    textures::character.loadFromFile("textures\\characters\\1.png");
    textures::walkCharacter1.loadFromFile("textures\\characters\\2.png");
    textures::walkCharacter2.loadFromFile("textures\\characters\\3.png");
    textures::walkCharacter3.loadFromFile("textures\\characters\\4.png");
    textures::walkCharacter4.loadFromFile("textures\\characters\\5.png");
}

void Game::TryMoveCharacter()
{
    if (m_moveClock.getElapsedTime().asMilliseconds() >= speed::character)
    {
        sf::Vector2f characterPos = m_character.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_map.IsAbleToMove({ characterPos.x, characterPos.y - 10.f }))
        {
            MoveCharacter({0.f, -10.f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_map.IsAbleToMove({ characterPos.x - 10.f, characterPos.y}))
        {
            MoveCharacter({ -10.f, 0.f });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_map.IsAbleToMove({ characterPos.x, characterPos.y + 10.f }))
        {
            MoveCharacter({ 0.f, 10.f });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_map.IsAbleToMove({ characterPos.x + 10.f, characterPos.y}))
        {
            MoveCharacter({ 10.f, 0.f });
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_character.setTexture(&textures::character);
        }
    }
}

void Game::MoveCharacter(sf::Vector2f moveValue)
{
    static int moveCounter = 0;
    if (moveCounter == 0)
    {
        m_character.setTexture(&textures::character);
        moveCounter++;
    }
    if (moveCounter == 1)
    {
        m_character.setTexture(&textures::walkCharacter1);
        moveCounter++;
    }
    else if (moveCounter == 2)
    {
        m_character.setTexture(&textures::walkCharacter2);
        moveCounter++;
    }
    else if (moveCounter == 3)
    {
        m_character.setTexture(&textures::walkCharacter3);
        moveCounter++;
    }
    else if (moveCounter == 4)
    {
        m_character.setTexture(&textures::walkCharacter4);
        moveCounter = 0;
    }
    m_character.move(moveValue);
    m_moveClock.restart();
}
