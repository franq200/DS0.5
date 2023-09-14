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
	void CharactersInit();
	void Events();
	void LoadTextures();
	void LoadMaps();
	void TryMoveCharacter();
	void TryChangeMap();
	void TryAttackWithCharacter();
	void TryKillCharacter();
	void TryLossHp();
	void MakeEnemiesMove();
	void TryDeleteEnemies();
	void TryOpenGate();
	void Restart();
	void Draw();

	sf::RenderWindow m_window;
	sf::View m_view;
	Character m_character;
	Goblin m_goblin;
	Warrior m_warrior;
	Dragon m_dragon;
	bool m_isGoblinAlive = true;
	bool m_isWarriorAlive = true;
	bool m_isDragonAlive = true;

	std::vector<std::unique_ptr<Map>> m_maps;
	MapStates m_currentMap = MapStates::village;
};
