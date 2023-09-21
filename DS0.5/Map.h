#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Character.h"

class Map
{
public:
	virtual void MapInit() = 0;
	virtual void Update(Character& character) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Restart() = 0;
	const sf::Vector2f& GetCharacterSpawnPos() const;
	bool IsCollisionWithCharacter(const sf::Vector2f& posAfterMove, const std::vector<CellState>& forbiddenStates);
protected:
	virtual void LoadMap() = 0;
	virtual void Init() = 0;
	void DrawMap(sf::RenderWindow& window);

	bool IsCollisionWithCell(const sf::Vector2f& cellPos, const sf::Vector2f& characterPos);
	std::vector<std::vector<Cell>> m_map;
	sf::Vector2f m_characterSpawnPos;
	std::vector<std::vector<bool>> m_rawMap;
};

