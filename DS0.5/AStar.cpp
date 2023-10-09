#include "AStar.h"
#include "Helper.h"
#include <cassert>

std::vector<sf::Vector2f> AStar::FindShortestPath(const IndexPosition& characterIndex, const IndexPosition& enemyIndex, const std::vector<std::vector<bool>>& map)
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

	data[enemyIndex.first][enemyIndex.second].m_distanceCost = position::CalculateDistance(characterIndex, enemyIndex);
	data[enemyIndex.first][enemyIndex.second].m_totalCost = data[enemyIndex.first][enemyIndex.second].m_moveCost + data[enemyIndex.first][enemyIndex.second].m_distanceCost;
	m_openList.insert(data[enemyIndex.first][enemyIndex.second]);

	while (!m_openList.empty())
	{
		AStarData currentData = *m_openList.begin();
		m_openList.erase(m_openList.begin());

		auto direction = ChooseDirection(currentData, data, characterIndex, enemyIndex, map);
		if (direction.has_value())
		{
			return direction.value();
		}
	}
	return {};
}

DirectionResult AStar::ChooseDirection(const AStarData& currentData, std::vector<std::vector<AStarData>>& data, const IndexPosition& characterIndex, const IndexPosition& enemyIndex, const std::vector<std::vector<bool>>& map)
{
	IndexPosition currentPos = currentData.m_pos;

	IndexPosition leftPos = { currentPos.first - 1, currentPos.second };
	if (!CheckEndPos(data, characterIndex, leftPos, currentData, currentPos, map))
	{
		return GetResult(data, characterIndex, enemyIndex);
	}

	IndexPosition rightPos = { currentPos.first + 1, currentPos.second };
	if (!CheckEndPos(data, characterIndex, rightPos, currentData, currentPos, map))
	{
		return GetResult(data, characterIndex, enemyIndex);
	}

	IndexPosition upPos = { currentPos.first, currentPos.second - 1 };
	if (!CheckEndPos(data, characterIndex, upPos, currentData, currentPos, map))
	{
		return GetResult(data, characterIndex, enemyIndex);
	}

	IndexPosition downPos = { currentPos.first, currentPos.second + 1 };
	if (!CheckEndPos(data, characterIndex, downPos, currentData, currentPos, map))
	{
		return GetResult(data, characterIndex, enemyIndex);
	}
	return std::nullopt;
}

bool AStar::CheckEndPos(std::vector<std::vector<AStarData>>& data, const IndexPosition& endPos, const IndexPosition& movePos, const AStarData& currentData, const IndexPosition& currentPos, const std::vector<std::vector<bool>>& map)
{
	if (!(currentPos.first >= data.size() || currentPos.first < 0 || currentPos.second >= data[0].size() || currentPos.second < 0 || map[currentPos.second][currentPos.first] == false))
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

std::vector<sf::Vector2f> AStar::GetResult(std::vector<std::vector<AStarData>>& data, const IndexPosition& characterIndex, const IndexPosition& enemyIndex)
{
	std::vector<sf::Vector2f> result;
	auto currentIndex = characterIndex;
	while (currentIndex != enemyIndex)
	{
		result.push_back({ static_cast<float>(currentIndex.first), static_cast<float>(currentIndex.second) });
		currentIndex = { data[currentIndex.first][currentIndex.second].m_parentPos.first, data[currentIndex.first][currentIndex.second].m_parentPos.second };
	}
	return result;
}
