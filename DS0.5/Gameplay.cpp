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
	TryMoveCharacter(view);
	TryChangeMap();
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
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_character.setTexture(textures::character);
	}
	else
	{
		if (m_character.GetMoveClockAsMilliseconds() >= speed::character)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextUp(), { CellState::Filled, CellState::CloseGate }))
			{
				Move({ 0.f, -character::moveRange }, view);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextLeft(), { CellState::Filled, CellState::CloseGate }))
			{
				Move({ -character::moveRange, 0.f }, view);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextDown(), { CellState::Filled, CellState::CloseGate }))
			{
				Move({ 0.f, character::moveRange }, view);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.GetNextRight(), { CellState::Filled, CellState::CloseGate }))
			{
				Move({ character::moveRange, 0.f }, view);
			}
		}
	}
}

void Gameplay::TryChangeMap()
{
	if (m_maps[static_cast<int>(m_currentMap)]->GetCollisionSquare(m_character.getPosition(), { CellState::Teleport }))
	{
		m_currentMap == MapStates::village ? m_currentMap = MapStates::dungeon : m_currentMap = MapStates::village;
		m_character.Teleport(m_maps[static_cast<int>(m_currentMap)]->GetCharacterSpawnPos());
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
}

void Gameplay::Draw(sf::RenderWindow& window, sf::View& view)
{
	sf::Vector2f characterPos = m_character.getPosition();
	view.setCenter(characterPos.x + size::cellSize, characterPos.y + size::cellSize / 2);
	window.setView(view);
	DrawObjects(window);

	m_miniMap.Update(characterPos);
	m_miniMap.DrawOutline(window);
	m_miniMap.DrawView(window);
	DrawObjects(window);
}
