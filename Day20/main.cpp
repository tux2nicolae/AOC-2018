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

Coordonate GetNextPosition(Coordonate currentPosition, char direction)
{
  switch (direction)
  {
  case 'N': currentPosition.x-=2; break;
  case 'E': currentPosition.y+=2; break;
  case 'S': currentPosition.x+=2; break;
  case 'W': currentPosition.y-=2; break;
  default:
    assert(false);
    break;
  }

  return currentPosition;
}

vector<Coordonate> traverse(vector<vector<int>> & map, string & data, Coordonate currentPos, string::iterator & it)
{
  vector<Coordonate> allPositions;
  
  while (it != data.end() && *it != ')')
  {
    vector<Coordonate> traversedPositions;
    traversedPositions.push_back(currentPos);

    while (it != data.end() && *it != '|' && *it != ')')
    {
      string::iterator tempIt;
      for (auto & position : traversedPositions)
      {
        tempIt = it;
        while (tempIt != data.end() && *tempIt != '(' && *tempIt != '|' && *tempIt != ')')
        {
          auto nextPosition = GetNextPosition(position, *tempIt);
          map[nextPosition.x][nextPosition.y] = std::min(map[nextPosition.x][nextPosition.y],
            map[position.x][position.y] + 1);

          position = nextPosition;
          tempIt++;
        }
      }
      it = tempIt;

      if (it != data.end() && *it == '(')
      {
        vector<Coordonate> childPositions;

        for (auto position : traversedPositions)
        {
          tempIt = it;
          auto temp = traverse(map, data, position, ++tempIt);
          copy(begin(temp), end(temp), back_inserter(childPositions));
        }

        traversedPositions = childPositions;
        tempIt++;
      }
      it = tempIt;
    }

    if(it != data.end() && *it == '|')
    {
      it++;
      copy(begin(traversedPositions), end(traversedPositions), back_inserter(allPositions));
    }
  }

  return allPositions;
}

int main()
{
  ifstream in("D:\\AOC-2018\\Day20\\Day20.in");
  ofstream out("D:\\AOC-2018\\Day20\\Day20.out");
  assert(in.good());
  assert(out.good());

  string data;
  in >> data;

  auto inf = numeric_limits<int>::max();
  vector<vector<int>> map(10000, vector<int>(10000, inf));

  auto it = data.begin();

  map[500][500] = 0;
  auto positions = traverse(map, data, Coordonate{500, 500}, it);

  int m = 0; int s = 0;
  for (auto & line : map)
  {
    for (auto & row : line)
    {
      if (row != inf)
        m = std::max(m, row);

      if (row >= 1000 && row != inf)
        s++;
    }
  }

  cout << m << " " << s << endl;
  return 0;
}
