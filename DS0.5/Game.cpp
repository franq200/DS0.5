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
	CharactersInit();
}

void Game::Update()
{
	while (m_window.isOpen())
	{
		if (m_currentMap == MapStates::dungeon)
		{
			TryOpenGate();
			if (m_isWarriorAlive || m_isGoblinAlive || m_isDragonAlive)
			{
				TryDeleteEnemies();
				MakeEnemiesMove();
				TryAttackWithCharacter();
				TryLossHp();
			}
		}
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
	for (int i = 0; i < m_maps.size(); i++)
	{
		m_maps[i]->LoadMap();
	}
}

void Game::CharactersInit()
{
	m_character.Init(m_maps[static_cast<int>(MapStates::village)]->GetCharacterSpawnPos());
	m_goblin.Init(m_maps[static_cast<int>(MapStates::dungeon)]->GetGoblinSpawnPos());
	m_warrior.Init(m_maps[static_cast<int>(MapStates::dungeon)]->GetWarriorSpawnPos());
	m_dragon.Init(m_maps[static_cast<int>(MapStates::dungeon)]->GetDragonSpawnPos());
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
	if (m_currentMap == MapStates::dungeon)
	{
		if (m_isGoblinAlive)
		{
			m_goblin.DrawHpBar(m_window);
			m_window.draw(m_goblin);
		}
		if (m_isWarriorAlive)
		{
			m_warrior.DrawHpBar(m_window);
			m_window.draw(m_warrior);
		}
		if (m_isDragonAlive)
		{
			m_dragon.DrawHpBar(m_window);
			m_window.draw(m_dragon);
		}
	}
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter(m_character.GetNextUp(), { CellState::Filled, CellState::Gate }))
			{																																																	   
				m_character.MakeMove({ 0.f, -character::moveRange });
			}																																																	   
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter(m_character.GetNextLeft(), { CellState::Filled, CellState::Gate }))
			{																																																	   																																							  																																									   
				m_character.MakeMove({ -character::moveRange, 0.f });
			}																																																	   
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter(m_character.GetNextDown(), { CellState::Filled, CellState::Gate }))
			{																																																	   
				m_character.MakeMove({ 0.f, character::moveRange });
			}																																																	   
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter(m_character.GetNextRight(), {CellState::Filled, CellState::Gate}))
			{
				m_character.MakeMove({ character::moveRange, 0.f });
			}
		}
	}
}

void Game::TryChangeMap()
{
	if (m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter(m_character.getPosition(), {CellState::Teleport}))
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

void Game::TryAttackWithCharacter()
{
	if (m_character.IsAttackSuccessful(m_goblin.getPosition()) && m_isGoblinAlive)
	{
		m_goblin.LossHp(20.f);
	}
	if (m_character.IsAttackSuccessful(m_warrior.getPosition()) && m_isWarriorAlive)
	{
		m_warrior.LossHp(20.f);
	}
	if (m_character.IsAttackSuccessful(m_dragon.getPosition()) && m_isDragonAlive)
	{
		m_dragon.LossHp(20.f);
	}
}

void Game::TryKillCharacter()
{
	if (m_character.IsDead())
	{
		Restart();
	}
}

void Game::TryLossHp()
{
	if (m_warrior.IsAttackSuccessful(m_character.getPosition()) && m_isWarriorAlive)
	{
		m_character.LossHp(30.f);
	}
	if (m_goblin.IsAttackSuccessful(m_character.getPosition()) && m_isGoblinAlive)
	{
		m_character.LossHp(20.f);
	}
	if (m_dragon.IsAttackSuccessful(m_character.getPosition()) && m_isDragonAlive)
	{
		m_character.LossHp(60.f);
	}
}

void Game::MakeEnemiesMove()
{
	if (m_isGoblinAlive)
	{
		m_goblin.MakeMove(m_character.getPosition(), m_maps[static_cast<int>(m_currentMap)]->GetRawMap());
	}
	if (m_isWarriorAlive)
	{
		m_warrior.MakeMove(m_character.getPosition(), m_maps[static_cast<int>(m_currentMap)]->GetRawMap());
	}
	if (m_isDragonAlive)
	{
		m_dragon.MakeMove(m_character.getPosition(), m_maps[static_cast<int>(m_currentMap)]->GetRawMap());
	}
}

void Game::TryDeleteEnemies()
{
	if (m_goblin.IsDead() && m_isGoblinAlive)
	{
		m_isGoblinAlive = false;
		character::damageScaling = 1.3f;
		m_character.SetHp(130.f);
	}
	if (m_warrior.IsDead() && m_isWarriorAlive)
	{
		m_isWarriorAlive = false;
		character::damageTakenScaling = 0.8f;
		m_character.SetHp(160.f);
	}
	if (m_dragon.IsDead() && m_isDragonAlive)
	{
		m_isDragonAlive = false;
	}
}

void Game::TryOpenGate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && m_currentMap == MapStates::dungeon)
	{
		m_maps[static_cast<int>(m_currentMap)]->TryOpenGate(m_character.getPosition(), m_character.getScale());
	}
}


void Game::Restart()
{
	auto* dungeonMap = dynamic_cast<Dungeon*>(m_maps[static_cast<int>(MapStates::dungeon)].get());
	m_character.Restart(m_maps[static_cast<int>(MapStates::village)]->GetCharacterSpawnPos());
	m_goblin.Restart(dungeonMap->GetGoblinSpawnPos());
	m_warrior.Restart(m_maps[static_cast<int>(MapStates::dungeon)]->GetWarriorSpawnPos());
	m_isGoblinAlive = true;
	m_isWarriorAlive = true;
	m_currentMap = MapStates::village;
}
