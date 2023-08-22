#pragma once
#include <SFML/Graphics.hpp>
#include "Fightable.h"
#include "Moveable.h"
#include "AStar.h"
#include "HpBar.h"

class Goblin : public sf::Sprite, public Moveable, public AStar, public HpBar
{
public:
	void Init(sf::Vector2f spawnPos);
	void MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map);
	void LossHp();
	void DrawHpBar(sf::RenderWindow& window);
	bool IsDead() const;
private:
	//void WalkAnimation(sf::Clock& moveClock) override;
	float m_hp = 100.f;
	sf::Clock m_moveClock;
	int m_movesCounter = 0;
	std::vector<sf::Vector2f> m_path;
	std::vector<sf::Vector2f> m_pathToCharacter;
	HpBar m_hpBar;
};