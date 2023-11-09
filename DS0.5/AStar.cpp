#include "AStar.h"
#include <cassert>
#include <set>

struct AStarData
{
	size_t m_totalCost = std::numeric_limits<size_t>::max();
	size_t m_moveCost = 0;
	size_t m_distanceCost = std::numeric_limits<size_t>::max();
	IndexPosition m_parentPos = { std::numeric_limits<std::size_t>::max(), std::numeric_limits<std::size_t>::max() };
	IndexPosition m_pos = { 0, 0 };

	bool operator<(const AStarData& first) const { return first.m_totalCost > m_totalCost; }
};

struct ObjectsIndexes
{
	IndexPosition targetIndex;
	IndexPosition sourceIndex;
};

struct AlgorithmCache
{
	std::vector<std::vector<AStarData>>& aStarDataMap;
	std::multiset <AStarData>& openList;
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

size_t CalculateDistance(IndexPosition start, IndexPosition end)
{
	int xPos = std::abs(static_cast<int>(start.first - end.first));
	int yPos = std::abs(static_cast<int>(start.second - end.second));
	return static_cast<size_t>(xPos + yPos);
}

bool IsStepPossible(const IndexPosition& currentPos, const AlgorithmCache& algorithmCache)
{
	bool isCurrentXPosCorrect = !(currentPos.first >= algorithmCache.aStarDataMap.size()) && !(currentPos.first < 0);
	bool isCurrentYPosCorrect = !(currentPos.second >= algorithmCache.aStarDataMap[0].size()) && !(currentPos.second < 0);
	bool isCellMoveable = algorithmCache.map[currentPos.second][currentPos.first];
	return isCurrentXPosCorrect && isCurrentYPosCorrect && isCellMoveable;
}

bool IsTargetPathReady(AlgorithmCache& algorithmCache, const IndexPositions& indexPositions, const AStarData& currentData)
{
	IndexPosition currentPos = indexPositions.currentPos;
	IndexPosition endPos = indexPositions.endPos;
	IndexPosition movePos = indexPositions.movePos;
	if (IsStepPossible(currentPos, algorithmCache))
	{
		if (movePos == endPos)
		{
			algorithmCache.aStarDataMap[movePos.first][movePos.second].m_parentPos = currentPos;
			return true;
		}
		else
		{
			size_t lastCost = algorithmCache.aStarDataMap[movePos.first][movePos.second].m_totalCost;
			if (currentData.m_moveCost + CalculateDistance(movePos, endPos) + 1 < lastCost)
			{
				algorithmCache.aStarDataMap[movePos.first][movePos.second].m_moveCost = currentData.m_moveCost;
				algorithmCache.aStarDataMap[movePos.first][movePos.second].m_distanceCost = CalculateDistance(movePos, endPos);
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
	indexPositions.movePos = { currentPos.first - 1, currentPos.second };
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

std::multiset<AStarData> CalculateFirstStep(const ObjectsIndexes& objectsIndexes, std::vector<std::vector<AStarData>>& aStarDataMap)
{
	const auto sourceXPos = objectsIndexes.sourceIndex.first;
	const auto sourceYPos = objectsIndexes.sourceIndex.second;
	aStarDataMap[sourceXPos][sourceYPos].m_distanceCost = CalculateDistance(objectsIndexes.targetIndex, objectsIndexes.sourceIndex);
	aStarDataMap[sourceXPos][sourceYPos].m_totalCost = aStarDataMap[sourceXPos][sourceYPos].m_moveCost + aStarDataMap[sourceXPos][sourceYPos].m_distanceCost;

	std::multiset<AStarData> openList;
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
	std::multiset <AStarData> openList = CalculateFirstStep(objectsIndexes, aStarDataMap);

	AlgorithmCache algorithmCache{ aStarDataMap, openList, map };
	std::vector<sf::Vector2f> resultPath = {};
	while (!openList.empty() && resultPath.empty())
	{
		resultPath = ProcessNextStep(algorithmCache, objectsIndexes);
	}
	return resultPath;
}
