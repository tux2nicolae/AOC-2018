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

template<class T>
auto Solve(T & coordonates)
{
  vector<vector<int>> map;
  map.resize(500);
  for (auto & line : map)
    line.resize(500);


  int id = 0;
  for (auto & point : coordonates)
    map[point.x][point.y] = ++id;
  
  // run lee
  auto infinitePoints = AOC::Lee(coordonates, map);

  // get finite points
  vector<Coordonate> finitePoints;
  for (int i = 0; i < coordonates.size(); ++i)
  {
    if (!infinitePoints.count(i + 1))
      finitePoints.push_back(coordonates[i]);
  }

  // part 1
  vector<int> distances;
  for (auto & point : finitePoints)
  {
    auto id = map[point.x][point.y];

    distances.push_back(accumulate(begin(map), end(map), 0, [&](int s, const vector<int> & line) {
      return s + accumulate(begin(line), end(line), 0, [&](int s, const int & value)
      {
        return s + (value == id ? 1 : 0);
      });
    }));
  }
  
  auto it = std::max_element(begin(distances), end(distances));
  int maxDistance = *it;

  // part 2
  int sum = 0;
  for (int x1 = 0; x1 <= 1000; ++x1)
  {
    for (int y1 = 0; y1 <= 1000 ; ++y1)
    {
      int distance = 0;
      for (auto & [x2, y2] : coordonates)
        distance += ManhattenDistance(x1, y1, x2, y2);
  
      if (distance < 10000)
        sum++;
    }
  }

  return make_pair(maxDistance, sum);
}

int main()
{
  ifstream in("D:\\AOC-2018\\Day6\\Day6.in");
  ofstream out("D:\\AOC-2018\\Day6\\Day6.out");

  assert(in.good());
  assert(out.good());

  vector<Coordonate> coordonates;

  char discard;

  Coordonate point;
  while (in >> point.x >> discard >> point.y)
    coordonates.push_back(point);
 
  auto ret = 
    Solve(coordonates);

  out << ret.first << " " << ret.second;
  return 0;
}
