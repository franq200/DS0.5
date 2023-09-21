#include "Cell.h"

Cell::Cell(const sf::Vector2f& size, const sf::Vector2f& pos, CellState state) :
m_state(state)
{
	setSize(size);
	setPosition(pos);

	switch (state)
	{
	case CellState::Empty:
		setFillColor(sf::Color::Green);
	case CellState::Filled:
		setFillColor(sf::Color::Red);
	case CellState::Teleport:
		setFillColor(sf::Color::Blue);
	case CellState::Gate:
		setFillColor(sf::Color::Yellow);
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
