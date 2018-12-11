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
    vector<char>::iterator worker{};
  };

  unordered_map<char, Node> graph;

  const int offset = 60;
  const int maxWorkers = 5;

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
  
  vector<char> workers (maxWorkers, 0);

  auto comparator = [](Element left, Element right) { return left.id > right.id; };
  priority_queue<Element, vector<Element>, decltype(comparator)> heap(comparator);

  priority_queue<int, vector<int>, greater<int>> work;
  for (auto & node : graph)
  {
    node.second.cost = (node.first + offset - 'A' + 1);

    sort(begin(node.second.edges), end(node.second.edges), less<int>());

    if (!node.second.dependencies)
    {
      // auto it = min_element(begin(workers), end(workers));
      // *it += offset + (node.first - 'A' + 1);

      work.push(node.first);
      heap.push({ node.first, workers.end() });
    }
  }


  int s = 0;
  while (!heap.empty())
  {
    // update workers
    for (auto & worker : workers)
    {
      if (!worker && !work.empty())
      {
        worker = work.top();
        work.pop();
      }
    }

    auto element = heap.top();
    heap.pop();

    cout << element.id;

    // calculate time cost
    int timecost = graph[element.id].cost;
    s += timecost;

    // update workers
    for (auto & worker : workers)
    {
      if(worker)
      {
        graph[worker].cost = std::max(0, graph[worker].cost - timecost);
        if (!graph[worker].cost)
          worker = 0;
      }
    }

    for (auto & edge : graph[element.id].edges)
    {
      if (!(--graph[edge].dependencies))
      {
        // auto it = min_element(begin(workers), end(workers));
        // *it += offset + (edge - 'A' + 1);

        work.push(edge);
        heap.push({ edge, workers.end() });
      }
    }
  }

  cout << endl;
  cout << s;

  return 0;
}
