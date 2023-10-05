#include "Cell.h"
#include "Helper.h"

Cell::Cell(const sf::Vector2f& pos, CellState state) :
m_state(state)
{
	setSize({size::cellSize, size::cellSize});
	setPosition(pos);

	switch (state)
	{
	case CellState::Empty:
		setFillColor(sf::Color::Green);
		break;
	case CellState::Filled:
		setFillColor(sf::Color::Red);
		break;
	case CellState::Teleport:
		setFillColor(sf::Color::Blue);
		break;
	case CellState::Gate:
		setFillColor(sf::Color::Yellow);
		break;
	}
}

CellState Cell::GetState() const
{
	return m_state;
}

void Cell::ChangeState(CellState newState)
{
	m_state = newState;
	setFillColor(sf::Color::Green);
}
