#pragma once
#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include "Fightable.h"

class Enemy;
class Map;

class ICharacter : public Moveable, public Fightable
{
public:
	ICharacter(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IClock> clock);
	virtual ~ICharacter() = default;
	virtual void Teleport(const sf::Vector2f& newPosition) = 0;
	virtual bool IsAbleToAttack() = 0;
	virtual void Init(sf::Vector2f spawnPos) = 0;
	virtual void MakeMove(const sf::Vector2f& moveValue) = 0;
	virtual void Attack(Enemy& enemy) = 0;
	virtual void Restart() = 0;
	virtual int GetMoveDistance() const = 0;
	virtual std::vector<sf::Vector2f> GetEveryPossibleMovement() const = 0;
	virtual bool IsSlowed() = 0;
	virtual bool IsLeftMovePossible(const Map* map) const = 0;
	virtual bool IsRightMovePossible(const Map* map) const = 0;
	virtual bool IsUpMovePossible(const Map* map) const = 0;
	virtual bool IsDownMovePossible(const Map* map) const = 0;
};

