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
  ifstream in("D:\\AOC-2018\\Day11\\Day11.in");
  ofstream out("D:\\AOC-2018\\Day11\\Day11.out");
  assert(in.good());
  assert(out.good());

  constexpr int maxSize = 301;
  constexpr int serial = 8979;

  int lineSums[maxSize][maxSize]{};
  int columnSums[maxSize][maxSize]{};

  // calculate partial sums
  for (int i = 1; i < maxSize; i++)
  {
    for (int j = 1; j < maxSize; j++)
    {
      int rackID = i + 10;
      int fuel = rackID * j;
      fuel += serial;
      fuel *= rackID;
      fuel = (fuel / 100) % 10;
      fuel -= 5;

      lineSums[i][j] = lineSums[i][j - 1] + fuel;
      columnSums[i][j] = columnSums[i - 1][j] + fuel;
    }
  }

  // find max square in O(n^3) iterations count : 9045050 
  int max = -100000, maxi = 0, maxj = 0, maxn = 0;
  for (int i = 1; i < maxSize; ++i)
  {
    for (int j = 1; j < maxSize; ++j)
    {
      int sum = 0;
      for (int n = 0; n < maxSize - std::max(i, j); n++)
      {
        sum += lineSums[i + n][j + n - 1] - lineSums[i + n][j - 1];
        sum += columnSums[i + n][j + n] - columnSums[i - 1][j + n];
        
        if (max < sum)
        {
          max = sum;
          maxi = i;
          maxj = j;
          maxn = n;
        }
      }
    }
  }

  cout << maxi << "," << maxj << "," << maxn + 1 << endl;
  return 0;
}
