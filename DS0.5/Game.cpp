#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Helper.h"
#include "Village.h"
#include "Dungeon.h"

Game::Game()
{
	LoadTextures();
	m_window.create(sf::VideoMode(size::windowSizeX, size::windowSizeY), "SFML works!");
	m_window.setFramerateLimit(60);
	ViewInit();
	m_gameplay.Init();
	m_menu.Init();
}

void Game::Update()
{
	while (m_window.isOpen())
	{
		Events();
		switch (m_gameState)
		{
		case GameState::game:
			if (!m_gameplay.Update(m_view))
			{
				Restart();
			}
			break;
		case GameState::menu:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (m_menu.ShouldExit(m_window))
				{
					m_window.close();
				}
				else if (m_menu.ShouldStart(m_window))
				{
					m_gameState = GameState::game;
				}
			}
			m_menu.Update(m_window);
			break;
		}
		Draw();
	}
}

void Game::LoadTextures()
{
	bool isLoaded = true;
	isLoaded &= textures::character.loadFromFile("textures\\characters\\1.png");
	isLoaded &= textures::walkCharacter1.loadFromFile("textures\\characters\\2.png");
	isLoaded &= textures::walkCharacter2.loadFromFile("textures\\characters\\3.png");
	isLoaded &= textures::walkCharacter3.loadFromFile("textures\\characters\\4.png");
	isLoaded &= textures::walkCharacter4.loadFromFile("textures\\characters\\5.png");
	isLoaded &= textures::goblin1.loadFromFile("textures\\characters\\Goblin1.png");
	isLoaded &= textures::goblin2.loadFromFile("textures\\characters\\Goblin2.png");
	isLoaded &= textures::goblin3.loadFromFile("textures\\characters\\Goblin3.png");
	isLoaded &= textures::goblin4.loadFromFile("textures\\characters\\Goblin4.png");
	isLoaded &= textures::goblin5.loadFromFile("textures\\characters\\Goblin5.png");
	isLoaded &= textures::warrior.loadFromFile("textures\\characters\\Warrior.png");
	isLoaded &= textures::dragon.loadFromFile("textures\\characters\\Dragon.png");
	isLoaded &= textures::start.loadFromFile("textures\\start.png");
	isLoaded &= textures::exit.loadFromFile("textures\\exit.png");
	isLoaded &= textures::grass.loadFromFile("textures\\grass.jpg");
	isLoaded &= textures::rocks.loadFromFile("textures\\rocks.jpg");
	isLoaded &= textures::wall.loadFromFile("textures\\wall.jpg");
	isLoaded &= textures::dirt.loadFromFile("textures\\dirt.jpg");
	isLoaded &= textures::teleport.loadFromFile("textures\\teleport.jpg");
	isLoaded &= textures::gate.loadFromFile("textures\\gate.jpg");
	if (!isLoaded)
	{
		throw(std::exception("failed to load textures"));
	}
}

void Game::ViewInit()
{
	m_view.setSize(static_cast<float>(size::windowSizeX), static_cast<float>(size::windowSizeY));
	m_view.setCenter(static_cast<float>(size::windowSizeX) / 2, static_cast<float>(size::windowSizeY) / 2);
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
	if (m_gameState == GameState::game)
		m_gameplay.Draw(m_window, m_view);
	else if (m_gameState == GameState::menu)
		m_menu.Draw(m_window);
	m_window.display();
}

void Game::Restart()
{
	ViewInit();
	m_window.setView(m_view);
	m_gameState = GameState::menu;
}