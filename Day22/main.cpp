#define _CRT_SECURE_NO_WARNINGS

/**
* Advent of code 2018
* @author : Nicolae Telechi
*/
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <queue>
#include <stack>
#include <numeric>
#include <set>
#include <bitset>

using namespace std;

#include "../AOCLib/src/Algorithm.h"
#include "../AOCLib/src/Math.h"
#include "../AOCLib/src/Time.h"
#include "../AOCLib/src/FStreamReader.h"
#include "../AOCLib/src/FStreamWriter.h"
#include "../AOCLib/src/Examples.h"

using namespace AOC;

enum RegionType
{
	rocky = 0,  // .
	wet = 1,    // =
	narrow = 2, // |
};

enum ToolType
{
	neither = 0,
	torch = 1,
	gear = 2,
};

struct Distance
{
	map<ToolType, int> cost;
};

constexpr int MOD = 20183;
constexpr int depth = 3339;
Coordonate target{ 10, 715 };

constexpr int maxX = 100;
constexpr int maxY = 1000;

int erosionMap[maxX + 1][maxY + 1]{};
Distance distances[maxX + 1][maxY + 1]{};

int GetErosionLevel(const Coordonate & point)
{
	int geologicalIndex = 0;

	if (point.x == 0 && point.y == 0)
	{
		geologicalIndex = 0;
	}
	else if (point.x == target.x && point.y == target.y)
	{
		geologicalIndex = 0;
	}
	else if (point.y == 0)
	{
		geologicalIndex = (point.x * 16807); // todo
	}
	else if (point.x == 0)
	{
		geologicalIndex = (point.y * 48271);
	}
	else
	{
		geologicalIndex = (erosionMap[point.x][point.y - 1] * erosionMap[point.x - 1][point.y]) % MOD;
	}


	return (geologicalIndex + depth) % MOD;
}

RegionType GetRegionType(const Coordonate & point)
{
	return RegionType(erosionMap[point.x][point.y] % 3);
}

vector<ToolType> GetTools(RegionType region)
{
	switch (region)
	{
	case rocky:
		return { gear, torch };
	case wet:
		return { gear, neither };
	case narrow:
		return { torch, neither };
	default:
		assert(false);
		break;
	}

	return {};
}

//----------------------------------------------------------------------------

int main()
{
	int riskLevel = 0;
	for (int i = 0; i <= maxX; i++)
	{
		for (int j = 0; j <= maxY; j++)
		{
			auto erosionLevel = GetErosionLevel(Coordonate{ i, j });
			erosionMap[i][j] = erosionLevel;

			if(i <= target.x && j <= target.y)
				riskLevel += GetRegionType(Coordonate{ i, j });
		}
	}

	// part 1
	cout << riskLevel << endl;

	queue<Coordonate> unvisited;
	unvisited.push(Coordonate{ 0, 0 });
	distances[0][0].cost[torch] = 1;
	distances[0][0].cost[gear] = 8;

	auto isInBoundary = [&](const Coordonate & to)-> bool
	{
		return !(to.x < 0 || to.y < 0 || to.x > maxX || to.y > maxY);
	};

	// run
	while (!unvisited.empty())
	{
		auto from = unvisited.front();
		unvisited.pop();

		static const int directionX[4] = { -1,  0, 1, 0 };
		static const int directionY[4] = { 0,  1, 0, -1 };

		for (int i = 0; i < 4; ++i)
		{
			Coordonate to;
			to.x = from.x + directionX[i];
			to.y = from.y + directionY[i];

			if (!isInBoundary(to))
				continue;

			auto nextTools = GetTools(GetRegionType(to));

			assert(nextTools.size() == 2);
			assert((from.x == 0 && from.y == 0) || distances[from.x][from.y].cost.size() == 2);

			for (auto &[currentTool, currentCost] : distances[from.x][from.y].cost)
			{
				if (find(begin(nextTools), end(nextTools), currentTool) == end(nextTools))
					continue;
				
				for (auto & nextTool : nextTools)
				{
					int cost = currentCost + 1;
					if (currentTool != nextTool)
						cost += 7;

					// set to infinite cost
					auto & nextCost = distances[to.x][to.y].cost[nextTool];
					if (nextCost == 0)
						nextCost = numeric_limits<int>::max();

					if (cost < nextCost)
					{
						nextCost = cost;
						unvisited.push(to);
					}
				}
			}
		}
	}

	auto targetCost = distances[target.x][target.y].cost;
	cout << targetCost[torch] - 1;

	return 0;
}
