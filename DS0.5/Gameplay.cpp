#include "Gameplay.h"
#include "Village.h"
#include "Dungeon.h"

void Gameplay::Init()
{
	LoadMaps();
	m_character.Init(m_maps[static_cast<int>(MapStates::village)]->GetCharacterSpawnPos());
	m_miniMap.Init();
}

bool Gameplay::Update(sf::View& view)
{
	std::unique_ptr<Map>& currentMap = m_maps[static_cast<int>(m_currentMap)];
	currentMap->Update(m_character);
	if (m_moveClock.getElapsedTime() >= sf::milliseconds(20))
	{
		TryMoveCharacter(view);
		currentMap->MakeEnemiesMove(m_character.getPosition());
		m_moveClock.restart();
	}
	TryChangeMap(view);
	return !TryKillCharacter();
}

void Gameplay::LoadMaps()
{
	m_maps.resize(2);
	m_maps[0] = std::make_unique<Village>();
	m_maps[1] = std::make_unique<Dungeon>();
	for (auto& map : m_maps)
	{
		map->MapInit();
	}
}

void Gameplay::TryMoveCharacter(sf::View& view)
{
	bool shouldMoveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_character.IsLeftMovePossible(m_maps[static_cast<int>(m_currentMap)].get());
	bool shouldMoveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_character.IsRightMovePossible(m_maps[static_cast<int>(m_currentMap)].get());
	bool shouldMoveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_character.IsDownMovePossible(m_maps[static_cast<int>(m_currentMap)].get());
	bool shouldMoveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_character.IsUpMovePossible(m_maps[static_cast<int>(m_currentMap)].get());

	if (!shouldMoveUp && !shouldMoveDown && !shouldMoveRight && !shouldMoveLeft)
	{
		m_character.setTexture(textures::character);
	}
	else
	{
		sf::Vector2f moveVector;
		if ((shouldMoveLeft || shouldMoveRight) && (shouldMoveDown || shouldMoveUp))
		{
			m_character.SetSpeed(2);
		}
		else
		{
			m_character.SetSpeed(3);
		}
		moveVector.x = shouldMoveLeft ? m_character.GetMoveDistance() * (-1.f) : shouldMoveRight ? m_character.GetMoveDistance() * 1.f : 0;
		moveVector.y = shouldMoveUp ? m_character.GetMoveDistance() * (-1.f) : shouldMoveDown ? m_character.GetMoveDistance() * 1.f : 0;
		Move(moveVector, view);
	}
}

void Gameplay::TryChangeMap(sf::View& view)
{
	if (m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.getPosition(), { CellState::Teleport }))
	{
		m_currentMap == MapStates::village ? m_currentMap = MapStates::dungeon : m_currentMap = MapStates::village;
		m_character.Teleport(m_maps[static_cast<int>(m_currentMap)]->GetCharacterSpawnPos());
		sf::Vector2f characterPos = m_character.getPosition();
		view.setCenter(characterPos.x + size::cellSize, characterPos.y + size::cellSize / 2);
	}
}

bool Gameplay::TryKillCharacter()
{
	if (m_character.IsDead())
	{
		Restart();
		return true;
	}
	return false;
}

void Gameplay::Move(sf::Vector2f moveValue, sf::View& view)
{
	m_character.MakeMove(moveValue);
	view.move(moveValue);
}

void Gameplay::DrawObjects(sf::RenderWindow& window)
{
	m_maps[static_cast<int>(m_currentMap)]->Draw(window);
	m_character.Draw(window);
}

void Gameplay::Restart()
{
	m_character.Restart();
	for (auto& map : m_maps)
	{
		map->Restart();
	}
	m_currentMap = MapStates::village;
	m_moveClock.restart();
}

void Gameplay::Draw(sf::RenderWindow& window, sf::View& view)
{
	sf::Vector2f characterPos = m_character.getPosition();
	//view.setCenter(characterPos.x + size::cellSize, characterPos.y + size::cellSize / 2);
	window.setView(view);
	DrawObjects(window);

	m_miniMap.Update(characterPos);
	m_miniMap.DrawOutline(window);
	m_miniMap.SetView(window);
	DrawObjects(window);
}
