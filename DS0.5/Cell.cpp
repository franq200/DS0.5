#include "Cell.h"

Cell::Cell(sf::Vector2f size, sf::Vector2f pos, CellState state) :
m_state(state)
{
	setSize(size);
	setPosition(pos);
	if (state == CellState::Empty)
	{
		setFillColor(sf::Color::Green);
	}
	else if (state == CellState::Filled)
	{
		setFillColor(sf::Color::Red);
	}
	else if (state == CellState::Teleport)
	{
		setFillColor(sf::Color::Blue);
	}
	else if (state == CellState::Gate)
	{
		setFillColor(sf::Color::Yellow);
	}
}

CellState Cell::GetState() const
{
	return m_state;
}

void Cell::ChangeState(const CellState& newState)
{
	m_state = newState;
	setFillColor(sf::Color::Green);
}
