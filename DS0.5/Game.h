#pragma once
#include "Map.h"
#include "Character.h"
#include "Village.h"
#include "Dungeon.h"
#include "Goblin.h"
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
	void TryAttackWithCharacter();
	void TryKillCharacter();
	void TryLossHp();
	bool IsAttackSuccessful();
	void MakeGoblinMove();
	void TryDeleteGoblin();
	void Restart();
	void Draw();

	sf::RenderWindow m_window;
	Character m_character;
	Goblin m_goblin;
	MapStates m_currentMap = MapStates::village;
	bool m_isAbleToAttack = true;
	bool m_isGoblinAlive = true;
	std::vector<Map*> m_maps;
	std::unique_ptr<Village> village = std::make_unique<Village>();
	std::unique_ptr<Dungeon> dungeon = std::make_unique<Dungeon>();
	bool m_isGoblinAttackClockRestarted = false;
};
