#pragma once
#include <SFML/Graphics.hpp>
#include "HpBar.h"

class Character : public sf::Sprite
{
public:
	void Init(sf::Vector2f spawnPos);
	void MakeMove(const sf::Vector2f& moveValue);
	bool IsAttackSuccessful(const sf::Vector2f& enemyPos);
	void LossHp(float lostHp);
	void SetHp(float newHp);
	void DrawHpBar(sf::RenderWindow& window);
	const int GetMoveClockAsMilliseconds() const;
	const bool IsDead() const;
	void HpBarUpdate();
	void Restart(const sf::Vector2f& spawnPos);
private:
	bool IsEnemyInRange(const sf::Vector2f& enemyPos) const;
	void WalkAnimation();
	sf::Clock m_moveClock;
	float m_hp = 100.f;
	HpBar m_hpBar;
	sf::Clock m_attackClock;
	std::vector <sf::Texture> m_walkTextures;
	int m_moveCounter = 0;
};

