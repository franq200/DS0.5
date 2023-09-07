#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <set>

using DirectionResult = std::optional< std::vector<sf::Vector2f>>;

class AStar
{
public:
	std::vector<sf::Vector2f> FindShortestPath(const std::pair <std::size_t, size_t>& characterIndex, const std::pair <std::size_t, size_t>& enemyIndex, const std::vector<std::vector<bool>>& map);
private:
	struct AStarData
	{
		double m_totalCost = std::numeric_limits<double>::max();
		double m_moveCost = 0.0;
		double m_distanceCost = std::numeric_limits<double>::max();
		std::pair <std::size_t, std::size_t> m_parentPos = { std::numeric_limits<std::size_t>::max(), std::numeric_limits<std::size_t>::max() };
		std::pair <std::size_t, std::size_t> m_pos = { 0, 0 };

		bool operator<(const AStarData& first) const { return first.m_totalCost < m_totalCost; }
	};
	std::set <AStarData> m_openList;

	DirectionResult ChooseDirection(const AStarData& currentData, 
															  std::vector<std::vector<AStarData>>& data, 
															  const std::pair<std::size_t, size_t>& characterIndex, 
															  const std::pair<std::size_t, size_t>& enemyIndex, 
															  const std::vector<std::vector<bool>>& map);

	bool CheckEndPos(std::vector<std::vector<AStarData>>& data, std::pair<int, int> endPos, std::pair<int, int> movePos, const AStarData& currentData, std::pair<int, int> currentPos, std::vector<std::vector<bool>> map);
	std::vector<sf::Vector2f> GetResult(std::vector<std::vector<AStarData>>& data, std::pair <std::size_t, size_t> characterIndex, std::pair <std::size_t, size_t> enemyIndex);
};
