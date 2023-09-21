#pragma once
#include "Map.h"
#include "Character.h"
#include "Goblin.h"
#include "Warrior.h"
#include "Dragon.h"
#include <SFML/Graphics.hpp>


enum class MapStates : uint8_t
{
	village = 0,
	dungeon
};

class Game
{
public:
	void Init();
	void Update();
private:
	void Events();
	void LoadTextures();
	void LoadMaps();
	void TryMoveCharacter();
	void TryChangeMap();
	void TryKillCharacter();
	void Restart();
	void Draw();

	sf::RenderWindow m_window;
	Character m_character;

	std::vector<std::unique_ptr<Map>> m_maps;
	MapStates m_currentMap = MapStates::village;
};
