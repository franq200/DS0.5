#pragma once
#include <SFML/Graphics.hpp>
#include "Helper.h"

enum class CellState : uint8_t
{
	Empty = 0,
	Filled,
	Teleport,
	CloseGate,
	OpenGate
};

class Cell : public sf::RectangleShape
{
public:
	Cell() = default;
	Cell(const sf::Vector2f& pos, const CellState& state, const sf::Texture* texture);
	CellState GetState() const;
	void SetCellOpen();
	void SetCellClosed();
private:
	CellState m_state;
};