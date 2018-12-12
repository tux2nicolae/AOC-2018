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


  string initialState;
  in >> initialState;

  char c;
  string note;

  vector<pair<string, char>> notes;
  vector<pair<string, char>> notesNext;

  while (in >> note >> c)
  {
    notes.push_back(make_pair(note, c));
  }

  int offset = 500;
  initialState = string(offset, '.') + initialState + string(offset, '.');

  for (int i = 0; i < 100 ; i++)
  {
    string temp(initialState.size(), '.');

    for (auto & note : notes)
    {
      auto it = initialState.find(note.first);
      while (it != string::npos)
      {
        temp[it + 2] = note.second;
        it = initialState.find(note.first, it + 1);
      }
    }

    out << initialState << endl;
    initialState = move(temp);
  }

  long long s = 0;
  for (int i = offset; i < initialState.size(); i++)
  {
    if (initialState[i] == '#')
      s += (i - offset) + 49999999900;
  }

  return 0;
}
