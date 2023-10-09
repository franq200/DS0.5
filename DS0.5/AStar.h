#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <set>

using DirectionResult = std::optional< std::vector<sf::Vector2f>>;
using IndexPosition = std::pair<size_t, size_t>;

class AStar
{
public:
	std::vector<sf::Vector2f> FindShortestPath(const IndexPosition& characterIndex,
											   const IndexPosition& enemyIndex,
											   const std::vector<std::vector<bool>>& map);
private:
	struct AStarData
	{
		double m_totalCost = std::numeric_limits<double>::max();
		double m_moveCost = 0.0;
		double m_distanceCost = std::numeric_limits<double>::max();
		IndexPosition m_parentPos = { std::numeric_limits<std::size_t>::max(), std::numeric_limits<std::size_t>::max() };
		IndexPosition m_pos = { 0, 0 };

		bool operator<(const AStarData& first) const { return first.m_totalCost < m_totalCost; }
	};
	std::set <AStarData> m_openList;

	DirectionResult ChooseDirection(const AStarData& currentData,
									std::vector<std::vector<AStarData>>& data, 
									const IndexPosition& characterIndex,
									const IndexPosition& enemyIndex,
									const std::vector<std::vector<bool>>& map);

	bool CheckEndPos(std::vector<std::vector<AStarData>>& data,
					 const IndexPosition& endPos,
					 const IndexPosition& movePos,
					 const AStarData& currentData,
					 const IndexPosition& currentPos,
					 const std::vector<std::vector<bool>>& map);

	std::vector<sf::Vector2f> GetResult(std::vector<std::vector<AStarData>>& data,
										const IndexPosition& characterIndex,
										const IndexPosition& enemyIndex);
};
