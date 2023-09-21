#pragma once
#include "Map.h"
#include "Character.h"
#include "Goblin.h"
#include "Dragon.h"
#include "Warrior.h"

class Dungeon : public Map
{
public:
	void MapInit() override;
	void Update(Character& character) override;
	void Draw(sf::RenderWindow& window) override;
	void Restart() override;
private:
	void TryOpenGate(const sf::Vector2f& characterPos);
	void AttackCharacter(Character& character);
	void AttackOpponent(Character& character);
	void MakeEnemiesMove(Character& character);
	void TryKillGoblin(Character& character);
	void TryKillWarrior(Character& character);
	void TryKillDragon(Character& character);
	void DrawEnemies(sf::RenderWindow& window);
	void LoadMap() override;
	void Init() override;
	void Open(int x, int y);

	sf::Vector2f m_goblinSpawnPos;
	sf::Vector2f m_warriorSpawnPos;
	sf::Vector2f m_dragonSpawnPos;
	Goblin m_goblin;
	Warrior m_warrior;
	Dragon m_dragon;
	bool m_isGoblinAlive = true;
	bool m_isWarriorAlive = true;
	bool m_isDragonAlive = true;
	bool m_isAnyEnemyAlive = true;
};

