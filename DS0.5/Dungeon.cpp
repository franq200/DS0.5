#include "Dungeon.h"
#include "Helper.h"
#include <fstream>
#include <string>

void Dungeon::MapInit()
{
	LoadMap();
	Init();
}

void Dungeon::Update(Character& character)
{
	if (m_isAnyEnemyAlive)
	{
		TryOpenGate(character.getPosition());
		AttackCharacter(character);
		AttackOpponent(character);
		MakeEnemiesMove(character);
	}
}

void Dungeon::Draw(sf::RenderWindow& window)
{
	DrawMap(window);
	if (m_isAnyEnemyAlive)
	{
		DrawEnemies(window);
	}
}

void Dungeon::Restart()
{
	m_goblin.Restart(m_goblinSpawnPos);
	m_warrior.Restart(m_warriorSpawnPos);
	m_dragon.Restart(m_dragonSpawnPos);
	m_isGoblinAlive = true;
	m_isWarriorAlive = true;
	m_isDragonAlive = true;
}

void Dungeon::TryOpenGate(const sf::Vector2f& characterPos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		for (int x = 0; x < m_map.size(); x++)
		{
			for (int y = 0; y < m_map[x].size(); y++)
			{
				if (m_map[x][y].GetState() == CellState::Gate && IsCollisionWithCell(m_map[x][y].getPosition(), characterPos))
				{
					Open(x, y);
				}
			}
		}
	}
}

void Dungeon::AttackCharacter(Character& character)
{
	sf::Vector2f characterPos = character.getPosition();
	if (m_goblin.IsAttackSuccessful(characterPos) && m_isGoblinAlive)
	{
		character.LossHp(m_goblin.GetAttackDamage() * character::damageTakenScaling);
	}
	else if (m_warrior.IsAttackSuccessful(characterPos) && m_isWarriorAlive)
	{
		character.LossHp(m_warrior.GetAttackDamage() * character::damageTakenScaling);
	}
	else if (m_dragon.IsAttackSuccessful(characterPos) && m_isDragonAlive)
	{
		character.LossHp(m_dragon.GetAttackDamage() * character::damageTakenScaling);
	}
}

void Dungeon::AttackOpponent(Character& character)
{
	if (character.IsAttackSuccessful(m_goblin.getPosition()) && m_isGoblinAlive)
	{
		m_goblin.LossHp(character::attackDamage * character::damageScaling);
		TryKillGoblin(character);
	}
	else if (character.IsAttackSuccessful(m_warrior.getPosition()) && m_isWarriorAlive)
	{
		m_warrior.LossHp(character::attackDamage * character::damageScaling);
		TryKillWarrior(character);
	}
	else if (character.IsAttackSuccessful(m_dragon.getPosition()) && m_isDragonAlive)
	{
		m_dragon.LossHp(character::attackDamage * character::damageScaling);
		TryKillDragon(character);
	}
}

void Dungeon::MakeEnemiesMove(Character& character)
{
	if (m_isGoblinAlive)
	{
		m_goblin.MakeMove(character.getPosition(), m_rawMap);
	}
	if (m_isWarriorAlive)
	{
		m_warrior.MakeMove(character.getPosition(), m_rawMap);
	}
	if (m_isDragonAlive)
	{
		m_dragon.MakeMove(character.getPosition(), m_rawMap);
	}
}

void Dungeon::TryKillGoblin(Character& character)
{
	if (m_goblin.IsDead() && m_isGoblinAlive)
	{
		m_isGoblinAlive = false;
		character::damageScaling = 1.3f;
		character.SetHp(130.f);
	}
}

void Dungeon::TryKillWarrior(Character& character)
{
	if (m_warrior.IsDead() && m_isWarriorAlive)
	{
		m_isWarriorAlive = false;
		character::damageTakenScaling = 0.8f;
		character.SetHp(150.f);
	}
}

void Dungeon::TryKillDragon(Character& character)
{
	if (m_dragon.IsDead() && m_isDragonAlive)
	{
		m_isDragonAlive = false;
	}
}

void Dungeon::DrawEnemies(sf::RenderWindow& window)
{
	if (m_isGoblinAlive)
	{
		m_goblin.DrawHpBar(window);
		window.draw(m_goblin);
	}
	if (m_isWarriorAlive)
	{
		m_warrior.DrawHpBar(window);
		window.draw(m_warrior);
	}
	if (m_isDragonAlive)
	{
		m_dragon.DrawHpBar(window);
		window.draw(m_dragon);
	}
}

void Dungeon::LoadMap()
{
	std::ifstream file;
	file.open("maps\\dungeon1.txt");
	std::string line;

	while (getline(file, line))
	{
		std::vector<Cell> row;
		std::vector<bool> rawRow;
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == '1')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Filled));
				rawRow.push_back(false);
			}
			else if (line[i] == '0')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
			}
			else if (line[i] == '2')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Gate));
				rawRow.push_back(false);
			}
			else if (line[i] == 'M')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
				m_characterSpawnPos = { i * size::cellSize / 2, m_map.size() * size::cellSize };
			}
			else if (line[i] == 'G')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
				m_goblinSpawnPos = { i * size::cellSize / 2, m_map.size() * size::cellSize };
			}
			else if (line[i] == 'W')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
				m_warriorSpawnPos = { i * size::cellSize / 2, m_map.size() * size::cellSize };
			}
			else if (line[i] == 'D')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Empty));
				rawRow.push_back(true);
				m_dragonSpawnPos = { i * size::cellSize / 2, m_map.size() * size::cellSize };
			}
			else if (line[i] == 'V')
			{
				row.push_back(Cell({ size::cellSize, size::cellSize }, { i * size::cellSize / 2, m_map.size() * size::cellSize }, CellState::Teleport));
				rawRow.push_back(true);
			}
		}
		m_map.push_back(row);
		m_rawMap.push_back(rawRow);
	}
}

void Dungeon::Init()
{
	m_goblin.Init(m_goblinSpawnPos);
	m_warrior.Init(m_warriorSpawnPos);
	m_dragon.Init(m_dragonSpawnPos);
}

void Dungeon::Open(int x, int y)
{
	m_map[x][y].ChangeState(CellState::Empty);
	m_rawMap[x][y] = true;
	const auto [rX, rY] = position::Right(x, y);
	if (m_map[rX][rY].GetState() == CellState::Gate)
	{
		Open(rX, rY);
	}
	const auto [lX, lY] = position::Left(x, y);
	if (m_map[lX][lY].GetState() == CellState::Gate)
	{
		Open(lX, lY);
	}
	const auto [tX, tY] = position::Top(x, y);
	if (m_map[tX][tY].GetState() == CellState::Gate)
	{
		Open(tX, tY);
	}
	const auto [bX, bY] = position::Bottom(x, y);
	if (m_map[bX][bY].GetState() == CellState::Gate)
	{
		Open(bX, bY);
	}
}
