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

using namespace std;

#include "../AOCLib/src/Algorithm.h"
#include "../AOCLib/src/Math.h"
#include "../AOCLib/src/Time.h"
#include "../AOCLib/src/FStreamReader.h"
#include "../AOCLib/src/FStreamWriter.h"
#include "../AOCLib/src/Examples.h"

using namespace AOC;

//----------------------------------------------------------------------------

template<class T>
auto Solve(T & data)
{
  bool run = true;

  while(run)
  {
    int s = 0;
    for (int i = 0; i < data.size(); i++)
    {
      s++;
      if ((data[i] - 'a') == (data[i + 1] - 'A') || (data[i] - 'A') == (data[i + 1] - 'a'))
      {
        data.erase(i, 2);
        run = true;

        break;
      }
    }

    if (s == data.size())
    {

      for (int i = 0; i < data.size(); i++)
      {
        if ((data[i] - 'a') == (data[i + 1] - 'A') || (data[i] - 'A') == (data[i + 1] - 'a'))
        {
          data.erase(i, 2);
          run = true;

          break;
        }
      }

      return s;
    }

  }

  return 0;
}

int main()
{
  ifstream in("D:\\AOC-2018\\Day5\\Day5.in");
  ofstream out("D:\\AOC-2018\\Day5\\Day5.out");

  assert(in.good());
  assert(out.good());

  FStreamReader reader(in);
  string data;
  in >> data;
  //auto data = inn reader.ReadVectorOfWords();
 
 //  cout << PrintTime(GetTime());

  int min = 100000000;
  for (char i = 'a'; i <= 'z'; ++i)
  {
    auto str = data;

    bool run = true;
    while(run)
    {
      run = false;

      string find;
      find.resize(1);
      find[0] = i;

      size_t pos = str.find(find, 0);
      while (pos != string::npos)
      {
        str.erase(pos, 1);
        pos = str.find(find, 0);

        run = true;
      }

      string find2;
      find2.resize(1);
      find2[0] = toupper(i);

      size_t pos1 = str.find(find2, 0);
      while (pos1 != string::npos)
      {
        str.erase(pos1, 1);
        pos1 = str.find(find, 0);

        run = true;
      }
    }

    int ret = Solve(str);
    if (ret < min)
    {
      min = ret;
    }
  }

  out << min;
  

  // FStreamWriter writer(out);
  // writer.WriteMatrix(data);

  return 0;
}
