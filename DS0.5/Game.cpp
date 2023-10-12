#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Helper.h"
#include "Village.h"
#include "Dungeon.h"

void Game::Init()
{
	m_window.create(sf::VideoMode(size::windowSizeX, size::windowSizeY), "SFML works!");
	ViewInit();
	LoadTextures();
	LoadMaps();
	m_character.Init(m_maps[static_cast<int>(MapStates::village)]->GetCharacterSpawnPos());
}

void Game::Update()
{
	while (m_window.isOpen())
	{
		std::unique_ptr<Map>& currentMap = m_maps[static_cast<int>(m_currentMap)];
		currentMap->Update(m_character);
		Events();
		TryKillCharacter();
		TryMoveCharacter();
		TryChangeMap();
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
	isLoaded &= textures::goblin.loadFromFile("textures\\characters\\Goblin1.png");
	isLoaded &= textures::walkGoblin1.loadFromFile("textures\\characters\\Goblin2.png");
	isLoaded &= textures::walkGoblin2.loadFromFile("textures\\characters\\Goblin3.png");
	isLoaded &= textures::walkGoblin3.loadFromFile("textures\\characters\\Goblin4.png");
	isLoaded &= textures::walkGoblin4.loadFromFile("textures\\characters\\Goblin5.png");
	isLoaded &= textures::warrior.loadFromFile("textures\\characters\\Warrior.png");
	isLoaded &= textures::dragon.loadFromFile("textures\\characters\\Dragon.png");
	if (!isLoaded)
	{
		throw(std::exception("failed to load textures"));
	}
}

void Game::LoadMaps()
{
	m_maps.resize(2);
	m_maps[0] = std::make_unique<Village>();
	m_maps[1] = std::make_unique<Dungeon>();
	for (auto& map : m_maps)
	{
		map->MapInit();
	}
}

void Game::ViewInit()
{
	m_view.setSize(static_cast<float>(size::windowSizeX), static_cast<float>(size::windowSizeY));
	m_view.setCenter(static_cast<float>(size::windowSizeX) / 2, static_cast<float>(size::windowSizeY) / 2);

	m_miniMap.Init();
}

void Game::Move(sf::Vector2f moveValue)
{
	m_character.MakeMove(moveValue);
	m_view.move(moveValue);
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
	sf::Vector2f characterPos = m_character.getPosition();
	m_view.setCenter(characterPos.x + size::cellSize, characterPos.y + size::cellSize/2);
	m_window.setView(m_view);
	DrawObjects();

	m_miniMap.Update(characterPos);
	m_miniMap.DrawOutline(m_window);
	m_miniMap.DrawView(m_window);
	DrawObjects();
	m_window.display();
}

void Game::TryMoveCharacter()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_character.setTexture(textures::character);
	}
	else
	{
		if (m_character.GetMoveClockAsMilliseconds() >= speed::character)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextUp(), { CellState::Filled, CellState::Gate }))
			{
				Move({ 0.f, -character::moveRange });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextLeft(), { CellState::Filled, CellState::Gate }))
			{
				Move({ -character::moveRange, 0.f });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextDown(), { CellState::Filled, CellState::Gate }))
			{
				Move({ 0.f, character::moveRange });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextRight(), {CellState::Filled, CellState::Gate}))
			{
				Move({ character::moveRange, 0.f });
			}
		}
	}
}

void Game::TryChangeMap()
{
	if (m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.getPosition(), {CellState::Teleport}))
	{
		if (m_currentMap == MapStates::village)
		{
			m_currentMap = MapStates::dungeon;
			m_character.setPosition(m_maps[static_cast<int>(m_currentMap)]->GetCharacterSpawnPos());
		}
		else
		{
			m_currentMap = MapStates::village;
			m_character.setPosition(m_maps[static_cast<int>(m_currentMap)]->GetCharacterSpawnPos());
		}
	}
}

void Game::TryKillCharacter()
{
	if (m_character.IsDead())
	{
		Restart();
	}
}


void Game::Restart()
{
	m_character.Restart();
	for (auto& map : m_maps)
	{
		map->Restart();
	}

	m_currentMap = MapStates::village;
}

void Game::DrawObjects()
{
	m_maps[static_cast<int>(m_currentMap)]->Draw(m_window);
	m_character.Draw(m_window);
}
