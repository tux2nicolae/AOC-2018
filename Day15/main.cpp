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

using namespace std;

#include "../AOCLib/src/Algorithm.h"
#include "../AOCLib/src/Math.h"
#include "../AOCLib/src/Time.h"
#include "../AOCLib/src/FStreamReader.h"
#include "../AOCLib/src/FStreamWriter.h"
#include "../AOCLib/src/Examples.h"

using namespace AOC;

enum class Cell{wall = 0, free, elf, goblin};


struct Unit
{
  enum class Type {elf, goblin};

  Type type;
  int x{0};
  int y{0};

  int points{ 200 };
  int dead{false};

  bool operator < (const Unit& second) const
  {
    if (x < second.x)
      return true;
    else if (x == second.x)
      return y < second.y;

    return false;
  }
};

//----------------------------------------------------------------------------

int main()
{
  ifstream in("D:\\AOC-2018\\Day15\\Day15.in");
  ofstream out("D:\\AOC-2018\\Day15\\Day15.out");
  assert(in.good());
  assert(out.good());

  FStreamReader reader(in);
  auto map = reader.ReadVectorOfWords();

  // read data
  vector<Unit> units;
  for (int i = 0; i < map.size(); ++i)
  {
    auto & row = map[i];
    for (int j = 0; j < row.size(); j++)
    {
      auto & x = row[j];
      if (x == 'G')
      {
        units.push_back(Unit{ Unit::Type::goblin, i, j });
      }
      else if (x == 'E')
      {
        units.push_back(Unit{ Unit::Type::elf, i, j });
      }
    }
  }

  auto backupmap = map;
  auto backupunits = units;

  auto getEnemiesInRange = [&](Unit & unit)
  {
    static const int directionX[4] = { -1,  0, 0, 1 };
    static const int directionY[4] = {  0, -1, 1, 0 };

    vector<Coordonate> enemiesInRange;

    for (int i = 0; i < 4; ++i)
    {
      int x = unit.x + directionX[i];
      int y = unit.y + directionY[i];

      auto c = map[x][y];
      if (unit.type == Unit::Type::elf && c == 'G')
      {
        enemiesInRange.push_back(Coordonate{ x, y });
      }

      if (unit.type == Unit::Type::goblin && c == 'E')
        enemiesInRange.push_back(Coordonate{ x, y });
    }

    return enemiesInRange;
  };

  auto getFreeNeighbours = [&](Unit & unit)
  {
    static const int directionX[4] = { -1,  0, 0, 1 };
    static const int directionY[4] = { 0, -1, 1, 0 };

    vector<Coordonate> neighbours;
    for (int i = 0; i < 4; ++i)
    {
      int x = unit.x + directionX[i];
      int y = unit.y + directionY[i];

      auto c = map[x][y];
      if (c == '.')
        neighbours.push_back({ x, y });
    }

    sort(begin(neighbours), end(neighbours));
    return neighbours;
  };

  auto getTargetPositions = [&](Unit & unit)
  {
    vector<Coordonate> positions;

    for (auto & enemy : units)
    {
      if(enemy.dead)
        continue;

      if (unit.type != enemy.type)
      {
        auto enemyNeighbours = getFreeNeighbours(enemy);
        copy(enemyNeighbours.begin(), enemyNeighbours.end(), back_inserter(positions));
      }
    }

    sort(begin(positions), end(positions));
    return positions;
  };

  auto getNearestPositions = [&](Unit & unit)
  {
    vector<vector<int>> leeMap;
    for (auto & row : map)
    {
      vector<int> leeRow;
      for (auto & c : row)
      {
        leeRow.push_back(c == '.' ? 0 : -1);
      }

      leeMap.push_back(leeRow);
    }

    leeMap[unit.x][unit.y] = 1;
    auto distances = AOC::Lee({ Coordonate{unit.x, unit.y} }, leeMap).first;

    vector<pair<int, Coordonate>> reachablePositions;
    for (auto position : getTargetPositions(unit))
    {
      auto distance = distances[position.x][position.y];
      if (distance != 0)
        reachablePositions.push_back({ distance, position });
    }

    vector<Coordonate> nearestPositions;
    if (reachablePositions.empty())
      return nearestPositions;

    sort(begin(reachablePositions), end(reachablePositions));
    for (auto & position : reachablePositions)
    {
      if (position.first == reachablePositions.front().first)
        nearestPositions.push_back(position.second);
    }

    sort(begin(nearestPositions), end(nearestPositions));
    return nearestPositions;
  };

  auto getDirection = [&](Unit & unit)
  {
    Coordonate to{};

    auto nearestPositions = getNearestPositions(unit);
    if (nearestPositions.empty())
      return to;

    auto chosen = nearestPositions.front();
    int minDistance = 99999999;

    for (const auto & neighbour : getFreeNeighbours(unit))
    {
      vector<vector<int>> leeMap;
      for (auto & row : map)
      {
        vector<int> leeRow;
        for (auto & c : row)
        {
          leeRow.push_back(c == '.' ? 0 : -1);
        }

        leeMap.push_back(leeRow);
      }

      leeMap[neighbour.x][neighbour.y] = 1;
      auto distances = AOC::Lee({ Coordonate{neighbour.x, neighbour.y} }, leeMap).first;

      if (leeMap[chosen.x][chosen.y] && minDistance > distances[chosen.x][chosen.y])
      {
        minDistance = distances[chosen.x][chosen.y];
        to = neighbour;
      }
    }

    return to;
  };

  auto elvesCount = count_if(begin(units), end(units), [](auto & unit)
  {
    return unit.type == Unit::Type::elf && !unit.dead;
  });

  // part 2
  int elvespower = 4;

  for (; ; elvespower++)
  {
    int round = 0;
    int remainingPoints = 0;
    size_t remainingElves = 0;
    size_t remainingGoblins = 0;
    while(true)
    {
      sort(begin(units), end(units));

      for (auto & unit : units)
      {
        if(unit.dead)
          continue;

        // try to move
        if (getEnemiesInRange(unit).empty())
        {
          auto to = getDirection(unit);
          if (to.x && to.y)
          {
            map[unit.x][unit.y] = '.';
            map[to.x][to.y] = unit.type == Unit::Type::elf ? 'E' : 'G';

            unit.x = to.x;
            unit.y = to.y;
          }
        }

        // attack
        auto enemiesInRange = getEnemiesInRange(unit);
        if(!enemiesInRange.empty())
        {
          // sort by points
          vector<vector<Unit>::iterator> enemies;

          for (auto & enemyInRange : enemiesInRange)
          {
            auto it = find_if(begin(units), end(units), [&](auto & unit)
            {
              return !unit.dead && enemyInRange.x == unit.x && enemyInRange.y == unit.y;
            });

            assert(it != end(units));
            enemies.push_back(it);
          }
           
          sort(begin(enemies), end(enemies), [&](auto & firstIt, auto & secondIt){
            if (firstIt->points < secondIt->points)
              return true;
            else if (firstIt->points == secondIt->points)
              return *firstIt < *secondIt;

            return false;
          });

          auto it = enemies.front();
          assert(it->points > 0);

          if(unit.type == Unit::Type::goblin)
            it->points -= 3;
          else
            it->points -= elvespower;

          if (it->points <= 0)
          {
            it->dead = true;
            map[it->x][it->y] = '.';
          }
        }
      }

      // print
      // out << "After " << round << " round:" << endl;
      // 
      // for (auto & row : map)
      // {
      //   out << row << endl;
      // }
      // 
      // out << endl;
      // 
      // sort(begin(units), end(units));
      // 
      // for (auto & unit : units)
      // {
      //   if(unit.type == Unit::Type::goblin)
      //     out << "G(" << unit.points << ")" << endl;
      //   else
      //     out << "E(" << unit.points << ")" << endl;
      // }
      // 
      // out << endl;

      remainingElves = count_if(begin(units), end(units), [](auto & unit)
      {
        return unit.type == Unit::Type::elf && !unit.dead;
      });

      remainingGoblins = count_if(begin(units), end(units), [](auto & unit)
      {
        return unit.type == Unit::Type::goblin && !unit.dead;
      });


      if (!(remainingElves && remainingGoblins))
      {
        remainingPoints = accumulate(begin(units), end(units), 0, [](auto & s, auto & unit)
        {
          return s + (unit.dead ? 0 : unit.points);
        });

        break;
      }

      round++;
    }

    map = backupmap;
    units = backupunits;

    if (elvesCount == remainingElves)
    {
      cout << round * remainingPoints << endl;
      break;
    }
  }


  return 0;
}
