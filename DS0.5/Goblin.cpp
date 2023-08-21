#include "Goblin.h"
#include "Helper.h"

void Goblin::Init()
{
	HpBarInit();
	setTexture(textures::goblin);
	setScale(0.5, 0.5);
	m_walkTextures = { textures::goblin, textures::walkGoblin1, textures::walkGoblin2, textures::walkGoblin3, textures::walkGoblin4 };
	m_moveClock.restart();
}

void Goblin::MakeMove(const sf::Vector2f& characterPos, const std::vector<std::vector<bool>>& map)
{
	if (m_moveClock.getElapsedTime() > sf::milliseconds(200))
	{
		if (m_movesCounter == 0)
		{
			m_path = FindShortestPath(position::GetMapIndexesFromPosition(characterPos), position::GetMapIndexesFromPosition(getPosition()), map);
		}
		if (!m_path.empty())
		{
			setPosition(position::GetPositionFromMapIndexes({ static_cast<float>(m_path[m_path.size() - 1].x), static_cast<float>(m_path[m_path.size() - 1].y) }));
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
	m_hpBar.setScale(m_hp/100, 1.f);
}

void Goblin::DrawHpBar(sf::RenderWindow& window)
{
	window.draw(m_hpBarBackground);
	window.draw(m_hpBar);
}

void Goblin::HpBarInit()
{
	sf::Vector2f currentPos = getPosition();
	m_hpBarBackground.setPosition(currentPos.x, currentPos.y + 50.f);
	m_hpBarBackground.setSize({50.f, 16.f});
	m_hpBarBackground.setFillColor(sf::Color(60, 50, 50, 160));

	m_hpBar.setPosition(currentPos.x + 2, currentPos.y + 52.f);
	m_hpBar.setSize({ 46.f, 12.f });
	m_hpBar.setFillColor(sf::Color(210, 50, 50, 230));
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