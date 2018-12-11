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

int main2()
{
  ifstream in("D:\\AOC-2018\\Day7\\Day7.in");
  ofstream out("D:\\AOC-2018\\Day7\\Day7.out");

  assert(in.good());
  assert(out.good());

  struct Node
  {
    int dependencies{};

    int cost;
    vector<char> edges;
  };

  struct Element
  {
    char id{};
    vector<int>::iterator worker{};
  };

  unordered_map<char, Node> graph;

  string line;
  while (getline(in, line))
  {
    std::istringstream ss(line);

    pair<char, char> p;
    while (ss >> p.first >> p.second)
    {
      graph[p.first].edges.push_back(p.second);
      graph[p.second].dependencies++;
    }
  }

  const int offset = 60;
  const int maxWorkers = 60;
  vector<int> workers;// (5, 0);

  auto comparator = [](Element left, Element right) { return left.id > right.id; };
  priority_queue<Element, vector<Element>, decltype(comparator)> heap(comparator);

  for (auto & node : graph)
  {
    sort(begin(node.second.edges), end(node.second.edges), less<int>());
    graph[node.first].cost = (node.first + 60 - 'A' + 1);

    if (!node.second.dependencies)
    {
      // auto it = min_element(begin(workers), end(workers));
      // *it += offset + (node.first - 'A' + 1);

      workers.push_back(node.first);
      heap.push({ node.first, workers.end() });
    }
  }

  int s = 0;
  while (!heap.empty())
  {
    auto element = heap.top();
    heap.pop();

    cout << element.id;

    // calculate time cost
    int timecost = graph[element.id].cost;

    s += timecost;

    // update workers
    for (auto & id : workers)
      graph[id].cost = std::max(0, graph[id].cost - timecost);

    workers.erase(find(begin(workers), end(workers), element.id));

    for (auto & edge : graph[element.id].edges)
    {
      if (!(--graph[edge].dependencies))
      {
        // auto it = min_element(begin(workers), end(workers));
        // *it += offset + (edge - 'A' + 1);

        workers.push_back(edge);
        if (workers.size() > 5)
          return false;

        heap.push({ edge, workers.end() });
      }
    }
  }

  cout << endl;
  cout << s;

  return 0;
}
