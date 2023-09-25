#include "Dungeon.h"
#include "Helper.h"
#include "Character.h"
#include <fstream>
#include <string>
#include <map>

namespace
{
	sf::Vector2f ConvertMapIndexPositionToPixelPosition(size_t mapSize, int i)
	{
		return { i * size::cellSize / 2, mapSize * size::cellSize };
	}

	struct LineParseResult
	{
		Cell cell;
		bool isMoveableCell;
	};

	enum class ObjType
	{
		Character,
		Warrior,
		Goblin,
		Dragon
	};

	struct MoveableObjPosition
	{
		sf::Vector2f position;
		ObjType type;
	};

	class ParserCommand
	{
	public:
		virtual LineParseResult execute(size_t mapSize, int i) = 0;
	};

	class ParserCommandWithPosition : public ParserCommand
	{
	public:
		virtual MoveableObjPosition GetPosition() const = 0;
	protected:
		sf::Vector2f position;
	};

	class ParserFilledCellCommand : public ParserCommand
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			return { Cell({ size::cellSize, size::cellSize }, { ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Filled), false };
		}
	};

	class ParserEmptyCellCommand : public ParserCommand
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			return { Cell({ size::cellSize, size::cellSize }, { ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
		}
	};

	class ParserGateCellCommand : public ParserCommand
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			return { Cell({ size::cellSize, size::cellSize }, { ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Gate), false };
		}
	};

	class ParserTeleportCellCommand : public ParserCommand
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			return { Cell({ size::cellSize, size::cellSize }, { ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Teleport), true };
		}
	};

	class ParserCharacterCellCommand : public ParserCommandWithPosition
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			position = ConvertMapIndexPositionToPixelPosition(mapSize, i);
			return { Cell({ size::cellSize, size::cellSize }, { ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
		}
		
 		MoveableObjPosition GetPosition() const
		{
			return {position, ObjType::Character};
		}
	};

	class ParserGoblinCellCommand : public ParserCommandWithPosition
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			position = ConvertMapIndexPositionToPixelPosition(mapSize, i);
			return { Cell({ size::cellSize, size::cellSize }, { ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
		}

		MoveableObjPosition GetPosition() const
		{
			return {position, ObjType::Goblin};
		}
	};

	class ParserWarriorCellCommand : public ParserCommandWithPosition
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			position = ConvertMapIndexPositionToPixelPosition(mapSize, i);
			return { Cell({ size::cellSize, size::cellSize }, { ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
		}

	 	MoveableObjPosition GetPosition() const
		{
			return {position, ObjType::Warrior};
		}
	};

	class ParserDragonCellCommand : public ParserCommandWithPosition
	{
	public:
		LineParseResult execute(size_t mapSize, int i) override
		{
			position = ConvertMapIndexPositionToPixelPosition(mapSize, i);
			return { Cell({ size::cellSize, size::cellSize }, { ConvertMapIndexPositionToPixelPosition(mapSize, i) }, CellState::Empty), true };
		}

		MoveableObjPosition GetPosition() const
		{
			return {position, ObjType::Dragon};
		}
	};

	class Parser
	{
	public:
		Parser(std::vector<std::vector<Cell>>& map, std::vector<std::vector<bool>> rawMap)
		: map(map), rawMap(rawMap)
		{
			commands['1'] = std::make_unique<ParserFilledCellCommand>();
			commands['0'] = std::make_unique<ParserEmptyCellCommand>();
			commands['2'] = std::make_unique<ParserGateCellCommand>();
			commands['V'] = std::make_unique<ParserTeleportCellCommand>();
			commands['M'] = std::make_unique<ParserCharacterCellCommand>();
			commands['G'] = std::make_unique<ParserGoblinCellCommand>();
			commands['W'] = std::make_unique<ParserWarriorCellCommand>();
			commands['D'] = std::make_unique<ParserDragonCellCommand>();
		}

		void Parse(char command, int i)
		{
			commands.at(command)->execute(map.size(), i);
		}
		
		void EndRow()
		{
			map.push_back(row);
			rawMap.push_back(rawRow);

			row.clear();
			rawRow.clear();
		}

		std::vector<MoveableObjPosition> GetPositions() const
		{
			std::vector<MoveableObjPosition> results;
			for(auto&[key, obj] : commands)
			{
				if(auto* moveableObj = dynamic_cast<ParserCommandWithPosition*>(obj.get()))
				{
					results.emplace_back(moveableObj->GetPosition());
				}
			}

			return results;
		}

	private:
		std::map<char, std::unique_ptr<ParserCommand>> commands;
		std::vector<std::vector<Cell>>& map;
		std::vector<std::vector<bool>>& rawMap;
		std::vector<Cell> row;
		std::vector<bool> rawRow;
	};
}


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
	MakeEnemiesMove(character.getPosition());
}

void Dungeon::Draw(sf::RenderWindow& window)
{
	DrawMap(window);
	DrawEnemies(window);
}

void Dungeon::Restart()
{
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
			if (auto collisionSquare = GetCollisionSquare(nextPos, { CellState::Gate }))
			{
				auto [x, y] = collisionSquare.value();
				Open(y, x);
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
			enemy->MakeMove(characterPos, m_rawMap);
		}
	}
}

