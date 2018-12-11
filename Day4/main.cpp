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
#include <set>
#include <numeric>
#include <ctime>

using namespace std;

#include "../AOCLib/src/Algorithm.h"
#include "../AOCLib/src/Math.h"
#include "../AOCLib/src/FStreamReader.h"
#include "../AOCLib/src/FStreamWriter.h"
#include "../AOCLib/src/Examples.h"

using namespace AOC;

//----------------------------------------------------------------------------

// falls asleep -> 1
// wakes up -> 2
// Guard # -> 3 begins shift

template<class T>
auto Solve(T & data)
{
  struct Command
  {
    tm time;
    int cmd;
    int id;
  };

  map<time_t, Command> commands;

  for (int i = 0; i < data.size() ; i++)
  {
    string & line = data[i];
    
    auto it = line.find("|");
    auto date = line.substr(0, it);
    auto str = line.substr(it + 2);

    stringstream dateStream(date);
    
    int year;
    int month;
    int day;
    int h;
    int m;

    char discard;
    dateStream >> year >> discard >> month >> discard >> day >> discard >> h >> discard >> m;

    struct tm tm {};

    time_t rawtime;
    time(&rawtime);
    tm = *localtime(&rawtime);

    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;

    tm.tm_hour = h;
    tm.tm_min = m;
    tm.tm_sec = 0;

    time_t timer;
    time(&timer);
    
    auto test = mktime(&tm);
    // int seconds = difftime(timer, mktime(&tm));

    stringstream stream(str);
    int command = 0;
    int id = 0;

    stream >> command >> id;
   
    Command c;
    c.time = tm;
    c.cmd = command;
    c.id = id;

    commands[test] = c;
  }

  struct Asleep
  {
    int sum{};
    int minutes[59]{};


  };


  map<int, Asleep> asleep;

  int currentGuardId = 0;
  for (auto it = commands.begin(), end = commands.end(); it != end; ++it)
  {
    auto & command = *it;
    auto & guard = it->second;

    if (guard.cmd == 3)
    {
      currentGuardId = guard.id;
    }

    if (guard.cmd == 1)
    {
      auto copyIt = it;
      copyIt++;

      auto & nextCommand = *copyIt;
      assert(nextCommand.second.cmd == 2);

      auto diff = nextCommand.second.time.tm_min-guard.time.tm_min;
      assert(diff > 0);

      for (int i = 0; i < diff; ++i)
      {
        asleep[currentGuardId].sum++;
        asleep[currentGuardId].minutes[(guard.time.tm_min + i) % 60]++;
      }
    }
  }

  // part 2
  int max = 0;

  int i = 0;
  int pos = 0;
  for (auto & g : asleep)
  {
    for (int j = 0; j < 60; ++j)
    {
      if (g.second.minutes[j] > max)
      {
        max = g.second.minutes[j];
        pos = i;
      }
    }

    ++i;
  }

  return 0;
}

int main()
{
  ifstream in("D:\\AOC-2018\\Day4\\Day4.in");
  ofstream out("D:\\AOC-2018\\Day4\\Day4.out");

  assert(in.good());
  assert(out.good());

  FStreamReader reader(in);
  auto data = reader.ReadVectorOfWords();
 
  auto result = 
    Solve(data);

  // FStreamWriter writer(out);
  // writer.WriteMatrix(data);

  return 0;
}
