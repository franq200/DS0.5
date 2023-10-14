#include "AStar.h"
#include <cassert>

struct AStarData
{
	double m_totalCost = std::numeric_limits<double>::max();
	double m_moveCost = 0.0;
	double m_distanceCost = std::numeric_limits<double>::max();
	IndexPosition m_parentPos = { std::numeric_limits<std::size_t>::max(), std::numeric_limits<std::size_t>::max() };
	IndexPosition m_pos = { 0, 0 };

	bool operator<(const AStarData& first) const { return first.m_totalCost < m_totalCost; }
};

struct ObjectsIndexes
{
	IndexPosition targetIndex;
	IndexPosition sourceIndex;
};

struct AlgorithmCache
{
	std::vector<std::vector<AStarData>>& aStarDataMap;
	std::set <AStarData>& openList;
	const std::vector<std::vector<bool>>& map;
};

struct IndexPositions
{
	IndexPosition endPos;
	IndexPosition movePos;
	IndexPosition currentPos;
};

std::vector<sf::Vector2f> GetResult(std::vector<std::vector<AStarData>>& data, const ObjectsIndexes& objectsIndexes)
{
	std::vector<sf::Vector2f> result;
	auto currentIndex = objectsIndexes.targetIndex;
	while (currentIndex != objectsIndexes.sourceIndex)
	{
		result.push_back({ static_cast<float>(currentIndex.first), static_cast<float>(currentIndex.second) });
		currentIndex = { data[currentIndex.first][currentIndex.second].m_parentPos.first, data[currentIndex.first][currentIndex.second].m_parentPos.second };
	}
	return result;
}

bool IsTargetPathReady(AlgorithmCache& algorithmCache, const IndexPositions& indexPositions, const AStarData& currentData)
{
	IndexPosition currentPos = indexPositions.currentPos;
	IndexPosition endPos = indexPositions.endPos;
	IndexPosition movePos = indexPositions.movePos;
	if (!(currentPos.first >= algorithmCache.aStarDataMap.size() || currentPos.first < 0 || currentPos.second >= algorithmCache.aStarDataMap[0].size() || currentPos.second < 0 || algorithmCache.map[currentPos.second][currentPos.first] == false))
	{
		if (movePos == endPos)
		{
			algorithmCache.aStarDataMap[movePos.first][movePos.second].m_parentPos = currentPos;
			return true;
		}
		else
		{
			double lastCost = algorithmCache.aStarDataMap[movePos.first][movePos.second].m_totalCost;
			if (currentData.m_moveCost + 1 + position::CalculateDistance(movePos, endPos) < lastCost)
			{
				algorithmCache.aStarDataMap[movePos.first][movePos.second].m_moveCost = currentData.m_moveCost;
				algorithmCache.aStarDataMap[movePos.first][movePos.second].m_distanceCost = position::CalculateDistance(movePos, endPos);
				algorithmCache.aStarDataMap[movePos.first][movePos.second].m_totalCost = algorithmCache.aStarDataMap[movePos.first][movePos.second].m_moveCost + algorithmCache.aStarDataMap[movePos.first][movePos.second].m_distanceCost;
				algorithmCache.aStarDataMap[movePos.first][movePos.second].m_parentPos = currentPos;

				algorithmCache.openList.insert(algorithmCache.aStarDataMap[movePos.first][movePos.second]);
			}
		}
	}
	return false;
}

DirectionResult ChooseDirection(const AStarData& currentData, AlgorithmCache& algorithmCache, const ObjectsIndexes& objectsIndexes)
{
	IndexPosition currentPos = currentData.m_pos;

	IndexPositions indexPositions{ objectsIndexes.targetIndex, { currentPos.first - 1, currentPos.second }, currentPos };
	if (IsTargetPathReady(algorithmCache, indexPositions, currentData))
	{
		return GetResult(algorithmCache.aStarDataMap, objectsIndexes);
	}

	indexPositions.movePos = { currentPos.first + 1, currentPos.second };
	if (IsTargetPathReady(algorithmCache, indexPositions, currentData))
	{
		return GetResult(algorithmCache.aStarDataMap, objectsIndexes);
	}

	indexPositions.movePos = { currentPos.first, currentPos.second - 1 };
	if (IsTargetPathReady(algorithmCache, indexPositions, currentData))
	{
		return GetResult(algorithmCache.aStarDataMap, objectsIndexes);
	}

	indexPositions.movePos = { currentPos.first, currentPos.second + 1 };
	if (IsTargetPathReady(algorithmCache, indexPositions, currentData))
	{
		return GetResult(algorithmCache.aStarDataMap, objectsIndexes);
	}
	return std::nullopt;
}

std::vector<std::vector<AStarData>> CreateAStarDataMap(const std::vector<std::vector<bool>>& map)
{
	std::vector<std::vector<AStarData>> aStarDataMap;
	aStarDataMap.resize(map.size());
	for (int i = 0; i < aStarDataMap.size(); ++i)
	{
		aStarDataMap[i].resize(map[i].size());
	}

	for (int x = 0; x < aStarDataMap.size(); ++x)
	{
		for (int y = 0; y < aStarDataMap[x].size(); ++y)
		{
			aStarDataMap[x][y].m_pos = { x, y };
		}
	}
	return aStarDataMap;
}

std::set<AStarData> CalculateFirstStep(const ObjectsIndexes& objectsIndexes, std::vector<std::vector<AStarData>>& aStarDataMap)
{
	const auto sourceXPos = objectsIndexes.sourceIndex.first;
	const auto sourceYPos = objectsIndexes.sourceIndex.second;
	aStarDataMap[sourceXPos][sourceYPos].m_distanceCost = position::CalculateDistance(objectsIndexes.targetIndex, objectsIndexes.sourceIndex);
	aStarDataMap[sourceXPos][sourceYPos].m_totalCost = aStarDataMap[sourceXPos][sourceYPos].m_moveCost + aStarDataMap[sourceXPos][sourceYPos].m_distanceCost;

	std::set <AStarData> openList;
	openList.insert(aStarDataMap[sourceXPos][sourceYPos]);
	return openList;
}

std::vector<sf::Vector2f> ProcessNextStep(AlgorithmCache& algorithmCache, const ObjectsIndexes& objectsIndexes)
{
	AStarData currentData = *algorithmCache.openList.begin();
	algorithmCache.openList.erase(algorithmCache.openList.begin());

	auto direction = ChooseDirection(currentData, algorithmCache, objectsIndexes);
	if (direction.has_value())
	{
		return direction.value();
	}
	return {};
}

std::vector<sf::Vector2f> aStar::FindShortestPath(const IndexPosition& targetIndex, const IndexPosition& sourceIndex, const std::vector<std::vector<bool>>& map)
{
	auto aStarDataMap = CreateAStarDataMap(map);
	ObjectsIndexes objectsIndexes{ targetIndex, sourceIndex };
	std::set <AStarData> openList = CalculateFirstStep(objectsIndexes, aStarDataMap);

	AlgorithmCache algorithmCache{ aStarDataMap, openList, map };
	std::vector<sf::Vector2f> resultPath = {};
	while (!openList.empty() && resultPath.empty())
	{
		resultPath = ProcessNextStep(algorithmCache, objectsIndexes);
	}
	return resultPath;
}
