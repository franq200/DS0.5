#include "Cell.h"
#include "Helper.h"

Cell::Cell(const sf::Vector2f& pos, const CellState& state) :
m_state(state)
{
	setSize({size::cellSize, size::cellSize});
	setPosition(pos);
}

void Cell::SetTextures(const Textures& textures)
{
	m_textures.ground = textures.ground;
	m_textures.wall = textures.wall;
	SetTexture();
}

CellState Cell::GetState() const
{
	return m_state;
}

void Cell::ChangeState(CellState newState)
{
	m_state = newState;
	SetTexture();
}

void Cell::SetTexture()
{
	switch (m_state)
	{
	case CellState::Empty:
		setTexture(&(m_textures.ground));
		break;
	case CellState::Filled:
		setTexture(&(m_textures.wall));
		break;
	case CellState::Teleport:
		setFillColor(sf::Color::Blue);
		break;
	case CellState::CloseGate:
		setFillColor(sf::Color::Yellow);
		break;
	case CellState::OpenGate:
		setTexture(&textures::dirt);
	}
}
