#pragma once
#include "Map.h"
#include "Character.h"

class Village : public Map
{
public:
	void MapInit() override;
	void Draw(sf::RenderWindow& window) override;
private:
	void SetTextures() override;
	void LoadMap() override;
};