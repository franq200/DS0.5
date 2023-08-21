#include "aster2.h"
#include "Helper.h"
#include <cassert>

std::vector<sf::Vector2f> AStar::FindShortestPath(const std::pair<std::size_t, size_t>& pacmanIndex, const std::pair<std::size_t, size_t>& ghostIndex, const std::vector<std::vector<bool>>& map)
{
	m_openList.clear();
	assert(m_openList.empty());

	std::vector<std::vector<AStarData>> data;
	data.resize(map.size());
	for (int i = 0; i < data.size(); ++i)
	{
		data[i].resize(map[i].size());
	}

	for (int x = 0; x < data.size(); ++x)
	{
		for (int y = 0; y < data[x].size(); ++y)
		{
			data[x][y].m_pos = { x, y };
		}
	}

	data[ghostIndex.first][ghostIndex.second].m_distanceCost = position::CalculateDistance(pacmanIndex, ghostIndex);
	data[ghostIndex.first][ghostIndex.second].m_totalCost = data[ghostIndex.first][ghostIndex.second].m_moveCost + data[ghostIndex.first][ghostIndex.second].m_distanceCost;
	m_openList.insert(data[ghostIndex.first][ghostIndex.second]);

	while (!m_openList.empty())
	{
		//std::sort(m_openList.begin(), m_openList.end(), [](const auto& first, const auto& second) {return first.m_totalCost > second.m_totalCost; }); // std::set O(n2), O(n), O(logn), O(1)
		AStarData currentData = *m_openList.begin();
		m_openList.erase(m_openList.begin());

		std::optional< std::vector<sf::Vector2f>> direction = ChooseDirection(currentData, data, pacmanIndex, ghostIndex, map);
		if (direction.has_value())
		{
			return direction.value();
		}
	}

	std::cout << "AStart algorithm return empty path";
	return {};
}

std::optional< std::vector<sf::Vector2f>> AStar::ChooseDirection(const AStarData& currentData, std::vector<std::vector<AStarData>>& data, const std::pair<std::size_t, size_t>& pacmanIndex, const std::pair<std::size_t, size_t>& ghostIndex, const std::vector<std::vector<bool>>& map)
{
	std::pair<int, int> currentPos = currentData.m_pos;

	std::pair<int, int> leftPos = { currentPos.first - 1, currentPos.second };
	if (!CheckEndPos(data, pacmanIndex, leftPos, currentData, currentPos, map))
	{
		return GetResult(data, pacmanIndex, ghostIndex);
	}

	std::pair<int, int> rightPos = { currentPos.first + 1, currentPos.second };
	if (!CheckEndPos(data, pacmanIndex, rightPos, currentData, currentPos, map))
	{
		return GetResult(data, pacmanIndex, ghostIndex);
	}

	std::pair<int, int> upPos = { currentPos.first, currentPos.second - 1 };
	if (!CheckEndPos(data, pacmanIndex, upPos, currentData, currentPos, map))
	{
		return GetResult(data, pacmanIndex, ghostIndex);
	}

	std::pair<int, int> downPos = { currentPos.first, currentPos.second + 1 };
	if (!CheckEndPos(data, pacmanIndex, downPos, currentData, currentPos, map))
	{
		return GetResult(data, pacmanIndex, ghostIndex);
	}
	return std::nullopt;
}

bool AStar::CheckEndPos(std::vector<std::vector<AStarData>>& data, std::pair<int, int> endPos, std::pair<int, int> movePos, const AStarData& currentData, std::pair<int, int> currentPos, std::vector<std::vector<bool>> map)
{
	if (!(currentPos.first >= data.size() || currentPos.first < 0 || currentPos.second >= data.size() || currentPos.second < 0 || map[currentPos.second][currentPos.first] == true))
	{
		if (movePos == endPos)
		{
			data[movePos.first][movePos.second].m_parentPos = currentPos;
			return false;
		}
		else
		{
			double lastCost = data[movePos.first][movePos.second].m_totalCost;
			if (currentData.m_moveCost + 1 + position::CalculateDistance(movePos, endPos) < lastCost)
			{
				data[movePos.first][movePos.second].m_moveCost = currentData.m_moveCost;
				data[movePos.first][movePos.second].m_distanceCost = position::CalculateDistance(movePos, endPos);
				data[movePos.first][movePos.second].m_totalCost = data[movePos.first][movePos.second].m_moveCost + data[movePos.first][movePos.second].m_distanceCost;
				data[movePos.first][movePos.second].m_parentPos = currentPos;

				m_openList.insert(data[movePos.first][movePos.second]);
			}
		}
	}
	return true;
}

std::vector<sf::Vector2f> AStar::GetResult(std::vector<std::vector<AStarData>>& data, std::pair<std::size_t, size_t> pacmanIndex, std::pair<std::size_t, size_t> ghostIndex)
{
	std::vector<sf::Vector2f> result;

	auto currentIndex = pacmanIndex;

	while (currentIndex != ghostIndex)
	{
		result.push_back({ static_cast<float>(currentIndex.first), static_cast<float>(currentIndex.second) });
		currentIndex = { data[currentIndex.first][currentIndex.second].m_parentPos.first, data[currentIndex.first][currentIndex.second].m_parentPos.second };
	}
	return result;
}
