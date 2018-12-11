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

  int maxSize = 301;
  int serial = 4455;

  vector<vector<int>> partialSums(maxSize, vector<int>(maxSize, 0));

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

      partialSums[i][j] = partialSums[i][j - 1] + fuel;
    }
  }

  // find max square
  int max = -100000, maxi = 0, maxj = 0, maxn = 0;
  for (int n = 1; n < maxSize; n++)
  {
    for (int i = 1; i + n < maxSize; ++i)
    {
      for (int j = 1; j + n < maxSize; ++j)
      {
        // get square sum

        int begj = j - 1;
        int endj = j + n - 1;

        int sum = 0;
        for (int k = i; k < i + n; k++)
        {
          sum += partialSums[k][endj] - partialSums[k][begj];
        }

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

  cout << maxi << "," << maxj << "," << maxn << endl;
  
  return 0;
}
