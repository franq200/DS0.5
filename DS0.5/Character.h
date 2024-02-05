#pragma once
#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include "Fightable.h"
#include "Mouse.h"
#include "ICharacter.h"

class Map;
class Enemy;

class Character : public ICharacter
{
public:
	Character(std::unique_ptr<IHpBar> hpBar, std::unique_ptr<IMouse> mouse, std::unique_ptr<IClock> clock);
	void Teleport(const sf::Vector2f& newPosition) override;
	bool IsAbleToAttack() override;
	void Init(sf::Vector2f spawnPos) override;
	void MakeMove(const sf::Vector2f& moveValue) override;
	void Attack(Enemy& enemy) override;
	void Restart() override;
	void UpdateHpBarPos() override;
	int GetMoveDistance() const override;
	std::vector<sf::Vector2f> GetEveryPossibleMovement() const override;
	bool IsSlowed() override;
	bool IsLeftMovePossible(const Map* map) const override;
	bool IsRightMovePossible(const Map* map) const override;
	bool IsUpMovePossible(const Map* map) const override;
	bool IsDownMovePossible(const Map* map) const override;
private:
	sf::Vector2f GetNextUp() const;
	sf::Vector2f GetNextDown() const;
	sf::Vector2f GetNextLeft() const;
	sf::Vector2f GetNextRight() const;
	bool m_isAbleToAttack = true;
	sf::Vector2f m_spawnPos;
	std::unique_ptr<IMouse> m_mouse;
};

