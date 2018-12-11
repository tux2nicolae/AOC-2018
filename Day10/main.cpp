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

int main()
{
  ifstream in("D:\\AOC-2018\\Day10\\Day10.in");  
  ofstream out("D:\\AOC-2018\\Day10\\Day10.out");
  assert(in.good());

  struct Point 
  {
    pair<int, int> position{};
    pair<int, int> velocity{};
  };

  vector<Point> points;

  pair<int, int> position{};
  pair<int, int> velocity{};

  //int offset = 70000;
  while (in >> position.first >> position.second>> velocity.first>> velocity.second)
  {
    // position.first += offset;
    // position.second += offset;

    points.push_back({ position, velocity });
  }



  bool run = true;
  
  int second = 0;

  do
  {
    ++second;
    for (auto & point : points)
    {
      // m[point.position.first][point.position.second] = false;

      point.position.first += point.velocity.first;
      point.position.second += point.velocity.second;

      //m[position.first][position.second] = true;
    }

    for (auto & point1 : points)
    {
      bool allpoints = true;
      for (auto & point2 : points)
      {
        if (!(ManhattenDistance(point1.position.first, point1.position.second, point2.position.first, point2.position.second) < 70))
        {
          allpoints = false;
          break;
        }
      }

      if (!allpoints)
        break;

      run = false;
    }

  } while (run);

  second;


  for (int i = 100; i < 400 ; i++)
  {
    for (int j = 100; j < 400; j++)
    {
      auto it = find_if(begin(points), end(points), [=](auto & point) 
      {
        return point.position.first == j && point.position.second == i;
      });

      if (it != end(points))
      {
        out << '*';
      }
      else
      {
        out << ' ';
      }
    }
    out << endl;
  }

  return 0;
}
