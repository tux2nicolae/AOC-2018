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

bool Search(list<int> & list, int n)
{
  int reverse = 0;
  while (n)
  {
    reverse = reverse * 10 + n % 10;
    n /= 10;
  }
    
  auto it = list.end();
  for (int i = 0; i < 6; ++i)
  {
    it = prev(it);
  }

  for (; it != list.end(); it++)
  {
    bool found = true;
    auto second = it;

    int x = reverse;
    while (x)
    {
      if (*second != x % 10)
      {
        found = false;
        break;
      }

      second = GetNext(second);
      x /= 10;
    }

    if (found)
      return true;
  }

  return false;
}

int main()
{
  // add to list
  int max = 598701;
  
  marbles.push_back(3);
  marbles.push_back(7);

  auto current = marbles.begin();
  auto current2 = next(marbles.begin());

  // vector<int> scores;

  int n = 1;
  while(true)
  {
    // add to list
    int receipe = *current + *current2;
    if (receipe >= 10)
    {
      n++;
      marbles.push_back(receipe / 10);
      // if (n >= max)
      //   scores.push_back(receipe / 10);

      if(Search(marbles, max))
        break;
 
      n++;
      marbles.push_back(receipe % 10);
      // if (n >= max)
      //   scores.push_back(receipe % 10);

      if (Search(marbles, max))
        break;
    }
    else
    {
      n++;
      marbles.push_back(receipe);
      // if (n >= max)
      //   scores.push_back(receipe);

      if (Search(marbles, max))
        break;
    }

    // move to next one
    for (int j = 0, to = *current + 1; j < to; ++j)
    {
      current = GetNext(current);
    }

    for (int j = 0, to = *current2 + 1; j < to; ++j)
    {
      current2 = GetNext(current2);
    }

  }

  // for (int i = 0; i < 10; ++i)
  //   cout << scores[i];

  cout << marbles.size() - 6;

  return 0;
}
