#pragma once
#include "Map.h"
#include "Character.h"

class Village : public Map
{
public:
	void MapInit() override;
	void Update(Character& character) override;
	void Draw(sf::RenderWindow& window) override;
	void Restart() override;
private:
	void LoadMap() override;
	void Init() override;
};

