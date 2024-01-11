#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "Cell.h"
#include "Helper.h"

class Character;

class Map
{
public:
	virtual void MapInit() = 0;
	virtual void Update(Character& character);
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Restart();
	const sf::Vector2f& GetCharacterSpawnPos() const;
	std::optional<std::pair<float, float>> GetCollisionSquare(const sf::Vector2f& posAfterMove, const std::vector<CellState>& forbiddenStates) const;
	virtual void MakeEnemiesMove(const sf::Vector2f& characterPos);
protected:
	virtual void LoadMap() = 0;
	virtual void Init();
	void DrawMap(sf::RenderWindow& window);

	bool IsCollisionWithCell(const sf::Vector2f& cellPos, const sf::Vector2f& characterPos) const;
	std::vector<std::vector<Cell>> m_map;
	sf::Vector2f m_characterSpawnPos;
	std::vector<std::vector<bool>> m_rawMap;
};

