#pragma once
#include "Character.h"
#include "MiniMap.h"
#include <vector>
#include "Map.h"

enum class MapStates : uint8_t
{
	village = 0,
	dungeon
};

class Gameplay
{
public:
	void Init();
	bool Update(sf::View& view);
	void Draw(sf::RenderWindow& window, sf::View& view);
private:
	void LoadMaps();
	void TryMoveCharacter(sf::View& view);
	void TryChangeMap(sf::View& view);
	void Move(sf::Vector2f moveValue, sf::View& view);
	void DrawObjects(sf::RenderWindow& window);
	void Restart();
	bool TryKillCharacter();

	Character m_character;
	MiniMap m_miniMap;
	std::vector<std::unique_ptr<Map>> m_maps;
	MapStates m_currentMap = MapStates::village;
	sf::Clock m_moveClock;
};

