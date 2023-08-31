#include "Goblin.h"
#include "Helper.h"

void Goblin::Init(sf::Vector2f spawnPos)
{
	setTexture(textures::goblin);
	setScale(0.5, 0.5);
	m_walkTextures = { textures::goblin, textures::walkGoblin1, textures::walkGoblin2, textures::walkGoblin3, textures::walkGoblin4 };
	m_moveClock.restart();
	setPosition(spawnPos);
	m_hpBar.Init(getPosition());
}

void Goblin::MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map)
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

void Goblin::LossHp()
{
	m_hp -= 10.f;
	m_hpBar.ChangeHpLevel(m_hp);
}

void Goblin::DrawHpBar(sf::RenderWindow& window)
{
	m_hpBar.Draw(window);
}

const bool Goblin::IsDead() const
{
	return m_hp <= 0.f;
}

int Goblin::GetAttackClockAsMilliseconds() const
{
	return m_attackClock.getElapsedTime().asMilliseconds();
}

void Goblin::RestartAttackClock()
{
	m_attackClock.restart();
}

void Goblin::Restart(sf::Vector2f spawnPos)
{
	m_moveClock.restart();
	SetPosition(spawnPos);
	m_hp = 100.f;
	m_hpBar.ChangeHpLevel(m_hp);
	m_movesCounter = 0;
}

/*
void Goblin::WalkAnimation(sf::Clock& moveClock)
{
	static int moveCounter = 0;
	setTexture(m_walkTextures[moveCounter]);
	if (moveCounter == 4)
	{
		setTexture(textures::walkCharacter4);
		moveCounter = 0;
		return;
	}
	moveCounter++;
}
*/