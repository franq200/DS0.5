#pragma once
#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include "Fightable.h"

class Map;
class Enemy;

class Character : public Moveable, public Fightable
{
public:
	Character(std::unique_ptr<IHpBar> hpBar);
	void Teleport(const sf::Vector2f& newPosition);
	bool IsAbleToAttack();
	void Init(sf::Vector2f spawnPos);
	void MakeMove(const sf::Vector2f& moveValue);
	void Attack(Enemy& enemy);
	void Restart();
	void UpdateHpBarPos() override;
	int GetMoveDistance() const;
	std::vector<sf::Vector2f> GetEveryPossibleMovement() const;
	bool IsSlowed();
	bool IsLeftMovePossible(const Map* map) const;
	bool IsRightMovePossible(const Map* map) const;
	bool IsUpMovePossible(const Map* map) const;
	bool IsDownMovePossible(const Map* map) const;
private:
	sf::Vector2f GetNextUp() const;
	sf::Vector2f GetNextDown() const;
	sf::Vector2f GetNextLeft() const;
	sf::Vector2f GetNextRight() const;
	bool m_isAbleToAttack;
	sf::Vector2f m_spawnPos;
};

