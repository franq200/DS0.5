#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Helper.h"

void Game::Init()
{
	m_window.create(sf::VideoMode(size::windowSizeX, size::windowSizeY), "SFML works!");
	LoadTextures();
	LoadMaps();
	m_character.Init(m_maps[static_cast<int>(MapStates::village)]->GetCharacterSpawnPos());
	m_goblin.Init(m_maps[static_cast<int>(MapStates::dungeon)]->GetGoblinSpawnPos());
}

void Game::Update()
{
	while (m_window.isOpen())
	{
		if (m_currentMap == MapStates::dungeon && m_isGoblinAlive)
		{
			TryDeleteGoblin();
			TryAttackWithCharacter();
			MakeGoblinMove();
		}
		Events();
		TryKillCharacter();
		TryMoveCharacter();
		TryChangeMap();
		TryLossHp();
		m_character.HpBarUpdate();
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
	if (!isLoaded)
	{
		throw(std::exception("failed to load textures"));
	}
}

void Game::LoadMaps()
{
	village->LoadMap();
	dungeon->LoadMap();

	m_maps.push_back(village.get());
	m_maps.push_back(dungeon.get());
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
	if (m_currentMap == MapStates::dungeon && m_isGoblinAlive)
	{
		m_goblin.DrawHpBar(m_window);
		m_window.draw(m_goblin);
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
			sf::Vector2f characterPos = m_character.getPosition();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter({ characterPos.x, characterPos.y - 10.f }, CellState::Filled, m_character.getScale().x))
			{
				m_character.MakeMove({ 0.f, -10.f });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter({ characterPos.x - 10.f, characterPos.y }, CellState::Filled, m_character.getScale().x))
			{
				if (m_character.getScale().x > 0)
				{
					m_character.setScale(-0.25, 0.25);
					m_character.move(50.f, 0.f);
				}
				m_character.MakeMove({ -10.f, 0.f });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter({ characterPos.x, characterPos.y + 10.f }, CellState::Filled, m_character.getScale().x))
			{
				m_character.MakeMove({ 0.f, 10.f });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter({ characterPos.x + 10.f, characterPos.y }, CellState::Filled, m_character.getScale().x))
			{
				if (m_character.getScale().x < 0)
				{
					m_character.setScale(0.25, 0.25);
					m_character.move(-50.f, 0.f);
				}
				m_character.MakeMove({ 10.f, 0.f });
			}
		}
	}
}

void Game::TryChangeMap()
{
	if (m_maps[static_cast<int>(m_currentMap)]->IsCollisionWithCharacter(m_character.getPosition(), CellState::Teleport, m_character.getScale().x))
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (IsAttackSuccessful() && m_isAbleToAttack)
		{
			m_goblin.LossHp();
		}
		m_isAbleToAttack = false;
		return;
	}
	m_isAbleToAttack = true;
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
	if (IsAttackSuccessful())
	{
		if (!m_isGoblinAttackClockRestarted)
		{
			m_goblin.RestartAttackClock();
			m_isGoblinAttackClockRestarted = true;
		}
		if (m_goblin.GetAttackClockAsMilliseconds() >= speed::goblinAttackSpeed)
		{
			m_character.LossHp();
			m_goblin.RestartAttackClock();
		}
	}
	else if (m_isGoblinAttackClockRestarted)
	{
		m_isGoblinAttackClockRestarted = false;
	}
}

void Game::MakeGoblinMove()
{
	m_goblin.MakeMove(m_character.getPosition(), m_maps[static_cast<int>(m_currentMap)]->GetRawMap());
}

void Game::TryDeleteGoblin()
{
	if (m_goblin.IsDead())
	{
		m_isGoblinAlive = false;
	}
}

void Game::Restart()
{
	m_character.Restart(m_maps[static_cast<int>(MapStates::village)]->GetCharacterSpawnPos());
	m_goblin.Restart(m_maps[static_cast<int>(MapStates::village)]->GetGoblinSpawnPos());
	m_isGoblinAlive = true;
	m_currentMap = MapStates::village;
}

bool Game::IsAttackSuccessful()
{
	sf::Vector2f goblinPos = m_goblin.getPosition();
	sf::Vector2f characterPos = m_character.getPosition();
	if (m_character.getScale().x < 0.f)
	{
		characterPos.x -= 50.f;
	}
	return (std::abs(goblinPos.x - characterPos.x) <= 60 && std::abs(goblinPos.y - characterPos.y) <= 60);
}