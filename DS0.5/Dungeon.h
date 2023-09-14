#pragma once
#include "Map.h"
#include "Character.h"

class Dungeon : public Map
{
public:
	void LoadMap() override;
	const sf::Vector2f& GetGoblinSpawnPos() const override;
	const sf::Vector2f& GetWarriorSpawnPos() const override;
	const sf::Vector2f& GetDragonSpawnPos() const override;
	void TryOpenGate(const sf::Vector2f& characterPos, const sf::Vector2f& characterScale) override;
private:
	void Open(int x, int y);
	sf::Vector2f m_goblinSpawnPos;
	sf::Vector2f m_warriorSpawnPos;
	sf::Vector2f m_dragonSpawnPos;
};

