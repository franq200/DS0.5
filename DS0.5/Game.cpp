#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Helper.h"
#include "Village.h"
#include "Dungeon.h"

void Game::Init()
{
	m_window.create(sf::VideoMode(size::windowSizeX, size::windowSizeY), "SFML works!");
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
	m_maps[static_cast<int>(m_currentMap)]->Draw(m_window);
	m_character.DrawHpBar(m_window);
	m_window.draw(m_character);
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
				m_character.MakeMove({ 0.f, -character::moveRange });
			}																																																	   
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextLeft(), { CellState::Filled, CellState::Gate }))
			{																																																	   																																							  																																									   
				m_character.MakeMove({ -character::moveRange, 0.f });
			}																																																	   
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextDown(), { CellState::Filled, CellState::Gate }))
			{																																																	   
				m_character.MakeMove({ 0.f, character::moveRange });
			}																																																	   
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextRight(), {CellState::Filled, CellState::Gate}))
			{
				m_character.MakeMove({ character::moveRange, 0.f });
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
	//auto* dungeonMap = dynamic_cast<Dungeon*>(m_maps[static_cast<int>(MapStates::dungeon)].get());
	m_character.Restart();
	for (auto& map : m_maps)
	{
		map->Restart();
	}

	m_currentMap = MapStates::village;
}
