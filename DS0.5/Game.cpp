#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Helper.h"
#include <iostream>

void Game::Init()
{
	m_window.create(sf::VideoMode(1500, 750), "SFML works!");
	LoadTextures();
	m_character.Init({0.f, 0.f});
	m_dungeonMap.LoadMap(m_character);
	m_villageMap.LoadMap(m_character);
}

void Game::Update()
{
	while (m_window.isOpen())
	{
		Events();
		CheckCurrentMapAndTryMoveCharacter();
		TryChangeMap();
		Draw();
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

void Game::Events()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::Draw()
{
	m_window.clear();
	if (m_currentMap == CurrentMap::village)
	{
		m_villageMap.Draw(m_window);
	}
	else if (m_currentMap == CurrentMap::dungeon)
	{
		m_dungeonMap.Draw(m_window);
	}
	m_window.draw(m_character);
	m_window.display();
}

void Game::CheckCurrentMapAndTryMoveCharacter()
{
	if (m_currentMap == CurrentMap::village)
	{
		TryMoveCharacter(&m_villageMap);
	}
	else if (m_currentMap == CurrentMap::dungeon)
	{
		TryMoveCharacter(&m_dungeonMap);
	}
}

void Game::TryMoveCharacter(Map* map)
{
	if (m_moveClock.getElapsedTime().asMilliseconds() >= speed::character)
	{
		sf::Vector2f characterPos = m_character.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !map->IsCollisionWithCharacter({ characterPos.x, characterPos.y - 10.f }, CellState::Filled, m_character.getScale().x))
		{
			m_character.MoveCharacter({ 0.f, -10.f }, m_moveClock);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !map->IsCollisionWithCharacter({ characterPos.x - 10.f, characterPos.y }, CellState::Filled, m_character.getScale().x))
		{
			if (m_character.getScale().x > 0)
			{
				m_character.setScale(-0.25, 0.25);
				m_character.move(50.f, 0.f);
			}
			m_character.MoveCharacter({ -10.f, 0.f }, m_moveClock);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !map->IsCollisionWithCharacter({ characterPos.x, characterPos.y + 10.f }, CellState::Filled, m_character.getScale().x))
		{
			m_character.MoveCharacter({ 0.f, 10.f }, m_moveClock);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !map->IsCollisionWithCharacter({ characterPos.x + 10.f, characterPos.y }, CellState::Filled, m_character.getScale().x))
		{
			if (m_character.getScale().x < 0)
			{
				m_character.setScale(0.25, 0.25);
				m_character.move(-50.f, 0.f);
			}
			m_character.MoveCharacter({ 10.f, 0.f }, m_moveClock);
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_character.setTexture(textures::character);
	}
}

void Game::TryChangeMap()
{
	if (m_currentMap == CurrentMap::village)
	{
		if (m_villageMap.IsCollisionWithCharacter(m_character.getPosition(), CellState::Teleport, m_character.getScale().x))
		{
			m_currentMap = CurrentMap::dungeon;
		}
	}
	else if (m_currentMap == CurrentMap::dungeon)
	{
		if (m_dungeonMap.IsCollisionWithCharacter(m_character.getPosition(), CellState::Teleport, m_character.getScale().x))
		{
			m_currentMap = CurrentMap::village;
		}
	}
}
