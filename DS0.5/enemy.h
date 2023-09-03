#pragma once
#include <SFML/Graphics.hpp>
#include "AStar.h"
#include "HpBar.h"
#include "Character.h"

class Enemy : public sf::Sprite, public AStar
{
public:
	virtual void Init(const sf::Vector2f& spawnPos) = 0;
	bool IsAttackSuccessful(const sf::Vector2f& characterPos, const float& characterScaleX);
	void MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map);
	void LossHp();
	const bool IsDead() const;
	void Restart(sf::Vector2f spawnPos);
	void DrawHpBar(sf::RenderWindow& window);
protected:
	bool IsCharacterInRange(const sf::Vector2f& characterPos, const float& characterScaleX) const;
	float m_hp;
	sf::Clock m_moveClock;
	sf::Clock m_attackClock;
	int m_movesCounter = 0;
	std::vector<sf::Vector2f> m_path;
	std::vector<sf::Vector2f> m_pathToCharacter;
	HpBar m_hpBar;
	bool m_isAttackClockRestarted = false;
};