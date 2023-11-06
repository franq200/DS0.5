#pragma once
#include <SFML/Graphics.hpp>
#include "Fightable.h"
#include "Moveable.h"

class Character;

class Enemy : public Fightable, public Moveable
{
public:
	Enemy(float attackDamage, const sf::Texture& texture, float startHp, float scale);
	void Init(const sf::Vector2f& spawnPos);
	virtual void Restart() = 0;
	void TryKill(Character& character);
	void Attack(Character& character);
	void MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map);
	void UpdateHpBarPos() override;
protected:
	virtual void Kill(Character& character) = 0;
	sf::Vector2f m_spawnPos;
	sf::Clock m_moveClock;
	int m_movesCounter = 0;
	std::vector<sf::Vector2f> m_pathToCharacter;
	bool m_isAttackClockRestarted = false;
private:
	const sf::Texture& m_texture;
	const float m_scale;
};