void Dungeon::DrawEnemies(sf::RenderWindow& window)
{
	for (auto& enemy : m_enemies)
	{
		if (!enemy->IsDead())
		{
			enemy->DrawHpBar(window);
			window.draw(*enemy);
		}
	}
}

void Dungeon::LoadMap()
{
	std::ifstream file("maps\\dungeon1.txt");
	std::string line;

	Parser parser(m_map, m_rawMap);
	while (getline(file, line))
	{
		for (int i = 0; i < line.size(); ++i)
		{
			parser.Parse(line[i], i);
		}
		parser.EndRow();
	}

	auto positions = parser.GetPositions();

	for(auto& [position, type] : positions)
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
	m_enemies.push_back(std::make_unique<Goblin>());
	m_enemies.push_back(std::make_unique<Warrior>());
	m_enemies.push_back(std::make_unique<Dragon>());
	m_enemies[0]->Init(m_goblinSpawnPos);
	m_enemies[1]->Init(m_warriorSpawnPos);
	m_enemies[2]->Init(m_dragonSpawnPos);
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
/*
void Dungeon::MapInit()
{
	LoadMap();
	Init();
}

void Dungeon::Update(Character& character)
{
	if (m_isAnyEnemyAlive)
	{
		TryOpenGate(character.GetEveryPossibleMovement());
		AttackCharacter(character);
		AttackOpponent(character);
		MakeEnemiesMove(character.getPosition());
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

void Dungeon::TryOpenGate(const std::vector<sf::Vector2f>& characterPositions)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		for (auto nextPos : characterPositions)
		{
			if (auto collisionSquare = GetCollisionSquare(nextPos, { CellState::Gate }))
			{
				auto [x, y] = collisionSquare.value();
				Open(y, x);
				break;
			}
		}
	}
}

void Dungeon::AttackCharacter(Character& character)
{
	sf::Vector2f characterPos = character.getPosition();
	if (m_goblin.Attack(character) && m_isGoblinAlive)
	{
		character.LossHp(m_goblin.GetAttackDamage() * character::damageTakenScaling);
	}
	else if (m_warrior.Attack(character) && m_isWarriorAlive)
	{
		character.LossHp(m_warrior.GetAttackDamage() * character::damageTakenScaling);
	}
	else if (m_dragon.Attack(character) && m_isDragonAlive)
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

void Dungeon::MakeEnemiesMove(const sf::Vector2f& characterPos)
{
	if (m_isGoblinAlive)
	{
		m_goblin.MakeMove(characterPos, m_rawMap);
	}
	if (m_isWarriorAlive)
	{
		m_warrior.MakeMove(characterPos, m_rawMap);
	}
	if (m_isDragonAlive)
	{
		m_dragon.MakeMove(characterPos, m_rawMap);
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
*/