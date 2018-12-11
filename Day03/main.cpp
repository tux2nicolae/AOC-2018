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

using namespace std;

#include "../AOCLib/src/Math.h"
#include "../AOCLib/src/FStreamReader.h"
#include "../AOCLib/src/FStreamWriter.h"
#include "../AOCLib/src/Examples.h"

using namespace AOC;

//----------------------------------------------------------------------------

template<class T>
auto Solve(T & data)
{
  vector<vector<int>> v;
  v.resize(1000);

  for (auto & x : v)
  {
    x.resize(1000);
  }

  // part 1
  for (auto & element : data)
  {
    for (int ki = element[0]; ki < element[0] + element[2]; ++ki)
    {
      for (int kj = element[1]; kj < element[1] + element[3]; ++kj)
      {
        v[ki][kj]++;
      }
    }
  }

  int sum = 0;
  for (auto & row : v)
  {
    for (auto & x : row)
    {
      if (x > 1)
        sum++;
    }
  }

  // part 2
  int elementId = 0;
  for (auto & element : data)
  {
    int sumEl = 0;
    for (int ki = element[0]; ki < element[0] + element[2]; ++ki)
    {
      for (int kj = element[1]; kj < element[1] + element[3]; ++kj)
      {
        if (v[ki][kj] == 1)
          sumEl++;
      }
    }

    if (sumEl == element[2] * element[3])
    {
      elementId = element[4];
      break;
    }
  }

  return make_pair(sum, elementId);
}

int main()
{
  ifstream in("D:\\AOC-2018\\Day3\\Day3.in");
  ofstream out("D:\\AOC-2018\\Day3\\Day3.out");

  assert(in.good());
  assert(out.good());

  FStreamReader reader(in);
  auto data = reader.ReadMatrix();
 
  auto result = Solve(data);
  out << result.first << " " << result.second << endl;

  return 0;
}
