#pragma once
#include "Map.h"
#include "Goblin.h"
#include "Dragon.h"
#include "Warrior.h"

class Character;

class Dungeon : public Map
{
public:
	void MapInit() override;
	void Update(Character& character) override;
	void Draw(sf::RenderWindow& window) override;
	void Restart() override;
	virtual void MakeEnemiesMove(const sf::Vector2f& characterPos) override;
private:
	void TryOpenGate(const std::vector<sf::Vector2f>& characterPositions);
	void AttackCharacter(Character& character);
	void AttackOpponents(Character& character);
	void DrawEnemies(sf::RenderWindow& window);
	void SetTextures() override;
	void LoadMap() override;
	void Init() override;
	void Open(int x, int y);

	std::vector<std::unique_ptr<Enemy>> m_enemies;
	sf::Vector2f m_goblinSpawnPos;
	sf::Vector2f m_warriorSpawnPos;
	sf::Vector2f m_dragonSpawnPos;
};

