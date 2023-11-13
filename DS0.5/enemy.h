#pragma once
#include <SFML/Graphics.hpp>
#include "Fightable.h"
#include "Moveable.h"

enum class Direction
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
	Enemy(float attackDamage, float startHp, float scale, const std::vector<sf::Texture>& textures);
	void Init(const sf::Vector2f& spawnPos);
	virtual void Restart() = 0;
	void TryKill(Character& character);
	void Attack(Character& character);
	void PreparePathAndMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map);
	void UpdateHpBarPos() override;
protected:
	virtual void Kill(Character& character) = 0;
	sf::Vector2f m_spawnPos;
	std::vector<sf::Vector2f> m_pathToCharacter;
	bool m_isAttackClockRestarted = false;
private:
	void Move();
	void ChooseDirection();
	Direction m_moveDirection;
};