#include "Dungeon.h"
#include "Helper.h"
#include "Character.h"
#include <fstream>
#include <string>
#include <map>
#include "Parser.h"
#include "Clock.h"


void Dungeon::MapInit()
{
	LoadMap();
	Init();
}

void Dungeon::Update(Character& character)
{
	TryOpenGate(character.GetEveryPossibleMovement());
	AttackCharacter(character);
	AttackOpponents(character);
}

void Dungeon::Draw(sf::RenderWindow& window)
{
	DrawMap(window);
	DrawEnemies(window);
}

void Dungeon::Restart()
{
	for (int x = 0; x < m_map.size(); x++)
	{
		for (int y = 0; y < m_map[x].size(); y++)
		{
			if (m_map[x][y].GetState() == CellState::OpenGate)
			{
				m_map[x][y].SetCellClosed();
				m_rawMap[x][y] = false;
			}
		}
	}
	for (auto& enemy : m_enemies)
	{
		enemy->Restart();
	}
}

void Dungeon::TryOpenGate(const std::vector<sf::Vector2f>& characterPositions)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		for (auto nextPos : characterPositions)
		{
			if (auto collisionSquare = GetCollisionSquare(nextPos, { CellState::CloseGate }))
			{
				auto [x, y] = collisionSquare.value();
				Open(static_cast<int>(y), static_cast<int>(x));
				break;
			}
		}
	}
}

void Dungeon::AttackCharacter(Character& character)
{
	for (auto& enemy : m_enemies)
	{
		if (!enemy->IsDead())
		{
			enemy->Attack(character);
		}
	}
}

void Dungeon::AttackOpponents(Character& character)
{
	if (character.IsAbleToAttack())
	{
		for (auto& enemy : m_enemies)
		{
			if (!enemy->IsDead())
			{
				character.Attack(*enemy);
			}
		}
	}
}

void Dungeon::MakeEnemiesMove(const sf::Vector2f& characterPos)
{
	for (auto& enemy : m_enemies)
	{
		if (!enemy->IsDead())
		{
			enemy->PreparePathAndMove(characterPos, m_rawMap);
		}
	}
}

void Dungeon::DrawEnemies(sf::RenderWindow& window)
{
	for (auto& enemy : m_enemies)
	{
		if (!enemy->IsDead())
		{
			enemy->Draw(window);
			window.draw(*enemy);
		}
	}
}

void Dungeon::LoadMap()
{
	std::ifstream file("maps\\dungeon1.txt");
	std::string line;
	Parser parser({ textures::wall, textures::rocks });
	//DungeonParser parser({&textures::dungeonWall, &textures::dugeonGround});
	while (getline(file, line))
	{
		for (int i = 0; i < line.size(); ++i)
		{
			parser.Parse(line[i], i, static_cast<uint16_t>(m_map.size()));
		}
		parser.EndRow(m_map, m_rawMap);
	}

	auto positions = parser.GetPositions();

	for (auto& [position, type] : positions)
	{
		switch (type)
		{
		case ObjType::Character:
			m_characterSpawnPos = position;
			break;
		case ObjType::Warrior:
			m_warriorSpawnPos = position;
			break;
		case ObjType::Goblin:
			m_goblinSpawnPos = position;
			break;
		case ObjType::Dragon:
			m_dragonSpawnPos = position;
			break;
		default:
			break;
		}
	}
}

void Dungeon::Init()
{
	m_enemies.push_back(std::make_unique<Goblin>(std::make_unique<HpBar>(), std::make_unique<Clock>()));
	m_enemies.push_back(std::make_unique<Warrior>(std::make_unique<HpBar>(), std::make_unique<Clock>()));
	m_enemies.push_back(std::make_unique<Dragon>(std::make_unique<HpBar>(), std::make_unique<Clock>()));
	m_enemies[0]->Init(m_goblinSpawnPos);
	m_enemies[1]->Init(m_warriorSpawnPos);
	m_enemies[2]->Init(m_dragonSpawnPos);
}

void Dungeon::Open(int x, int y)
{
	m_map[x][y].SetCellOpen();
	m_rawMap[x][y] = true;
	const auto [rX, rY] = position::Right(x, y);
	if (m_map[rX][rY].GetState() == CellState::CloseGate)
	{
		Open(rX, rY);
	}
	const auto [lX, lY] = position::Left(x, y);
	if (m_map[lX][lY].GetState() == CellState::CloseGate)
	{
		Open(lX, lY);
	}
	const auto [tX, tY] = position::Top(x, y);
	if (m_map[tX][tY].GetState() == CellState::CloseGate)
	{
		Open(tX, tY);
	}
	const auto [bX, bY] = position::Bottom(x, y);
	if (m_map[bX][bY].GetState() == CellState::CloseGate)
	{
		Open(bX, bY);
	}
}