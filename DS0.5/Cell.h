#pragma once
#include <SFML/Graphics.hpp>
#include "Helper.h"

struct Textures
{
	sf::Texture wall;
	sf::Texture ground;
};

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
	Cell(const sf::Vector2f& pos, const CellState& state);
	void SetTextures(const Textures& textures);
	CellState GetState() const;
	void ChangeState(CellState newState);
private:
	void SetTexture();
	CellState m_state;
	Textures m_textures;
};