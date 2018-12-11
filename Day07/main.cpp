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
    int cost;
  };

  unordered_map<char, Node> graph;

  const int offset = 60;
  const int workersCount = 5;


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

  vector<pair<bool, char>> workers(workersCount, {false, 0});

  auto comparator = [](Element left, Element right) { return left.cost > right.cost; };
  priority_queue<Element, vector<Element>, decltype(comparator)> heap(comparator);

  for (auto & node : graph)
  {
    node.second.cost = offset + (node.first - 'A' + 1);
    sort(begin(node.second.edges), end(node.second.edges), less<int>());

    if (!node.second.dependencies)
    {
      heap.push({ node.first, offset + (node.first - 'A' + 1) });

      for (auto & worker : workers)
      {
        if (!worker.first)
        {
          worker.first = true;
          worker.second = node.first;
          break;
        }
      }
    }
  }
  
  int s = 0;
  while (!heap.empty())
  {
    auto currentEl = heap.top();
    heap.pop();

    /*
    for (int i = 0; i < currentEl.cost ; i++)
    {
      for(auto & worker : workers)
      {
        out << "  " << (worker.first ? worker.second : '.' ) << " ";
      }

      out << endl;
    }*/

    // calculate time cost
    s += currentEl.cost;
    out<<currentEl.cost<<endl;

    auto it = find_if(begin(workers), end(workers), [&](pair<bool, char> & w) { return w.first && w.second == currentEl.id; });
    assert(it != workers.end());

    it->first = false;

    // update workers
    vector<Element> roots;
    while(!heap.empty())
    {
      auto el = heap.top();
      heap.pop();

      auto it = find_if(begin(workers), end(workers), [&](pair<bool, char> & w) { return w.first && w.second == el.id; });
      if (it != workers.end())
      {
        el.cost = std::max(0, el.cost - currentEl.cost);
        if (!el.cost)
        {
          it->first = false;
        }
      }

      roots.push_back(el);
    }

    for (auto & workingElement : roots)
    {
      heap.push(workingElement);

      // try to assign an worker
      auto it = find_if(begin(workers), end(workers), [&](pair<bool, char> & w) { return w.first && w.second == workingElement.id; });
      if (it == workers.end())
      {
        for (auto & worker : workers)
        {
          if (!worker.first)
          {
            worker.first = true;
            worker.second = workingElement.id;
            break;
          }
        }
      }
    }

/*
    for (auto & worker : workers)
      worker = std::max(0, worker - timecost);
*/

    for (auto & edge : graph[currentEl.id].edges)
    {
      if (!(--graph[edge].dependencies))
      {  
        heap.push({ edge, offset + (edge - 'A' + 1) });

        for (auto & worker : workers)
        {
          if (!worker.first)
          {
            worker.first = true;
            worker.second = edge;
            break;
          }
        }
      }
    }
  }

  cout << endl;
  cout << s;

  return 0;
}
