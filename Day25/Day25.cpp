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
#include <regex>

using namespace std;

int Abs2(const int x)
{
  if (x > 0)
    return x;

  return -x;
};

//----------------------------------------------------------------------------

struct Point
{
  int id{};

  int x{};
  int y{};
  int z{};
  int t{};

  int neighbours{};
};

int Distance(const Point & first, const Point & second)
{
  return Abs2(first.x - second.x) + Abs2(first.y - second.y) + Abs2(first.z - second.z) + Abs2(first.t - second.t);
};

vector<Point> stars;

bool intersects[1500][1500];
bool visited[1500];

void dfs(int currentNode) 
{
  visited[currentNode] = true;

  for (auto & star : stars)
  {
    if (intersects[currentNode][star.id] && !visited[star.id])
    {
      visited[star.id] = true;
      dfs(star.id);
    }
  }
}

int GetConexComponents() {
  int components = 0;
  for (auto & star : stars)
  {
    if (!visited[star.id])
    {
      dfs(star.id);
      components++;
    }
  }

  return components;
}

int main()
{
  ifstream in("C:\\Users\\Telechi\\Desktop\\Day25.in");
  ofstream out("C:\\Users\\Telechi\\Desktop\\Day25.out");
  assert(in.good());
  assert(out.good());

  int id = 0;

  // read data
  string line;
  while (getline(in, line))
  {
    smatch match;
    regex_match(line, match, regex("(.*),(.*),(.*),(.*)"));
    assert(match.size() == 5);

    Point star;
    star.id = id++;
    star.x = stoi(match[1]);
    star.y = stoi(match[2]);
    star.z = stoi(match[3]);
    star.t = stoi(match[4]);

    stars.push_back(star);

  }

  // calculate intersections
  for (auto & currentStar : stars)
  {
    int intersections = 0;
    for (auto & neighbourStar : stars)
    {
      auto d = Distance(currentStar, neighbourStar);
      if (d <= 3)
      {
        intersections++;
        intersects[currentStar.id][neighbourStar.id] = true;
      }
    }

    currentStar.neighbours = intersections;
  }

  cout << GetConexComponents();
  return 0;
}
