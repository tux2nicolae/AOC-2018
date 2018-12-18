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

//----------------------------------------------------------------------------

vector<Coordonate> GetNeighbours(vector<string> & map, int ax, int ay)
{
  static const int directionX[8] = { -1,  0, 0, 1, 1, -1, -1, 1 };
  static const int directionY[8] = { 0, -1, 1, 0, 1, -1, 1, -1 };

  vector<Coordonate> neighbours;

  for (int i = 0; i < 8; ++i)
  {
    int x = ax + directionX[i];
    int y = ay + directionY[i];

    if (x < 0 || y < 0 || x >= map.size() || y >= map[0].size())
      continue;

    neighbours.push_back({ x, y });
  }

  return neighbours;
}

int main()
{
  ifstream in("D:\\AOC-2018\\Day18\\Day18.in");
  ofstream out("D:\\AOC-2018\\Day18\\Day18.out");
  assert(in.good());
  assert(out.good());

  FStreamReader reader(in);
  auto map = reader.ReadVectorOfWords();

  FStreamWriter writter(out);
  unordered_map<int, int> frequencies;

  // part 1
  int itPart1Count = 10;
  int part1ResourceValue = 0;

  // part 2
  int itCount = 1027;

  for (int i = 1; i <= itCount; ++i)
  {
    auto nextMap = map;
    for (int i = 0; i < nextMap.size(); i++)
    {
      for (int j = 0; j < nextMap[i].size(); j++)
      {
        auto neighbours = GetNeighbours(map, i, j);

        int trees = 0;
        int lumberyards = 0;
        for (auto & neighbour : neighbours)
        {
          if (map[neighbour.x][neighbour.y] == '|')
          {
            trees++;
          }
          else if (map[neighbour.x][neighbour.y] == '#')
          {
            lumberyards++;
          }
        }

        auto & acre = nextMap[i][j];
        if (acre == '.' && trees >= 3)
        {
          acre = '|';
        }
        else if (acre == '|' && lumberyards >= 3)
        {
          acre = '#';
        }
        else if (acre == '#')
        {
          if (lumberyards >= 1 && trees >= 1)
            acre = '#';
          else
            acre = '.';
        }
      }
    }

    map = nextMap;

    // part 1 / part two
    if (i == itPart1Count || i >= 1000)
    {
      int trees = 0;
      int lumberyards = 0;
      for (auto & line : map)
      {
        for (auto & x : line)
        {
          if (x == '|')
          {
            trees++;
          }
          else if (x == '#')
          {
            lumberyards++;
          }
        }
      }

      if (i == itPart1Count)
        part1ResourceValue = trees * lumberyards;
      else
        frequencies[trees * lumberyards] = i;
    }
  }

  // part 2
  unordered_map<int, int> cicle;
  for (auto &[value, i] : frequencies)
    cicle[i] = value;

  cout << part1ResourceValue << " " << cicle[1000 + ((1000000000 - 1000) % 28)];
  return 0;
}
