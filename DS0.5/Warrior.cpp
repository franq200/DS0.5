#include "Warrior.h"
#include "Helper.h"

void Warrior::Init(sf::Vector2f spawnPos)
{
	setTexture(textures::warrior);
	setScale(0.33f, 0.33f);
	//m_walkTextures = { textures::goblin, textures::walkGoblin1, textures::walkGoblin2, textures::walkGoblin3, textures::walkGoblin4 };
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hpBar.Init(getPosition());
}

void Warrior::MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map)
{
	if (m_moveClock.getElapsedTime() > sf::milliseconds(600))
	{
		if (m_movesCounter == 0)
		{
			m_path = FindShortestPath(position::GetMapIndexesFromPosition(characterPos), position::GetMapIndexesFromPosition(getPosition()), map);
		}
		if (!m_path.empty())
		{
			sf::Vector2f movePos = position::GetPositionFromMapIndexes({ static_cast<float>(m_path[m_path.size() - 1].x), static_cast<float>(m_path[m_path.size() - 1].y) });
			setPosition(movePos);
			m_hpBar.SetPosition(movePos);
			m_path.pop_back();
		}
		if (m_movesCounter == 2)
		{
			m_movesCounter = 0;
		}
		else
		{
			m_movesCounter++;
		}
		m_moveClock.restart();
	}
}

void Warrior::LossHp()
{
	m_hp -= 10.f * character::damageScaling;
	m_hpBar.ChangeHpLevel(m_hp);
}

void Warrior::DrawHpBar(sf::RenderWindow& window)
{
	m_hpBar.Draw(window);
}

const bool Warrior::IsDead() const
{
	return m_hp <= 0.f;
}

int Warrior::GetAttackClockAsMilliseconds() const
{
	return m_attackClock.getElapsedTime().asMilliseconds();
}

void Warrior::RestartAttackClock()
{
	m_attackClock.restart();
}

void Warrior::Restart(sf::Vector2f spawnPos)
{
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hp = 100.f;
	m_hpBar.ChangeHpLevel(m_hp);
	m_movesCounter = 0;
}
