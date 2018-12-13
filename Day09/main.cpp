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
list<int> marbles;

list<int>::iterator GetPrevious(list<int>::iterator it) {
  if (it == marbles.begin())
    it = marbles.end();

  return --it;
};

list<int>::iterator GetNext(list<int>::iterator it) {
  if (++it == marbles.end())
    return marbles.begin();

  return it;
};

int main()
{
  //ifstream in("D:\\AOC-2018\\Day9\\Day9.in");
  //ofstream out("D:\\AOC-2018\\Day9\\Day9.out");
  //
  //assert(in.good());
  //assert(out.good());

  vector<long long> scores;
  scores.resize(10000000);

  int players = 471;
  int last = 72026;
  //in >> players >> last;

  // part 2
  last *= 100;

  marbles.push_back(0);
  auto current = marbles.begin();

  for (int i = 1; i < last; ++i)
  {
    auto currentPlayer = i % players;

    if (i % 23 != 0)
    {
      // move 2 positions forward
      current = marbles.insert(GetNext(GetNext(current)), i);
    }
    else
    {
      scores[currentPlayer] += i;

      // move 7 positions backwards
      for (int j = 0; j < 7; ++j)
      {
        current = GetPrevious(current);
      }

      scores[currentPlayer] += *current;

      // int pos = current - marbles.begin();
      // marbles.erase(current);
      //
      // if (pos == marbles.size())
      //   current = marbles.begin();
      // else
      //   current = marbles.begin() + pos;

      current = marbles.erase(current);
    }
  }

  auto x = *std::max_element(scores.begin(), scores.end());
  cout << x;

  return 0;
}
