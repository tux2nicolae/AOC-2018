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

using namespace std;

#include "../AOCLib/src/Math.h"
#include "../AOCLib/src/FStreamReader.h"

bool AlmostSiblings(const string & a, const string & b)
{
  int dif = 0;
  for (int i = 0; i < a.size(); ++i)
  {
    if (a[i] != b[i])
      dif++;      
  }
   
  return dif == 1;
}


template<class T>
pair<int, string> f(T & data)
{
  int two = 0;
  int three = 0;

  string almostSiblings;

  for (auto & word : data)
  {   
    // part 1
    int m[30]{};
    for (auto letter : word)
    {
      m[letter - 'a']++;
    }

    for (int i = 0; i <= 26; ++i)
    {
      if (m[i] == 2)
      {
        two++;
        break;
      }
    }

    for (int i = 0; i <= 26; ++i)
    {
      if (m[i] == 3)
      {
        three++;
        break;
      }
    }

    // part 2
    for (auto & secondWord : data)
    {
      if (word != secondWord)
      {
        if (AlmostSiblings(word, secondWord))
        {
          almostSiblings = word + ":" + secondWord;
          break;
        }
      }
    }
  }

  return { two * three, almostSiblings};
}

//----------------------------------------------------------------------------

int main()
{
  ifstream in("D:\\AOC-2018\\Day2\\Day2.in");
  ofstream out("D:\\AOC-2018\\Day2\\Day2.out");

  assert(in.good());
  assert(out.good());

  FStreamReader reader(in);
  auto ret = reader.ReadVectorOfWords();

  auto solution = f(ret);
  out << solution.first << " " << solution.second;

  return 0;
}
