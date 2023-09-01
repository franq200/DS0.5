#pragma once
#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include "HpBar.h"

class Character : public sf::Sprite, public Moveable
{
public:
	void Init(sf::Vector2f spawnPos);
	void MakeMove(const sf::Vector2f& moveValue);
	void LossHp();
	void GetHp();
	void DrawHpBar(sf::RenderWindow& window);
	const int GetMoveClockAsMilliseconds() const;
	const bool IsDead() const;
	void HpBarUpdate();
	void Restart(sf::Vector2f spawnPos);
private:
	void WalkAnimation();
	sf::Clock m_moveClock;
	float m_hp = 100.f;
	HpBar m_hpBar;
};

