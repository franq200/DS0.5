#pragma once
#include <SFML/Graphics.hpp>
#include "AStar.h"
#include "Moveable.h"
#include "Fightable.h"

class Goblin : public sf::Sprite, public Moveable
{
public:
	void Init();
	void HpBarInit();
	void MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map);
	void LossHp();
	void DrawHpBar(sf::RenderWindow& window);
private:
	//void WalkAnimation(sf::Clock& moveClock) override;
	float m_hp = 100.f;
	sf::RectangleShape m_hpBarBackground;
	sf::RectangleShape m_hpBar;

	sf::Clock m_moveClock;
	int m_movesCounter = 0;
	std::vector<sf::Vector2f> m_path;
	AStar m_aStar;
};

