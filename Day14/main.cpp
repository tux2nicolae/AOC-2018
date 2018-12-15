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

list<int> receipes;

list<int>::iterator GetPrevious(list<int>::iterator it) {
  if (it == receipes.begin())
    it = receipes.end();

  return --it;
};

list<int>::iterator GetNext(list<int>::iterator it) {
  if (++it == receipes.end())
    return receipes.begin();

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
    it = GetPrevious(it);
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
  
  receipes.push_back(3);
  receipes.push_back(7);

  auto current = receipes.begin();
  auto current2 = next(receipes.begin());

  // vector<int> scores;

  int n = 1;
  while(true)
  {
    // add to list
    int receipe = *current + *current2;
    if (receipe >= 10)
    {
      n++;
      receipes.push_back(receipe / 10);
      // if (n >= max)
      //   scores.push_back(receipe / 10);

      if(Search(receipes, max))
        break;
 
      n++;
      receipes.push_back(receipe % 10);
      // if (n >= max)
      //   scores.push_back(receipe % 10);

      if (Search(receipes, max))
        break;
    }
    else
    {
      n++;
      receipes.push_back(receipe);
      // if (n >= max)
      //   scores.push_back(receipe);

      if (Search(receipes, max))
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

  cout << receipes.size() - 6;

  return 0;
}
