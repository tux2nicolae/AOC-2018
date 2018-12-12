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
  ifstream in("D:\\AOC-2018\\Day12\\Day12.in");
  ofstream out("D:\\AOC-2018\\Day12\\Day12.out");
  assert(in.good());
  assert(out.good());

  string currentState;
  in >> currentState;

  int offset = 500;
  currentState = string(offset, '.') + currentState + string(offset, '.');

  vector<pair<string, char>> notes;

  char c;
  string note;

  while (in >> note >> c)
  {
    notes.push_back(make_pair(note, c));
  }

  for (int i = 0; i < 100 ; i++)
  {
    string temp(currentState.size(), '.');

    for (auto & note : notes)
    {
      auto it = currentState.find(note.first);
      while (it != string::npos)
      {
        temp[it + 2] = note.second;
        it = currentState.find(note.first, it + 1);
      }
    }

    out << currentState << endl;
    currentState = move(temp);
  }

  long long s = 0;
  for (int i = offset; i < currentState.size(); i++)
  {
    if (currentState[i] == '#')
      s += (i - offset) + 49999999900;
  }

  return 0;
}
