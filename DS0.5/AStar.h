#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

class AStar
{
public:
	std::vector<sf::Vector2f> FindShortestPath(const std::pair <std::size_t, size_t>& characterIndex, const std::pair <std::size_t, size_t>& goblinIndex, const std::vector<std::vector<bool>>& map);
private:
	struct AStarData
	{
		double m_totalCost = std::numeric_limits<double>::max();
		double m_moveCost = 0.0;
		double m_distanceCost = std::numeric_limits<double>::max();
		std::pair <std::size_t, std::size_t> m_parentPos = { -1, -1 };
		std::pair <std::size_t, std::size_t> m_pos = { 0, 0 };
	};
	std::vector<AStarData> m_openList;

	std::optional< std::vector<sf::Vector2f>> ChooseDirection(const AStarData& currentData, std::vector<std::vector<AStarData>>& data, const std::pair<std::size_t, size_t>& characterIndex, const std::pair<std::size_t, size_t>& GoblinIndex, const std::vector<std::vector<bool>>& map);

	bool CheckEndPos(std::vector<std::vector<AStarData>>& data, std::pair<int, int> endPos, std::pair<int, int> movePos, const AStarData& currentData, std::pair<int, int> currentPos, std::vector<std::vector<bool>> map);
	std::vector<sf::Vector2f> GetResult(std::vector<std::vector<AStarData>>& data, std::pair <std::size_t, size_t> characterIndex, std::pair <std::size_t, size_t> goblinIndex);
};
