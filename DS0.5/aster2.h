#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>
#include <set>

class AStar
{
public:
	std::vector<sf::Vector2f> FindShortestPath(const std::pair <std::size_t, size_t>& pacmanIndex, const std::pair <std::size_t, size_t>& ghostIndex, const std::vector<std::vector<bool>>& map);
private:
	struct AStarData
	{
		double m_totalCost = std::numeric_limits<double>::max();
		double m_moveCost = 0.0; // g
		double m_distanceCost = std::numeric_limits<double>::max();
		std::pair <std::size_t, std::size_t> m_parentPos = { -1, -1 };
		std::pair <std::size_t, std::size_t> m_pos = { 0, 0 };
	};
	std::set < AStarData, decltype([](AStarData first, AStarData second) {return first.m_totalCost < second.m_totalCost; }) > m_openList;

	std::optional< std::vector<sf::Vector2f>> ChooseDirection(const AStarData& currentData, std::vector<std::vector<AStarData>>& data, const std::pair<std::size_t, size_t>& pacmanIndex, const std::pair<std::size_t, size_t>& ghostIndex, const std::vector<std::vector<bool>>& map);

	bool CheckEndPos(std::vector<std::vector<AStarData>>& data, std::pair<int, int> endPos, std::pair<int, int> movePos, const AStarData& currentData, std::pair<int, int> currentPos, std::vector<std::vector<bool>> map);
	std::vector<sf::Vector2f> GetResult(std::vector<std::vector<AStarData>>& data, std::pair <std::size_t, size_t> pacmanIndex, std::pair <std::size_t, size_t> ghostIndex);
};

