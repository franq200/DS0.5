#pragma once
#include "Map.h"
#include "Character.h"
#include "Village.h"
#include "Dungeon.h"
#include "Goblin.h"
#include <SFML/Graphics.hpp>


enum class CurrentMap : uint8_t
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
	void LoadTextures();
	void Draw();
	void Events();

	void CheckCurrentMapAndTryMoveCharacter();
	void TryMoveCharacter(Map* map);
	void TryChangeMap();
	void TryAttackWithCharacter();
	bool IsAttackSuccessful();

	void MakeGoblinMove();
	void TryDeleteGoblin();

	void Restart();

	sf::RenderWindow m_window;
	Village m_villageMap;
	Dungeon m_dungeonMap;
	sf::CircleShape shape;
	Character m_character;
	Goblin m_goblin;
	CurrentMap m_currentMap = CurrentMap::village;
	bool m_isAbleToAttack = true;
	bool m_isGoblinAlive = true;
};