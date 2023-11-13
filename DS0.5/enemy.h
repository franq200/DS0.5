#pragma once
#include <SFML/Graphics.hpp>
#include "Fightable.h"
#include "Moveable.h"

enum Direction
{
	Left = 0,
	Right,
	Down,
	Up
};

class Character;

class Enemy : public Fightable, public Moveable
{
public:
	Enemy(float attackDamage, const sf::Texture& texture, float startHp, float scale);
	void Init(const sf::Vector2f& spawnPos);
	virtual void Restart() = 0;
	void TryKill(Character& character);
	void Attack(Character& character);
	void PreparePathAndMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map);
	void UpdateHpBarPos() override;
protected:
	virtual void Kill(Character& character) = 0;
	sf::Vector2f m_spawnPos;
	sf::Clock m_moveClock;
	std::vector<sf::Vector2f> m_pathToCharacter;
	bool m_isAttackClockRestarted = false;
private:
	void Move();
	void ChooseDirection();
	bool m_isMoveDone = true;
	const sf::Texture& m_texture;
	const float m_scale;
	Direction m_moveDirection;
	int m_movesCounter = 0;
};